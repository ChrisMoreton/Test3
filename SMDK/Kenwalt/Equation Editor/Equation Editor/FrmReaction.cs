using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO;
using System.Collections;
using System.Collections.Specialized;

namespace Reaction_Editor
{
    public partial class FrmReaction : Form
    {
        #region Regex's
        protected static Regex s_EndRegex = new Regex(@"(^|\r\n)\s*End",
            RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.ExplicitCapture);
        protected static Regex s_CommentRemovingRegex = new Regex(@"^[^;]*",
            RegexOptions.ExplicitCapture | RegexOptions.Multiline | RegexOptions.Compiled);
        protected static Regex s_OpeningCommentRegex = new Regex(@"^(\s*(?>;(?<Comment>[^\r\n]*))?)*",
            RegexOptions.ExplicitCapture | RegexOptions.Compiled); //If the first match is non-zero, discard.
        protected static Regex s_SourceRegex = new Regex(@"(?<=(^|\r\n)\s*?Source:)[^:]*(?=Reactions:)",
            RegexOptions.IgnoreCase | RegexOptions.ExplicitCapture | RegexOptions.Compiled);
        public static Regex s_ReactionRegex = new Regex(
            @"(^|\r\n)\s*((?<Comment>;.*)\r\n)?(?<Reactants>[^;\r\n<>=\-:]*)(?<Direction>->|=|<->|->)\s*(?<Products>[^;:\r\n]*?(?=Extent|Sequence|HeatOfReaction|;|\r\n|$))(?>(?>\s*(;.*\r\n)?)*((?<Extent>Extent\s*:[^\r\n;]*?)|(?<Sequence>Sequence\s*:[^\r\n;]*?)|(?<HOR>HeatOfReaction\s*:[^\r\n;]*?))(?=Extent|Sequence|HeatOfReaction|;|\r\n|$)){0,3}",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Compiled);
        public static Regex s_DisabledReactionRegex = new Regex(
            @"(^|\r\n)\s*((?<Comment>;.*)\r\n[^\S\r\n]*)?;(?<Reactants>[^;\r\n<>=\-:]*)(?<Direction>->|=|<->|->)\s*(?<Products>[^;:\r\n]*?(?=Extent|Sequence|HeatOfReaction|;|\r\n|$))(?>[^\S\r\n]*(\r\n\s*;)?((?<Extent>Extent\s*:[^\r\n;]*?)|(?<Sequence>Sequence\s*:[^\r\n;]*?)|(?<HOR>HeatOfReaction\s*:[^\r\n;]*?))(?=Extent|Sequence|HeatOfReaction|;|\r\n|$)){0,3}",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Compiled);
        protected static Regex s_SinkRegex = new Regex(@"(?<=\r\n\s*?Sink:)[^:]*?(?=End|HeatExchange|$)",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Compiled);
        protected static Regex s_HXRegex = new Regex(
            @"^\s*HeatExchange:\s*(
                (?<Type>FinalT|Power|Electrolysis)\s*=\s*(?<Value>\d+(\.\d+)?|\.\d+) |
                (?<Type>TargetT|Ambient)\s*=\s*(?<Value>\d+(\.\d+)?|\.\d+)\s*,\s*(ApproachT|ApproachAmbient)\s*=\s*(?<Value2>d+(\.\d+)?|\.\d+))",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Multiline | RegexOptions.Compiled | RegexOptions.IgnorePatternWhitespace);
        protected static Regex s_RxnBlockStartRegex = new Regex(@"(^|\r\n\s*)Reactions:",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Compiled);
        protected static Regex s_RxnBlockEndRegex = new Regex(@"\r\n\s*(End|^|HeatExchange|Sink)",
            RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase | RegexOptions.Compiled);
        #endregion Regex's

        #region Variables
        //protected List<SimpleReaction> m_Reactions = new List<SimpleReaction>();
        //protected List<Compound> m_Sources = new List<Compound>();
        //protected List<Compound> m_Sinks = new List<Compound>();
        //Dictionary<int, ListViewGroup> m_ListViewGroups = new Dictionary<int, ListViewGroup>();
        protected bool m_bChanged = false;
        protected string m_sTitle = "Untitled Reaction Block";
        protected FileStream m_File;
        protected SimpleReaction m_CurrentReaction;

        //protected ToolStripStatusLabel m_StatusControl;
        protected ILog m_Log;

        protected bool m_bDoEvents = true;
        protected List<Control> m_OptionalExtentControls = new List<Control>();
        protected Control[] m_HXControls;

        public const int sMaxSequences = 32;

        protected ListViewGroup m_selectedGroup = null;
        #endregion Variables

        #region Properties
        public string Filename
        {
            get
            {
                if (m_File != null)
                    return m_File.Name;
                throw new IOException("Attempt to retrieve filename when no file has been opened");
            }
        }

        public bool FileOpen
        {
            get { return m_File != null; }
        }

        public bool Changed
        {
            get { return m_bChanged; }
            protected set 
            { 
                m_bChanged = value;
                Title = Title;
            }
        }

        public string Title
        {
            get { return m_sTitle; }
            set 
            {
                m_sTitle = value;
                Text = m_sTitle + (m_bChanged ? "*" : ""); 
            }
        }

        public List<SimpleReaction> Reactions
        {
            get
            {
                List<SimpleReaction> ret = new List<SimpleReaction>();
                foreach (ListViewItem lvi in lstReactions.Items)
                    ret.Add((SimpleReaction)lvi.Tag);
                return ret;
            }
        }

        public ILog Log
        {
            get { return m_Log; }
            set { m_Log = value; }
        }

        protected ListViewGroup SelectedGroup
        {
            set
            {
                if (value == m_selectedGroup) return;
                if (m_selectedGroup != null)
                    m_selectedGroup.HeaderAlignment = HorizontalAlignment.Left;
                m_selectedGroup = value;
                if (m_selectedGroup != null)
                    m_selectedGroup.HeaderAlignment = HorizontalAlignment.Center;
            }
        }

        public bool CanCutCopy
        {
            get
            {
                return 
                    (lstReactions.Focused && lstReactions.SelectedItems.Count > 0) ||
                    (txtComment.Focused && !string.IsNullOrEmpty(txtComment.SelectedText)) ||
                    (txtDescription.Focused && !string.IsNullOrEmpty(txtDescription.SelectedText)) ||
                    (txtSources.Focused && !string.IsNullOrEmpty(txtSources.SelectedText)) ||
                    (txtSinks.Focused && !string.IsNullOrEmpty(txtSinks.SelectedText)) ||
                    (txtProducts.Focused && !string.IsNullOrEmpty(txtProducts.SelectedText)) ||
                    (txtReactants.Focused && !string.IsNullOrEmpty(txtReactants.SelectedText));
            }
        }

        public bool CanPaste
        {
            get
            {
                IDataObject obj = Clipboard.GetDataObject();
                return obj.GetDataPresent(typeof(SimpleReaction)) ||
                    (Clipboard.ContainsText() && (
                    txtComment.Focused || txtDescription.Focused || txtSources.Focused || txtSinks.Focused ||
                    txtProducts.Focused || txtReactants.Focused));
            }
        }
        #endregion Properties

        #region Events
        public event EventHandler NowChanged;
        public event EventHandler CompoundsChanged;
        #endregion Events

        #region Constructors
        public FrmReaction(ILog log)
        {
            SetUp(log);
        }

