#ifndef INDEX_HH
#define INDEX_HH
////////////////////////////////////////////////////////////////////////
//! file="amma/Contain/Array/Index1/Index.hh"
//! lib=MIndex1
//! userlevel=Normal
//! author="Radek Marik"
//! date="2/1/1996"
//! docentry="Containers.Arrays.1-D Arrays;Basic Types;Basic Types.Indexing"
//! rcsid="$Id$"

#include "amma/StdTypeA.hh"
#include "amma/Boolean.hh"
#include "amma/Error.hh"

class istream;
class ostream;

//====================================================================
//======= IndexC =====================================================
//====================================================================

//: Index class for indexing 1D arrays: an integer class with modified rounding and other operations

// The class IndexC is designed as a replacement for the built-in C
// <code>int</code> type, in an atttempt to correct some of the perceived
// deficiencies of <code>int</code>:

// <dl>
// <dt> Unsigned integers:
// <dd> When combining signed and unsigned integers in a binary operation, C
// always converts the signed integer to unsigned, which can generate
// surprising results such as: <code>(unsigned int) 4 / (-2) = 0</code>.
// <dt> Rounding:
// <dd>With the <code>int</code> type, rounding is either towards zero (e.g. on conversion
// from floating point representations), or implementation-dependent (e.g.
// integer division operations).  Where negative numbers are
// involved, this behaviour is often not what is required, particularly for
// indexing purposes.  
// </dl>
// The behaviour of IndexC therefore differs from that of <code>int</code>, to
// provide more consistent behaviour for indexing purposes, and to improve
// portability of code. 

// <p> The major differences between IndexC and <code>int</code> are: 
// <dl>
// <dt> Unsigned integers:
// <dd> Where relevant, unsigned integers are converted to signed before
// combining with IndexC.
// <dt>Rounding:
// <dd>Rounding is always to the nearest more negative integer.  This affects:
// <ul> 
// <li> Truncation of floating point values on conversion to IndexC.
// <li> Integer division operations involving IndexC, for which:
// <ul> 
// <li> if the divisor is negative, the signs of both divisor and dividend
// are reversed; 
// <li> if the divisor is positive, the quotient is always rounded towards
// the more negative nearest integer, regardless of the sign of the dividend.
// </ul>
// Thus (IndexC) -4 / 3 yields -2, and (IndexC) -4 % 3 yields 2.
// With the <code>int</code> type, the results would probably be -1 and -1 respectively. 
// </ul>
// <dt> Modulo operator:
// <dd> The modulo operator is always consistent with the divide operator, as
// per the C and C++ standards.  It accordingly always returns a non-negative
// value.
// </dl>

// Remember: IndexC is a class, not a built-in. So:<ul>

// <li> The type conversion rules are not necessarily the same as for <code>int</code>.  For
// a class, the type of the <b>first</b> operand of binary operator determines
// the class member function used.

// <li> Because there is no implicit conversion from IndexC to
// <code>int</code>, you can't use IndexC everywhere you would use an
// <code>int</code>.  In particular you can't use an IndexC object directly as
// an <code>int</code> function argument.  You need to use the <a
// href="#IndexC_V_void__const">V()</a> member function to achieve this.  (We <i>could</i> have provided the implicit conversion, but it would then be very difficult sometimes to know which was actually being used.) </ul>

// See also the class bugs above.
//!classbugs: <dl>
//!classbugs: <dt>operator-:
//!classbugs: <dd> Currently, IndexC::operator-(IndexC) returns an IntT, not
//!classbugs: (as you might have expected) an IndexC.  This can give
//!classbugs:  surprising results.
//!classbugs: </dl>

class IndexC
{
  public:
    // <p><h2>Constructors, copies, assigment, and destructor:</h2>
    /* ----------------------------------------------- */

    inline IndexC(const IntT i = 0);
    // Creates the index with the value 'i'.

    inline IndexC(const SizeT s);
    // Creates the index with the same value as the value of size 's'.

    inline IndexC(const IndexC & i);
    // Creates the index with the same value as the index 'i' has.
  
    inline IndexC(const DoubleT i);
    // Creates the index with the value rounded version of 'i'.
  
    // <p><h2>Access functions:</h2>
    /* ---------------- */

    inline IntT V(void) const;
    // Returns the current value of the index.

    inline IntT & V(void);
    // Returns the current value of the index.

    inline BooleanT IsInRange(SizeT size) const;
    // True if 0 <= this < size

    // <p><h2>Conversions:</h2>
    /* ----------- */
    // The obvious conversions from index to integer numbers
    // are missing to avoid automatic conversion of an index expression
    // into integer expression. In this way such a conversion
    // is detected in compilation time and one can decide which
    // type of expression is proper one.

#if !USE_BUILTIN_BOOL
    inline operator BooleanT() const;
    // Returns TRUE if the index value is different from 0.
#endif

