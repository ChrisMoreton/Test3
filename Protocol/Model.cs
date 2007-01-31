using System;
using System.Collections.Generic;
using System.Text;

namespace SysCAD.Protocol
{
  [Serializable]
  public class Model
  {
    String str = String.Empty;

    public Model(String str)
    {
      this.str = str;
    }

    public Model()
    {
    }

    public static implicit operator Model(String str)
    {
      Model model = new Model();
      model.str = str;
      return model;
    }

    public static implicit operator String(Model model)
    {
      if (model != null)
        return model.str;
      else
        return String.Empty;
    }

    public override String ToString()
    {
      return str;
    }
  }
}