        public FrmReaction(string filename, ILog log)
        {
            SetUp(log);
            m_File = new FileStream(filename, FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
            this.Title = Path.GetFileName(filename);
            ReadFile();
        }

        public FrmReaction(int titleNum, ILog log)
        {
            SetUp(log);
            this.Title = "Untitled-" + titleNum;
        }

        private void SetUp(ILog log)
        {
            InitializeComponent();
            m_Log = log;

            m_OptionalExtentControls.AddRange(new Control[] {
                this.numExtentVal2,
                this.numExtentVal3,
                this.comboExtentPhase,
                this.chkExtentStabilised,
                this.lblExtent2,
                this.lblExtent3 });

            m_HXControls = new Control[] {
                this.numHXApproach,
                this.numHX,
                this.lblHXApproach,
                this.lblHXPercent,
                this.lblHXUnits,
                this.lblHXValue, };

            ArrayList phases = new ArrayList(Enum.GetValues(typeof(Phases)));
            comboExtentPhase.Items.AddRange(phases.ToArray());

            for (int i = 0; i <= sMaxSequences; i++)
            {
                ListViewGroup grp = new ListViewGroup("grpSequence" + i, "Sequence " + i);
                lstReactions.Groups.Add(grp);
            }

            comboHXType.SelectedItem = "None";
            comboDirection.SelectedItem = "=";

            tabSources_Sinks_Resize(null, new EventArgs());
            pnlReaction_Resize(null, new EventArgs());

            txtSources.AllowDrop = txtReactants.AllowDrop = true;
            grpSources.AllowDrop = true;
            grpSources.DragEnter += new DragEventHandler(grpSources_DragEnter);
            txtSources.DragDrop += new DragEventHandler(txtCompounds_DragDrop);
            txtSinks.DragDrop += new DragEventHandler(txtCompounds_DragDrop);
            txtSources.DragEnter += new DragEventHandler(txtCompounds_DragEnter);
            txtSinks.DragEnter += new DragEventHandler(txtCompounds_DragEnter);
            numSequence.Text = "";

            Changed = false;
        }

        void grpSources_DragEnter(object sender, DragEventArgs e)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        #endregion Constructors

        #region Public Functions
        public void Save()
        {
            m_File.SetLength(0);
            StreamWriter sr = new StreamWriter(m_File);
            //First, the comments:
            if (!string.IsNullOrEmpty(txtDescription.Text))
            {
                sr.WriteLine(";" + txtDescription.Text.TrimEnd().Replace("\r\n", "\r\n;"));
                sr.WriteLine();
            }

            //Sources, if they exist:
            if (!string.IsNullOrEmpty(txtSources.Text))
            {
                sr.WriteLine("Source: " + txtSources.Text.Replace("\r\n", ", "));
                sr.WriteLine();
            }

            //Reactions:
            sr.WriteLine("Reactions:");
            foreach (ListViewItem lvi in lstReactions.Items)
            {
                SimpleReaction rxn = (SimpleReaction)lvi.Tag;
                sr.WriteLine();
                if (!string.IsNullOrEmpty(rxn.Comment))
                    sr.WriteLine(";" + rxn.Comment);
                sr.WriteLine(rxn.ToSaveString(chkSequence.Checked));
            }
            sr.WriteLine();
            
            if ((HXTypes) comboHXType.SelectedIndex == HXTypes.Electrolysis ||
                (HXTypes) comboHXType.SelectedIndex == HXTypes.FinalT ||
                (HXTypes) comboHXType.SelectedIndex == HXTypes.Power)
            {
                sr.WriteLine("HeatExchange: " + (HXTypes)comboHXType.SelectedIndex + " = " + numHX.Text);
                sr.WriteLine();
            }
            else if ((HXTypes)comboHXType.SelectedIndex == HXTypes.ApproachAmbient)
            {
                sr.WriteLine("HeatExchange: Ambient = " + numHX.Text + ", ApproachAmbient = " + numHXApproach.Value.ToString());
                sr.WriteLine();
            }
            else if ((HXTypes)comboHXType.SelectedIndex == HXTypes.ApproachT)
            {
                sr.WriteLine("Heat Exchange: TargetT = " + numHX.Text + ", ApproachT = " + numHXApproach.Value.ToString());
                sr.WriteLine();
            }


            if (!string.IsNullOrEmpty(txtSinks.Text))
            {
                sr.WriteLine("Sink: " + txtSinks.Text.Replace("\r\n", ", "));
                sr.WriteLine();
            }

            sr.WriteLine("End");
            sr.Flush();
            Changed = false;
        }

        public void SaveAs(string newName)
        {
            if (m_File != null)
                m_File.Close();
            m_File = new FileStream(newName, FileMode.Create, FileAccess.ReadWrite, FileShare.Read);
            this.Title = Path.GetFileName(newName);
            Save();
        }

        public void RepopulateSpecies()
        {
            comboHORSpecie.Items.Clear();
            foreach (Compound c in Compound.CompoundList.Values)
            {
                comboHORSpecie.Items.Add(c);
                comboExtentSpecie.Items.Add(c);
            }
        }

        public void SelectReaction(SimpleReaction rxn)
        {
            if (rxn == null)
            {
                lstReactions.SelectedItems.Clear();
                return;
            }
            if (rxn.LVI == null 
                || !lstReactions.Items.Contains(rxn.LVI)
                || lstReactions.SelectedItems.Contains(rxn.LVI))
                return;
            lstReactions.SelectedItems.Clear();
            rxn.LVI.Selected = true;
        }

        public bool ContainsReaction(SimpleReaction rxn)
        {
            foreach (ListViewItem lvi in lstReactions.Items)
                if (lvi.Tag == rxn)
                    return true;
            return false;
        }

        public SimpleReaction AddReaction(SimpleReaction rxn, int location)
        {
            ListViewItem lvi = new ListViewItem();
            lvi.SubItems.AddRange(new string[] { "", "" });
            if (location < 0 || location > lstReactions.Items.Count)
                lstReactions.Items.Add(lvi);
            else
                lstReactions.Items.Insert(location, lvi);
            SimpleReaction newRxn = rxn.Clone(lvi);
            newRxn.FireChanged();
            return newRxn;
        }

        public List<Compound> GetCompounds()
        {
            List<Compound> ret = new List<Compound>();
            foreach (ListViewItem lvi in lstReactions.Items)
            {
                SimpleReaction rxn = (SimpleReaction)lvi.Tag;
                foreach (Compound c in rxn.Compounds)
                    if (!ret.Contains(c))
                        ret.Add(c);
            }
            return ret;
        }

        public void DoDatabaseChanged()
        {
            foreach (ListViewItem lvi in lstReactions.Items)
                ((SimpleReaction)lvi.Tag).DoDatabaseChanged();
        }

        public void Copy()
        {
            if (lstReactions.Focused && lstReactions.SelectedItems.Count > 0)
                Clipboard.SetData(SimpleReaction.sFormat.Name, ((SimpleReaction)lstReactions.SelectedItems[0].Tag).ToSaveString(true));
            else if (txtComment.Focused)
                txtComment.Copy();
            else if (txtDescription.Focused)
                txtDescription.Copy();
            else if (txtSources.Focused)
                txtSources.Copy();
            else if (txtSinks.Focused)
                txtSinks.Copy();
            else if (txtProducts.Focused)
                txtProducts.Copy();
            else if (txtReactants.Focused)
                txtReactants.Copy();
        }

        public void Cut()
        {
            if (lstReactions.Focused && lstReactions.SelectedItems.Count > 0)
            {
                /*DataObject obj = new DataObject(SimpleReaction.sFormat.Name, lstReactions.SelectedItems[0].Tag);
                Clipboard.SetDataObject(obj);*/
                DataObject obj = new DataObject();
                string s = ((SimpleReaction)lstReactions.SelectedItems[0].Tag).ToSaveString(true);
                obj.SetData(
                    SimpleReaction.sFormat.Name,
                    s);
                Clipboard.SetData(SimpleReaction.sFormat.Name, s);

                lstReactions.SelectedItems[0].Remove();
            }
            else if (txtComment.Focused)
                txtComment.Cut();
            else if (txtDescription.Focused)
                txtDescription.Cut();
            else if (txtSources.Focused)
                txtSources.Cut();
            else if (txtSinks.Focused)
                txtSinks.Cut();
            else if (txtProducts.Focused)
                txtProducts.Cut();
            else if (txtReactants.Focused)
                txtReactants.Cut();
        }

        public void Paste()
        {
            IDataObject obj = Clipboard.GetDataObject();
            object bleh = Clipboard.GetData(SimpleReaction.sFormat.Name);
            if (obj.GetDataPresent(SimpleReaction.sFormat.Name))
            {
                string data = (string)obj.GetData(SimpleReaction.sFormat.Name);
                CheckBox properChkSequence = chkSequence; //Because the new reaction will always carry sequence information.
                chkSequence = new CheckBox();
                //A reaction shouldn't be both enabled and disabled, so simply call both:
                FindReactions(data, s_ReactionRegex, true);
                FindReactions(data, s_DisabledReactionRegex, false);
                chkSequence = properChkSequence;
                if (NowChanged != null)
                    NowChanged(this, new EventArgs());
                if (CompoundsChanged != null)
                    CompoundsChanged(this, new EventArgs());
            }
            if (Clipboard.ContainsText())
                PasteText(this);
        }
        #endregion Public Functions

        #region Protected Functions
        protected bool PasteText(Control c)
        {
            if (c.GetType() == typeof(TextBox) || c.GetType() == typeof(RichTextBox))
            {
                ((TextBoxBase)c).Paste();
                return true;
            }
            foreach (Control subc in c.Controls)
                if (PasteText(subc))
                    return true;
            return false;
        }
        protected void ReadFile()
        {
            //Now, stopping at the End token:
            Log.SetSource(new MessageFrmReaction(this.Title, this, null));

            StreamReader sr = new StreamReader(m_File);
            string contents = sr.ReadToEnd().Trim();
            
            //Sources and sinks use a comment stripped version of the file:
            StringBuilder sb = new StringBuilder();
            for (Match m = s_CommentRemovingRegex.Match(contents); m.Success; m = m.NextMatch())
            {
                sb.AppendLine(m.Value);
                if (m.Value.ToLowerInvariant().Trim() == "end")
                    break;
            }
            string commentsRemoved = sb.ToString();
            if (!s_EndRegex.Match(commentsRemoved).Success)
                Log.Message("'End' token not found. Reading to end of file (May cause unpredictable results)", MessageType.Warning);

            //General comments:
            StringBuilder comments = new StringBuilder();
            Match commentsMatch = s_OpeningCommentRegex.Match(contents);
            if (commentsMatch.Success)
            {
                Group g = commentsMatch.Groups["Comment"];
                if (g.Success)
                    foreach (Capture c in g.Captures)
                        comments.AppendLine(c.Value);
                txtDescription.Text = comments.ToString();
            }

            //Sources:
            Match sourcesMatch = s_SourceRegex.Match(commentsRemoved);
            if (sourcesMatch.Success)
            {
                txtSources.Text = sourcesMatch.Value.Trim().Replace("\r\n", ", ");
            }

            //Reactions:
            Match start = s_RxnBlockStartRegex.Match(contents);
            Match end = s_RxnBlockEndRegex.Match(contents);
            if (!start.Success || !end.Success)
            {
                Log.Message("Reaction Block Not Found", MessageType.Error);
                throw new Exception("Reaction block not found");
            }
            int rxnBlockStart = start.Index;
            int rxnBlockEnd = end.Index;
            string rxnBlock = contents.Substring(rxnBlockStart, rxnBlockEnd - rxnBlockStart);
            
            FindReactions(rxnBlock, s_ReactionRegex, true);
            FindReactions(rxnBlock, s_DisabledReactionRegex, false);

            Match HXMatch = s_HXRegex.Match(commentsRemoved);
            if (HXMatch.Success)
            {
                string type = HXMatch.Groups["Type"].Value;
                if (type == "FinalT")
                    comboHXType.SelectedItem = "Final Temp.";
                else if (type == "TargetT")
                {
                    comboHXType.SelectedItem = "Approach Temp.";
                    numHXApproach.Value = Decimal.Parse(HXMatch.Groups["Value2"].Value);
                }
                else if (type == "Ambient")
                {
                    comboHXType.SelectedItem = "Approach Ambient";
                    numHXApproach.Value = Decimal.Parse(HXMatch.Groups["Value2"].Value);
                }
                else if (type == "Power")
                    comboHXType.SelectedItem = "Power";
                else if (type == "Electrolyisis")
                    comboHXType.SelectedItem = "Electrolysis";
                else
                    Log.Message("Unknown Heat Exchange type '" + HXMatch.Groups["Type"].Value + "'", MessageType.Warning);
                numHX.Text = HXMatch.Groups["Value"].Captures[0].Value;
            }

            Match SinkMatch = s_SinkRegex.Match(commentsRemoved);
            if (SinkMatch.Success)
            {
                txtSources.Text = SinkMatch.Value.Trim().Replace("\r\n", ", ");
                //TODO: process input.
            }
            Changed = false;
            if (lstReactions.Items.Count != 1)
                Log.Message("File opened. " + lstReactions.Items.Count + " Reactions found.", MessageType.Note);
            else
                Log.Message("File opened. 1 Reaction found.", MessageType.Note);
            Log.RemoveSource();
        }

        protected void FindReactions(string rxnBlock, Regex reactionRegex, bool enabled)
        {
            int lastSequence = 1;
            bool sequenceFound = false;
            int reactionNo = 0;
            for (Match rxnMatch = reactionRegex.Match(rxnBlock); rxnMatch.Success; rxnMatch = rxnMatch.NextMatch())
            {
                reactionNo++;
                SimpleReaction currentReaction = CreateReaction(null);
                MessageSource source = new MessageFrmReaction(
                    this.Title + ", Reaction " + reactionNo,
                    this,
                    currentReaction);
                Log.SetSource(source);
                Group grpComment = rxnMatch.Groups["Comment"];
                if (grpComment.Success)
                    currentReaction.Comment = grpComment.Captures[0].Value;

                Group grpReactants = rxnMatch.Groups["Reactants"];
                currentReaction.ParseReactants(grpReactants.Captures[0].Value);


                Group grpDirection = rxnMatch.Groups["Direction"];
                currentReaction.DirectionString = grpDirection.Captures[0].Value;

                Group grpProducts = rxnMatch.Groups["Products"];
                currentReaction.ParseProducts(grpProducts.Captures[0].Value);

                source.Source = this.Title + ": " + currentReaction;

                Group grpExtent = rxnMatch.Groups["Extent"];
                if (grpExtent.Success)
                    try
                    {
                        currentReaction.ParseExtent(grpExtent.Captures[0].Value);
                    }
                    catch (Exception ex)
                    {
                        Log.Message("Unable to parse extent (" + grpExtent.Value + "). Reason: " +ex.Message, MessageType.Warning);
                    }
                else
                    Log.Message("Extent not found for reaction", MessageType.Warning);

                Group grpSequence = rxnMatch.Groups["Sequence"];
                if (grpSequence.Success)
                {
                    Match sequenceMatch = SimpleReaction.s_SequenceRegex.Match(grpSequence.Captures[0].Value.Trim());
                    if (sequenceMatch.Success)
                    {
                        sequenceFound = true;
                        lastSequence = int.Parse(sequenceMatch.Groups["Value"].Captures[0].Value);
                    }
                    else
                        Log.Message("Unable to parse sequence '" + grpSequence.Value + "'", MessageType.Warning);
                }
                currentReaction.Sequence = lastSequence;

                Group grpHOR = rxnMatch.Groups["HOR"];
                if (grpHOR.Success)
                    try
                    {
                        currentReaction.ParseHOR(grpHOR.Captures[0].Value.Trim());
                    }
                    catch (Exception ex)
                    {
                        Log.Message("Unable to parse HeatOfReaction '" + grpHOR.Value + "' Reason: " + ex.Message, MessageType.Warning);
                    }

                currentReaction.Enabled = enabled;
                Log.RemoveSource();
            }
            if (sequenceFound)
                chkSequence.Checked = true;
        }

        protected void OldReadFile()
        {
            StreamReader sr = new StreamReader(m_File);
            string str = sr.ReadLine();
            bool bReactionsFound = false, bEndFound = false;
            bool bSourceFound = false, bSinksFound = false;
            SimpleReaction curReaction = null;
            while (str != null)
            {
                str = str.Trim();
                if (string.IsNullOrEmpty(str) || str.StartsWith(";")) //Discard comment and empty lines
                {
                    str = sr.ReadLine();
                    continue;
                }
                if (str.Contains(";")) //Discard comments
                    str = str.Split(';')[0];

                if (str.ToLowerInvariant().StartsWith("end"))
                {
                    bEndFound = true;
                    break;
                }

                if (str.ToLowerInvariant().StartsWith("source:"))
                {
                    bSourceFound = true;
                    str = str.Remove(0, ("Source:").Length);
                    str.Trim();
                }
                if (bSourceFound && !bReactionsFound)
                {
                    string[] tokens = str.Split(',');
                    foreach (string s in tokens)
                    {
                        if (Compound.CompoundList.ContainsKey(s.Trim()))
                        {
                            if (!string.IsNullOrEmpty(txtSources.Text))
                                txtSources.Text += ", ";
                            txtSources.Text += s.Trim();
                        }
                        else
                        {
                            //TODO: Log errors
                        }
                    }
                }
                if (str.ToLowerInvariant().StartsWith("reactions:"))
                {
                    bReactionsFound = true;
                    if (!string.IsNullOrEmpty(str.Remove(0, ("reactions:").Length).Trim()))
                    {
                        //Log this error
                    }
                    str = sr.ReadLine();
                    continue;
                }
                if (bReactionsFound && !bSinksFound)
                {
                    string sFormula = null, sExtent = null, sHOR = null;
                    int nExtentLoc = str.ToLowerInvariant().IndexOf("extent :");
                    int nHORLoc = str.ToLowerInvariant().IndexOf("heat of reaction:");
                    if (nExtentLoc == -1 && nHORLoc == -1)
                        sFormula = str;
                    else if (nExtentLoc == -1)
                    {
                        sFormula = str.Substring(0, nHORLoc);
                        sHOR = str.Substring(nHORLoc);
                    }
                    else if (nHORLoc == -1)
                    {
                        sFormula = str.Substring(0, nExtentLoc);
                        sExtent = str.Substring(nExtentLoc, str.Length - nExtentLoc);
                    }
                    else if (nExtentLoc < nHORLoc)
                    {
                        sFormula = str.Substring(0, nExtentLoc);
                        sExtent = str.Substring(nExtentLoc, nHORLoc - nExtentLoc);
                        sHOR = str.Substring(nHORLoc);
                    }
                    else
                    {
                        sFormula = str.Substring(0, nHORLoc);
                        sHOR = str.Substring(nHORLoc, nExtentLoc - nHORLoc);
                        sExtent = str.Substring(nExtentLoc);
                    }
                    if (sFormula.Length > 0)
                        try
                        {
                            curReaction = CreateReaction(sFormula);
                        }
                        catch
                        {
                            //TODO: Log the error.
                        }
                    if (curReaction == null && (sHOR != null || sExtent != null))
                    {
                        //TODO: Log this error.
                        str = sr.ReadLine();
                        continue;
                    }
                    if (sHOR != null)
                    {
                        sHOR = sHOR.Remove(0, "heat of reaction :".Length).Trim();
                        string[] subStrings = sHOR.Split('/');
                        try
                        {
                            curReaction.HeatOfReactionValue = double.Parse(subStrings[0].Trim());
                            curReaction.HeatOfReactionSpecie = Compound.FromString(subStrings[1].Trim());
                        }
                        catch
                        {
                            //TODO: Log the error
                        }
                    }
                    if (sExtent != null)
                    {
                        try
                        {
                            sExtent = sExtent.Remove(0, "extent :".Length).Trim();
                            curReaction.ParseExtent(sExtent);
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex.ToString());
                            //TODO: Log the error.
                        }
                    }
                }
                if (str.ToLowerInvariant().StartsWith("sink:"))
                {
                    bSinksFound = true;
                    str = str.Remove(0, ("sink:").Length);
                }
                if (bSinksFound)
                {
                    string[] sinks = str.Split(',');
                    foreach (string s in sinks)
                        if (Compound.CompoundList.ContainsKey(s.Trim()))
                        {
                            if (!string.IsNullOrEmpty(txtSinks.Text))
                                txtSinks.Text += ", ";
                            txtSinks.Text += s.Trim();
                        }
                        else
                        {
                            //TODO: Log this error.
                        }
                }
                str = sr.ReadLine();
            }
            //TODO: Log the error if "end" is not found.
        }

