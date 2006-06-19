// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Audio.Audio IO.Audio File"
//! lib=RavlAudioFile
//! file="Ravl/Contrib/Audio/AudioFile/AudioFileFormat.cc"

#include "Ravl/Audio/AudioFileFormat.hh"
#include "Ravl/Audio/AudioFileIO.hh"
#include "Ravl/TypeName.hh"

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlAudioN {
  
  void InitAudioFileFormat()
  {}
  
  // AudioFile ////////////////////////////////////////////////////////////////
  
  //: Constructor.
  FileFormatAudioFileBodyC::FileFormatAudioFileBodyC(const StringC &nvName)
    : FileFormatBodyC(nvName,StringC("AudioFile driver.")),
      vName(nvName)
  {}
  
  
  const type_info &FileFormatAudioFileBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const
  { return typeid(void); }

  
  const type_info &
  FileFormatAudioFileBodyC::ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const { 
    if(filename.length() == 0)
      return typeid(void);
    ONDEBUG(cerr << "FileFormatAudioFileBodyC::ProbeLoad(), Checking file type." << obj_type.name() << " for '" << filename << "'\n");
    
    AFfilehandle setup = afOpenFile(filename.chars(),"r", AF_NULL_FILESETUP);
    if(setup == 0) {
      ONDEBUG(cerr << "Failed to open file '" << filename << "' for reading, probe failed. \n");
      return typeid(void);
    }
    
    int channels = afGetChannels (setup,AF_DEFAULT_TRACK);
    int sampfmt,sampwidth;
    afGetSampleFormat (setup, AF_DEFAULT_TRACK, &sampfmt,&sampwidth);
    ONDEBUG(cerr << "Open of file '" << filename << "' ok. Probe passed. Channels=" << channels << " Format=" <<sampfmt << " Width=" << sampwidth << " \n");
    afCloseFile(setup);

    // 16 bit samples     
    if (sampwidth == 16) {
      ONDEBUG(cerr << "16 bit samples " ) ; 
      if(channels == 1)
	return typeid(SampleElemC<1,Int16T>);
      if(channels == 2)
	return typeid(SampleElemC<2,Int16T>);
    }
    // 8 bit samples 
    if (sampwidth == 8) {
      ONDEBUG(cerr << "8 bit samples " ) ; 
      if(channels == 1)
	return typeid(SampleElemC<1,UByteT> );
      if(channels == 2) 
	return typeid(SampleElemC<2,UByteT> ); 
    }
    
    cerr << "Unexpected number of audio channels in '" << filename << "' Channels=" << channels << "\n";
    return typeid(void);
  }


  const type_info &
  FileFormatAudioFileBodyC::ProbeSave(const StringC &nfilename,const type_info &obj_type,bool forceFormat) const { 
    StringC ext = Extension(nfilename);
    ONDEBUG(cerr <<"FileFormatAudioFileBodyC::ProbeSave(), Extension='" << ext << "'\n");
    if(!(ext == "wav" || ext == "aiff" || ext == "aiffc" ||
       ext == "bicsf" || ext == "nextsnd" || ext == "au")) 
      return typeid(void);

      // mono formats
    if ( (obj_type == typeid ( SampleElemC<1,Int16T> )) || (obj_type == typeid(SampleElemC<1,RealT>)) ||
         (obj_type == typeid ( SampleElemC<1,UByteT>)) || (obj_type == typeid(SampleElemC<1,IntT>) ) )
	 return typeid ( SampleElemC<1,Int16T> ) ; // default for mono formats
      
      return typeid ( SampleElemC<2,Int16T> ) ; // stereo is the default for all others
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatAudioFileBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const
  { return DPIPortBaseC(); }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatAudioFileBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const 
  { return DPOPortBaseC(); }

  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  
  DPIPortBaseC FileFormatAudioFileBodyC::CreateInput(const StringC &filename,const type_info &obj_type) const
  {
    ONDEBUG(cerr << "FileFormatAudioFileBodyC::CreateInput(const StringC &,const type_info &), Called. \n");
    // 1 channel 16 bit 
    if(obj_type == typeid(SampleElemC<1,Int16T> ))
      return DPIAudioC<SampleElemC<1,Int16T>,AudioFileBaseC>(filename,0);
    
    // 2 channels 16 bit 
    if(obj_type == typeid(SampleElemC<2,Int16T> ))
      return DPIAudioC<SampleElemC<2,Int16T>,AudioFileBaseC>(filename,0);
   
    // 1 channel 8 bit 
    if(obj_type == typeid(SampleElemC<1,UByteT> ))
      return DPIAudioC<SampleElemC<1,UByteT> ,AudioFileBaseC>(filename,0);
    
    // 2 channels 8 bit 
    if (obj_type == typeid(SampleElemC<2,UByteT> )) 
      return DPIAudioC<SampleElemC<2,UByteT>, AudioFileBaseC> (filename,0) ; 
    
    // unknown 
    return DPIPortBaseC();
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatAudioFileBodyC::CreateOutput(const StringC &filename,const type_info &obj_type) const
  { 
    ONDEBUG(cerr << "FileFormatAudioFileBodyC::CreateOutput(const StringC &,const type_info &), Called. \n");
    //if(obj_type == typeid(Int16T))
    //return DPOAudioC<Int16T,AudioFileBaseC>(filename,0);
    if(obj_type == typeid(SampleElemC<2,Int16T>))
      return DPOAudioC<SampleElemC<2,Int16T>,AudioFileBaseC>(filename,0);
    if(obj_type == typeid(SampleElemC<1,Int16T>))
	return DPOAudioC<SampleElemC<1,Int16T>, AudioFileBaseC> (filename,0) ; 
   // if(obj_type == typeid(SByteT))
     // return DPOAudioC<SByteT,AudioFileBaseC>(filename,0);
    return DPOPortBaseC();
  }
  
  //: Get prefered IO type.
  
  const type_info &FileFormatAudioFileBodyC::DefaultType() const 
  { return typeid ( SampleElemC<2,Int16T>) ; }
  
  // Some common cif formats.
  
  FileFormatAudioFileC RegisterFileFormatAudioFile("audiofile");
}
