// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLINDEX_HH
#define RAVLINDEX_HH
////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/Index.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik"
//! date="2/1/1996"
//! docentry="Ravl.Core.Indexing"
//! example=exIndex.cc
//! rcsid="$Id$"

#include "Ravl/Types.hh"
#include "Ravl/Assert.hh"
#include "Ravl/Math.hh"

namespace RavlN {
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
  
  class IndexC {
  public:
    // <p><h2>Constructors, copies, assigment, and destructor:</h2>
    /* ----------------------------------------------- */
    
    inline IndexC(IntT i = 0);
    // Creates the index with the value 'i'.
    
    inline IndexC(SizeT s);
    // Creates the index with the same value as the value of size 's'.
    
    inline IndexC(const IndexC & i);
    // Creates the index with the same value as the index 'i' has.
  
    inline IndexC(RealT i);
    // Creates the index with the value rounded version of 'i'.
    
    // <p><h2>Access functions:</h2>
    /* ---------------- */
    
    inline IntT V() const;
    // Returns the current value of the index.
    
    inline IntT & V();
    // Returns the current value of the index.
    
    inline bool IsInRange(SizeT size) const;
    // True if 0 <= this < size
    
    // <p><h2>Conversions:</h2>
    /* ----------- */
    // The obvious conversions from index to integer numbers
    // are missing to avoid automatic conversion of an index expression
    // into integer expression. In this way such a conversion
    // is detected in compilation time and one can decide which
    // type of expression is proper one.
    
    inline operator bool() const;
    // Returns TRUE if the index value is different from 0.
    
    inline operator ByteT() const;
    // Truncates the index value and returns it as ByteT.

#if 0
    inline operator UByteT() const;
    // Truncates the index value and returns it as UByteT.
#endif
    
    inline operator SByteT() const;
    // Truncates the index value and returns it as SByteT.

    inline operator FloatT() const;
    // Converts the index value into float representation.

    inline operator RealT() const;
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

    inline IndexC operator+(IntT i) const;
    // Returns a new index with value of this index added by integer 'i'.

    inline IndexC operator-(IntT i) const;
    // Returns a new index with value of this index subtracted by integer 'i'.

    inline IndexC operator*(IntT i) const;
    // Returns a new index with value of this index multiplied by integer 'i'.

    inline IndexC operator/(IntT i) const;
    // Returns a new index with value of this index divided by integer 'i'.

    inline const IndexC & operator+=(IntT i);
    // Returns this index added by integer 'i'.

    inline const IndexC & operator-=(IntT i);
    // Returns this index subtracted by integer 'i'.

    inline const IndexC & operator*=(IntT i);
    // Returns this index multiplied by integer 'i'.

    inline const IndexC & operator/=(IntT i);
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

    inline IndexC operator%(IntT i) const;
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

    inline RealT operator+(RealT i) const;
    // Returns a new index with value of this index added by double 'i'
    // cut to integer value.

    inline RealT operator-(RealT i) const;
    // Returns a new index with value of this index subtracted by double 'i'
    // cut to integer value.

    inline RealT operator*(RealT i) const;
    // Returns a new index with value of this index multiplied by double 'i'.
    // The result is cut to integer value and converted to index value.

    inline RealT operator/(RealT i) const;
    // Returns a new index with value of this index divided by double 'i'.
    // The result is cut to integer value and converted to index value.

    inline const IndexC & operator+=(RealT i);
    // Returns this index added by double 'i' cut to integer value.

    inline const IndexC & operator-=(RealT i);
    // Returns this index subtracted by double 'i' cut to integer value.

    inline const IndexC & operator*=(RealT i);
    // Returns this index multiplied by double 'i' with the result converted to
    // index value type.

    inline const IndexC & operator/=(RealT i);
    // Returns this index divided by double 'i' with the result converted to
    // index value type.

    inline IndexC operator+(const IndexC & i) const;
    // Returns a new index with value of this index added by the value
    // of index 'i'.

