// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef NETMESSAGESIG_HEADER
#define NETMESSAGESIG_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.OS.Network"
//! file="amma/StdType/Network/NetMsgSig.hh"
//! lib=RavlOS
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.OS.Network"
//! date="13/12/2000"

#include "Ravl/OS/NetMessage.hh"
#include "Ravl/Calls.hh"

namespace RavlN
{  

  class NetEndPointC;
  
  ///// NetMsgCall0 ////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Net message Signal0
  
  class NetMsgCall0BodyC 
    : public NetMsgRegisterBodyC
  {
  public:
    NetMsgCall0BodyC(UIntT nid,const StringC &nname,const CallFunc0C<bool> &nsig);
    //: Constructor.
    
    virtual bool Decode(NetEndPointC &ep,BinIStreamC &pkt);
    //: Decode and execute a packet.
    
    bool Encode(BinOStreamC &os) {
      NetMsgRegisterBodyC::Encode(os);
      return true;
    }
    
  protected:
    CallFunc0C<bool> sig;
  };
  
  //! userlevel=Advanced
  //: Net message Signal0
  
  class NetMsgCall0C 
    : public NetMsgRegisterC
  {
  public:
    NetMsgCall0C()
      {}
    //: Default constructor.
    
    NetMsgCall0C(UIntT nid,const StringC &nname,const CallFunc0C<bool> &nsig)
      : NetMsgRegisterC(*new NetMsgCall0BodyC(nid,nname,nsig))
      {}
    //: Constructor.
    
    NetMsgCall0C(const NetMsgRegisterC &oth)
      : NetMsgRegisterC(oth)
      {
	if(dynamic_cast<NetMsgCall0BodyC *>(&Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    // If the body isn't of the appropriate type, an invalid handle is generated.
    
  protected:
    NetMsgCall0C(NetMsgCall0BodyC &bod)
      : NetMsgRegisterC(bod)
      {}
    //: Body constructor.
    
    NetMsgCall0BodyC &Body()
      { return static_cast<NetMsgCall0BodyC &>(NetMsgRegisterC::Body()); }
    //: Access body.
    
    const NetMsgCall0BodyC &Body() const
      { return static_cast<const NetMsgCall0BodyC &>(NetMsgRegisterC::Body()); }
    //: Access body.

  public:
    
    bool Encode(BinOStreamC &os) 
      { return Body().Encode(os); }
    //: Encode a call.
    
  };

  ///// NetMsgCall1 ////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Net message Signal1
  
  template<class Data1T>
  class NetMsgCall1BodyC 
    : public NetMsgRegisterBodyC
  {
  public:
    NetMsgCall1BodyC(UIntT nid,const StringC &nname,const CallFunc1C<Data1T,bool> &nsig)
      : NetMsgRegisterBodyC(nid,nname),
        sig(nsig)
      {}
    //: Constructor.
    
    virtual bool Decode(NetEndPointC &ep,BinIStreamC &is) { 
      //cerr << "Decode: Call1 at " << is.Tell() << "\n";
      Data1T dat1;
      is >> dat1;
      sig(dat1);
      return true;
    }
    //: Decode and execute a packet.

    bool Encode(BinOStreamC &os,const Data1T &dat1) {
      NetMsgRegisterBodyC::Encode(os);
      os << dat1;
      return true;
    }
    //: Encode a message.
    
  protected:
    CallFunc1C<Data1T,bool> sig;
  };

  //! userlevel=Advanced
  //: Net message Signal1
  
  template<class Data1T>
  class NetMsgCall1C 
    : public NetMsgRegisterC
  {
  public:
    NetMsgCall1C()
      {}
    //: Default constructor.
    
    NetMsgCall1C(UIntT nid,const StringC &nname,const CallFunc1C<Data1T,bool> &nsig)
      : NetMsgRegisterC(*new NetMsgCall1BodyC<Data1T>(nid,nname,nsig))
      {}
    //: Constructor.

    NetMsgCall1C(const NetMsgRegisterC &oth)
      : NetMsgRegisterC(oth)
      {
	if(dynamic_cast<NetMsgCall1BodyC<Data1T> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    // If the body isn't of the appropriate type, an invalid handle is generated.
    
  protected:
    NetMsgCall1C(NetMsgCall1BodyC<Data1T> &bod)
      : NetMsgRegisterC(bod)
      {}
    //: Body constructor.
    
    NetMsgCall1BodyC<Data1T> &Body()
      { return static_cast<NetMsgCall1BodyC<Data1T> &>(NetMsgRegisterC::Body()); }
    //: Access body.
    
    const NetMsgCall1BodyC<Data1T> &Body() const
      { return static_cast<const NetMsgCall1BodyC<Data1T> &>(NetMsgRegisterC::Body()); }
    //: Access body.
    
  public:
    
    bool Encode(BinOStreamC &os,const Data1T &p) 
      { return Body().Encode(os,p); }
    //: Encode a call.
  };

  ///// NetMsgCall2 ////////////////////////////////////////////////////
  //! userlevel=Develop
  //: NetMsgCall2

  template<class Data1T,class Data2T>
  class NetMsgCall2BodyC 
    : public NetMsgRegisterBodyC
  {
  public:    
    NetMsgCall2BodyC(UIntT nid,const StringC &nname,const CallFunc2C<Data1T,Data2T,bool> &nsig)
      : NetMsgRegisterBodyC(nid,nname),
        sig(nsig)
      {}
    //: Constructor.
    
    virtual bool Decode(NetEndPointC &ep,BinIStreamC &is) { 
      //cerr << "Decode: Call2 at " << is.Tell() << "\n";
      Data1T dat1;
      Data2T dat2;
      is >> dat1 >> dat2;
      sig(dat1,dat2);
      return true;
    }
    //: Process a message.
    
    bool Encode(BinOStreamC &os,const Data1T &dat1,const Data2T &dat2) {
      NetMsgRegisterBodyC::Encode(os);
      os << dat1 << dat2;
      return true;
    }
    //: Encode a message.

  protected:
    CallFunc2C<Data1T,Data2T,bool> sig;
  };

    //! userlevel=Advanced
  //: NetMsgCall2

  template<class Data1T,class Data2T>
  class NetMsgCall2C 
    : public NetMsgRegisterC
  {
  public:
    NetMsgCall2C()
      {}
    //: Default constructor.
    
    NetMsgCall2C(UIntT nid,const StringC &nname,const CallFunc2C<Data1T,Data2T,bool> &nsig)
      : NetMsgRegisterC(*new NetMsgCall2BodyC<Data1T,Data2T>(nid,nname,nsig))
      {}
    //: Constructor.
    
    NetMsgCall2C(const NetMsgRegisterC &oth)
      : NetMsgRegisterC(oth)
      {
	if(dynamic_cast<NetMsgCall2BodyC<Data1T,Data2T> *>(&Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    // If the body isn't of the appropriate type, an invalid handle is generated.
  protected:
    NetMsgCall2C(NetMsgCall2BodyC<Data1T,Data2T> &bod)
      : NetMsgRegisterC(bod)
      {}
    //: Body constructor.
    
    NetMsgCall2BodyC<Data1T,Data2T> &Body()
      { return static_cast<NetMsgCall2BodyC<Data1T,Data2T> &>(NetMsgRegisterC::Body()); }
    //: Access body.
    
    const NetMsgCall2BodyC<Data1T,Data2T> &Body() const
      { return static_cast<const NetMsgCall2BodyC<Data1T,Data2T> &>(NetMsgRegisterC::Body()); }
    //: Access body.
    
  public:
    
    bool Encode(BinOStreamC &os,const Data1T &p1,const Data2T &p2) 
      { return Body().Encode(os,p1,p2); }
    //: Encode a call.
    
  };
  
}

#endif
