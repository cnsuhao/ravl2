// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GuppiScalarSequence.cc 3401 2003-09-06 08:11:47Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiScalarSequence.cc"

#include "Ravl/Plot/GuppiScalarSequence.hh"
#include "Ravl/Plot/GuppiHeaders.hh"
#include "Ravl/Assert.hh"
#include "Ravl/Array1dIter.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlPlotN {

  //: Constructor.  
  GuppiScalarSequenceBodyC::GuppiScalarSequenceBodyC() {
    seq = guppi_seq_scalar_core_new ();
  }
  
  //: Construct from an array of values.
  
  GuppiScalarSequenceBodyC::GuppiScalarSequenceBodyC(const Array1dC<RealT> &data) {
    seq = guppi_seq_scalar_core_new ();
    Set(data);
  }

  //: Constructor.
  
  GuppiScalarSequenceBodyC::GuppiScalarSequenceBodyC(GuppiScalarSequenceTypeT seqType,RealT start,RealT inc,UIntT size) {
    seq = guppi_seq_scalar_core_new ();
    if(!Generate(seqType,start,inc,size)) {
      cerr <<"GuppiScalarSequenceBodyC::GuppiScalarSequenceBodyC(), WARNING: Failed to generate requested sequence. \n";
    }
  }
  
  //: Generate a sequence
  
  bool GuppiScalarSequenceBodyC::Generate(GuppiScalarSequenceTypeT seqType,RealT start,RealT inc,UIntT size) {
    RealT at = start;
    UIntT i = 0;
    guppi_seq_size_hint (GUPPI_SEQ(seq),size);
    
    switch(seqType)
      {
      case GSSLinear:
	for(;i < size;i++,at += inc)
	  guppi_seq_scalar_append (seq,at);
	break;
      case GSSLog:
	for(;i < size;i++,at += inc)
	  guppi_seq_scalar_append (seq,Log(at));
	break;
      }
    return true;
  }
  
  //: Set sequence to contents of 'data'.
  // This could be handled better....
  
  bool GuppiScalarSequenceBodyC::Set(const Array1dC<RealT> &data) {
    ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(const Array1dC<RealT> &), Called. \n");
    Array1dC<RealT> tmp(data);
    RavlAssert(seq != 0);
    gint min,max;
    guppi_seq_indices (GUPPI_SEQ(seq),&min, &max);
    UIntT size = (max - min)+1;
    if(size < 1) {
      for(Array1dIterC<RealT> it(data);it;it++)
	guppi_seq_scalar_append(seq,*it);
    } else {
      ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(), Updating. Min=" << min << " Size=" << size << " data.Size()=" << data.Size() << ". \n");
      if(size == data.Size())
	guppi_seq_scalar_set_many (seq,min,&(tmp[data.Range().Min()]),sizeof(RealT),data.Range().Size());
      else {
	cerr << "GuppiScalarSequenceBodyC::Set(), Eeek! I'm confused. \n";
	RavlAlwaysAssert(0);
      }
    }
    ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(const Array1dC<RealT> &), Done. \n");
    return true;
  }

  //: Set sequence to either the first or second element of an array of points2d's.
  // Note: This is NOT thread safe.
  
  bool GuppiScalarSequenceBodyC::Set(const Array1dC<Point2dC> &data,int index) {
    ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(const Array1dC<RealT> &), Called. \n");
    Array1dC<Point2dC> tmp(data);
    RavlAssert(seq != 0);
    gint min,max;
    guppi_seq_indices (GUPPI_SEQ(seq),&min, &max);
    UIntT size = (max - min)+1;
    if(size < 1) {
      for(Array1dIterC<Point2dC> it(data);it;it++)
	guppi_seq_scalar_append(seq,(*it)[index]);
    } else {
      ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(), Updating. Min=" << min << " Size=" << size << " data.Size()=" << data.Size() << ". \n");
      if(size == data.Size())
	guppi_seq_scalar_set_many (seq,min,&(tmp[data.Range().Min()][index]),
				   sizeof(RealT) * (index+1),data.Range().Size());
      else {
	cerr << "GuppiScalarSequenceBodyC::Set(), Eeek! I'm confused. \n";
	RavlAlwaysAssert(0);
      }
    }
    ONDEBUG(cerr <<"GuppiScalarSequenceBodyC::Set(const Array1dC<RealT> &), Done. \n");
    return true;
  }
  
  //: Append a value to the sequence.
  
  bool GuppiScalarSequenceBodyC::Append(RealT value) {
    RavlAssert(seq != 0);
    guppi_seq_scalar_append(seq,value);
    return true;
  }

  //: Destructor.
  
  GuppiScalarSequenceBodyC::~GuppiScalarSequenceBodyC() {
    
  }
  
}