    inline IndexC operator-(const IndexC & i) const;
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

    inline IndexC operator<<(IntT i) const;
    // Returns the new index with the value equal to the value of this
    // index shifted 'i' position to the left.
    
    inline IndexC operator>>(IntT i) const;
    // Returns the new index with the value equal to the value of this
    // index shifted 'i' position to the right.

    // <h2>Logical operators with integer numbers:</h2>
    /* --------------------------------------*/

    inline bool operator==(IntT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline bool operator!=(IntT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline bool operator<(IntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the integer number 'i'.

    inline bool operator<=(IntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the integer number 'i'.

    inline bool operator>(IntT i) const;
    // Returns TRUE if the value of this index is greater than
    // the integer number 'i'.

    inline bool operator>=(IntT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the integer number 'i'.

    // <h2>Logical operators with unsigned integer numbers:</h2>
    /* -----------------------------------------------*/

    inline bool operator==(const UIntT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline bool operator!=(const UIntT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline bool operator<(const UIntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the integer number 'i'.

    inline bool operator<=(const UIntT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the integer number 'i'.

    inline bool operator>(const UIntT i) const;
    // Returns TRUE if the value of this index is greater than
    // the integer number 'i'.

    inline bool operator>=(const UIntT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the integer number 'i'.

    // <h2>Logical operators with double numbers:</h2>
    /* -------------------------------------*/

    inline bool operator==(RealT i ) const;
    // Returns TRUE if the value of this index is equal to 
    // the integer number 'i'.

    inline bool operator!=(RealT i ) const;
    // Returns TRUE if the value of this index is not equal to 
    // the integer number 'i'.

    inline bool operator<(RealT i) const;
    // Returns TRUE if the value of this index is smaller than
    // the double number 'i'.

    inline bool operator<=(RealT i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the double number 'i'.

    inline bool operator>(RealT i) const;
    // Returns TRUE if the value of this index is greater than
    // the double number 'i'.

    inline bool operator>=(RealT i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the double number 'i'.

    // <h2>Logical operators with another index:</h2>
    /* ------------------------------------*/

    inline bool operator==(const IndexC & i ) const;
    // Returns TRUE if the value of this index and index 'i' have got
    // the same value.

    inline bool operator!=(const IndexC & i ) const;
    // Returns TRUE if the value of this index and index 'i' are different.

    inline bool operator<(const IndexC & i) const;
    // Returns TRUE if the value of this index is smaller than
    // the value of index 'i'.

    inline bool operator<=(const IndexC & i) const;
    // Returns TRUE if the value of this index is smaller than
    // or equal to the value of index 'i'.

    inline bool operator>(const IndexC & i) const;
    // Returns TRUE if the value of this index is greater than
    // the value of index 'i'.

    inline bool operator>=(const IndexC & i) const;
    // Returns TRUE if the value of this index is greater than
    // or equal to the value of index 'i'.

    // <h2>Miscellaneous functions:</h2>
    /* -------------------------*/

    inline IndexC Abs() const;
    // Returns the index whose index value is equal to the absolute value
    // of this index value.

    inline IndexC & SetAbs();
    // Returns this index whose index value is equal to the absolute value
    // of the original index value.

    inline IndexC ILog2() const;
    // Returns the index which is logarithm of this index value
    // with base 2.
  
    inline IndexC Min(const IndexC & i) const;
    // Returns the index with the smaller value.
  
    inline IndexC Max(const IndexC & i) const;
    // Returns the index with the greater value.
  
    // <h2>Special member functions:</h2>
    /* ------------------------*/
  
    inline UIntT Hash() const;
    // Generates a randomised hash value for this index.
  
    inline SizeT Size() const;
    // Returns the number of dimensions indexed.
    

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
  
  inline IndexC operator+(IntT i, const IndexC & j)
  { return i+j.V(); }
  
  // Returns the integer number constructed as addition of integer number 'i'
  // and index value 'j'.
  
  inline IndexC operator-(IntT i, const IndexC & j)
  { return i-j.V(); }
  // Returns the integer number constructed as subtraction of index value 'j'
  // from integer number 'i'.
  
  inline IndexC operator*(IntT i, const IndexC & j)
  { return i*j.V(); }
  // Returns the integer number constructed as multiplication
  // of integer number 'i' and index value 'j'.
  
  inline IndexC operator/(IntT i, const IndexC & j)
  { return (IndexC(i)/j); }
  // Returns the integer number constructed as division
  // of integer number 'i' and index value 'j'.
  
  inline const IntT & operator+=(IntT & i, const IndexC & j)
  { return i += j.V(); }
  // Adds index value 'j' to integer number 'i'.
  
  inline const IntT & operator-=(IntT & i, const IndexC & j)
  { return i -= j.V(); }
  // Subtracts index value 'j' from integer number 'i'.
  
  inline const IntT & operator*=(IntT & i, const IndexC & j)
  { return i *= j.V(); }
  // Multiplies index value 'j' by integer number 'i'.
  
  inline const IntT & operator/=(IntT & i, const IndexC & j) {
    i = (i / j).V();
    return i;
  }
  // Divides index value 'j' by integer number 'i'.
  
  inline bool operator==(IntT i, const IndexC & j)
  { return i==j.V(); }
  // Returns TRUE if the value of index 'j' is equal to 
  // the integer number 'i'.
  
  inline bool operator!=(IntT i, const IndexC & j)
  { return i!=j.V(); }
  // Returns TRUE if the values of index 'j' is not equal to 
  // the integer number 'i'.
  
  inline bool operator<(IntT i, const IndexC & j)
  { return i < j.V(); }
  // Returns TRUE if the integer number 'i' is smaller than  
  // the value of index 'j' .
  
  inline bool operator<=(IntT i, const IndexC & j)
  { return i <= j.V(); }
  // Returns TRUE if the integer number 'i' is smaller than  
  // or equal to the value of index 'j' .
  
  inline bool operator>(IntT i, const IndexC & j)
  { return i > j.V(); }
  // Returns TRUE if the integer number 'i' is greater than  
  // the value of index 'j' .
  
  inline bool operator>=(IntT i, const IndexC & j)
  { return i >= j.V(); }
  // Returns TRUE if the integer number 'i' is greater than  
  // or equal to the value of index 'j' .
  
  // Operations of unsigned integer numbers and indices
  // --------------------------------------------------
  
  inline IndexC operator+(const UIntT i, const IndexC & j)
  { return IndexC(i+j.V()); }
  // Returns the integer number constructed as addition of integer number 'i'
  // and index value 'j'.
  
  inline IndexC operator-(const UIntT i, const IndexC & j)
  { return IndexC(i-j.V()); }
  // Returns the integer number constructed as subtraction of index value 'j'
  // from integer number 'i'.
  
  inline IndexC operator*(const UIntT i, const IndexC & j)
  { return IndexC(i*j.V()); }
  // Returns the integer number constructed as multiplication
  // of integer number 'i' and index value 'j'.
  
  inline IndexC operator/(const UIntT i, const IndexC & j) {
    RavlAssertMsg(j>0,
		  "Illegal division of unsigned by non-+ve.\n" 
		  "In function: IntT operator/(const UIntT i, const IndexC & j)");
    return i/j.V();
  }
  // Returns the integer number constructed as division
  // of integer number 'i' and index value 'j'.
  
  inline const UIntT & operator+=(UIntT & i, const IndexC & j) 
  { return i += j.V(); }
  // Adds index value 'j' to integer number 'i'.

  inline const UIntT & operator-=(UIntT & i, const IndexC & j)
  { return i -= j.V(); }
  // Subtracts index value 'j' from integer number 'i'.
  
  inline const UIntT & operator*=(UIntT & i, const IndexC & j)
  { return i *= j.V(); }
  // Multiplies index value 'j' by integer number 'i'.
  
  inline const UIntT & operator/=(UIntT & i, const IndexC & j){
    i = (i / j).V();
    return i;
  }
  // Divides index value 'j' by integer number 'i'.
  
  inline bool operator==(const UIntT i, const IndexC & j)
  { return IntT(i) == j.V(); }
  // Returns TRUE if the value of index 'j' is equal to 
  // the integer number 'i'.
  
  inline bool operator!=(const UIntT i, const IndexC & j)
  { return IntT(i) != j.V(); }
  // Returns TRUE if the values of index 'j' is not equal to 
  // the integer number 'i'.
  
  inline bool operator<(const UIntT i, const IndexC & j)
  { return IntT(i) < j.V(); }
  // Returns TRUE if the integer number 'i' is smaller than  
  // the value of index 'j' .
  
  inline bool operator<=(const UIntT i, const IndexC & j)
  { return IntT(i) <= j.V(); }
  // Returns TRUE if the integer number 'i' is smaller than  
  // or equal to the value of index 'j' .
  
  inline bool operator>(const UIntT i, const IndexC & j)
  { return IntT(i) > j.V(); }
  // Returns TRUE if the integer number 'i' is greater than  
  // the value of index 'j' .
  
  inline bool operator>=(const UIntT i, const IndexC & j)
  { return IntT(i) >= j.V(); }
  // Returns TRUE if the integer number 'i' is greater than  
  // or equal to the value of index 'j' .
  
  // Operations of byte (unsigned char) numbers and indices
  // --------------------------------------------------
  // ByteT binary operators omitted, as I don't feel they make much sense (maybe
  // wrong)
  
  
  inline const UByteT & operator+=(UByteT & i, const IndexC & j)
  { return i += j.V(); }
  // Adds index value 'j' to byte number 'i'.
  
  inline const UByteT & operator-=(UByteT & i, const IndexC & j)
  { return i -= j.V(); }
  // Subtracts index value 'j' from byte number 'i'.
  
  inline const UByteT & operator*=(UByteT & i, const IndexC & j)
  { return i *= j.V(); }
  // Multiplies index value 'j' by byte number 'i'.
  
  inline const UByteT & operator/=(UByteT & i, const IndexC & j) {
    RavlAssertMsg(j>0,
		  "Illegal division of unsigned by non-+ve\n"
		  "const UByteT & operator/=(UByteT & i, const IndexC & j))");
    return i /= j.V();
  }
  // Divides index value 'j' by byte number 'i'.
  
  inline bool operator==(const UByteT i, const IndexC & j)
  { return IntT(i) == j.V(); }
  // Returns TRUE if the value of index 'j' is equal to 
  // the byte number 'i'.
  
  inline bool operator!=(const UByteT i, const IndexC & j)
  { return IntT(i) != j.V(); }
  // Returns TRUE if the values of index 'j' is not equal to 
  // the byte number 'i'.
  
  inline bool operator<(const UByteT i, const IndexC & j)
  { return IntT(i) < j.V(); }
  // Returns TRUE if the byte number 'i' is smaller than  
  // the value of index 'j' .
  
  inline bool operator<=(const UByteT i, const IndexC & j)
  { return IntT(i) <= j.V(); }
  // Returns TRUE if the byte number 'i' is smaller than  
  // or equal to the value of index 'j' .
  
  inline bool operator>(const UByteT i, const IndexC & j)
  { return IntT(i) > j.V(); }
  // Returns TRUE if the byte number 'i' is greater than  
  // the value of index 'j' .
  
  inline bool operator>=(const UByteT i, const IndexC & j)
  { return IntT(i) >= j.V(); }
  // Returns TRUE if the byte number 'i' is greater than  
  // or equal to the value of index 'j' .
  
  // Operations of double numbers and indices
  // ----------------------------------------
  
  inline RealT operator+(RealT i, const IndexC & j)
  { return i+j.V(); }
  // Returns the double number constructed as addition of double number 'i'
  // and index value 'j'.
  
  inline RealT operator-(RealT i, const IndexC & j)
  { return i-j.V(); }
  // Returns the double number constructed as subtraction of index value 'j'
  // from double number 'i'.
  
  inline RealT operator*(RealT i, const IndexC & j)
  { return i*j.V(); }
  // Returns the double number constructed as multiplication
  // of double number 'i' and index value 'j'.
  
  inline RealT operator/(RealT i, const IndexC & j)
  { return i/j.V(); }
  // Returns the double number constructed as division
  // of double number 'i' and index value 'j'.
  
  inline const RealT & operator+=(RealT & i, const IndexC & j)
  { return i += j.V(); }
  // Adds double number 'i' to index value 'j'.
  
  inline const RealT & operator-=(RealT & i, const IndexC & j)
  { return i -= j.V(); }
  // Subtracts index value 'j' from double number 'i'.
  
  inline const RealT & operator*=(RealT & i, const IndexC & j)
  { return i *= j.V(); }
  // Multiplies index value 'j' by double number 'i'.
  
  inline const RealT & operator/=(RealT & i, const IndexC & j)
  { return i /= j.V(); }
  // Divides index value 'j' by double number 'i'.
  
  inline bool operator==(RealT i, const IndexC & j)
  { return i==j.V(); }
  // Returns TRUE if the value of index 'j' is equal to 
  // the double number 'i'.
  
  inline bool operator!=(RealT i, const IndexC & j)
  { return i!=j.V(); }
  // Returns TRUE if the values of index 'j' is not equal to 
  // the double number 'i'.
  
  inline bool operator<(RealT i, const IndexC & j)
  { return i < j.V(); }
  // Returns TRUE if the double number 'i' is smaller than  
  // the value of index 'j' .
  
  inline bool operator<=(RealT i, const IndexC & j)
  { return i <= j.V(); }
  // Returns TRUE if the double number 'i' is smaller than  
  // or equal to the value of index 'j' .
  
  inline bool operator>(RealT i, const IndexC & j)
  { return i > j.V(); }
  // Returns TRUE if the double number 'i' is greater than  
  // the value of index 'j' .
  
  inline bool operator>=(RealT i, const IndexC & j)
  { return i >= j.V(); }
  // Returns TRUE if the double number 'i' is greater than  
  // or equal to the value of index 'j' .
  
  inline 
  IndexC::IndexC(IntT i)
    : v(i)
  {}
  
  inline 
  IndexC::IndexC(SizeT s)
    : v((IntT) s)
  {}
  
  inline 
  IndexC::IndexC(const IndexC & i)
    : v(i.v)
  {}

  inline 
  IndexC::IndexC(RealT i)
    : v((IntT) RavlN::Floor(i)) // floor is needed for correct round of negative numbers.
  {}
  
  inline 
  IntT 
  IndexC::V() const
  { return v; }
  
  inline 
  IntT & 
  IndexC::V()
  { return v; }

  inline 
  bool 
  IndexC::IsInRange(SizeT size) const
  { return (UIntT) v < size; }
  
  inline 
  IndexC::operator bool() const
  { return v!=0; }

#if 0  
  inline 
  IndexC::operator UByteT() const
  { return (UByteT) v; }
#endif
  
  inline 
  IndexC::operator ByteT() const
  { return (ByteT) v; }
  
  inline 
  IndexC::operator SByteT() const
  { return (SByteT) v; }
  
  inline 
  IndexC::operator FloatT() const
  { return (FloatT) v; }

  inline 
  IndexC::operator RealT() const
  { return (RealT) v; }

  inline 
  IndexC 
  IndexC::operator- () const
  { return -v; }
  
  inline 
  IndexC & 
  IndexC::operator++() {
    ++v;
    return *this;
  }
  
  inline 
  IndexC  
  IndexC::operator++(int)
  { return v++ ; }

  inline 
  IndexC & 
  IndexC::operator--() {
    --v;
    return *this;
  }
  
  inline 
  IndexC 
  IndexC::operator--(int)
  { return v--; }
  
  inline 
  IndexC 
  IndexC::operator+ (IntT i) const
  { return v + i; }
  
  inline 
  IndexC 
  IndexC::operator- (IntT i) const
  { return v - i; }
  
  inline 
  IndexC 
  IndexC::operator*(IntT i) const
  { return v * i; }
   
  inline 
  IndexC 
  IndexC::operator/(IntT i) const {
    if(i >= 0)
      return (v >= 0) ? (v/i) : (v-i+1)/i;
    return (v <= 0) ? ((-v)/(-i)) : (-v+i+1)/(-i);
  }
  
  inline 
  IndexC 
  IndexC::operator%(IntT i) const {
    if(i >= 0)
      return (v >= 0) ? (v%i) : (v-i+1)%i;
    return (v <= 0) ? ((-v)%(-i)) : (-v+i+1)%(-i);
  }
  
  inline 
  const IndexC & IndexC::operator+=(IntT i) {
    v += i;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator-=(IntT i) {
    v -= i;
    return *this;
  }

  inline 
  const IndexC & IndexC::operator*=(IntT i) {
    v *= i;
    return *this;
  }

  inline 
  const IndexC & IndexC::operator/=(IntT i) {
    (*this) = (*this)/i; // Use proper division, defined above.
    return *this;
  }

  inline 
  IndexC IndexC::operator+(const UIntT i) const
  { return v + i; }

  inline 
  IndexC IndexC::operator-(const UIntT i) const
  { return v - i; }

  inline 
  IndexC IndexC::operator*(const UIntT i) const
  { return v * i; }
  
  inline 
  IndexC IndexC::operator/(const UIntT i) const {
    return (v>=0) 
      ? (v/i) 
      : (v-IntT(i)+1)/IntT(i);
  }
  
  inline 
  IndexC IndexC::operator%(const UIntT i) const
  { return (v>=0) ? (v%i) : (v-IntT(i)+1)%IntT(i); }

  inline 
  const IndexC & IndexC::operator+=(const UIntT i) {
    v += i;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator-=(const UIntT i) {
    v -= i;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator*=(const UIntT i) {
    v *= i;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator/=(const UIntT i) {
    (*this) = (*this)/i; // Use proper division, see above.
    return *this;
  }

  inline 
  RealT IndexC::operator+ (RealT i) const
  { return (RealT) v + i; }

  inline 
  RealT IndexC::operator- (RealT i) const
  { return (RealT) v - i; }
  
  inline 
  RealT IndexC::operator*(RealT i) const
  { return (RealT) v * i; }

  inline 
  RealT IndexC::operator/(RealT i) const
  { return (RealT) v / i; }
  
  inline 
  const IndexC & IndexC::operator+=(RealT i) {
    v += IntT(RavlN::Floor(i));
  return *this;
  }
  
  inline 
  const IndexC & IndexC::operator-=(RealT i) {
    v -= IntT(ceil(i));
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator*=(RealT i) {
    v = IntT(RavlN::Floor(v * i));
    return *this;
  }

  inline 
  const IndexC & IndexC::operator/=(RealT i) {
    v = IntT(RavlN::Floor(v / i));
    return *this;
  }
  
  inline 
  IndexC IndexC::operator+(const IndexC & i) const  
  { return v+i.v; }

  inline 
  IndexC IndexC::operator-(const IndexC & i) const
  { return v-i.v; }

  inline 
  IndexC 
  IndexC::operator*(const IndexC & i) const
  { return v*i.v; }

  inline 
  IndexC 
  IndexC::operator/(const IndexC & i) const
  { return (*this)/i.v; }

  inline 
  const IndexC & IndexC::operator+=(const IndexC & i) {
    v += i.v;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator-=(const IndexC & i) {
    v -= i.v;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator*=(const IndexC & i) {
    v *= i.v;
    return *this;
  }
  
  inline 
  const IndexC & IndexC::operator/=(const IndexC & i) {
    (*this) = (*this)/i.v;
    return *this;
  }
  
  inline 
  IndexC IndexC::operator<<(IntT i) const
  { return v << i; }
  
  inline 
  IndexC IndexC::operator>>(IntT i) const
  { return v >> i; }
  
  inline 
  bool IndexC::operator==(IntT i ) const
  { return v == i; }

  inline 
  bool IndexC::operator!=(IntT i ) const
  { return v != i; }
  
  inline 
  bool IndexC::operator<(IntT i ) const
  { return v < i; }

  inline 
  bool 
  IndexC::operator<=(IntT i ) const
  { return v <= i; }

  inline 
  bool 
  IndexC::operator>(IntT i ) const
  { return v > i; }
  
  inline 
  bool 
  IndexC::operator>=(IntT i ) const
  { return v >= i; }
  
  inline 
  bool 
  IndexC::operator==(const UIntT i ) const
  { return v == IntT(i); }
  
  inline 
  bool 
  IndexC::operator!=(const UIntT i ) const
  { return v != IntT(i); }
  
  inline 
  bool 
  IndexC::operator<(const UIntT i ) const
  { return v < IntT(i); }

  inline 
  bool 
  IndexC::operator<=(const UIntT i ) const
  { return v <= IntT(i); }
  
  inline 
  bool 
  IndexC::operator>(const UIntT i ) const
  { return v > IntT(i); }
  
  inline 
  bool 
  IndexC::operator>=(const UIntT i ) const
  { return v >= IntT(i); }

  inline 
  bool 
  IndexC::operator==(RealT i ) const
  { return v == i; }

  inline 
  bool 
  IndexC::operator!=(RealT i ) const
  { return v != i; }

  inline 
  bool 
  IndexC::operator<(RealT i ) const
  { return v < i; }
  
  inline 
  bool 
  IndexC::operator<=(RealT i ) const
  { return v <= i; }

  inline 
  bool 
  IndexC::operator>(RealT i ) const
  { return v > i; }

  inline 
  bool
  IndexC::operator>=(RealT i ) const
  { return v >= i; }

  inline 
  bool 
  IndexC::operator==(const IndexC & i ) const
  { return v==i.v; }
  
  inline 
  bool 
  IndexC::operator!=(const IndexC & i ) const
  { return v!=i.v; }

  bool 
  IndexC::operator<(const IndexC & i ) const
  { return v < i.v; }

  bool 
  IndexC::operator<=(const IndexC & i ) const
  { return v <= i.v; }

  bool 
  IndexC::operator>(const IndexC & i ) const
  { return v > i.v; }
  
  bool 
  IndexC::operator>=(const IndexC & i ) const
  { return v >= i.v; }

  inline 
  IndexC 
  IndexC::Abs() const
  { return RavlN::Abs(v); }

  inline 
  IndexC & 
  IndexC::SetAbs() {
    v = RavlN::Abs(v);
    return *this;
  }
  
  inline 
  IndexC 
    IndexC::ILog2() const {
    IntT mex = 0;
    IntT i   = v;
    while((i/=2) != 0) mex++;
    return mex;
  }

  inline 
  IndexC 
  IndexC::Min(const IndexC & i) const
  { return v <= i.v ? *this : i; }

  inline 
  IndexC 
  IndexC::Max(const IndexC & i) const
  { return v >= i.v ? *this : i; }

  inline 
  UIntT 
  IndexC::Hash() const
  { return UIntT(v); }

  inline 
  SizeT 
  IndexC::Size() const
  { return dim; }


}

#endif

// IAPS - Image analysis program system.
// End of include file Index.hh