        public SimpleReaction CreateReaction(string initialFormula)
        {
            ListViewItem lvi = new ListViewItem();
            lvi.SubItems.AddRange(new string[] { "", "" });
            lstReactions.Items.Add(lvi);
            SimpleReaction rxn = new SimpleReaction(lvi, Log);
            rxn.Changed += new EventHandler(rxn_Changed);
            if (initialFormula != null)
                try
                {
                    rxn.SetString(initialFormula);
                }
                catch (Exception ex)
                {
                    //TODO: Log the error
                }
            else
                rxn_Changed(rxn, new EventArgs());
            return rxn;
        }

        protected void LoadReaction(SimpleReaction rxn)
        {
            if (m_CurrentReaction != null)
            {
                m_CurrentReaction.Changed -= new EventHandler(currentReactionChanged);
                m_CurrentReaction.ReactantsChanged -= new EventHandler(rxn_ReactantsChanged);
            }
            m_CurrentReaction = rxn;
            txtReactants.Visible = txtProducts.Visible = comboDirection.Visible = true;
            txtFormula.Visible = false;
            if (rxn == null)
            {
                btnCopy.Enabled = btnMoveDown.Enabled = btnMoveUp.Enabled = btnRemove.Enabled = false;
                pnlReaction.Enabled = false;
                txtReactants.Text = txtProducts.Text = "";
                comboDirection.SelectedIndex = -1;
                comboExtentType.SelectedIndex = -1;
                comboHORSpecie.SelectedIndex = -1;
                comboHXType.SelectedIndex = -1;
                numSequence.Text = "";
                chkEnabled.Checked = false;
                return;
            }
            rxn.Changed += new EventHandler(currentReactionChanged);
            rxn.ReactantsChanged += new EventHandler(rxn_ReactantsChanged);
            rxn.ProductsChanged += new EventHandler(rxn_ProductsChanged);
            btnCopy.Enabled = btnMoveDown.Enabled = btnMoveUp.Enabled = btnRemove.Enabled = true;
            if (rxn.UseOriginalString)
            {
                txtReactants.Visible = txtProducts.Visible = comboDirection.Visible = false;
                txtFormula.Visible = true;
                txtFormula.Text = rxn.ToString();
            }
            /*if (string.IsNullOrEmpty(rxn.GetProductsString()))
                SetWaitingText(txtProducts, "Products");
            else
            {
                txtProducts.Text = rxn.GetProductsString();
                txtProducts.TextAlign = HorizontalAlignment.Left;
                txtProducts.ForeColor = System.Drawing.SystemColors.WindowText;
                txtProducts.Tag = true;
            }
            if (string.IsNullOrEmpty(rxn.GetReactantsString()))
                SetWaitingText(txtReactants, "Reactants");
            else
            {
                txtReactants.TextAlign = HorizontalAlignment.Right;
                txtReactants.Text = rxn.GetReactantsString();
                txtReactants.ForeColor = System.Drawing.SystemColors.WindowText;
                txtReactants.Tag = true;
            }*/
            txtReactants.Text = rxn.GetReactantsString();
            txtProducts.Text = rxn.GetProductsString();

            rxn_ReactantsChanged(null, new EventArgs());

            comboDirection.SelectedIndex = (int)rxn.Direction;

            comboExtentType.SelectedIndex = (int) rxn.ExtentType;
            comboHORType.SelectedIndex = rxn.CustomHeatOfReaction ? 1 : 0;

            numExtentValue.Text = rxn.ExtentInfo.Value.ToString();
            chkEnabled.Checked = rxn.Enabled;
            txtComment.Text = rxn.Comment;

            if (chkSequence.Checked)
            {
                numSequence.Value = Math.Min(Math.Max(rxn.Sequence, 1), sMaxSequences);
                numSequence.Text = numSequence.Value.ToString();
            }
            pnlReaction.Enabled = true;
        }

