
using System;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

using System.Runtime.Remoting.Lifetime;
using System.Drawing;
using System.Threading;

using System.Runtime.Remoting.Channels.Ipc;
using System.Runtime.Remoting.Channels;
using System.Collections;
using System.Runtime.Remoting.Channels.Tcp;

using System.Drawing.Drawing2D;

namespace SysCAD.Protocol
{

  [Serializable]
  public sealed class EngineProtocol : BaseProtocol
  {

    private String connectionError = String.Empty;
    private EngineServiceProtocol serviceGraphic;

    Uri url = null;

    public EngineProtocol()
    {
    }

    //[EnvironmentPermissionAttribute(SecurityAction.LinkDemand, Unrestricted = true)]
    public bool Connect()
    {

      try
      {
        serviceGraphic = Activator.GetObject(typeof(BaseProtocol), url.ToString()) as EngineServiceProtocol;

        Name = serviceGraphic.Name; // Force a test of the connection.

        Syncxxx();

        connectionError = "";
        return true;
      }

      catch (System.Runtime.Remoting.RemotingException remotingException)
      {
        connectionError = remotingException.Message;
        return false;
      }
    }

    public void LogMessage(out Int64 requestId, String message, SysCAD.Log.MessageType messageType)
    {
      serviceGraphic.LogMessage(out requestId, message, messageType);
    }

    public void Syncxxx()
    {
      MemoryStream memoryStream;
      BinaryFormatter bf = new BinaryFormatter();

      memoryStream = new MemoryStream();
      bf.Serialize(memoryStream, serviceGraphic.graphicGroups);
      memoryStream.Seek(0, SeekOrigin.Begin);
      graphicGroups = bf.Deserialize(memoryStream) as Dictionary<Guid, GraphicGroup>;

      memoryStream = new MemoryStream();
      bf.Serialize(memoryStream, serviceGraphic.graphicLinks);
      memoryStream.Seek(0, SeekOrigin.Begin);
      graphicLinks = bf.Deserialize(memoryStream) as Dictionary<Guid, GraphicLink>;

      memoryStream = new MemoryStream();
      bf.Serialize(memoryStream, serviceGraphic.graphicItems);
      memoryStream.Seek(0, SeekOrigin.Begin);
      graphicItems = bf.Deserialize(memoryStream) as Dictionary<Guid, GraphicItem>;

      memoryStream = new MemoryStream();
      bf.Serialize(memoryStream, serviceGraphic.graphicThings);
      memoryStream.Seek(0, SeekOrigin.Begin);
      graphicThings = bf.Deserialize(memoryStream) as Dictionary<Guid, GraphicThing>;
    }

    public bool TestUrl(Uri url)
    {

      try
      {
        serviceGraphic = Activator.GetObject(typeof(BaseProtocol), url.ToString()) as EngineServiceProtocol;

        Name = serviceGraphic.Name; // Force a test of the connection.

        this.url = url;
        connectionError = "";
        return true;
      }

      catch (System.Runtime.Remoting.RemotingException remotingException)
      {
        url = null;
        connectionError = remotingException.Message;
        return false;
      }
    }

    ~EngineProtocol()
    {

      if (serviceGraphic != null)
      {

      }
    }
  }
}
