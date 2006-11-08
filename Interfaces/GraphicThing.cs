 using System;
using System.Data;
using System.Data.OleDb;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.Collections;
using System.Collections.Generic;
using System.Drawing.Drawing2D;

namespace SysCAD.Interface
{
  [Serializable]
  public class GraphicThing
  {
    private Guid guid;
    private String path;
    private String tag;

    public ArrayList elements;
    public ArrayList decorations;
    public ArrayList textArea;
    public FillMode fillMode;

    private String text;
    private RectangleF boundingRect;
    
    private float angle;
    private bool mirrorX = false;
    private bool mirrorY = false;
    private System.Drawing.Color fillColor;
    private System.Drawing.Color frameColor;

    [CategoryAttribute("Model"),
     DescriptionAttribute("Guid of the item."),
     ReadOnlyAttribute(true),
     DisplayName("Guid")]
    public Guid Guid
    {
      get { return guid; }
      set { guid = value; }
    }

    [CategoryAttribute("Model"),
     DescriptionAttribute("Tag name of the item.")]
    public String Tag
    {
      get { return tag; }
      set { tag = value; }
    }

    [CategoryAttribute("Graphic"),
     DescriptionAttribute("Area path of the item."),
     ReadOnlyAttribute(true),
    DisplayName("Path")]
    public String Path
    {
      get { return path; }
      set { path = value; }
    }

    [CategoryAttribute("Graphic"),
    Browsable(false),
    DescriptionAttribute("Horizontal position of the center of the item.")]
    public float X
    {
      get { return boundingRect.X; }
      set { boundingRect.X = value; }
    }

    [CategoryAttribute("Graphic"),
   Browsable(false),
    DescriptionAttribute("Vertical position of the center of the item.")]
    public float Y
    {
      get { return boundingRect.Y; }
      set { boundingRect.Y = value; }
    }

    [CategoryAttribute("Graphic"),
   Browsable(false),
    DescriptionAttribute("Width of the item.")]
    public float Width
    {
      get { return boundingRect.Width; }
      set { boundingRect.Width = value; }
    }

    [CategoryAttribute("Graphic"),
   Browsable(false),
    DescriptionAttribute("Height of the item.")]
    public float Height
    {
      get { return boundingRect.Height; }
      set { boundingRect.Height = value; }
    }

    [CategoryAttribute("Graphic"),
    DescriptionAttribute("Bounding rectangle of the item."),
    //ReadOnlyAttribute(true),
   DisplayName("Bounding Rect")]
    public ARectangleF BoundingRect
    {
      get { return boundingRect; }
      set { boundingRect = value; }
    }

    [CategoryAttribute("Graphic"),
     DescriptionAttribute("Angle of the item.")]
    public float Angle
    {
      get { return angle; }
      set { angle = value; }
    }

    [CategoryAttribute("Graphic"),
     DescriptionAttribute("Color of fill."),
     DisplayName("Fill Color")]
    public System.Drawing.Color FillColor
    {
      get { return fillColor; }
      set { fillColor = value; }
    }

    [CategoryAttribute("Graphic"),
    DescriptionAttribute("Color of frame."),
    DisplayName("Frame Color")]
    public System.Drawing.Color FrameColor
    {
      get { return frameColor; }
      set { frameColor = value; }
    }

    [CategoryAttribute("Graphic"),
     DescriptionAttribute("Whether the item is flipped horizontally."),
     DisplayName("Mirror X")]
    public bool MirrorX
    {
      get { return mirrorX; }
      set { mirrorX = value; }
    }

    [CategoryAttribute("Graphic"),
     DescriptionAttribute("Whether the item is flipped horizontally."),
     DisplayName("Mirror Y")]
    public bool MirrorY
    {
      get { return mirrorY; }
      set { mirrorY = value; }
    }

    public GraphicThing(Guid guid, String tag)
    {
      this.guid = guid;
      this.tag = tag;
    }

    public GraphicThing(String tag)
    {
      this.guid = Guid.NewGuid();
      this.tag = tag;
    }

    public void Populate(String filename, String Page, String EqpGUID, float InsertX, float InsertY, float ScaleX, float ScaleY, float Rotation)
    {
      path = "/" + filename + "/" + Page + "/";
      guid = new Guid(EqpGUID);

      float sx = 1.0F; float sy = 1.0F; float dx = 0.0F; float dy = 0.0F;

      boundingRect.Width = ScaleX * 30.0F * sx;
      boundingRect.Height = ScaleY * 30.0F * sy;

      if (boundingRect.Width < 0.0F)
      {
        mirrorX = true;
        boundingRect.Width = -boundingRect.Width;
      }

      if (boundingRect.Height < 0.0F)
      {
        mirrorY = true;
        boundingRect.Height = -boundingRect.Height;
      }

      boundingRect.X = InsertX - boundingRect.Width / 2.0F + dx;
      boundingRect.Y = -InsertY - boundingRect.Height / 2.0F + dy;
      angle = Rotation;

    }

    public void Populate(String filename, String Page, String EqpGUID, RectangleF rectangle, float Rotation)
    {
      path = "/" + filename + "/" + Page + "/";
      guid = new Guid(EqpGUID);

      boundingRect = rectangle;

      if (boundingRect.Width < 0.0F)
      {
        mirrorX = true;
        boundingRect.Width = -boundingRect.Width;
      }

      if (boundingRect.Height < 0.0F)
      {
        mirrorY = true;
        boundingRect.Height = -boundingRect.Height;
      }

      angle = Rotation;
    }
  }
}