        void rxn_ProductsChanged(object sender, EventArgs e)
        {
            if (CompoundsChanged != null)
                CompoundsChanged(this, new EventArgs());
        }

        void rxn_ReactantsChanged(object sender, EventArgs e)
        {
            object cHOR = comboHORSpecie.SelectedItem;
            object cExt = comboExtentSpecie.SelectedItem;
            comboExtentSpecie.Items.Clear();
            comboHORSpecie.Items.Clear();
            foreach (Compound c in m_CurrentReaction.Reactants.Keys)
            {
                comboExtentSpecie.Items.Add(c);
                comboHORSpecie.Items.Add(c);
            }
            if (cExt != null && comboExtentSpecie.Items.Contains(cExt))
                comboExtentSpecie.SelectedItem = cExt;
            if (cHOR != null && comboHORSpecie.Items.Contains(cHOR))
                comboHORSpecie.SelectedItem = cHOR;
            if (CompoundsChanged != null)
                CompoundsChanged(this, new EventArgs());
        }

        protected void SetWaitingText(TextBox box, string text)
        {
            return;
            box.Text = text;
            box.TextAlign = HorizontalAlignment.Center;
            box.ForeColor = System.Drawing.SystemColors.GrayText;
            box.Tag = false;
        }

        protected void SetStatusMessage(string message)
        {
            //TODO: Make the message only appear for a finite amount of time.
            Log.Message("SetStatusMessageCalled - " + message, MessageType.Warning);
            //m_StatusControl.Text = message;
        }

