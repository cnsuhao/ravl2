// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TIMECODE_HEADER 
#define RAVL_TIMECODE_HEADER 1
////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! date="14/05/2002"
//! lib=RavlCore
//! file="Ravl/Core/Base/TimeCode.hh"
//! docentry="Ravl.Core.Misc"
//! userlevel=Normal
//! author="Kieron J Messer"

#include "Ravl/Assert.hh"
#include "Ravl/Types.hh"

namespace RavlN {
#if RAVL_VISUALCPP_NAMESPACE_BUG && RAVL_HAVE_STDNAMESPACE
  using namespace std;
#endif
  
  class StringC;
  
  //! userlevel=Normal
  //: Time code.
  
  class TimeCodeC  
  {
  public:
    
    //:------------------
    // Constructors
    
    TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr,RealT frameRate = 25.0);
    //: Construct timecode from 4 bytes
    
    TimeCodeC(ByteT * in,RealT frameRate = 25.0);
    //: Construct timecode from byte array
    
    TimeCodeC(IntT hr, IntT min, IntT sec, IntT fr,RealT frameRate = 25.0);
    //: Construct timecode from 4 ints
    
    TimeCodeC(const IntT nFrames,RealT frameRate = 25.0);
    //: Construct timecode from absolute frame count
    
    TimeCodeC(const char * string,RealT frameRate = 25.0);
    //: Construct from a valid string representation
    
    TimeCodeC()
      : m_liFrame(0),
	frameRate(25.0)
    {}
    //: Construct empty timecode
    
    //:-------------------
    //: Operators

    bool operator==(const TimeCodeC &in) const; 
    //: Checks for equals assignment
    
    bool operator!=(const TimeCodeC &in);
    // Checks for not equals assignment
    
    bool operator<(const TimeCodeC &in) const;
    // Checks if timecode smaller than input timecode
    
    bool operator>(const TimeCodeC &in) const;
    // Checks if timecode is bigger than input
    
    bool operator>=(const TimeCodeC &in) const;
    // Checks if timecode is bigger or equal to input
    
    bool operator<=(const TimeCodeC &in) const;
    // Checks if timecode is smaller or equal to input
    
    TimeCodeC operator+(const TimeCodeC & in) const;
    // Adds timecodes
    
    TimeCodeC operator-(const TimeCodeC & in) const;
    // Subtracts timecodes
    
    TimeCodeC & operator+=(const TimeCodeC & in);
    // Adds input timecode to this timecode
    
    TimeCodeC & operator+=(IntT frame);
    // Adds frame count to timecode
    
    TimeCodeC & operator-=(const TimeCodeC & in);
    // Subtracts input timecode from this
    
    friend ostream &operator<<(ostream &s, const TimeCodeC &out);
    // Output stream for timecode
    
    friend istream &operator>>(istream &s, TimeCodeC &inds);
    // Input stream fot timecode
    
    //:----------------------
    // Member Functions
    
    UIntT Hash() const { return (UIntT) m_liFrame; }
    //: the hash key
    
    inline IntT bcd(ByteT in) { return (in >> 4) * 10  + (in & 0xf);}
    //: Routine to convert binary coded decimal to int
    
    StringC ToText() const;
    //: Return a char  representation of timecode
    
    IntT NumberOfFramesTo(const TimeCodeC &in);
    //: Count the number of frames to a timecode
    
    bool IsValid();
    //: Checks whether the timecode holds valid data
        
    long int getFrameCount() const {return m_liFrame;}
    //: Access frame count.

    bool ConvertTo(IntT &hr, IntT &min, IntT &sec, IntT &fr) const;
    //: Convert to hours, minutes, seconds, frame.
    
    bool ConvertFrom(IntT hr,IntT min,IntT sec,IntT fr);
    //: Convert from hours, minutes, seconds, frame.

    RealT FrameRate() const
    { return frameRate; }
    //: Access the frame rate
  public:
    
    //long int m_liFrame;
    IntT m_liFrame ; 
    // Absolute frame count of timecode
    
    RealT frameRate;
    // Refrence frame rate.
  };
  
  ostream &operator<<(ostream &s, const TimeCodeC &out);
  //: Write time code out to stream.
  
  istream &operator>>(istream &s, TimeCodeC &tc);
  //: Read time code in from stream.
  
} // end namespace RavlN

#endif
