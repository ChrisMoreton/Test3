
using System;
using System.Data;
using System.Data.OleDb;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.Collections.Generic;
using System.Drawing.Drawing2D;

namespace SysCAD.Protocol
{
  [Serializable]
  public class GraphicNode : GraphicItem
  {
    private String path;

    private Guid modelGuid;
    private Stencil stencil;

    private Rectangle boundingRect;
    private Double angle;

    private System.Drawing.Color fillColor;
    private FillMode fillMode;
    private bool mirrorX;
    private bool mirrorY;

    public GraphicNode()
    {

    }

    public GraphicNode(Guid guid, String tag, String path, Guid modelGuid, Stencil stencil, Rectangle boundingRect,
      Double angle, Rectangle tagArea, Double tagAngle, Font tagFont, Boolean tagVisible, Double opacity,
      System.Drawing.Color fillColor, FillMode fillMode, bool mirrorX, bool mirrorY)
      : base(guid, tag, tagArea, tagAngle, tagFont, tagVisible, opacity)
    {
      this.path = path;

      this.modelGuid = modelGuid;
      this.stencil = stencil;

      this.boundingRect = boundingRect;
      this.angle = angle;

      this.fillColor = fillColor;
      this.fillMode = fillMode;
      this.mirrorX = mirrorX;
      this.mirrorY = mirrorY;
    }

    public GraphicNode(String tag, String path, Guid modelGuid, Stencil stencil, Rectangle boundingRect,
      Double angle, Rectangle tagArea, Double tagAngle, Font tagFont, Boolean tagVisible, Double opacity,
      System.Drawing.Color fillColor, FillMode fillMode, bool mirrorX, bool mirrorY)
      : base(tag, tagArea, tagAngle, tagFont, tagVisible, opacity)
    {
      this.path = path;

      this.modelGuid = modelGuid;
      this.stencil = stencil;

      this.boundingRect = boundingRect;
      this.angle = angle;

      this.fillColor = fillColor;
      this.fillMode = fillMode;
      this.mirrorX = mirrorX;
      this.mirrorY = mirrorY;
    }

    public Double Angle
    {
      get { return angle; }
      set { angle = value; }
    }

    public Rectangle BoundingRect
    {
      get { return boundingRect; }
      set { boundingRect = value; }
    }

    public System.Drawing.Color FillColor
    {
      get { return fillColor; }
      set { fillColor = value; }
    }

    public FillMode FillMode
    {
      get { return fillMode; }
      set { fillMode = value; }
    }

    public Double Height
    {
      get { return boundingRect.Height; }
      set { boundingRect.Height = value; }
    }

    public bool MirrorX
    {
      get { return mirrorX; }
      set { mirrorX = value; }
    }

    public bool MirrorY
    {
      get { return mirrorY; }
      set { mirrorY = value; }
    }

    public Guid ModelGuid
    {
      get { return modelGuid; }
      set { modelGuid = value; }
    }

    public String Path
    {
      get { return path; }
      set { path = value; }
    }

    public Stencil Stencil
    {
      get { return stencil; }
      set { stencil = value; }
    }

    public Double Width
    {
      get { return boundingRect.Width; }
      set { boundingRect.Width = value; }
    }

    public Double X
    {
      get { return boundingRect.X; }
      set { boundingRect.X = value; }
    }

    public Double Y
    {
      get { return boundingRect.Y; }
      set { boundingRect.Y = value; }
    }

    public GraphicNode Clone()
    {
      return new GraphicNode(Guid, Tag, path, ModelGuid, Stencil, BoundingRect, Angle, TagArea, TagAngle, TagFont, TagVisible, Opacity, FillColor, FillMode, MirrorX, MirrorY);
    }
  }
}
