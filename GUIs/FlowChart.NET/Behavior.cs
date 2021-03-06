// Copyright (c) 2003-2006, MindFusion Limited - Gibraltar.
// This source code is provided to you as part of the FlowChart.NET control software
// package you have purchased. Its purpose is to help you trace and/or fix
// problems or customize the Control as needed for your application. To get permission
// to use the sources in any other way, please contact us at info@mindfusion.org
// Redistribution or any usage of the sources in a way not mentioned above is
// illegal and shall be pursued and punished with all means provided by Copyright laws.

using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace MindFusion.FlowChartX.Behaviors
{
	/// <summary>
	/// Classes derived from Behavior define how FlowChart.NET reacts
	/// to users' actions with a mouse or other pointing devices.
	/// </summary>
	public abstract class Behavior
	{
		public Behavior(FlowChart flowChart)
		{
			this.fc = flowChart;
			this.currentCursor = fc.CurModify;
		}

		public abstract InteractionState StartDraw(PointF point);

		public abstract void SetMouseCursor(PointF point);

		public virtual Node GetTargetNode(PointF point)
		{
			return null;
		}

		internal InteractionState startDraw(PointF pt, Graphics g)
		{
			InteractionState ist = null;
			int handle = 0;
			Arrow arrow = null;
			int segmentToSplit = 0;

			// draw a selection rectangle if the appropriate modifier key is pressed
			if ((fc.ModifierKeyActions.GetKeys(ModifierKeyAction.Select) &
				Control.ModifierKeys) != 0)
			{
				ist = new InteractionState(fc.Selection, 8, Action.Create);
			}
			else

			// or move selection if the mouse points to a handle in multiple selection
			if (fc.Selection.HitTestHandle(pt, ref handle))
			{
				ist = new InteractionState(fc.Selection, handle, Action.Modify);
			}
			else
			
			// or split the arrow if appropriate
			if ((arrow = shouldSplitArrow(pt, ref segmentToSplit)) != null)
			{
				ist = new InteractionState(arrow, segmentToSplit, Action.Split);
			}
			else
			{
				// select the auto-handles object
				if (fc.getAutoHObj() != null &&
					fc.getAutoHObj().HitTestHandle(pt, ref handle))
				{
					RectangleF rcInv = fc.Selection.getRepaintRect(false);
					fc.Selection.Change(fc.getAutoHObj());
					rcInv = Utilities.unionNonEmptyRects(
						rcInv, fc.Selection.getRepaintRect(false));
					fc.setAutoHObj(null);

					rcInv.Inflate(fc.SelHandleSize, fc.SelHandleSize);
					Utilities.addToRect(ref rcInv, fc.ShadowOffsetX, fc.ShadowOffsetY);
					Rectangle rcInvDev = Utilities.docToDevice(g, rcInv);
					fc.Invalidate(rcInvDev);
				}

				// start operation defined by the distinct behavior types
				ist = StartDraw(pt);
			}

			return ist;
		}

		protected FlowChart FlowChart
		{
			get { return fc; }
		}

		protected FlowChart fc;

		protected void setModfCursor(PointF pt, int handle, bool active, bool autoh)
		{
			Node node = null;
			bool checkHandleId = false;

			if (active && fc.ActiveObject.getType() != ItemType.Arrow)
			{
				node = fc.ActiveObject as Node;
				checkHandleId = true;
			}

			if (!checkHandleId &&
				autoh && fc.getAutoHObj().getType() != ItemType.Arrow)
			{
				node = fc.getAutoHObj() as Node;
				checkHandleId = true;
			}

			if (checkHandleId && handle != 8)
			{
				if (handle == 9)
				{
					currentCursor = fc.CurRotateShape;
				}
				else if (node != null && node.rotation() != 0)
				{
					float a = 0, r = 0;
					float d = 360 / 16;
					MindFusion.Geometry.Geometry2D.Convert.DekartToPolar(
						node.getCenter(), pt, ref a, ref r);
					a = (int)(360 - a) % 360;
					if (a >= 1*d && a < 3*d) currentCursor = fc.CurMainDgnlResize; else
					if (a >= 3*d && a < 5*d) currentCursor = fc.CurVertResize; else
					if (a >= 5*d && a < 7*d) currentCursor = fc.CurSecDgnlResize; else
					if (a >= 7*d && a < 9*d) currentCursor = fc.CurHorzResize; else
					if (a >= 9*d && a < 11*d) currentCursor = fc.CurMainDgnlResize; else
					if (a >= 11*d && a < 13*d) currentCursor = fc.CurVertResize; else
					if (a >= 13*d && a < 15*d) currentCursor = fc.CurSecDgnlResize; else
					currentCursor = fc.CurHorzResize;
				}
				else
				{
					if (handle == 0 || handle == 2) currentCursor = fc.CurMainDgnlResize;
					if (handle == 1 || handle == 3) currentCursor = fc.CurSecDgnlResize;
					if (handle == 4 || handle == 6) currentCursor = fc.CurVertResize;
					if (handle == 5 || handle == 7) currentCursor = fc.CurHorzResize;
				}
				
			}
			else
			{
				currentCursor = fc.CurModify;
			}

			fc.Cursor = currentCursor;
		}

		private Arrow shouldSplitArrow(PointF point, ref int segmentToSplit)
		{
			if (!fc.AllowSplitArrows)
				return null;

			Arrow arrow = fc.GetArrowAt(point,
				 Constants.getLineHitTest(fc.MeasureUnit)/2, true, ref segmentToSplit);
			
			if (arrow != null && (arrow == fc.ActiveObject || arrow == fc.getAutoHObj()))
			{
				if (!arrow.pointInHandle(point) && arrow.Style != ArrowStyle.Bezier)
					return arrow;

				int handle = -1;
				segmentToSplit = 0;
				if (arrow.Style == ArrowStyle.Cascading && arrow.SegmentCount == 2 &&
					arrow.HitTestHandle(point, ref handle) && handle == 1)
					return arrow;
			}

			return null;
		}

		internal Cursor getCurrentCursor()
		{
			return currentCursor;
		}

		internal void setCurrentCursor(Cursor cursor)
		{
			currentCursor = cursor;
		}

		protected Cursor currentCursor;
	}
}