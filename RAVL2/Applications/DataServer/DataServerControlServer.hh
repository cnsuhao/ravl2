// This file is part of RAVL, Recognition And Vision Library.
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASERVERCONTROLSERVER_H
#define	RAVL_DATASERVERCONTROLSERVER_H

#include "Ravl/DataServer/DataServerControlInterface.hh"
#include "Ravl/DataServer/DataServer.hh"
#include "Ravl/RCBodyV.hh"
#include "Ravl/String.hh"

namespace RavlN
{

  //! userlevel = Develop
  //: Data server control interface server.

  class DataServerControlServerBodyC
  : public RCBodyVC
  {
  public:
    DataServerControlServerBodyC(const StringC& controlAddress, const DataServerC& dataServer);
    //: Ctor.
    //!param: controlAddress - Network address for the controller to listen on.
    //!param: dataServer - The data server to be controlled.

    bool Listen();
    //: Start the server.
    // If the server starts successfully, this call will block (currently permanently).
    //!return: False if the server fails to start.

  private:
    StringC m_controlAddress;
    DataServerC m_dataServer;
  };

  //! userlevel = Normal
  //: Data server control interface server.

  class DataServerControlServerC
  : public RCHandleVC<DataServerControlServerBodyC>
  {
  public:
    DataServerControlServerC() {}
    //! Default ctor.

    DataServerControlServerC(const StringC& controlAddress, const DataServerC& dataServer)
    : RCHandleVC<DataServerControlServerBodyC>(*new DataServerControlServerBodyC(controlAddress, dataServer))
    {}
    //! Ctor.

    bool Listen()
    { return Body().Listen(); }
    //: Start the server.
    // If the server starts successfully, this call will block (currently permanently).
    //!return: False if the server fails to start.
  };

}

#endif
