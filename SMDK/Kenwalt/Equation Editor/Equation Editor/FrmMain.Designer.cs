namespace Reaction_Editor
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Specie Database");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Reaction Blocks");
            System.Windows.Forms.ListViewGroup listViewGroup1 = new System.Windows.Forms.ListViewGroup("Solids", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup2 = new System.Windows.Forms.ListViewGroup("Liquids", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup3 = new System.Windows.Forms.ListViewGroup("Vapours", System.Windows.Forms.HorizontalAlignment.Left);
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.menuNew = new System.Windows.Forms.ToolStripMenuItem();
            this.menuOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.menuOpenDir = new System.Windows.Forms.ToolStripMenuItem();
            this.menuClose = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuSave = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSaveAll = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.menuOpenDB = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuCut = new System.Windows.Forms.ToolStripMenuItem();
            this.menuCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.arrangeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuCascade = new System.Windows.Forms.ToolStripMenuItem();
            this.undockToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.logToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutSysCADReactionEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.m_StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.grpFiles = new System.Windows.Forms.GroupBox();
            this.treeFiles = new System.Windows.Forms.TreeView();
            this.grpSpecies = new System.Windows.Forms.GroupBox();
            this.lstSpecies = new System.Windows.Forms.ListView();
            this.chName = new System.Windows.Forms.ColumnHeader();
            this.chSymbol = new System.Windows.Forms.ColumnHeader();
            this.menuSpecieList = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.sortByPhaseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.txtFilter = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.dlgOpenRxn = new System.Windows.Forms.OpenFileDialog();
            this.dlgSaveRxn = new System.Windows.Forms.SaveFileDialog();
            this.dlgOpenDB = new System.Windows.Forms.OpenFileDialog();
            this.menuDatabaseFile = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.unloadAllSpeciesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.grpFiles.SuspendLayout();
            this.grpSpecies.SuspendLayout();
            this.menuSpecieList.SuspendLayout();
            this.panel1.SuspendLayout();
            this.menuDatabaseFile.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFile,
            this.editToolStripMenuItem,
            this.windowToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(734, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuFile
            // 
            this.menuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuNew,
            this.menuOpen,
            this.menuOpenDir,
            this.menuClose,
            this.toolStripMenuItem1,
            this.menuSave,
            this.menuSaveAs,
            this.menuSaveAll,
            this.toolStripMenuItem2,
            this.menuOpenDB,
            this.toolStripSeparator1,
            this.menuExit});
            this.menuFile.Name = "menuFile";
            this.menuFile.Size = new System.Drawing.Size(35, 20);
            this.menuFile.Text = "&File";
            this.menuFile.Click += new System.EventHandler(this.fileToolStripMenuItem_Click);
            // 
            // menuNew
            // 
            this.menuNew.Name = "menuNew";
            this.menuNew.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.menuNew.Size = new System.Drawing.Size(160, 22);
            this.menuNew.Text = "&New";
            this.menuNew.Click += new System.EventHandler(this.menuNew_Click);
            // 
            // menuOpen
            // 
            this.menuOpen.Name = "menuOpen";
            this.menuOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.menuOpen.Size = new System.Drawing.Size(160, 22);
            this.menuOpen.Text = "&Open";
            this.menuOpen.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // menuOpenDir
            // 
            this.menuOpenDir.Name = "menuOpenDir";
            this.menuOpenDir.Size = new System.Drawing.Size(160, 22);
            this.menuOpenDir.Text = "Open &Directory";
            this.menuOpenDir.Click += new System.EventHandler(this.menuOpenDir_Click);
            // 
            // menuClose
            // 
            this.menuClose.Name = "menuClose";
            this.menuClose.Size = new System.Drawing.Size(160, 22);
            this.menuClose.Text = "&Close";
            this.menuClose.Click += new System.EventHandler(this.menuClose_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(157, 6);
            // 
            // menuSave
            // 
            this.menuSave.Name = "menuSave";
            this.menuSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.menuSave.Size = new System.Drawing.Size(160, 22);
            this.menuSave.Text = "&Save";
            this.menuSave.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // menuSaveAs
            // 
            this.menuSaveAs.Name = "menuSaveAs";
            this.menuSaveAs.Size = new System.Drawing.Size(160, 22);
            this.menuSaveAs.Text = "Save &As";
            this.menuSaveAs.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // menuSaveAll
            // 
            this.menuSaveAll.Name = "menuSaveAll";
            this.menuSaveAll.Size = new System.Drawing.Size(160, 22);
            this.menuSaveAll.Text = "Save A&ll";
            this.menuSaveAll.Click += new System.EventHandler(this.menuSaveAll_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(157, 6);
            // 
            // menuOpenDB
            // 
            this.menuOpenDB.Name = "menuOpenDB";
            this.menuOpenDB.Size = new System.Drawing.Size(160, 22);
            this.menuOpenDB.Text = "Open Da&tabase";
            this.menuOpenDB.Click += new System.EventHandler(this.menuOpenDB_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(157, 6);
            // 
            // menuExit
            // 
            this.menuExit.Name = "menuExit";
            this.menuExit.Size = new System.Drawing.Size(160, 22);
            this.menuExit.Text = "E&xit";
            this.menuExit.Click += new System.EventHandler(this.menuExit_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuCut,
            this.menuCopy,
            this.menuPaste});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.editToolStripMenuItem.Text = "&Edit";
            this.editToolStripMenuItem.DropDownOpening += new System.EventHandler(this.editToolStripMenuItem_DropDownOpening);
            // 
            // menuCut
            // 
            this.menuCut.Name = "menuCut";
            this.menuCut.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.menuCut.Size = new System.Drawing.Size(150, 22);
            this.menuCut.Text = "Cu&t";
            this.menuCut.Click += new System.EventHandler(this.menuCut_Click);
            // 
            // menuCopy
            // 
            this.menuCopy.Name = "menuCopy";
            this.menuCopy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.menuCopy.Size = new System.Drawing.Size(150, 22);
            this.menuCopy.Text = "&Copy";
            this.menuCopy.Click += new System.EventHandler(this.menuCopy_Click);
            // 
            // menuPaste
            // 
            this.menuPaste.Name = "menuPaste";
            this.menuPaste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.menuPaste.Size = new System.Drawing.Size(150, 22);
            this.menuPaste.Text = "&Paste";
            this.menuPaste.Click += new System.EventHandler(this.menuPaste_Click);
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.arrangeToolStripMenuItem,
            this.undockToolStripMenuItem,
            this.toolStripMenuItem3,
            this.logToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.windowToolStripMenuItem.Text = "&Window";
            // 
            // arrangeToolStripMenuItem
            // 
            this.arrangeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuCascade});
            this.arrangeToolStripMenuItem.Name = "arrangeToolStripMenuItem";
            this.arrangeToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.arrangeToolStripMenuItem.Text = "&Arrange";
            // 
            // menuCascade
            // 
            this.menuCascade.Name = "menuCascade";
            this.menuCascade.Size = new System.Drawing.Size(126, 22);
            this.menuCascade.Text = "&Cascade";
            this.menuCascade.Click += new System.EventHandler(this.menuCascade_Click);
            // 
            // undockToolStripMenuItem
            // 
            this.undockToolStripMenuItem.Enabled = false;
            this.undockToolStripMenuItem.Name = "undockToolStripMenuItem";
            this.undockToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.undockToolStripMenuItem.Text = "&Undock";
            this.undockToolStripMenuItem.Click += new System.EventHandler(this.undockToolStripMenuItem_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(121, 6);
            // 
            // logToolStripMenuItem
            // 
            this.logToolStripMenuItem.Name = "logToolStripMenuItem";
            this.logToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.logToolStripMenuItem.Text = "&Log";
            this.logToolStripMenuItem.Click += new System.EventHandler(this.logToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutSysCADReactionEditorToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutSysCADReactionEditorToolStripMenuItem
            // 
            this.aboutSysCADReactionEditorToolStripMenuItem.Name = "aboutSysCADReactionEditorToolStripMenuItem";
            this.aboutSysCADReactionEditorToolStripMenuItem.Size = new System.Drawing.Size(231, 22);
            this.aboutSysCADReactionEditorToolStripMenuItem.Text = "&About SysCAD Reaction Editor";
            this.aboutSysCADReactionEditorToolStripMenuItem.Click += new System.EventHandler(this.aboutSysCADReactionEditorToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_StatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 361);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(734, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // m_StatusLabel
            // 
            this.m_StatusLabel.Name = "m_StatusLabel";
            this.m_StatusLabel.Size = new System.Drawing.Size(109, 17);
            this.m_StatusLabel.Text = "toolStripStatusLabel1";
            // 
            // grpFiles
            // 
            this.grpFiles.Controls.Add(this.treeFiles);
            this.grpFiles.Dock = System.Windows.Forms.DockStyle.Left;
            this.grpFiles.Location = new System.Drawing.Point(0, 24);
            this.grpFiles.Name = "grpFiles";
            this.grpFiles.Size = new System.Drawing.Size(146, 337);
            this.grpFiles.TabIndex = 2;
            this.grpFiles.TabStop = false;
            this.grpFiles.Text = "Files";
            // 
            // treeFiles
            // 
            this.treeFiles.AllowDrop = true;
            this.treeFiles.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeFiles.Location = new System.Drawing.Point(3, 16);
            this.treeFiles.Name = "treeFiles";
            treeNode1.Name = "SpecieDB";
            treeNode1.Text = "Specie Database";
            treeNode2.Name = "RBs";
            treeNode2.Text = "Reaction Blocks";
            this.treeFiles.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            this.treeFiles.Size = new System.Drawing.Size(140, 318);
            this.treeFiles.TabIndex = 0;
            this.treeFiles.DragDrop += new System.Windows.Forms.DragEventHandler(this.treeFiles_DragDrop);
            this.treeFiles.DragOver += new System.Windows.Forms.DragEventHandler(this.treeFiles_DragOver);
            this.treeFiles.DoubleClick += new System.EventHandler(this.treeFiles_DoubleClick);
            this.treeFiles.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.treeFiles_ItemDrag);
            // 
            // grpSpecies
            // 
            this.grpSpecies.Controls.Add(this.lstSpecies);
            this.grpSpecies.Controls.Add(this.panel1);
            this.grpSpecies.Dock = System.Windows.Forms.DockStyle.Right;
            this.grpSpecies.Location = new System.Drawing.Point(562, 24);
            this.grpSpecies.Name = "grpSpecies";
            this.grpSpecies.Size = new System.Drawing.Size(172, 337);
            this.grpSpecies.TabIndex = 3;
            this.grpSpecies.TabStop = false;
            this.grpSpecies.Text = "Species";
            // 
            // lstSpecies
            // 
            this.lstSpecies.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.chName,
            this.chSymbol});
            this.lstSpecies.ContextMenuStrip = this.menuSpecieList;
            this.lstSpecies.Dock = System.Windows.Forms.DockStyle.Fill;
            listViewGroup1.Header = "Solids";
            listViewGroup1.Name = "Solid";
            listViewGroup2.Header = "Liquids";
            listViewGroup2.Name = "Liquid";
            listViewGroup3.Header = "Vapours";
            listViewGroup3.Name = "Gas";
            this.lstSpecies.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup1,
            listViewGroup2,
            listViewGroup3});
            this.lstSpecies.Location = new System.Drawing.Point(3, 16);
            this.lstSpecies.Name = "lstSpecies";
            this.lstSpecies.ShowGroups = false;
            this.lstSpecies.Size = new System.Drawing.Size(166, 284);
            this.lstSpecies.TabIndex = 0;
            this.lstSpecies.UseCompatibleStateImageBehavior = false;
            this.lstSpecies.View = System.Windows.Forms.View.Details;
            this.lstSpecies.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.lstSpecies_ItemDrag);
            // 
            // chName
            // 
            this.chName.Text = "Name";
            this.chName.Width = 77;
            // 
            // chSymbol
            // 
            this.chSymbol.Text = "Symbol";
            // 
            // menuSpecieList
            // 
            this.menuSpecieList.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sortByPhaseToolStripMenuItem});
            this.menuSpecieList.Name = "menuSpecieList";
            this.menuSpecieList.Size = new System.Drawing.Size(153, 26);
            // 
            // sortByPhaseToolStripMenuItem
            // 
            this.sortByPhaseToolStripMenuItem.CheckOnClick = true;
            this.sortByPhaseToolStripMenuItem.Name = "sortByPhaseToolStripMenuItem";
            this.sortByPhaseToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.sortByPhaseToolStripMenuItem.Text = "&Sort By Phase";
            this.sortByPhaseToolStripMenuItem.Click += new System.EventHandler(this.sortByPhaseToolStripMenuItem_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.txtFilter);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(3, 300);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(166, 34);
            this.panel1.TabIndex = 1;
            // 
            // txtFilter
            // 
            this.txtFilter.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtFilter.Location = new System.Drawing.Point(38, 6);
            this.txtFilter.Name = "txtFilter";
            this.txtFilter.Size = new System.Drawing.Size(119, 20);
            this.txtFilter.TabIndex = 1;
            this.txtFilter.TextChanged += new System.EventHandler(this.txtFilter_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Filter";
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(146, 24);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 337);
            this.splitter1.TabIndex = 5;
            this.splitter1.TabStop = false;
            // 
            // splitter2
            // 
            this.splitter2.Dock = System.Windows.Forms.DockStyle.Right;
            this.splitter2.Location = new System.Drawing.Point(559, 24);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(3, 337);
            this.splitter2.TabIndex = 6;
            this.splitter2.TabStop = false;
            // 
            // dlgOpenRxn
            // 
            this.dlgOpenRxn.Filter = "Reaction files|*.rct|All files|*.*";
            this.dlgOpenRxn.Multiselect = true;
            this.dlgOpenRxn.Title = "Open Reaction";
            // 
            // dlgSaveRxn
            // 
            this.dlgSaveRxn.Filter = "Reaction Files|*.rct|All files|*.*";
            this.dlgSaveRxn.Title = "Save Reaction";
            // 
            // dlgOpenDB
            // 
            this.dlgOpenDB.Filter = "ini files|*.ini|All files|*.*";
            this.dlgOpenDB.Title = "Open Database";
            // 
            // menuDatabaseFile
            // 
            this.menuDatabaseFile.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.unloadAllSpeciesToolStripMenuItem});
            this.menuDatabaseFile.Name = "menuDatabaseFile";
            this.menuDatabaseFile.Size = new System.Drawing.Size(221, 26);
            // 
            // unloadAllSpeciesToolStripMenuItem
            // 
            this.unloadAllSpeciesToolStripMenuItem.Name = "unloadAllSpeciesToolStripMenuItem";
            this.unloadAllSpeciesToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.unloadAllSpeciesToolStripMenuItem.Text = "Unload &All Specie Databases";
            this.unloadAllSpeciesToolStripMenuItem.Click += new System.EventHandler(this.unloadAllSpeciesToolStripMenuItem_Click);
            // 
            // folderBrowserDialog1
            // 
            this.folderBrowserDialog1.RootFolder = System.Environment.SpecialFolder.MyComputer;
            this.folderBrowserDialog1.ShowNewFolderButton = false;
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(734, 383);
            this.Controls.Add(this.splitter2);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.grpSpecies);
            this.Controls.Add(this.grpFiles);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FrmMain";
            this.Text = "SysCAD Reaction Editor";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.MdiChildActivate += new System.EventHandler(this.FrmMain_MdiChildActivate);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.grpFiles.ResumeLayout(false);
            this.grpSpecies.ResumeLayout(false);
            this.menuSpecieList.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.menuDatabaseFile.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.GroupBox grpFiles;
        private System.Windows.Forms.TreeView treeFiles;
        private System.Windows.Forms.GroupBox grpSpecies;
        private System.Windows.Forms.ListView lstSpecies;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Splitter splitter2;
        private System.Windows.Forms.ToolStripMenuItem menuFile;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuNew;
        private System.Windows.Forms.ToolStripMenuItem menuOpen;
        private System.Windows.Forms.ToolStripMenuItem menuClose;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menuSave;
        private System.Windows.Forms.ToolStripMenuItem menuSaveAs;
        private System.Windows.Forms.ToolStripMenuItem menuSaveAll;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem menuExit;
        private System.Windows.Forms.ColumnHeader chName;
        private System.Windows.Forms.ColumnHeader chSymbol;
        private System.Windows.Forms.ToolStripMenuItem menuOpenDir;
        private System.Windows.Forms.ToolStripStatusLabel m_StatusLabel;
        private System.Windows.Forms.OpenFileDialog dlgOpenRxn;
        private System.Windows.Forms.SaveFileDialog dlgSaveRxn;
        private System.Windows.Forms.ToolStripMenuItem menuOpenDB;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.OpenFileDialog dlgOpenDB;
        private System.Windows.Forms.ToolStripMenuItem arrangeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem undockToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutSysCADReactionEditorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuCascade;
        public System.Windows.Forms.ToolStripMenuItem menuCut;
        public System.Windows.Forms.ToolStripMenuItem menuCopy;
        public System.Windows.Forms.ToolStripMenuItem menuPaste;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem logToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip menuDatabaseFile;
        private System.Windows.Forms.ToolStripMenuItem unloadAllSpeciesToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox txtFilter;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ContextMenuStrip menuSpecieList;
        private System.Windows.Forms.ToolStripMenuItem sortByPhaseToolStripMenuItem;


    }
}

