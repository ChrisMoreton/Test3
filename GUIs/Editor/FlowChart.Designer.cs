using MindFusion.FlowChartX;
namespace SysCAD.Editor
{
  partial class FrmFlowChart
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmFlowChart));
      this.fcFlowChart = new MindFusion.FlowChartX.FlowChart();
      this.fcFlowChart.SuspendLayout();
      this.SuspendLayout();
      // 
      // fcFlowChart
      // 
      this.fcFlowChart.AllowDrop = true;
      this.fcFlowChart.AllowRefLinks = false;
      this.fcFlowChart.AllowSplitArrows = true;
      this.fcFlowChart.AllowUnconnectedArrows = true;
      this.fcFlowChart.AntiAlias = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
      this.fcFlowChart.ArrowBrush = new MindFusion.FlowChartX.SolidBrush("#FF000000");
      this.fcFlowChart.ArrowCascadeOrientation = MindFusion.FlowChartX.Orientation.Auto;
      this.fcFlowChart.ArrowCrossings = MindFusion.FlowChartX.ArrowCrossings.BreakOff;
      this.fcFlowChart.ArrowHandlesStyle = MindFusion.FlowChartX.HandlesStyle.SquareHandles2;
      this.fcFlowChart.ArrowHead = MindFusion.FlowChartX.ArrowHead.Triangle;
      this.fcFlowChart.ArrowStyle = MindFusion.FlowChartX.ArrowStyle.Cascading;
      this.fcFlowChart.ArrowTextStyle = MindFusion.FlowChartX.ArrowTextStyle.OverLongestSegment;
      this.fcFlowChart.AutoSizeDoc = MindFusion.FlowChartX.AutoSize.AllDirections;
      this.fcFlowChart.Behavior = MindFusion.FlowChartX.BehaviorType.Modify;
      this.fcFlowChart.BoxHandlesStyle = MindFusion.FlowChartX.HandlesStyle.EasyMove;
      this.fcFlowChart.BoxStyle = MindFusion.FlowChartX.BoxStyle.Shape;
      this.fcFlowChart.CurrentCursor = System.Windows.Forms.Cursors.Default;
      this.fcFlowChart.Cursor = System.Windows.Forms.Cursors.Default;
      this.fcFlowChart.DefaultControlType = typeof(System.Windows.Forms.Button);
      this.fcFlowChart.DocExtents = ((System.Drawing.RectangleF)(resources.GetObject("fcFlowChart.DocExtents")));
      this.fcFlowChart.Dock = System.Windows.Forms.DockStyle.Fill;
      this.fcFlowChart.DoubleBuffer = true;
      this.fcFlowChart.GridSizeX = 1F;
      this.fcFlowChart.GridSizeY = 1F;
      this.fcFlowChart.InplaceEditFont = new System.Drawing.Font("Microsoft Sans Serif", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.fcFlowChart.IntermArrowHead = MindFusion.FlowChartX.ArrowHead.Triangle;
      this.fcFlowChart.Location = new System.Drawing.Point(0, 0);
      this.fcFlowChart.Margin = new System.Windows.Forms.Padding(2);
      this.fcFlowChart.Name = "fcFlowChart";
      this.fcFlowChart.PrintOptions.EnableShadows = false;
      this.fcFlowChart.RestrObjsToDoc = MindFusion.FlowChartX.RestrictToDoc.NoRestriction;
      this.fcFlowChart.ShadowsStyle = MindFusion.FlowChartX.ShadowsStyle.None;
      this.fcFlowChart.ShowDisabledHandles = false;
      this.fcFlowChart.Size = new System.Drawing.Size(292, 266);
      this.fcFlowChart.SortGroupsByZ = true;
      this.fcFlowChart.TabIndex = 0;
      this.fcFlowChart.TextRendering = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;
      this.fcFlowChart.ArrowModified += new MindFusion.FlowChartX.ArrowMouseEvent(this.fcFlowChart_ArrowModified);
      this.fcFlowChart.DrawArrow += new MindFusion.FlowChartX.ArrowCustomDraw(this.fcFlowChart_DrawArrow);
      this.fcFlowChart.MouseMove += new System.Windows.Forms.MouseEventHandler(this.fcFlowChart_MouseMove);
      this.fcFlowChart.BoxModified += new MindFusion.FlowChartX.BoxMouseEvent(this.fcFlowChart_BoxModified);
      this.fcFlowChart.BoxModifying += new MindFusion.FlowChartX.BoxConfirmation(this.fcFlowChart_BoxModifying);
      this.fcFlowChart.DrawBox += new MindFusion.FlowChartX.BoxCustomDraw(this.fcFlowChart_DrawBox);
      this.fcFlowChart.ArrowCreated += new MindFusion.FlowChartX.ArrowEvent(this.fcFlowChart_ArrowCreated);
      this.fcFlowChart.ArrowDeleting += new MindFusion.FlowChartX.ArrowConfirmation(this.fcFlowChart_ArrowDeleting);
      this.fcFlowChart.ArrowModifying += new MindFusion.FlowChartX.ArrowConfirmation(this.fcFlowChart_ArrowModifying);
      this.fcFlowChart.ArrowCreating += new MindFusion.FlowChartX.AttachConfirmation(this.fcFlowChart_ArrowCreating);
      this.fcFlowChart.Click += new System.EventHandler(this.fcFlowChart_Click);
      this.fcFlowChart.BoxDeleting += new MindFusion.FlowChartX.BoxConfirmation(this.fcFlowChart_BoxDeleting);
      this.AllowDrop = true;
      this.fcFlowChart.DragEnter += new System.Windows.Forms.DragEventHandler(fcFlowChart_DragEnter);
      this.fcFlowChart.DragOver += new System.Windows.Forms.DragEventHandler(this.fcFlowChart_DragOver);
      this.fcFlowChart.DragDrop += new System.Windows.Forms.DragEventHandler(this.fcFlowChart_DragDrop);
      this.fcFlowChart.ShowAnchors = ShowAnchors.Selected | ShowAnchors.Auto;

      // 
      // FrmFlowChart
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(292, 266);
      this.Controls.Add(this.fcFlowChart);
      this.AllowDrop = true;
      this.Margin = new System.Windows.Forms.Padding(2);
      this.Name = "FrmFlowChart";
      this.Text = "FlowChart";
      this.fcFlowChart.ResumeLayout(false);
      this.ResumeLayout(false);

    }

    #endregion

    private FlowChart fcFlowChart;
  }
}
