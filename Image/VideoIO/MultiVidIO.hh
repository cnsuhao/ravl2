// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVideoIO

#ifndef _MULTI_VID_IO_HH_
#define _MULTI_VID_IO_HH_

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SDArray1d.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/SequenceIO.hh"

#include <iomanip.h>
#include <unistd.h>
#include <stdio.h>

namespace RavlImageN
{
  using namespace RavlN;
  using namespace RavlImageN;

  //!userlevel:Develop
  //: Multi-view video sequence input body class

  template<class PixelC> class DPIMultiVidBodyC 
    : public DPISPortBodyC< SArray1dC< ImageC< PixelC > > >
  {
  public:
    DPIMultiVidBodyC(const StringC &fnBase, const StringC& fnFormat)
    {
      frame = 0;
      numviews = 0;
      numframes = 0;

      while (1)
      {
	// look for sequence files
	StrOStreamC fnSequence;
	fnSequence << fnBase << "." << setw(1) << numviews << ".%05d." << fnFormat;

	// create new port for sequence
	DPISPortC< ImageC<PixelC> > port;

	// open sequence
	if (!OpenISequence(port, fnSequence.String()))
	{
	  break;
	} 
	
	// if not ready, can't use this sequence
	if (!port.IsGetReady())
	  break;
	
	// take min frame count as number of frames
	if (numframes == 0)
	  numframes = port.Size();
	else if (port.Size() < numframes)
	  numframes = port.Size();

	// add to array
	array_port.Add(port);

	// continue until we have found all the views there are
	++numviews;
      }
#if 1
      // numframes should be set by now, but it seems
      // port.Size() doesn't always work
      if (numframes == 0)
      {
	while (1)
	{
#ifdef __linux__
	  StrOStreamC str_frame; 
	  str_frame
	    << fnBase 
	    << ".0."
	    << setw(5) << numframes
	    << fnFormat;
	  if (access(str_frame.String(), R_OK) != 0)
	    break;
#else
	  char str_frame[256];
	  snprintf(str_frame, 
		   256, 
		   "%s.0.%05d.%s",
		   (const char*)fnBase,
		   numframes,
		   (const char*)fnFormat);
	    // cerr << "Looking for: " << str_frame.String() << endl;
	  if (access(str_frame, R_OK) != 0)
	    break;
#endif
	  ++numframes;
	}
      }
#endif
      // numframes = -1;

      // cerr << "Found " << numviews << " views with " << numframes << " frames." << endl;

      // return true if at least one view was opened
      // return ( (numviews > 0) ? true : false );
    }
    //: Constructor from filename
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue)
    {
      if (downcase(attrName) == "numviews")
      {
	attrValue = StringC(numviews);
	return true;
      }
      else
      {
	return DPISPortBodyC< SArray1dC< ImageC< PixelC > > >::GetAttr(attrName, attrValue);
      }
    }

