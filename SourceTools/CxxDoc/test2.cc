
//: Boolean value
// The class BooleanT has a long story of changes. At first, BooleanT

class BooleanC
{
public:
  inline BooleanC();
  //: Default constructor. The logical value is determined.
  
  inline BooleanC(const BooleanC & l);
  // Copy constructor.

#ifdef VISUAL_CPP
  inline BooleanC(int x);
  // Construct from an integer
#endif

  inline BooleanC(const bool l);
    // Constructor from the object 'l' of built-in logical type.
  
  inline const BooleanC & operator=(const BooleanC & l);
  // Assigment.
  
  inline const BooleanC & operator=(const bool l);
  // Assigment.
  
#if defined(VISUAL_CPP)
  inline BooleanC operator! () const;
  // Not.
  
  inline BooleanC operator&& (BooleanC Oth) const;
  // And another boolean value.
  
  inline BooleanC operator&& (IntT Oth) const;
  // And an integer
  
  inline BooleanC operator|| (BooleanC Oth)  const;
  // Or a boolean.
  
  inline BooleanC operator|| (IntT Oth)  const;
  // Or an integer.
#endif
  
  // Conversions
  // -----------
  
  //inline operator bool() const;
  // Converts into the built-in logical type.
  
  //  inline operator bool () const;
  // Converts into the built-in logical type.
  
  inline operator bool & ();
  // Converts into the built-in logical type.
  
  inline operator const bool & () const;
  // Converts into the built-in logical type.
  
  inline IntT Int() const;
  // Converts into 0/1 integer.
  
  inline BooleanC operator==(const bool a) const;
  // Returns TRUE if this logical value is equal to the value 'a'.

  inline BooleanC operator!=(const bool a) const;
  // Returns TRUE if this logical value is not equal to the value 'a'.
  
#ifndef __OLD_BOOLEAN__
  inline BooleanC operator==(const int a) const;
  inline BooleanC operator!=(const int a) const;
#endif
  inline BooleanC operator<(const int a) const;
  inline BooleanC operator<=(const int a) const;
  inline BooleanC operator>(const int a) const;
  inline BooleanC operator>=(const int a) const;
  
  // Special operators
  // -----------------
  
  inline BooleanC XOr(const BooleanC y) const;
  // Returns TRUE iff exactly one argument is true (Exlusive OR).
  
  inline const BooleanC & operator|=(const BooleanC y);
  // Returns the result of '*this = *this || y'.
  
  inline const BooleanC &Invert();
  // Invert truth value.
    // Does v = !v;  return v;
  
private:
  // Object representation
  // ---------------------
  
  bool v; // the logical value.
  
  // Friends
  // -------
  friend istream & operator>>(istream & s, BooleanC & v);
};

// I/O of BooleanC
// ---------------

istream & operator>>(istream & s, BooleanC & v);
// Reads the logical value 'v' from the intput stream 's'.


ostream & operator<<(ostream & s, const BooleanC & v);
// Sends the logical value 'v' into the output stream 's'.

//====================================================================
//======= Boolean ====================================================
//====================================================================

inline 
BooleanC::BooleanC()
//==================
: v(false)
{}

// Constructor from the object 'l' of built-in logical type.

inline BooleanC::BooleanC(const bool l) 
  : v(l)
{}


inline 
const BooleanC &
BooleanC::operator=(const BooleanC & l)
//=====================================
{
  v = l.v;
  return *this;
}

inline 
const BooleanC &
BooleanC::operator=(const bool l)
//===============================
{
  v = l;
  return *this;
}

inline 
BooleanC::operator bool & ()
//==========================
{ return v; }

inline 
BooleanC::operator const bool & () const
//==========================
{ return v; }

inline 
IntT 
BooleanC::Int() const
//===================
{ return v ? 1 :0; }
