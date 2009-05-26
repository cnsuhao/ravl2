// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLAUDIO_TRANSCRIPTIONLIST_HEADER
#define RAVLAUDIO_TRANSCRIPTIONLIST_HEADER 1
//! author="Jack Longton"
//! docentry="Ravl.API.Audio.Feature Extraction"
//! rcsid="$Id: Transcription.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlAudioUtil
//! file="Ravl/Audio/Util/TranscriptionList.hh"

#include "Ravl/Audio/Segment.hh"
#include "Ravl/DList.hh"
#include "Ravl/Tuple3.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/SArray1d.hh"

namespace RavlAudioN {

  //! userlevel=Normal
  //: Transcription list.
  // Stores a base list of transriptions
  
  class TranscriptionBaseListC
  : public DListC<Tuple3C<IntT,RealRangeC,StringC> >
  {
    public:
      TranscriptionBaseListC();
      //: Constructor reates invalid handle
      
      TranscriptionBaseListC(StringC _label);
      //: Constructor
      
      TranscriptionBaseListC(const DListC<Tuple3C<IntT,RealRangeC,StringC> > &lst, StringC _label);
    //: Constructor.
      
      bool AddEvent(IntT val, RealRangeC range, StringC comment);
      //: Add a label event
    
      bool MergeSort();
      //: Merge and sort labels
    
      StringC &Label();
      //: Access label name
    
      bool Save(const StringC &filename, bool append = true);
      //: Save transcription
    
      bool Test(RealT time,SArray1dC<UIntT> val);
      //: test for a label at time
      
    protected:
      
      bool Sort();
      //: Sort
    
      IntT Merge();
      //: Merge    
      
      StringC label;
  };
  
  //: Transcription list.
  // Stores list of base transcription lists
  class LabelTranscriptionC 
  : public DListC<TranscriptionBaseListC> 
  {
    public:
      LabelTranscriptionC()
      {}
    //: Default constructor.
    // Creates an empty transcription
    
      LabelTranscriptionC(const StringC &transFile,const StringC &dataFile = StringC());
      //: Load from a file.
    
      LabelTranscriptionC(const DListC<TranscriptionBaseListC> &lst);
      //: Constructor.
    
      bool Load1(const StringC &fn);
      //: Load transcription from file.
    
      bool Save(const StringC &fn);
      //: Save transcription to a file.
    
      StringC &DataFile();
      //: Access data file.
    
      const StringC &DataFile() const;
      //: Access data file.
    
      bool MergeSort();
      //: Merge and sort labels
      
      bool Test(StringC label, RealT time, SArray1dC<UIntT> val);
      //: Search for label at time
    
      bool AddLabel(StringC label);
      //: Add label category
    
      bool AddData(StringC label, RealRangeC range, IntT value,StringC comment);
      //: Add data
    
    protected:
      StringC dataFile;
  };
}

#endif