        protected void ChangePosition(ListViewItem item, int newIndex)
        {
            m_bDoEvents = false;
            bool wasSelected = item.Selected;
            int oldIndex = item.Index;
            ListViewGroup grp = item.Group;
            lstReactions.Items.Remove(item);
            //if (oldIndex < newIndex)
                //newIndex--;
            try
            {
                lstReactions.Items.Insert(newIndex, item);
            }
            catch
            {
                lstReactions.Items.Add(item);
            }
            item.Group = grp;

            lstReactions.SelectedIndices.Clear();
            if (wasSelected)
                lstReactions.SelectedIndices.Add(item.Index);
            m_bDoEvents = true;
        }

        protected void rxn_Changed(object sender, EventArgs e)
        {
            SimpleReaction rxn = (SimpleReaction)sender;
            if (lstReactions.ShowGroups)
                if (lstReactions.Groups["grpSequence" + rxn.Sequence] != rxn.LVI.Group)
                {
                    m_bDoEvents = false;
                    rxn.LVI.Group = lstReactions.Groups["grpSequence" + rxn.Sequence];
                    m_bDoEvents = true;
                }
            ChangeOccured();
        }

        protected void currentReactionChanged(object sender, EventArgs e)
        {
            txtFormula.Text = m_CurrentReaction.ToString();
            txtProducts.Text = m_CurrentReaction.GetProductsString();
            txtReactants.Text = m_CurrentReaction.GetReactantsString();
        }

        protected void ChangeOccured()
        {
            Changed = true;
            if (NowChanged != null)
                NowChanged(this, new EventArgs());
        }

        protected static Regex s_CompoundSeperator = new Regex(@"^(?<Comp>[^,\r\n]*)((,(\r?\n)?|\r?\n)(?<Comp>[^,\r\n]*))*$",
            RegexOptions.Compiled | RegexOptions.ExplicitCapture);
        /// <summary>
        /// Checks a comma seperated list of compounds.
        /// </summary>
        /// <param name="s">The list of compounds</param>
        /// <returns>A list of all locations where the compound is unparseable, and the length of this compound</returns>
        protected Dictionary<int, int> CheckCompounds(string s)
        {
            Dictionary<int, int> ret = new Dictionary<int, int>();
            if (string.IsNullOrEmpty(s.Trim()))
                return ret;
            Match m = s_CompoundSeperator.Match(s);
            //string[] seperatedCompounds = s.Split(new string[] { ",", "\r\n" }, StringSplitOptions.None);
            foreach (Capture c in m.Groups["Comp"].Captures)
            {
                if (!Compound.CompoundList.ContainsKey(c.Value.Trim()))
                {
                    if (!string.IsNullOrEmpty(c.Value.Trim()))
                    {
                        Log.Message("Unable to parse compound '" + c.Value.Trim() + "'", MessageType.Warning);
                        int beforeLen = c.Length - c.Value.TrimStart().Length;
                        ret.Add(c.Index + beforeLen, c.Length);
                    }
                    else
                    {
                        Log.Message("Empty field found", MessageType.Warning);
                        ret.Add(c.Index, c.Length);
                    }
                }
            }
            return ret;
        }

        protected void ColourCompounds(RichTextBox box)
        {
            int oldSelectionStart = box.SelectionStart;
            int oldSelectionLength = box.SelectionLength;
            box.SelectAll();
            box.SelectionBackColor = box.BackColor;
            box.SelectionColor = box.ForeColor;
            Dictionary<int, int> unparseable = CheckCompounds(box.Text);
            foreach (KeyValuePair<int, int> kvp in unparseable)
            {
                box.Select(kvp.Key, kvp.Value);
                box.SelectionBackColor = Color.DarkRed;
                box.SelectionColor = Color.White;
            }
            box.Select(oldSelectionStart, oldSelectionLength);
        }

        protected ListViewItem FindLVIBelow(Point p)
        {
            int nClosestVal = int.MaxValue;
            ListViewItem closestLVI = null;
            foreach (ListViewItem lvi in lstReactions.Items)
                if (lvi.Bounds.Bottom > p.Y && lvi.Bounds.Bottom - p.Y < nClosestVal)
                {
                    nClosestVal = lvi.Bounds.Bottom - p.Y;
                    closestLVI = lvi;
                }
            return closestLVI;
        }
        #endregion Protected Functions

        #region Subclasses
        protected class MessageFrmReaction : MessageSource
        {
            protected FrmReaction m_owner;
            protected SimpleReaction m_rxn;
            public MessageFrmReaction(string title, FrmReaction owner, SimpleReaction rxn) :
                base(title)
            {
                m_owner = owner;
                m_rxn = rxn;
            }

