// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSEQUENCEIO_HEADERS
#define RAVLSEQUENCEIO_HEADERS 1
//////////////////////////////////////////////////////////////
//! docentry="Basic_Types.Sequence IO" 
//! rcsid="$Id$"
//! userlevel=Normal
//! file="amma/StdType/DataConv/SequenceIO.hh"
//! lib=RavlOS
//! author="Charles Galambos"
//! date="08/04/99"

#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/String.hh"

namespace RavlN
{
  //! userlevel=Develop
  
  bool OpenISequenceBase(DPIPortBaseC &ip,DPSeekCtrlC &sc,const StringC &filename,const StringC &fileformat,const type_info &obj_type,bool verbose = false);
  //: Open input stream base.
  // Returns TRUE on succcess.
  
  //! userlevel=Develop
  
  bool OpenOSequenceBase(DPOPortBaseC &op,DPSeekCtrlC &sc,const StringC &filename,const StringC &fileformat,const type_info &obj_type,bool verbose = false);
  //: Open output stream base.
  // Returns TRUE on succcess.

  //! userlevel=Normal
  
  template<class DataT>
  bool OpenOSequence(DPOSPortC<DataT> &op,const StringC &fn,const StringC &fileformat = "",bool verbose = false)
  { 
    DPOPortBaseC anOp;
    DPSeekCtrlC sc;
    if(!OpenOSequenceBase(anOp,sc,fn,fileformat,typeid(DataT),verbose))
      return false;
    assert(anOp.IsValid());
    // Check return'd port is a sport !
    op = DPOSPortC<DataT>(anOp);
    if(!op.IsValid()) {
      if(sc.IsValid())
	op = DPOSPortAttachC<DataT>(anOp,sc);
      else
	op = DPOSPortAttachC<DataT>(anOp);
    }
    return TRUE;
  }
  //: Open a seekable output stream.
  // - Not all streams are seekable, the seek/tell functions are not garanteed to work
  // for all formats. <p>
  // - If a fileformat is a zero length string, all formats are considered.
  // Returns TRUE on succcess.
  
  template<class DataT>
  bool OpenISequence(DPISPortC<DataT> &ip,const StringC &fn,const StringC &fileformat = "",bool verbose = false)
  { 
    DPIPortBaseC anIp;
    DPSeekCtrlC sc;
    if(!OpenISequenceBase(anIp,sc,fn,fileformat,typeid(DataT),verbose))
      return false;
    assert(anIp.IsValid());
    // Check return'd port is a sport !
    ip = DPISPortC<DataT>(anIp);
    //cerr << "Attaching... \n";
    if(!ip.IsValid()) {
      if(sc.IsValid())
	ip = DPISPortAttachC<DataT>(anIp,sc);
      else
	ip = DPISPortAttachC<DataT>(anIp);
    }
    //cerr << "Attach done. \n";
    return TRUE;
  }
  //: Open a seekable input stream.
  // Note: Not all streams are seekable, the seek/tell functions are not garanteed to work
  // for all formats. <p>
  // - If a fileformat is a zero length string, all formats are considered.
  // Returns TRUE on succcess.

  //! userlevel=Normal
  
  template<class DataT>
  bool OpenOSequence(DPOPortC<DataT> &op,const StringC &fn,const StringC &fileformat = "",bool verbose = false)
  { 
    DPOPortBaseC anOp;
    DPSeekCtrlC sc;
    if(!OpenOSequenceBase(anOp,sc,fn,fileformat,typeid(DataT),verbose))
      return false;
    assert(anOp.IsValid());
    op = DPOPortC<DataT>(anOp); // This makes sure type checking gets done.
    return op.IsValid();
  }
  //: Open a normal output stream
  // - If a fileformat is a zero length string, all formats are considered.
  // Returns TRUE on succcess.
  
  //! userlevel=Normal
  
  template<class DataT>
  bool OpenISequence(DPIPortC<DataT> &ip,const StringC &fn,const StringC &fileformat = "",bool verbose = false)
  { 
    DPIPortBaseC anIp;
    DPSeekCtrlC sc;
    if(!OpenISequenceBase(anIp,sc,fn,fileformat,typeid(DataT),verbose))
      return false;
    assert(anIp.IsValid());
    ip = DPIPortC<DataT>(anIp);  // This makes sure type checking gets done.
    return ip.IsValid();
  }
  //: Open a normal input stream
  // - If a fileformat is a zero length string, all formats are considered.
  // Returns TRUE on succcess.
}


#endif