    inline operator bool() const;
    // Returns TRUE if the index value is different from 0.

    inline operator ByteT() const;
    // Truncates the index value and returns it as ByteT.

    inline operator CharT() const;
    // Truncates the index value and returns it as CharT.

    inline operator SCharT() const;
    // Truncates the index value and returns it as SCharT.

    inline operator FloatT() const;
    // Converts the index value into float representation.

    inline operator DoubleT() const;
    // Converts the index value into double representation.

    // <p><h2>Arithmetical operations:</h2>
    /* -----------------------*/

    inline IndexC operator-() const;
    // Returns opposite index (unary minus operator).

    inline IndexC & operator++();
    // The prefix operator increments the index value by 1.

    inline IndexC operator++(int);
    // The postfix operator increments the index value by 1.

    inline IndexC & operator--();
    // The prefix operator decrements the index value by 1.

    inline IndexC operator--(int);
    // The postfix operator decrements the index value by 1.

    inline IndexC operator+(const IntT i) const;
    // Returns a new index with value of this index added by integer 'i'.

    inline IndexC operator-(const IntT i) const;
    // Returns a new index with value of this index subtracted by integer 'i'.

    inline IndexC operator*(const IntT i) const;
    // Returns a new index with value of this index multiplied by integer 'i'.

    inline IndexC operator/(const IntT i) const;
    // Returns a new index with value of this index divided by integer 'i'.

    inline const IndexC & operator+=(const IntT i);
    // Returns this index added by integer 'i'.

    inline const IndexC & operator-=(const IntT i);
    // Returns this index subtracted by integer 'i'.

    inline const IndexC & operator*=(const IntT i);
    // Returns this index multiplied by integer 'i'.

    inline const IndexC & operator/=(const IntT i);
    // Returns this index divided by integer 'i'.

    inline IndexC operator+(const UIntT i) const;
    // Returns a new index with value of this index added by integer 'i'.

    inline IndexC operator-(const UIntT i) const;
    // Returns a new index with value of this index subtracted by integer 'i'.

    inline IndexC operator*(const UIntT i) const;
    // Returns a new index with value of this index multiplied by integer 'i'.

    inline IndexC operator/(const UIntT i) const;
    // Returns a new index with value of this index divided by integer 'i'.

    inline IndexC operator%(const UIntT i) const;
    // Returns a new index with value of modulo operation between
    // this index and integer 'i'.

    inline IndexC operator%(const IntT i) const;
    // Returns a new index with value of modulo operation between
    // this index and integer 'i'.

    inline const IndexC & operator+=(const UIntT i);
    // Returns this index added by integer 'i'.

    inline const IndexC & operator-=(const UIntT i);
    // Returns this index subtracted by integer 'i'.

    inline const IndexC & operator*=(const UIntT i);
    // Returns this index multiplied by integer 'i'.

    inline const IndexC & operator/=(const UIntT i);
    // Returns this index divided by integer 'i'.

    inline DoubleT operator+(const DoubleT i) const;
    // Returns a new index with value of this index added by double 'i'
    // cut to integer value.

    inline DoubleT operator-(const DoubleT i) const;
    // Returns a new index with value of this index subtracted by double 'i'
    // cut to integer value.

    inline DoubleT operator*(const DoubleT i) const;
    // Returns a new index with value of this index multiplied by double 'i'.
    // The result is cut to integer value and converted to index value.

    inline DoubleT operator/(const DoubleT i) const;
    // Returns a new index with value of this index divided by double 'i'.
    // The result is cut to integer value and converted to index value.

    inline const IndexC & operator+=(const DoubleT i);
    // Returns this index added by double 'i' cut to integer value.

    inline const IndexC & operator-=(const DoubleT i);
    // Returns this index subtracted by double 'i' cut to integer value.

    inline const IndexC & operator*=(const DoubleT i);
    // Returns this index multiplied by double 'i' with the result converted to
    // index value type.

    inline const IndexC & operator/=(const DoubleT i);
    // Returns this index divided by double 'i' with the result converted to
    // index value type.

    inline IndexC operator+(const IndexC & i) const;
    // Returns a new index with value of this index added by the value
    // of index 'i'.

    inline IntT operator-(const IndexC & i) const;
    // Returns a value of this index subtracted by the value
    // of index 'i'.

    inline IndexC operator/(const IndexC & i) const;
    // Returns a new index with value of this index divided by the value
    // of index 'i'.

    inline IndexC operator*(const IndexC & i) const;
    // Returns a new index with value of this index multiplied by the value
    // of index 'i'.

    inline const IndexC & operator+=(const IndexC & i);
    // Returns this index added by index 'i'.

    inline const IndexC & operator-=(const IndexC & i);
    // Returns this index subtracted by index 'i'.

    inline const IndexC & operator*=(const IndexC & i);
    // Returns this index multiplied by index 'i'.

    inline const IndexC & operator/=(const IndexC & i);
    // Returns his index divided by index 'i'.