            public override void DoCallback()
            {
                try
                {
                    if (m_owner != null && !m_owner.IsDisposed)
                    {
                        m_owner.Activate();
                        if (m_rxn != null)
                            m_owner.SelectReaction(m_rxn);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
                base.DoCallback();
            }
        }
        #endregion Subclasses

        private void lstReactions_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!m_bDoEvents) return;

            if (lstReactions.SelectedIndices.Count == 0)
                LoadReaction(null);
            else
                LoadReaction((SimpleReaction)lstReactions.SelectedItems[0].Tag);
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            CreateReaction(null).LVI.Selected = true;
        }

        private void chkSequence_CheckedChanged(object sender, EventArgs e)
        {
            m_bDoEvents = false;
            numSequence.Enabled = chkSequence.Checked;

            List<ListViewItem> originalList = new List<ListViewItem>();

            if (!chkSequence.Checked)
            {
                //To get the damned order correct:
                foreach (ListViewGroup grp in lstReactions.Groups)
                    foreach (ListViewItem lvi in grp.Items)
                        originalList.Add(lvi);
                foreach (ListViewGroup grp in lstReactions.Groups)
                    grp.Items.Clear();
                lstReactions.Items.Clear();
                lstReactions.Items.AddRange(originalList.ToArray());

                lstReactions.ShowGroups = false;

                foreach (ListViewItem lvi in originalList)
                {
                    SimpleReaction rxn = (SimpleReaction)lvi.Tag;
                    rxn.Sequence = 1;
                }
            }
            else
            {
                foreach (ListViewItem lvi in lstReactions.Items)
                    originalList.Add(lvi);
                lstReactions.ShowGroups = true;
                foreach (ListViewItem lvi in originalList)
                    lvi.Group = lstReactions.Groups["grpSequence" + ((SimpleReaction)lvi.Tag).Sequence];
                
            }
            m_bDoEvents = true;

            ChangeOccured();
        }

        private void comboExtentType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null)
            {
                numExtentValue.Text = "";
                return;
            }
            m_CurrentReaction.ExtentType = (ExtentTypes) comboExtentType.SelectedIndex;
            foreach (Control ctrl in m_OptionalExtentControls)
                ctrl.Visible = false;
            this.comboExtentSpecie.Visible = true;
            numExtentValue.Text = m_CurrentReaction.ExtentInfo.Value.ToString();
            if (m_CurrentReaction.ExtentInfo.Specie == null)
                comboExtentSpecie.SelectedIndex = -1;
            else
                comboExtentSpecie.SelectedItem = m_CurrentReaction.ExtentInfo.Specie;

