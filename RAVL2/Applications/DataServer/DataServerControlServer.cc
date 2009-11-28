// This file is part of RAVL, Recognition And Vision Library.
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/DataServer/DataServerControlServer.hh"
#include "Ravl/DataServer/DataServerControlClient.hh"
#include "Ravl/DataServer/DataServerControlConnection.hh"
#include "Ravl/OS/Socket.hh"
#include "Ravl/Threads/LaunchThread.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{

  DataServerControlServerBodyC::DataServerControlServerBodyC(const StringC& controlAddress, const DataServerC& dataServer)
  : m_controlAddress(controlAddress),
    m_dataServer(dataServer)
  {}

  static bool startClient(SocketC socketConnection, DataServerC dataServer)
  {
    DataServerControlClientC controlClient(dataServer);
    DataServerControlConnectionC controlConnection(socketConnection, controlClient);
    
    return controlConnection.Initialise();
  }

  bool DataServerControlServerBodyC::Listen()
  {
    SocketC socketServer(m_controlAddress, true);
    if (!socketServer.IsOpen())
    {
      cerr << "DataServerControlServerBodyC::Listen failed to open socket (" << m_controlAddress << ")" << endl;
      return false;
    }

    //TODO(WM) Add a kill signal to this loop?
    while (true)
    {
      try
      {
        ONDEBUG(cerr << "DataServerControlServerBodyC::Listen listening on (" << m_controlAddress << ")" << endl);
        SocketC socketConnection = socketServer.Listen(true, 20);
        if (!socketConnection.IsValid())
        {
          cerr << "DataServerControlServerBodyC::Listen opened invalid socket" << endl;
          break;
        }

        if (!socketConnection.IsOpen())
        {
          if (!socketServer.IsOpen())
          {
            cerr << "DataServerControlServerBodyC::Listen server socket was closed on us" << endl;
            break;
          }

          cerr << "DataServerControlServerBodyC::Listen connection not opened, looping again" << endl;
          continue;
        }

        LaunchThread(&startClient, socketConnection, m_dataServer);
      }
      catch(ExceptionC& e)
      {
        cerr << "DataServerControlServerBodyC::Listen RAVL exception (" << e.Text() << ")" << endl;
        break;
      }
      catch( ... )
      {
        cerr << "DataServerControlServerBodyC::Listen unknown exception" << endl;
        break;
      }
    }

    ONDEBUG(cerr << "DataServerControlServerBodyC::Listen loop finished (so something went wrong)");
    return false;
  }

}