    // <h2>Modifications of indices:</h2>
    /* ------------------------*/

    inline IndexC operator<<(const IntT i) const;
    // Returns the new index with the value equal to the value of this
    // index shifted 'i' position to the left.

    inline IndexC operator>>(const IntT i) const;
    // Returns the new index with the value equal to the value of this
    // index shifted 'i' position to the right.

    // <h2>Logical operators with integer numbers:</h2>
    /* --------------------------------------*/

    inline BooleanT operator==(const IntT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline BooleanT operator!=(const IntT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline BooleanT operator<(const IntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the integer number 'i'.

    inline BooleanT operator<=(const IntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the integer number 'i'.

    inline BooleanT operator>(const IntT i) const;
    // Returns TRUE if the value of this index is greater than
    // the integer number 'i'.

    inline BooleanT operator>=(const IntT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the integer number 'i'.

    // <h2>Logical operators with unsigned integer numbers:</h2>
    /* -----------------------------------------------*/

    inline BooleanT operator==(const UIntT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline BooleanT operator!=(const UIntT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline BooleanT operator<(const UIntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the integer number 'i'.

    inline BooleanT operator<=(const UIntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the integer number 'i'.

    inline BooleanT operator>(const UIntT i) const;
    // Returns TRUE if the value of this index is greater than
    // the integer number 'i'.

    inline BooleanT operator>=(const UIntT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the integer number 'i'.

    // <h2>Logical operators with double numbers:</h2>
    /* -------------------------------------*/

    inline BooleanT operator==(const DoubleT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline BooleanT operator!=(const DoubleT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline BooleanT operator<(const DoubleT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the double number 'i'.

    inline BooleanT operator<=(const DoubleT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the double number 'i'.

    inline BooleanT operator>(const DoubleT i) const;
    // Returns TRUE if the value of this index is greater than
    // the double number 'i'.

    inline BooleanT operator>=(const DoubleT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the double number 'i'.

    // <h2>Logical operators with another index:</h2>
    /* ------------------------------------*/

    inline BooleanT operator==(const IndexC & i ) const;
    // Returns TRUE if the value of this index and index 'i' have got
    // the same value.

    inline BooleanT operator!=(const IndexC & i ) const;
    // Returns TRUE if the value of this index and index 'i' are different.

    inline BooleanT operator<(const IndexC & i) const;
    // Returns TRUE if the value of this index is smaller than
    // the value of index 'i'.

    inline BooleanT operator<=(const IndexC & i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the value of index 'i'.

    inline BooleanT operator>(const IndexC & i) const;
    // Returns TRUE if the value of this index is greater than
    // the value of index 'i'.

    inline BooleanT operator>=(const IndexC & i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the value of index 'i'.

    // <h2>Miscellaneous functions:</h2>
    /* -------------------------*/

    inline IndexC Abs(void) const;
    // Returns the index whose index value is equal to the absolute value
    // of this index value.

    inline IndexC & SetAbs(void);
    // Returns this index whose index value is equal to the absolute value
    // of the original index value.

    inline IndexC ILog2(void) const;
    // Returns the index which is logarithm of this index value
    // with base 2.
  
    inline IndexC Min(const IndexC & i) const;
    // Returns the index with the smaller value.
  
    inline IndexC Max(const IndexC & i) const;
    // Returns the index with the greater value.
  
    // <h2>Special member functions:</h2>
    /* ------------------------*/
  
    inline UIntT Hash(void) const;
    // Generates a randomised hash value for this index.
  
    inline SizeT Dim(void) const;
    // Returns the number of dimensions indexed.

    inline SizeT GetSize(void) const;
    // This function has no useful meaning


  private:
    /* Object Representation
     * ---------------------*/
    enum {dim = 1};  // number of indexes     
    IntT v; // The value of the index.
};

// I/O operators
// -------------

istream & operator>>(istream & s, IndexC & r);
// Read information from the intput stream 's' and sets the index 'r'
// according obtained data.

ostream & operator<<(ostream & s, const IndexC & r);
// Saves the index 'r' into the output stream 's'.


// Operations of integer numbers and indices
// -----------------------------------------

inline IntT operator+(const IntT i, const IndexC & j);
// Returns the integer number constructed as addition of integer number 'i'
// and index value 'j'.

inline IntT operator-(const IntT i, const IndexC & j);
// Returns the integer number constructed as subtraction of index value 'j'
// from integer number 'i'.

inline IntT operator*(const IntT i, const IndexC & j);
// Returns the integer number constructed as multiplication
// of integer number 'i' and index value 'j'.

inline IntT operator/(const IntT i, const IndexC & j);
// Returns the integer number constructed as division
// of integer number 'i' and index value 'j'.

inline const IntT & operator+=(IntT & i, const IndexC & j);
// Adds index value 'j' to integer number 'i'.

inline const IntT & operator-=(IntT & i, const IndexC & j);
// Subtracts index value 'j' from integer number 'i'.

inline const IntT & operator*=(IntT & i, const IndexC & j);
// Multiplies index value 'j' by integer number 'i'.

inline const IntT & operator/=(IntT & i, const IndexC & j);
// Divides index value 'j' by integer number 'i'.

inline BooleanT operator==(const IntT i, const IndexC & j);
// Returns TRUE if the value of index 'j' is equal to 
// the integer number 'i'.

inline BooleanT operator!=(const IntT i, const IndexC & j);
// Returns TRUE if the values of index 'j' is not equal to 
// the integer number 'i'.

inline BooleanT operator<(const IntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is smaller than  
// the value of index 'j' .

inline BooleanT operator<=(const IntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is smaller than  
// or equal to the value of index 'j' .

inline BooleanT operator>(const IntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is greater than  
// the value of index 'j' .

inline BooleanT operator>=(const IntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is greater than  
// or equal to the value of index 'j' .

// Operations of unsigned integer numbers and indices
// --------------------------------------------------

inline IntT operator+(const UIntT i, const IndexC & j);
// Returns the integer number constructed as addition of integer number 'i'
// and index value 'j'.

inline IntT operator-(const UIntT i, const IndexC & j);
// Returns the integer number constructed as subtraction of index value 'j'
// from integer number 'i'.

inline IntT operator*(const UIntT i, const IndexC & j);
// Returns the integer number constructed as multiplication
// of integer number 'i' and index value 'j'.

inline IntT operator/(const UIntT i, const IndexC & j);
// Returns the integer number constructed as division
// of integer number 'i' and index value 'j'.

inline const UIntT & operator+=(UIntT & i, const IndexC & j);
// Adds index value 'j' to integer number 'i'.

inline const UIntT & operator-=(UIntT & i, const IndexC & j);
// Subtracts index value 'j' from integer number 'i'.

inline const UIntT & operator*=(UIntT & i, const IndexC & j);
// Multiplies index value 'j' by integer number 'i'.

inline const UIntT & operator/=(UIntT & i, const IndexC & j);
// Divides index value 'j' by integer number 'i'.

inline BooleanT operator==(const UIntT i, const IndexC & j);
// Returns TRUE if the value of index 'j' is equal to 
// the integer number 'i'.

inline BooleanT operator!=(const UIntT i, const IndexC & j);
// Returns TRUE if the values of index 'j' is not equal to 
// the integer number 'i'.

inline BooleanT operator<(const UIntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is smaller than  
// the value of index 'j' .

inline BooleanT operator<=(const UIntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is smaller than  
// or equal to the value of index 'j' .

inline BooleanT operator>(const UIntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is greater than  
// the value of index 'j' .

inline BooleanT operator>=(const UIntT i, const IndexC & j);
// Returns TRUE if the integer number 'i' is greater than  
// or equal to the value of index 'j' .

// Operations of byte (unsigned char) numbers and indices
// --------------------------------------------------


inline const ByteT & operator+=(ByteT & i, const IndexC & j);
// Adds index value 'j' to byte number 'i'.

inline const ByteT & operator-=(ByteT & i, const IndexC & j);
// Subtracts index value 'j' from byte number 'i'.

inline const ByteT & operator*=(ByteT & i, const IndexC & j);
// Multiplies index value 'j' by byte number 'i'.

inline const ByteT & operator/=(ByteT & i, const IndexC & j);
// Divides index value 'j' by byte number 'i'.

inline BooleanT operator==(const ByteT i, const IndexC & j);
// Returns TRUE if the value of index 'j' is equal to 
// the byte number 'i'.

inline BooleanT operator!=(const ByteT i, const IndexC & j);
// Returns TRUE if the values of index 'j' is not equal to 
// the byte number 'i'.

inline BooleanT operator<(const ByteT i, const IndexC & j);
// Returns TRUE if the byte number 'i' is smaller than  
// the value of index 'j' .

inline BooleanT operator<=(const ByteT i, const IndexC & j);
// Returns TRUE if the byte number 'i' is smaller than  
// or equal to the value of index 'j' .

inline BooleanT operator>(const ByteT i, const IndexC & j);
// Returns TRUE if the byte number 'i' is greater than  
// the value of index 'j' .

inline BooleanT operator>=(const ByteT i, const IndexC & j);
// Returns TRUE if the byte number 'i' is greater than  
// or equal to the value of index 'j' .

// Operations of double numbers and indices
// ----------------------------------------

inline DoubleT operator+(const DoubleT i, const IndexC & j);
// Returns the double number constructed as addition of double number 'i'
// and index value 'j'.

inline DoubleT operator-(const DoubleT i, const IndexC & j);
// Returns the double number constructed as subtraction of index value 'j'
// from double number 'i'.

inline DoubleT operator*(const DoubleT i, const IndexC & j);
// Returns the double number constructed as multiplication
// of double number 'i' and index value 'j'.

inline DoubleT operator/(const DoubleT i, const IndexC & j);
// Returns the double number constructed as division
// of double number 'i' and index value 'j'.

inline const DoubleT & operator+=(DoubleT & i, const IndexC & j);
// Adds double number 'i' to index value 'j'.

inline const DoubleT & operator-=(DoubleT & i, const IndexC & j);
// Subtracts index value 'j' from double number 'i'.

inline const DoubleT & operator*=(DoubleT & i, const IndexC & j);
// Multiplies index value 'j' by double number 'i'.

inline const DoubleT & operator/=(DoubleT & i, const IndexC & j);
// Divides index value 'j' by double number 'i'.

inline BooleanT operator==(const DoubleT i, const IndexC & j);
// Returns TRUE if the value of index 'j' is equal to 
// the double number 'i'.

inline BooleanT operator!=(const DoubleT i, const IndexC & j);
// Returns TRUE if the values of index 'j' is not equal to 
// the double number 'i'.

inline BooleanT operator<(const DoubleT i, const IndexC & j);
// Returns TRUE if the double number 'i' is smaller than  
// the value of index 'j' .

inline BooleanT operator<=(const DoubleT i, const IndexC & j);
// Returns TRUE if the double number 'i' is smaller than  
// or equal to the value of index 'j' .

inline BooleanT operator>(const DoubleT i, const IndexC & j);
// Returns TRUE if the double number 'i' is greater than  
// the value of index 'j' .

inline BooleanT operator>=(const DoubleT i, const IndexC & j);
// Returns TRUE if the double number 'i' is greater than  
// or equal to the value of index 'j' .

typedef IndexC IndexT;
// General index type.

#include <iostream.h>
#include <stdlib.h> //abs().
#include <math.h> //floor().

//====================================================================
//======= IndexC =====================================================
//====================================================================

inline 
IndexC::IndexC(const IntT i)
//==========================
  : v(i)
{}

inline 
IndexC::IndexC(const SizeT s)
//===========================
  : v((IntT) s)
{}

inline 
IndexC::IndexC(const IndexC & i)
//==============================
  : v(i.v)
{}

inline 
IndexC::IndexC(const DoubleT i)
//==============================
  : v((IntT) floor(i)) // floor is needed for correct round of negative numbers.
{}

inline 
IntT 
IndexC::V(void) const
//===================
{ return v; }

inline 
IntT & 
IndexC::V(void)
//=============
{ return v; }

inline 
BooleanT 
IndexC::IsInRange(SizeT size) const
{ return (UIntT) v < size; }

#if !USE_BUILTIN_BOOL
inline 
IndexC::operator BooleanT() const
//===============================
{ return v!=0; }
#endif

inline 
IndexC::operator bool() const
//===========================
{ return v!=0; }

inline 
IndexC::operator ByteT() const
//============================
{ return (ByteT) v; }

inline 
IndexC::operator CharT() const
//============================
{ return (CharT) v; }

inline 
IndexC::operator SCharT() const
//=============================
{ return (SCharT) v; }

inline 
IndexC::operator FloatT() const
//=============================
{ return (FloatT) v; }

inline 
IndexC::operator DoubleT() const
//==============================
{ return (DoubleT) v; }

inline 
IndexC 
IndexC::operator- () const
//=======================
{ return -v; }

inline 
IndexC & 
IndexC::operator++()
//==================
{
  ++v;
  return *this;
}

inline 
IndexC  
IndexC::operator++(int)
//=====================
{ return v++ ; }

inline 
IndexC & 
IndexC::operator--()
//==================
{
  --v;
  return *this;
}

inline 
IndexC 
IndexC::operator--(int)
//=====================
{ return v--; }

inline 
IndexC 
IndexC::operator+ (const IntT i) const
//===================================
{ return v + i; }

inline 
IndexC 
IndexC::operator- (const IntT i) const
//===================================
{ return v - i; }

inline 
IndexC 
IndexC::operator*(const IntT i) const
//===================================
{ return v * i; }

inline 
IndexC 
IndexC::operator/(const IntT i) const
//===================================
{
  if(i >= 0)
    return (v >= 0) ? (v/i) : (v-i+1)/i;
  return (v <= 0) ? ((-v)/(-i)) : (-v+i+1)/(-i);
}

inline 
IndexC 
IndexC::operator%(const IntT i) const
//===================================
{
  if(i >= 0)
    return (v >= 0) ? (v%i) : (v-i+1)%i;
  return (v <= 0) ? ((-v)%(-i)) : (-v+i+1)%(-i);
}

inline 
const IndexC & 
IndexC::operator+=(const IntT i)
//==============================
{
  v += i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator-=(const IntT i)
//==============================
{
  v -= i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator*=(const IntT i)
//==============================
{
  v *= i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator/=(const IntT i)
//==============================
{
  (*this) = (*this)/i; // Use proper division, defined above.
  return *this;
}

inline 
IndexC 
IndexC::operator+(const UIntT i) const
//===================================
{ return v + i; }

inline 
IndexC 
IndexC::operator-(const UIntT i) const
//===================================
{ return v - i; }

inline 
IndexC 
IndexC::operator*(const UIntT i) const
//====================================
{ return v * i; }

inline 
IndexC 
IndexC::operator/(const UIntT i) const
//====================================
{
  return (v>=0) 
? (v/i) 
: (v-IntT(i)+1)/IntT(i);
}

inline 
IndexC 
IndexC::operator%(const UIntT i) const
//====================================
{ return (v>=0) ? (v%i) : (v-IntT(i)+1)%IntT(i); }

inline 
const IndexC & 
IndexC::operator+=(const UIntT i)
//===============================
{
  v += i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator-=(const UIntT i)
//===============================
{
  v -= i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator*=(const UIntT i)
//===============================
{
  v *= i;
  return *this;
}

inline 
const IndexC & 
IndexC::operator/=(const UIntT i)
//===============================
{
  (*this) = (*this)/i; // Use proper division, see above.
  return *this;
}

inline 
DoubleT 
IndexC::operator+ (const DoubleT i) const
//======================================
{ return (DoubleT) v + i; }

inline 
DoubleT 
IndexC::operator- (const DoubleT i) const
//======================================
{ return (DoubleT) v - i; }

inline 
DoubleT 
IndexC::operator*(const DoubleT i) const
//======================================
{ return (DoubleT) v * i; }

inline 
DoubleT 
IndexC::operator/(const DoubleT i) const
//======================================
{ return (DoubleT) v / i; }

inline 
const IndexC & 
IndexC::operator+=(const DoubleT i)
//=================================
{
  v += IntT(floor(i));
  return *this;
}

inline 
const IndexC & 
IndexC::operator-=(const DoubleT i)
//=================================
{
  v -= IntT(ceil(i));
  return *this;
}

inline 
const IndexC & 
IndexC::operator*=(const DoubleT i)
//=================================
{
  v = IntT(floor(v * i));
  return *this;
}

inline 
const IndexC & 
IndexC::operator/=(const DoubleT i)
//=================================
{
  v = IntT(floor(v / i));
  return *this;
}

inline 
IndexC 
IndexC::operator+(const IndexC & i) const
//=======================================
{ return v+i.v; }

inline 
IntT 
IndexC::operator-(const IndexC & i) const
//=======================================
{ return v-i.v; }

inline 
IndexC 
IndexC::operator*(const IndexC & i) const
//=======================================
{ return v*i.v; }

inline 
IndexC 
IndexC::operator/(const IndexC & i) const
//=======================================
{ return (*this)/i.v; }

inline 
const IndexC & 
IndexC::operator+=(const IndexC & i)
//==================================
{
  v += i.v;
  return *this;
}

inline 
const IndexC & 
IndexC::operator-=(const IndexC & i)
//==================================
{
  v -= i.v;
  return *this;
}

inline 
const IndexC & 
IndexC::operator*=(const IndexC & i)
//==================================
{
  v *= i.v;
  return *this;
}

inline 
const IndexC & 
IndexC::operator/=(const IndexC & i)
//==================================
{
  (*this) = (*this)/i.v;
  return *this;
}

inline 
IndexC 
IndexC::operator<<(const IntT i) const
//====================================
{ return v << i; }

inline 
IndexC 
IndexC::operator>>(const IntT i) const
//====================================
{ return v >> i; }

inline 
BooleanT 
IndexC::operator==(const IntT i ) const
//=====================================
{ return v == i; }

inline 
BooleanT 
IndexC::operator!=(const IntT i ) const
//=====================================
{ return v != i; }

inline 
BooleanT 
IndexC::operator<(const IntT i ) const
//====================================
{ return v < i; }

inline 
BooleanT 
IndexC::operator<=(const IntT i ) const
//=====================================
{ return v <= i; }

inline 
BooleanT 
IndexC::operator>(const IntT i ) const
//====================================
{ return v > i; }

inline 
BooleanT 
IndexC::operator>=(const IntT i ) const
//=====================================
{ return v >= i; }

inline 
BooleanT 
IndexC::operator==(const UIntT i ) const
//=====================================
{ return v == IntT(i); }

inline 
BooleanT 
IndexC::operator!=(const UIntT i ) const
//=====================================
{ return v != IntT(i); }

inline 
BooleanT 
IndexC::operator<(const UIntT i ) const
//====================================
{ return v < IntT(i); }

inline 
BooleanT 
IndexC::operator<=(const UIntT i ) const
//=====================================
{ return v <= IntT(i); }

inline 
BooleanT 
IndexC::operator>(const UIntT i ) const
//====================================
{ return v > IntT(i); }

inline 
BooleanT 
IndexC::operator>=(const UIntT i ) const
//=====================================
{ return v >= IntT(i); }

inline 
BooleanT 
IndexC::operator==(const DoubleT i ) const
//========================================
{ return v == i; }

inline 
BooleanT 
IndexC::operator!=(const DoubleT i ) const
//========================================
{ return v != i; }

inline 
BooleanT 
IndexC::operator<(const DoubleT i ) const
//=======================================
{ return v < i; }

inline 
BooleanT 
IndexC::operator<=(const DoubleT i ) const
//========================================
{ return v <= i; }

inline 
BooleanT 
IndexC::operator>(const DoubleT i ) const
//=======================================
{ return v > i; }

inline 
BooleanT 
IndexC::operator>=(const DoubleT i ) const
//========================================
{ return v >= i; }

inline 
BooleanT 
IndexC::operator==(const IndexC & i ) const
//=========================================
{ return v==i.v; }

inline 
BooleanT 
IndexC::operator!=(const IndexC & i ) const
//=========================================
{ return v!=i.v; }

BooleanT 
IndexC::operator<(const IndexC & i ) const
//========================================
{ return v < i.v; }

BooleanT 
IndexC::operator<=(const IndexC & i ) const
//=========================================
{ return v <= i.v; }

BooleanT 
IndexC::operator>(const IndexC & i ) const
//========================================
{ return v > i.v; }

BooleanT 
IndexC::operator>=(const IndexC & i ) const
//=========================================
{ return v >= i.v; }

inline 
IndexC 
IndexC::Abs(void) const
//=====================
{ return abs(v); }

inline 
IndexC & 
IndexC::SetAbs(void)
//==================
{
  v = abs(v);
  return *this;
}

inline 
IndexC 
IndexC::ILog2(void) const
//=======================
{
  IntT mex = 0;
  IntT i   = v;
  while((i/=2) != 0) mex++;
  return mex;
}

inline 
IndexC 
IndexC::Min(const IndexC & i) const
//=================================
{ return v <= i.v ? *this : i; }

inline 
IndexC 
IndexC::Max(const IndexC & i) const
//=================================
{ return v >= i.v ? *this : i; }

inline 
UIntT 
IndexC::Hash(void) const
//======================
{ return UIntT(v); }

inline 
SizeT 
IndexC::Dim(void) const
//=====================
{ return dim; }

inline 
IntT 
operator+(const IntT i, const IndexC & j)
//=======================================
{ return i+j.V(); }

inline 
IntT 
operator-(const IntT i, const IndexC & j)
//=======================================
{ return i-j.V(); }

inline 
IntT 
operator*(const IntT i, const IndexC & j)
//=======================================
{ return i*j.V(); }

inline 
IntT 
operator/(const IntT i, const IndexC & j)
//=======================================
{ return (IndexT(i)/j).V(); }

inline 
const IntT & 
operator+=(IntT & i, const IndexC & j)
//====================================
{ return i += j.V(); }

inline 
const IntT & 
operator-=(IntT & i, const IndexC & j)
//====================================
{ return i -= j.V(); }

inline 
const IntT & 
operator*=(IntT & i, const IndexC & j)
//====================================
{ return i *= j.V(); }

inline 
const IntT & 
operator/=(IntT & i, const IndexC & j)
//====================================
{
   i = i / j;
  return i;
}

inline 
BooleanT 
operator==(const IntT i, const IndexC & j)
//========================================
{ return i==j.V(); }

inline 
BooleanT 
operator!=(const IntT i, const IndexC & j)
//========================================
{ return i!=j.V(); }

inline 
BooleanT 
operator<(const IntT i, const IndexC & j)
//=======================================
{ return i < j.V(); }

inline 
BooleanT 
operator<=(const IntT i, const IndexC & j)
//=======================================
{ return i <= j.V(); }

inline 
BooleanT 
operator>(const IntT i, const IndexC & j)
//=======================================
{ return i > j.V(); }

inline 
BooleanT 
operator>=(const IntT i, const IndexC & j)
//=======================================
{ return i >= j.V(); }

inline 
IntT 
operator+(const UIntT i, const IndexC & j)
//=======================================
{ return i+j.V(); }

inline 
IntT 
operator-(const UIntT i, const IndexC & j)
//=======================================
{ return i-j.V(); }

inline 
IntT 
operator*(const UIntT i, const IndexC & j)
//=======================================
{ return i*j.V(); }

inline 
IntT 
operator/(const UIntT i, const IndexC & j)
//=======================================
{
  if (j<=0) {
    errAMMA << "Illegal division of unsigned by non-+ve: " << i << " / " << j;
    errAMMA.Function("IntT operator/(const UIntT i, const IndexC & j)")
      .Exit(-1);
  }
  return i/j.V();
}

inline 
const UIntT & 
operator+=(UIntT & i, const IndexC & j)
//====================================
{ return i += j.V(); }

inline 
const UIntT & 
operator-=(UIntT & i, const IndexC & j)
//====================================
{ return i -= j.V(); }

inline 
const UIntT & 
operator*=(UIntT & i, const IndexC & j)
//====================================
{
  return i *= j.V();
}

inline 
const UIntT & 
operator/=(UIntT & i, const IndexC & j)
//====================================
{
  i = i / j;
  return i;
}


inline 
BooleanT 
operator==(const UIntT i, const IndexC & j)
//========================================
{ return IntT(i) == j.V(); }

inline 
BooleanT 
operator!=(const UIntT i, const IndexC & j)
//========================================
{ return IntT(i) != j.V(); }

inline 
BooleanT 
operator<(const UIntT i, const IndexC & j)
//=======================================
{ return IntT(i) < j.V(); }

inline 
BooleanT 
operator<=(const UIntT i, const IndexC & j)
//=======================================
{ return IntT(i) <= j.V(); }

inline 
BooleanT 
operator>(const UIntT i, const IndexC & j)
//=======================================
{ return IntT(i) > j.V(); }

inline 
BooleanT 
operator>=(const UIntT i, const IndexC & j)
//=======================================
{ return IntT(i) >= j.V(); }

// ByteT binary operators omitted, as I don't feel they make much sense (maybe
// wrong)

inline 
const ByteT & 
operator+=(ByteT & i, const IndexC & j)
//====================================
{ return i += j.V(); }

inline 
const ByteT & 
operator-=(ByteT & i, const IndexC & j)
//====================================
{ return i -= j.V(); }

inline 
const ByteT & 
operator*=(ByteT & i, const IndexC & j)
//====================================
{
  return i *= j.V();
}

inline 
const ByteT & 
operator/=(ByteT & i, const IndexC & j)
//====================================
{
  if (j<=0) {
    errAMMA << "Illegal division of unsigned by non-+ve: " << i << " / " << j;
    errAMMA.Function("const ByteT & operator/=(ByteT & i, const IndexC & j))")
      .Exit(-1);
  }
  return i /= j.V();
}


inline 
BooleanT 
operator==(const ByteT i, const IndexC & j)
//========================================
{ return IntT(i) == j.V(); }

inline 
BooleanT 
operator!=(const ByteT i, const IndexC & j)
//========================================
{ return IntT(i) != j.V(); }

inline 
BooleanT 
operator<(const ByteT i, const IndexC & j)
//=======================================
{ return IntT(i) < j.V(); }

inline 
BooleanT 
operator<=(const ByteT i, const IndexC & j)
//=======================================
{ return IntT(i) <= j.V(); }

inline 
BooleanT 
operator>(const ByteT i, const IndexC & j)
//=======================================
{ return IntT(i) > j.V(); }

inline 
BooleanT 
operator>=(const ByteT i, const IndexC & j)
//=======================================
{ return IntT(i) >= j.V(); }


inline 
DoubleT 
operator+(const DoubleT i, const IndexC & j)
//==========================================
{ return i+j.V(); }

inline 
DoubleT 
operator-(const DoubleT i, const IndexC & j)
//==========================================
{ return i-j.V(); }

inline 
DoubleT 
operator*(const DoubleT i, const IndexC & j)
//==========================================
{ return i*j.V(); }

inline 
DoubleT 
operator/(const DoubleT i, const IndexC & j)
//==========================================
{ return i/j.V(); }

inline 
const DoubleT & 
operator+=(DoubleT & i, const IndexC & j)
//=======================================
{ return i += j.V(); }

inline 
const DoubleT & 
operator-=(DoubleT & i, const IndexC & j)
//=======================================
{ return i -= j.V(); }

inline 
const DoubleT & 
operator*=(DoubleT & i, const IndexC & j)
//=======================================
{ return i *= j.V(); }

inline 
const DoubleT & 
operator/=(DoubleT & i, const IndexC & j)
//=======================================
{ return i /= j.V(); }


inline 
BooleanT 
operator==(const DoubleT i, const IndexC & j)
//===========================================
{ return i==j.V(); }

inline 
BooleanT 
operator!=(const DoubleT i, const IndexC & j)
//===========================================
{ return i!=j.V(); }

inline 
BooleanT 
operator<(const DoubleT i, const IndexC & j)
//==========================================
{ return i < j.V(); }

inline 
BooleanT 
operator<=(const DoubleT i, const IndexC & j)
//===========================================
{ return i <= j.V(); }

inline 
BooleanT 
operator>(const DoubleT i, const IndexC & j)
//==========================================
{ return i > j.V(); }

inline 
BooleanT 
operator>=(const DoubleT i, const IndexC & j)
//===========================================
{ return i >= j.V(); }

inline 
SizeT 
IndexC::GetSize(void) const
//=========================
{ return v+1; }

#endif

// IAPS - Image analysis program system.
// End of include file Index.hh