            lblExtentValue.Text = "Value";
            switch ((ExtentTypes)comboExtentType.SelectedIndex)
            {
                case ExtentTypes.Fraction:
                    lblExtentUnits.Text = "of";
                    break;
                case ExtentTypes.Ratio:
                    RatioExtent ratExtent = (RatioExtent) m_CurrentReaction.ExtentInfo;
                    lblExtentUnits.Text = "of";
                    lblExtentValue.Text = "Val 1:";
                    numExtentVal2.Visible =
                        numExtentVal3.Visible =
                        lblExtent2.Visible =
                        lblExtent3.Visible = true;
                    numExtentVal2.Text = ratExtent.Time.ToString();
                    numExtentVal3.Text = ratExtent.Ratio2.ToString();
                    lblExtent2.Text = "At Time";
                    lblExtent3.Text = "Val 1:";
                    break;
                case ExtentTypes.Equilibrium:
                    comboExtentSpecie.Visible = false;
                    lblExtentUnits.Text = "";
                    break;
                case ExtentTypes.FinalConc:
                    lblExtentUnits.Text = "g/L of";
                    lblExtent2.Visible = numExtentVal2.Visible = lblExtent3.Visible = true;
                    lblExtent2.Text = "At Temp";
                    numExtentVal2.Text = ((Final_ConcExtent) m_CurrentReaction.ExtentInfo).T.ToString();
                    lblExtent3.Text = "degC";
                    break;
                case ExtentTypes.FinalFrac:
                    lblExtentUnits.Text = "of";
                    comboExtentPhase.Visible = true;
                    comboExtentPhase.SelectedItem = ((Final_FracExtent) m_CurrentReaction.ExtentInfo).Phase;
                    break;
                case ExtentTypes.Rate:
                    lblExtentUnits.Text = "Frac / s";
                    chkExtentStabilised.Visible = true;
                    chkExtentStabilised.Checked = ((RateExtent) m_CurrentReaction.ExtentInfo).Stabilised;
                    break;
            }

        }

        /*private void FormulaBox_Enter(object sender, EventArgs e)
        {
            TextBox box = (TextBox)sender;
            if (box.Tag == null || (bool)box.Tag == true) return;
            box.Text = "";
            box.ForeColor = System.Drawing.SystemColors.WindowText;
            if (box == txtReactants) box.TextAlign = HorizontalAlignment.Right;
            if (box == txtProducts) box.TextAlign = HorizontalAlignment.Left;
        }*/

        private void FormulaBox_Leave(object sender, EventArgs e)
        {
            try
            {
                TextBox box = (TextBox)sender;
                if (m_CurrentReaction != null)
                {
                    if (box == txtReactants)
                        m_CurrentReaction.ParseReactants(box.Text);
                    if (box == txtProducts)
                        m_CurrentReaction.ParseProducts(box.Text);
                }
                /*if (box.Text == "")
                {
                    if (box == txtReactants) SetWaitingText(box, "Reactants");
                    if (box == txtProducts) SetWaitingText(box, "Products");
                }*/
                //else
                //    box.Tag = true;
            }
            catch (RxnEdException ex)
            {
                SetStatusMessage(ex.Message);
            }
        }

        private void comboDirection_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction != null)
            {
                m_CurrentReaction.Direction = (RxnDirections)comboDirection.SelectedIndex;
            }
        }

        private void comboHORType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboHORType.SelectedIndex == 0) //Default:
            {
                comboHORSpecie.Enabled = false;
                comboHORSpecie.SelectedIndex = -1;
                comboHORUnits.SelectedItem = "kJ/mol";
                comboHORUnits.Enabled = false;
                /*if (m_CurrentReaction != null)
                {
                    m_CurrentReaction.HeatOfReactionValue = double.NaN;
                    numHORValue.Text = m_CurrentReaction.HeatOfReactionValue.ToString();
                }
                else*/
                numHORValue.Text = "";
                numHORValue.Enabled = false;
            }
            else //Override:
            {
                comboHORUnits.Enabled = true;
                comboHORSpecie.Enabled = true;
                numHORValue.Enabled = true;
                if (m_CurrentReaction != null && m_CurrentReaction.CustomHeatOfReaction)
                {
                    comboHORSpecie.SelectedItem = m_CurrentReaction.HeatOfReactionSpecie;
                    numHORValue.Text = m_CurrentReaction.HeatOfReactionValue.ToString();
                    if (m_CurrentReaction.HeatOfReactionType == FracTypes.ByMass)
                        comboHORUnits.SelectedItem = "kJ/kg";
                    else
                        comboHORUnits.SelectedItem = "kJ/mol";
                }
            }
        }

        private void comboHORSpecie_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction != null)
                m_CurrentReaction.HeatOfReactionSpecie = (Compound)comboHORSpecie.SelectedItem;
        }

        private void numSequence_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction != null)
            {
                m_CurrentReaction.Sequence = (int)numSequence.Value;
            }
        }

        private void FrmReaction_Load(object sender, EventArgs e)
        {
            RepopulateSpecies();
        }

        private void btnMoveUp_Click(object sender, EventArgs e)
        {
            if (lstReactions.SelectedItems.Count == 0) return;

            ListViewItem curItem = lstReactions.SelectedItems[0];
            if (!lstReactions.ShowGroups)
            {
                int curIndex = lstReactions.SelectedIndices[0];
                if (curIndex > 0)
                    ChangePosition(curItem, curIndex - 1);
            }
            else
            {
                if (m_CurrentReaction.Sequence > 0)
                    m_CurrentReaction.Sequence--;
            }
            ChangeOccured();
        }

        private void comboHXType_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (Control c in m_HXControls)
                c.Visible = false;
            switch ((HXTypes)comboHXType.SelectedIndex)
            {
                case HXTypes.None:
                    break;
                case HXTypes.FinalT:
                    lblHXUnits.Text = "degC"; lblHXUnits.Visible = true;
                    lblHXValue.Text = "Temperature"; lblHXValue.Visible = true;
                    numHX.Visible = true;
                    break;
                case HXTypes.ApproachT:
                    foreach (Control c in m_HXControls)
                        c.Visible = true;
                    lblHXUnits.Text = "degC,"; lblHXValue.Text = "Temperature";
                    break;
                case HXTypes.ApproachAmbient:
                    foreach (Control c in m_HXControls)
                        c.Visible = true;
                    lblHXUnits.Text = "degC,"; lblHXValue.Text = "Temperature";
                    break;
                case HXTypes.Power:
                    lblHXUnits.Text = "kJ/s"; lblHXUnits.Visible = true;
                    lblHXValue.Text = "Value"; lblHXValue.Visible = true;
                    numHX.Visible = true;
                    break;
                case HXTypes.Electrolysis:
                    lblHXUnits.Text = "%"; lblHXUnits.Visible = true;
                    lblHXValue.Text = "Value"; lblHXValue.Visible = true;
                    numHX.Visible = true;
                    break;
            }
            ChangeOccured();
        }

        private void numHORValue_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            double temp;
            double.TryParse(numHORValue.Text, out temp);
            m_CurrentReaction.HeatOfReactionValue = temp;
        }

        private void numExtentValue_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            double temp;
            double.TryParse(numExtentValue.Text, out temp);
            m_CurrentReaction.ExtentInfo.Value = temp;
        }

        private void txtFormula_Leave(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            try
            {
                m_CurrentReaction.SetString(txtFormula.Text);
            }
            catch (Reaction_Editor.RxnEdException ex)
            {
                SetStatusMessage(ex.Message);
            }
        }

        private void comboExtentSpecie_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            m_CurrentReaction.ExtentInfo.Specie = (Compound) comboExtentSpecie.SelectedItem;
        }

        private void chkExtentStabilised_CheckedChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null || m_CurrentReaction.ExtentType != ExtentTypes.Rate) return;
            ((RateExtent)m_CurrentReaction.ExtentInfo).Stabilised = chkExtentStabilised.Checked;
        }

        private void numExtentVal3_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null || m_CurrentReaction.ExtentType != ExtentTypes.Ratio) return;
            double temp;
            if (!double.TryParse(numExtentVal3.Text, out temp) || numExtentVal3.Text.Length == 0)
                temp = double.NaN;
            ((RatioExtent)m_CurrentReaction.ExtentInfo).Ratio2 = temp;
        }

        private void numExtentVal2_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            double temp;
            if (!double.TryParse(numExtentVal2.Text, out temp) || numExtentVal2.Text.Length == 0)
                temp = double.NaN;

            if (m_CurrentReaction.ExtentType == ExtentTypes.Ratio)
                ((RatioExtent)m_CurrentReaction.ExtentInfo).Time = temp;
            if (m_CurrentReaction.ExtentType == ExtentTypes.FinalConc)
                ((Final_ConcExtent)m_CurrentReaction.ExtentInfo).T = temp;
        }

        private void comboExtentPhase_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null || m_CurrentReaction.ExtentType != ExtentTypes.FinalFrac)
                return;
            ((Final_FracExtent)m_CurrentReaction.ExtentInfo).Phase = (Phases)comboExtentPhase.SelectedItem;
        }

        private void txtProducts_DragEnter(object sender, DragEventArgs e)
        {
            if (m_CurrentReaction == null || !m_CurrentReaction.ProductsOk)
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            if (e.Data.GetDataPresent(typeof(Compound)))
                e.Effect = DragDropEffects.Link;
            else
                e.Effect = DragDropEffects.None;
        }

        private void txtProducts_DragDrop(object sender, DragEventArgs e)
        {
            if (m_CurrentReaction == null || !m_CurrentReaction.ProductsOk)
            {
                e.Effect = DragDropEffects.None;
                return;
            }

            Point clientPoint = txtProducts.PointToClient(new Point(e.X, e.Y));
            int chIndex = txtProducts.GetCharIndexFromPosition(clientPoint);
            if (!e.Data.GetDataPresent(typeof(Compound)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            Compound compound = (Compound) e.Data.GetData(typeof(Compound));
            m_CurrentReaction.AddProduct(compound, 1.0, chIndex);
            e.Effect = DragDropEffects.Link;
            txtProducts.Select();
            txtProducts.Select(m_CurrentReaction.LastAddedNumStart, 1);
        }

        private void txtReactants_DragEnter(object sender, DragEventArgs e)
        {
            if (m_CurrentReaction == null || !m_CurrentReaction.ReactantsOk)
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            if (e.Data.GetDataPresent(typeof(Compound)))
                e.Effect = DragDropEffects.Link;
            else
                e.Effect = DragDropEffects.None;
        }

        private void txtReactants_DragDrop(object sender, DragEventArgs e)
        {
            if (m_CurrentReaction == null || !m_CurrentReaction.ReactantsOk)
            {
                e.Effect = DragDropEffects.None;
                return;
            }

            Point clientPoint = txtReactants.PointToClient(new Point(e.X, e.Y));
            int chIndex = txtReactants.GetCharIndexFromPosition(clientPoint);
            if (!e.Data.GetDataPresent(typeof(Compound)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            e.Effect = DragDropEffects.Link;
            Compound compound = (Compound)e.Data.GetData(typeof(Compound));
            m_CurrentReaction.AddReactant(compound, 1.0, chIndex);
            txtReactants.Select();
            txtReactants.Select(m_CurrentReaction.LastAddedNumStart, 1);
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            if (lstReactions.SelectedItems.Count == 0) return;

            ListViewItem curItem = lstReactions.SelectedItems[0];
            if (!lstReactions.ShowGroups)
            {
                int curIndex = lstReactions.SelectedIndices[0];
                if (curIndex < lstReactions.Items.Count - 1)
                    ChangePosition(curItem, curIndex + 1);
            }
            else
            {
                if (m_CurrentReaction.Sequence < sMaxSequences)
                    m_CurrentReaction.Sequence++;
            }
            ChangeOccured();
        }

        private void pnlReaction_Resize(object sender, EventArgs e)
        {
            const int outsidePadding = 3;
            const int spacing = 6;
            int comboWidth = comboDirection.Width;
            txtProducts.Width = txtReactants.Width = (pnlReaction.ClientSize.Width - comboWidth) / 2 - (outsidePadding + spacing);
            comboDirection.Left = txtReactants.Right + spacing;
            txtProducts.Left = comboDirection.Right + spacing;
            //txtReactants.Left = outsidePadding + 2 * spacing + comboWidth + txtReactants.Width;
        }

        private void tabSources_Sinks_Resize(object sender, EventArgs e)
        {
            grpSinks.Height = tabOptions.Height / 2;
        }

        private void chkEnabled_CheckedChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction != null)
                m_CurrentReaction.Enabled = chkEnabled.Checked;
        }

        private void txtComment_TextChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction != null)
                m_CurrentReaction.Comment = txtComment.Text;
        }

        private void comboHORUnits_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            if ((string)comboHORUnits.SelectedItem == "kJ/mol")
                m_CurrentReaction.HeatOfReactionType = FracTypes.ByMole;
            else if ((string)comboHORUnits.SelectedItem == "kJ/kg")
                m_CurrentReaction.HeatOfReactionType = FracTypes.ByMass;
        }

        private void btnCopy_Click(object sender, EventArgs e)
        {
            if (m_CurrentReaction == null) return;
            ListViewItem lvi = AddReaction(m_CurrentReaction, -1).LVI;
            lvi.Selected = true;
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (lstReactions.SelectedItems.Count == 0)
                return;
            else
                lstReactions.SelectedItems[0].Remove();
        }

        private void txtSources_TextChanged(object sender, EventArgs e)
        {
            bool bWasActive = Log.Active;
            Log.Active = false;
            ColourCompounds((RichTextBox)sender);
            Log.Active = bWasActive;
            ChangeOccured();
        }

        private void txtSinks_TextChanged(object sender, EventArgs e)
        {
            bool bWasActive = Log.Active;
            Log.Active = false;
            ColourCompounds((RichTextBox)sender);
            Log.Active = bWasActive;
            ChangeOccured();
        }

        private void numHX_TextChanged(object sender, EventArgs e)
        {

            ChangeOccured();
        }

        private void txtDescription_TextChanged(object sender, EventArgs e)
        {
            ChangeOccured();
        }

        private void FrmReaction_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_File != null)
                m_File.Close();
        }

        private void lstReactions_ItemDrag(object sender, ItemDragEventArgs e)
        {
            DoDragDrop(((ListViewItem)e.Item).Tag, DragDropEffects.Move | DragDropEffects.Copy);
        }

        private void lstReactions_DragOver(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(typeof(SimpleReaction)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            SimpleReaction rxn = (SimpleReaction)e.Data.GetData(typeof(SimpleReaction));
            if (this.ContainsReaction(rxn))
                if ((e.AllowedEffect & DragDropEffects.Move) != 0)
                    e.Effect = DragDropEffects.Move;
                else
                {
                    e.Effect = DragDropEffects.None;
                    return;
                }
            else
                e.Effect = DragDropEffects.Copy;
            Point p = lstReactions.PointToClient(new Point(e.X, e.Y));
            ListViewHitTestInfo hti = lstReactions.HitTest(p);
            ListViewItem insertionItem = FindLVIBelow(p);
            if (!lstReactions.ShowGroups)
            { }
            else if (insertionItem == null) //It's in the lower portion of the list, so find the highest group with an item in it:
            {
                int i;
                for (i = sMaxSequences; i > 0 && lstReactions.Groups["grpSequence" + i].Items.Count == 0; i--) ;
                SelectedGroup = lstReactions.Groups["grpSequence" + (i)];
            }
            else                        //It's over an item, we'll move / add it to that group.
            {
                SelectedGroup = insertionItem.Group;
            }
        }

        private void lstReactions_DragLeave(object sender, EventArgs e)
        {
            SelectedGroup = null;
        }

        private void lstReactions_DragDrop(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(typeof(SimpleReaction)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            SimpleReaction rxn = (SimpleReaction)e.Data.GetData(typeof(SimpleReaction));
            if (this.ContainsReaction(rxn))
                if ((e.AllowedEffect & DragDropEffects.Move) != 0)
                    e.Effect = DragDropEffects.Move;
                else
                {
                    e.Effect = DragDropEffects.None;
                    return;
                }
            else
                e.Effect = DragDropEffects.Copy;
            Point p = lstReactions.PointToClient(new Point(e.X, e.Y));
            ListViewHitTestInfo hti = lstReactions.HitTest(p);
            ListViewItem insertionItem = FindLVIBelow(p);
            if (!lstReactions.ShowGroups)
            {
                int newLoc = insertionItem != null ? newLoc = insertionItem.Index : lstReactions.Items.Count;

                if (this.ContainsReaction(rxn))
                    ChangePosition(rxn.LVI, newLoc);
                else
                    AddReaction(rxn, newLoc);
            }
            else if (insertionItem == null) //It's in the lower portion of the list, so find the highest group with an item in it:
            {
                int i;
                for (i = sMaxSequences; i > 1 && lstReactions.Groups["grpSequence" + i].Items.Count == 0; i--) ;
                if (this.ContainsReaction(rxn))
                    rxn.Sequence = i;
                else
                    AddReaction(rxn, -1).Sequence = i;              
            }
            else                        //It's over an item, we'll move / add it to that group.
            {
                if (this.ContainsReaction(rxn))
                    rxn.Sequence = ((SimpleReaction)insertionItem.Tag).Sequence;
                else
                    AddReaction(rxn, -1).Sequence = ((SimpleReaction)insertionItem.Tag).Sequence;
            }
            SelectedGroup = null;
        }

        private void txtSources_Leave(object sender, EventArgs e)
        {
            Log.SetSource(new MessageFrmReaction(this.Title + " Sources", this, null));
            Match m = s_EndsWithComma.Match(txtSources.Text);
            if (m.Success)
                txtSources.Text = m.Groups["Data"].Value;
            ColourCompounds(txtSources);
            Log.RemoveSource();
        }

        private void txtSinks_Leave(object sender, EventArgs e)
        {
            Log.SetSource(new MessageFrmReaction(this.Title + " Sinks", this, null));
            Match m = s_EndsWithComma.Match(txtSinks.Text);
            if (m.Success)
                txtSinks.Text = m.Groups["Data"].Value;
            ColourCompounds(txtSinks);
            Log.RemoveSource();
        }

        void txtCompounds_DragEnter(object sender, DragEventArgs e)
        {
            RichTextBox box = (RichTextBox)sender;
            if (!e.Data.GetDataPresent(typeof(Compound)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            Compound newComp = (Compound)e.Data.GetData(typeof(Compound));
            //Determine if we already have the compound in the textbox:
            if (Regex.Match(box.Text, @"(^|,)\s*" + Regex.Escape(newComp.Symbol) + @"\s*(,|$)", RegexOptions.ExplicitCapture).Success)
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            e.Effect = DragDropEffects.Link;
        }

        protected static Regex s_EndsWithComma = new Regex(@"(?<Data>.*),\s*$", RegexOptions.Compiled | RegexOptions.ExplicitCapture | RegexOptions.Singleline);
        void txtCompounds_DragDrop(object sender, DragEventArgs e)
        {
            RichTextBox box = (RichTextBox)sender;
            if (!e.Data.GetDataPresent(typeof(Compound)))
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            Compound newComp = (Compound)e.Data.GetData(typeof(Compound));
            //Determine if we already have the compound in the textbox:
            if (Regex.Match(box.Text, @"(^|,)\s*" + Regex.Escape(newComp.Symbol) + @"\s*(,|$)", RegexOptions.ExplicitCapture).Success)
            {
                e.Effect = DragDropEffects.None;
                return;
            }
            e.Effect = DragDropEffects.Link;
            if (s_EndsWithComma.Match(box.Text).Success)
                box.Text = box.Text.Trim() + newComp;
            else
                box.Text = box.Text.Trim() + ", " + newComp;
            bool bWasActive = Log.Active;
            Log.Active = false;
            ColourCompounds(box);
            Log.Active = bWasActive;
            ChangeOccured();
        }

        private void numHXApproach_ValueChanged(object sender, EventArgs e)
        {
            ChangeOccured();
        }
    }
}