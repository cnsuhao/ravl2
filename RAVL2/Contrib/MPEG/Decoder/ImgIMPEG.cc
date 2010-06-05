// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgIMPEG.cc 1121 2002-05-13 16:52:55Z craftit $"
//! lib=RavlMPEG
//! file="Ravl/Image/ExternalVideoIO/ImgIOMpeg.cc"
//! author="Ramesh Krishna"

#include "Ravl/Image/ImgIMPEG.hh"
#include "Ravl/Array2dIter.hh"
#include <ctype.h>

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  //: Constructor.
  
  DPImageIMPEGBaseC::DPImageIMPEGBaseC()
    : EOS(false)
  {
    MpegI = 0;
  }
  
  //: Destructor.
  
  DPImageIMPEGBaseC::~DPImageIMPEGBaseC() 
  {
    if(MpegI != 0) {
      CloseMPEG();
      fclose( MpegI );
      MpegI = 0;
    }
    if(TmpPixels != 0)
      delete [] TmpPixels;
  }
  
  ///////////////////////////////////////
  
  //: Constructor from filename.    INPUT  (DECODER)
  
  DPIImageMPEGByteRGBBodyC::DPIImageMPEGByteRGBBodyC(StringC fn )
  {
    ONDEBUG(cerr << "DPIImageMPEGByteRGBBodyC(), Open file '" << fn << "' \n");
    MpegI = fopen( fn.chars(), "r" );
    
    DPIImageMPEGByteRGBBodyC::DPIImageMPEGOpen();
  }
  
  
  //: Constructor from stream.    INPUT  (DECODER)
  
  DPIImageMPEGByteRGBBodyC::DPIImageMPEGByteRGBBodyC(const IStreamC &in)
    : inf(in)
  {
    ONDEBUG(cerr << "DPIImageMPEGByteRGBBodyC(), Open istream \n");
    MpegI = fopen ( inf.Name().chars(), "r" );
    
    DPIImageMPEGByteRGBBodyC::DPIImageMPEGOpen();
  }
  
  
  //: Get next piece of data.
  
  ImageC<ByteRGBAValueC> DPIImageMPEGByteRGBBodyC::Get() {
    ONDEBUG(cerr << "DPIImageMPEGByteRGBBodyC::Get(), Called. \n");
    
    if (MpegI == 0) 
      throw DataNotReadyC("DPIImageMPEGByteRGBBodyC: Not file handle. ");
    
    ImageC<ByteRGBAValueC> img(MpegImgI.Height+1,MpegImgI.Width);
    if(!EOS)
      EOS = !((bool) GetMPEGFrame( (char *) &(img[0][0]) ));
    else
      throw DataNotReadyC("DPIImageMPEGByteRGBBodyC: Read failed. ");
    
    return img;
  }

  
  int DPIImageMPEGByteRGBBodyC::MPEGSeekProc(int off, int whence) {
    
    switch(whence)  {
    case SEEK_SET:
      RewindMPEG( MpegI, &MpegImgI );
      if ( off > 0 ) {
	for ( int i = 0; i < off; i++ )  {
	  EOS = (bool) GetMPEGFrame( TmpPixels );
	}
	CurFrame = off;
      }
      break;
	
    case SEEK_CUR:

      if ( off > 0 ) {
	for ( int i = 0; i < off; i++ ) {
	  EOS = (bool) GetMPEGFrame( TmpPixels );
	  CurFrame++;
	}
      }
	
      if ( off < 0 ) {
	RewindMPEG( MpegI, &MpegImgI );
	for ( int i = 0; i < CurFrame - off; i++ ) {
	  EOS = (bool) GetMPEGFrame( TmpPixels );
	}
	CurFrame = CurFrame - off;
      }

      break;

    case SEEK_END:
	
      if ( off < 0 ) {
	RewindMPEG( MpegI, &MpegImgI );
	for ( int i = 0; i < CurFrame - off; i++ ) {
	  EOS = (bool) GetMPEGFrame( TmpPixels );
	}
	CurFrame = CurFrame - off;
      }

    default:
      cerr << "DPIImageMPEGByteRGBBodyC::MPEGSeekProc(), WARNING: Illegal value for whence : " << whence << "\n";
    }

    if ( CurFrame > 0 )
      CurFrame = CurFrame - 1;   // Align so next frame is the read next.

    return CurFrame;
  }
  
  ////////////////////////////////////////////
  //: Save a RGB image in ByteRGB format.
  

  DPIImageMPEGByteRGBC::DPIImageMPEGByteRGBC(StringC fn)
    : DPEntityC(*new DPIImageMPEGByteRGBBodyC(fn))
  {}
  
  DPIImageMPEGByteRGBC::DPIImageMPEGByteRGBC(const IStreamC &strm)
    : DPEntityC(*new DPIImageMPEGByteRGBBodyC(strm))
  {}
  
  
  ImageDesc *DPIImageMPEGByteRGBBodyC::DPIImageMPEGOpen() {
    SetMPEGOption (MPEG_DITHER, FULL_COLOR_DITHER);
    OpenMPEG (MpegI, &MpegImgI);
    TmpPixels = new char[MpegImgI.Size * 4];
    CurFrame = 0;
    EOS = false;
    return &MpegImgI;
  }
  
  
}

