#if !defined(TIMECODE_H)
#define TIMECODE_H

////////////////////////////////////////////////////////////////////////////
//! rcsid=""
//! date="14/05/102"
//! lib=RavlCore
//! file="Ravl/Core/Base/TimeCode.hh"
//! docentry="Ravl.Core.Misc"
//! userlevel=Normal
//! author="Kieron J Messer"

#include "Ravl/Assert.hh"
#include "Ravl/Types.hh"

namespace RavlN {

  
  class TimeCodeC  
  {
    
  public:
    
    // ============
    // Constructors
    // ============
    TimeCodeC(ByteT hr, ByteT min, ByteT sec, ByteT fr);
    // Construct timecode from 4 bytes
    
    TimeCodeC(ByteT * in);
    // Construct timecode from byte array
    
    TimeCodeC(int hr, int min, int sec, int fr);
    // Construct timecode from 4 ints
    
    TimeCodeC(const long int nFrames);
    // Construct timecode from absolute frame count
    
    TimeCodeC(const TimeCodeC &in);
    // Construct timecode from another timecode
    
    TimeCodeC(const char * string);
    // Construct from a valid string representation
    
    TimeCodeC();
    // Construct empty timecode
    
    virtual ~TimeCodeC();
    // Destroy timecode
        
    // =========
    // Operators
    // =========
    
    TimeCodeC &operator=(const TimeCodeC &in);
    // Equal assignment
    
    bool operator==(const TimeCodeC &in) const; 
    // Checks for equals assignment
    
    bool operator==(TimeCodeC &in); 
    // Checks for equals assignment
    
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
    
    TimeCodeC & operator+=(long int frame);
    // Adds frame count to timecode
    
    TimeCodeC & operator-=(const TimeCodeC & in);
    // Subtracts input timecode from this
    
    friend ostream &operator<<(ostream &s, const TimeCodeC &out);
    // Output stream for timecode
    
    friend istream &operator>>(istream &s, TimeCodeC &inds);
    // Input stream fot timecode
    
    // ================
    // Member Functions
    // ================
    unsigned int Hash() const { return (unsigned int) m_liFrame; }
    //: the hash key
    
    inline int bcd(ByteT in){return (in >> 4) * 10  + (in & 0xf);}
    // Routine to convert binary coded decimal to int
    
    char * ToChar() const;
    // Return a char  representation of timecode
    
    int NumberOfFramesTo(const TimeCodeC &in);
    // Count the number of frames to a timecode
    
    bool IsValid();
    // Checks whether the timecode holds valid data
        
    long int getFrameCount() const {return m_liFrame;}


    // =====================
    // Object Representation
    // =====================
    
  public:
    
    long int m_liFrame;
    // Absolute frame count of timecode

    
  };
  
  
  inline
  ostream &
  operator<<(ostream &s, const TimeCodeC &out)
    //==========================================
  {
    s << out.ToChar();
    return s;
  }
  
  inline
  istream &
  operator>>(istream &s, TimeCodeC &tc)
    //===================================
  {
    //cerr << "operator>>(istream &s, TimeCodeC &tc): not implemented" << endl;
    IssueError(__FILE__, __LINE__, "not implemented");
    return s;
  }
} // end namespace RavlN

#endif // !defined(AFX_TIMECODEC_H)
