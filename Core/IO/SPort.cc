// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/SPort.cc"

#include "Ravl/DP/SPort.hh"

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  //: Seek to location in stream.
  
  bool DPSeekCtrlBodyC::Seek(UIntT) { 
    cerr << "DPSeekCtrlBodyC::Seek(UIntT),  WARNING: Not implemented. \n";
    return false; 
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPSeekCtrlBodyC::DSeek(IntT off) {
    UIntT at = Tell();
    if(at == ((UIntT) (-1)))
      return false; // Tell failed.
    if(((IntT) at - off) < 0)
      return false; // Seek before begining of file.
    return Seek((UIntT) ((IntT) at + off));
  }
  
  //: Find current location in stream.
  
  UIntT DPSeekCtrlBodyC::Tell() const { 
    cerr << "DPSeekCtrlBodyC::Tell() const, WARNING: Not implemented. \n";
    return ((UIntT)(-1)); 
  }
  
  //: Find the total size of the stream.
  // May return ((UIntT) (-1)) if not implemented.
  
  UIntT DPSeekCtrlBodyC::Size() const { 
    cerr << "DPSeekCtrlBodyC::Size() const, WARNING: Not implemented. \n";
    return ((UIntT)(-1)); 
  }
  
  UIntT DPSeekCtrlBodyC::Start() const { 
    return 0; 
  }
  
  //////////////////////////////////////////////////////
  
  //: Default constructor.
  DPSeekCtrlStubBodyC::DPSeekCtrlStubBodyC() { 
    ONDEBUG(cerr << "DPSeekCtrlStubBodyC::DPSeekCtrlStubBodyC(), Called. \n"); 
  }

  //: Constructor.
  DPSeekCtrlStubBodyC::DPSeekCtrlStubBodyC(const DPPortC &npb)
    : pb(npb)
  { ONDEBUG(cerr << "DPSeekCtrlStubBodyC::DPSeekCtrlStubBodyC(), Called. \n"); }

  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  bool DPSeekCtrlStubBodyC::Seek(UIntT) { 
    ONDEBUG(cerr << "DPSeekCtrlStubBodyC::Seek(UIntT), Called. \n");
    return false; 
  }
  
  //: Delta Seek, goto location relative to the current one.
  // The default behavour of this functions is :
  // Do some error checking then:
  //   Seek((UIntT)((IntT) Tell() + off));
  // if an error occurered (DSeek returned False) then stream
  // position will not be changed.
  
  bool DPSeekCtrlStubBodyC::DSeek(IntT d) { 
    if(d < 0 || !pb.IsValid())
      return false;
    DPIPortBaseC ip(pb);
    if(!ip.IsValid())
      return false;
    for(;d > 0;d--)
      if(!ip.Discard())
	return false;
    return true;
  }
  
  //: Find current location in stream.
  // May return ((UIntT) (-1)) if not implemented.
  
  UIntT DPSeekCtrlStubBodyC::Tell() const 
  { return ((UIntT) -1); }

  //: Find the total size of the stream. (assume start from 0.)
  // May return ((UIntT) (-1)) if not implemented.
  
  UIntT DPSeekCtrlStubBodyC::Size() const
  { return ((UIntT) -1); }
  
  /////////////////////////////////////////////////////////////////
  
  //: Constructor.
  // If stubIt is true, a body the produces no
  // error message is used, otherwise its a noisy one.
  
  DPSeekCtrlC::DPSeekCtrlC(bool stubIt,const DPPortC &pb)
    : DPEntityC(true)
  {
    if(stubIt)
      (*this) = DPSeekCtrlC(*new DPSeekCtrlStubBodyC(pb));
    else
      (*this) = DPSeekCtrlC(*new DPSeekCtrlBodyC());
  }
  
}