    virtual bool Seek(UIntT off)
    {
      if (off >= numframes)
	return false;
      frame = off;
      SyncViews();
      return true;
    }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed.
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off)
    {
      // cerr << "DSeek: " << frame << " + " << off << endl;
      if (off < 0)
      {
	UIntT neg_off = (UIntT)(-off);
	if (neg_off > frame)
	  return false;
	frame -= neg_off;
      }
      else
      {
	if (off + frame >= numframes)
	  return false;
	frame += off;
      }
      SyncViews();
      return true;
    }
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const
    {
      return frame;
    } 
    //: Find current location in stream.
    
    virtual UIntT Size() const
    {
      return numframes;
    }
    //: Find the total size of the stream.
    
    virtual SArray1dC< ImageC<PixelC> > Get()
    {
      SArray1dC< ImageC<PixelC> > view(numviews);
      Get(view);
      return view;
    }
    //: Get next image.
    
    virtual bool Get(SArray1dC< ImageC<PixelC> > &buff)
    {
      // cerr << "Get()" << endl;

      if (!IsGetReady())
	return false;

      // cerr << "getting all views" << endl;

      RavlAssert(buff.Size() == 0 || buff.Size() == numviews); // only know how to deal with these
      
      if (buff.Size() == 0)
      {
	// cerr << "resizing array" << endl;
	buff = SArray1dC< ImageC<PixelC> > (numviews);
      }

      for (UIntT iview = 0; iview < numviews; iview++)
	array_port[iview].Get(buff[iview]);

      ++frame;
      SyncViews();
      return true;
    }
    //: Get next image.
    
    virtual bool IsGetReady() const 
      { return (frame < numframes); }
    //: Is some data ready ?
    // TRUE = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const
      { return (frame >= numframes); }
    //: Has the End Of Stream been reached ?
    // TRUE = yes.

  protected:
    void SyncViews()
    {
      for (UIntT iview = 0; iview < numviews; iview++)
	array_port[iview].Seek(frame);
    }

  protected:
    UIntT numviews;
    UIntT frame;
    UIntT numframes;
    SDArray1dC< DPISPortC< ImageC<PixelC> > > array_port;
  };

  //!userlevel:Develop
  //:Multi-view video sequence input port
  //
  // Used for reading syncronised multi-view video sequences
  // from disk or from frame grabbers. 
  //
  // Expects sequences of the form basename.C.FFFFF.type
  // Where:
  //   basename is a text id for the file
  //   C        is a 1 digit view number
  //   FFFFF    is a 5 digit frame number
  //   type     is the file type, such as "tif", "ppm", etc
  //
  // To open a sequence from disk use: 
  //
  //   DPISPortC< SArray1dC< ImageC<DataT> > > port;
  //   OpenISequence(port, "@multiview:basename:type");
  //
  // Sequences are expected to start from frame 0, view 0
  // If no type is specified, tif is assumed
  
  template<class PixelC> class DPIMultiVidC 
    : public DPISPortC< SArray1dC< ImageC< PixelC > > >
  {
  public:
    DPIMultiVidC(const StringC &fnBase, const StringC& fnFormat)
      : DPEntityC(*new DPIMultiVidBodyC<PixelC>(fnBase, fnFormat))
    {
    }
  };

  //!userlevel:Develop
  //: Multi-view video sequence output body class

  template<class PixelC> class DPOMultiVidBodyC 
    : public DPOSPortBodyC< SArray1dC< ImageC<PixelC> > >
  {
  public:
    DPOMultiVidBodyC(const StringC &nfnBase, const StringC& nfnFormat) :
      fnBase(nfnBase),
      fnFormat(nfnFormat),
      done_init(false),
      frame(0)
    {
    }
    //: Constructor from filename
    
    virtual bool Seek(UIntT off)
    {
      return false;
    }
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off)
    {
      return false;
    }
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const
    {
      return frame;
    }
    //: Find current location in stream.
    
    virtual UIntT Size() const
    {
      return frame;
    }
    //: Find the total size of the stream.
    
    bool Put(const SArray1dC< ImageC<PixelC> > &buff)
    {
      if (array_port.Size() == 0)
      {
	RavlAssert(buff.Size() > 0);
	array_port = SArray1dC< DPOSPortC< ImageC<PixelC> > > (buff.Size());
      }

      if (!done_init)
      {
	for (UIntT iview = 0; iview < array_port.Size(); iview++)
	{
	  StrOStreamC fnSequence;
	  fnSequence << fnBase << "." << setw(1) << iview << ".%05d." << fnFormat;
	  OpenOSequence(array_port[iview], fnSequence.String());
	}
	done_init = true;
      }

      bool putok = true;
      for (UIntT iview = 0; iview < array_port.Size(); iview++)
      {
	if (!array_port[iview].Put(buff[iview]))
	  putok = false;
      }

      ++frame;
      return putok;
    }
    //: Put image to a stream.
    
    virtual bool IsPutReady() const 
    {
      if (!done_init)
	return true;

      for (UIntT iview = 0; iview < array_port.Size(); iview++)
      {
	if (!array_port[iview].IsPutReady())
	  return false;
      }

      return true;
    }
    //: Read to write some data ?
    // TRUE = yes.
    
    virtual void PutEOS() {}
    //: Put End Of Stream marker.
    
   protected:
    StringC fnBase;
    StringC fnFormat;
    bool done_init;
    SArray1dC< DPOSPortC< ImageC<PixelC> > > array_port;
    UIntT frame;
   };

  //!userlevel:Develop
  //:Multi-view video sequence output port
  //
  // Used for saving multi-view video sequences to disk
  //
  // Saves sequences of the form basename.C.FFFFF.type
  // Where:
  //   basename is a text id for the file
  //   C        is a 1 digit view number
  //   FFFFF    is a 5 digit frame number
  //   type     is the file type, such as "tif", "ppm", etc
  //
  // To save a sequence to disk use: 
  //
  //   DPOSPortC< SArray1dC< ImageC<DataT> > > port;
  //   OpenOSequence(port, "@multiview:basename:type");
  //
  // Sequences start at frame 0, view 0
  // If no type is specified, tif is assumed

  template<class PixelC> class DPOMultiVidC 
    : public DPOSPortC< SArray1dC< ImageC< PixelC > > >
  {
  public:
    DPOMultiVidC(const StringC &fnBase, const StringC& fnFormat)
      : DPEntityC(*new DPOMultiVidBodyC<PixelC>(fnBase, fnFormat))
    {
    }
  };

  //!userlevel:Develop
  //:Multi-view video sequence format body

  template<class PixelC>  class FileFormatMultiVidBodyC : public FileFormatBodyC
  {
  public:
    FileFormatMultiVidBodyC() :
      FileFormatBodyC("multiview-video-sequence")
    {
    }

   virtual const type_info &ProbeLoad(IStreamC &in,const type_info &obj_type) const
   {
     return typeid(void);
   }
    //: always return 0 - cannot determine type from stream
    
    virtual const type_info &ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const
    {
      if (downcase(filename).contains("@multiview:") &&
	  obj_type == typeid(SArray1dC< ImageC< PixelC > >))
      {
	return obj_type;
      }

      return typeid(void);
    }
    //: Probe for load.  
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const
    {
      if (downcase(filename).contains("@multiview:") &&
	  obj_type == typeid(SArray1dC< ImageC< PixelC > >))
      {
	return obj_type;
      }

      return typeid(void);    }
    //: Probe for Save.
    
    virtual DPIPortBaseC CreateInput(IStreamC &in,const type_info &obj_type) const
    {
      DPIPortC< ImageC<PixelC> > null_port;
      return null_port;
    }
    //: Create a input port for loading.
    // Will create an Invalid port if not supported.
    
    virtual DPOPortBaseC CreateOutput(OStreamC &out,const type_info &obj_type) const
    {
      DPOPortC< ImageC<PixelC> > null_port;
      return null_port;
    }
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual DPIPortBaseC CreateInput(const StringC &filename,const type_info &obj_type) const
    {
      StringC fnBase;
      StringC fnFormat;
      ParsePathName(filename, fnBase, fnFormat);
      return DPIMultiVidC<PixelC>(fnBase, fnFormat);
    }
    //: Create a input port for loading from file 'filename'.
    // Will create an Invalid port if not supported. <p>
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const
    {
      StringC fnBase;
      StringC fnFormat;
      ParsePathName(filename, fnBase, fnFormat);
      return DPOMultiVidC<PixelC>(fnBase, fnFormat);      
    }
    //: Create a output port for saving to file 'filename'..
    // Will create an Invalid port if not supported. <p>
    
    virtual const type_info &DefaultType() const
    { 
      return typeid( SArray1dC< ImageC< PixelC > > ); 
    };
    //: Get prefered IO type.
    
    virtual IntT Priority() const { return 0; }
    //: Find the priority of the format. the higher the better.
    // Default is zero, use this if nothing better.
    
    virtual bool IsStream() const { return true; }
    //: Test if format is a fully streamable.
    // i.e. check if you can read/write more than object object.

  protected:
    static bool ParsePathName(const StringC& filename, StringC& fnBase, StringC& fnFormat)
    {
      StringC fnBaseLong = StringC(filename).after(':');

      // base is first iterm after @multiview
      if (fnBaseLong.contains(':'))
      {
	fnBase = fnBaseLong.before(':');
	fnFormat = fnBaseLong.after(':');
      }
      else
      {
	fnBase = fnBaseLong;
	fnFormat = "tif"; // default format
      }

      return true;
    }
    //: work out video file base name and file format from specified path

  };

  //!userlevel:Develop
  //:Multi-view video sequence format definition class

  template<class PixelC> class FileFormatMultiVidC 
    : public FileFormatC< SArray1dC< ImageC<PixelC> > >
  {
  public:
    FileFormatMultiVidC()
      : FileFormatC< SArray1dC< ImageC<PixelC> > >(*new FileFormatMultiVidBodyC<PixelC>())
    {
    }    
  };

  //!userlevel:Develop
  //:Initialise multi-view video sequence IO 
  // See DPIMultiVidC and DPOMultiVidC for details
  void InitMultiVidIO();
};

#endif
