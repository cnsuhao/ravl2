// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_EXCEPTION_HEADER
#define RAVL_EXCEPTION_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id: Exception.hh 7460 2010-01-07 13:30:17Z omn-crida $"
//! docentry="Ravl.API.Core.Error Handling"
//! file="Ravl/Core/Base/Exception.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Types.hh"
#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif

namespace RavlN {
#if RAVL_HAVE_STDNAMESPACE
  using namespace std;
#endif

  //: RAVL Exception.
  // Base class for Ravl's exceptions. <P>

  class ExceptionC {
  public:
    ExceptionC(const char *ntext)
      : desc(ntext),
      ref(false)
      {}
    //: Constructor

    ExceptionC(const char *ntext,bool copy);
    //: Constructor.
    // Copy string if 'copy' is true.

    ExceptionC(const ExceptionC &oth)
      : desc(oth.desc),
      ref(oth.ref)
      {
	if(oth.ref)
	  const_cast<ExceptionC &>(oth).ref = false;
      }
    //: Copy Constructor
    // This assumes the only time you use a copy constructor
    // on an exception is when passing it as an argument!

    virtual ~ExceptionC();
    //: Virtualise destructor.

    const char *Text() const { return desc; }
    //: Get error description.

    virtual void Dump(ostream &strm);
    //: Dump contents of exception to strm;

    const char *what() const { return desc; }
    //: Standard exception text message.
  protected:
    const char *desc;
    bool ref; // Delete string in constructor ?
  };

  //: Casting exception class.
  // Thrown when an illegal cast is attempted.

  class ExceptionErrorCastC : public ExceptionC {
  public:
    ExceptionErrorCastC(const char *ndesc,const type_info &nfrom,const type_info &nto)
      : ExceptionC(ndesc),
      from(nfrom),
      to(nto)
      {}
    //: Constructor.

    const type_info &From() const { return from; }
    //: Cast from.

    const type_info &To() const { return to; }
    //: Cast to.

    virtual void Dump();
    //: Dump contents of exception to cerr;
  protected:
    const type_info &from;
    const type_info &to;
  };

  //: Exception: Operation Failed
  // Thrown if a requested operation failed because of
  // conditions outside the programs control. (Such as running
  // out of disk space.)

  class ExceptionOperationFailedC : public ExceptionC {
  public:
    ExceptionOperationFailedC(const char *ndesc)
      : ExceptionC(ndesc)
      {}
    //: Constructor.

    ExceptionOperationFailedC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
  // if copy is true, a copy is made of string ntext.
  };

  //: Exception: Bad Configuration
  // Exception indicating problem loading a configuration.

  class ExceptionBadConfigC : public ExceptionC {
  public:
    ExceptionBadConfigC(const char *ndesc)
      : ExceptionC(ndesc)
      {}
    //: Constructor.

    ExceptionBadConfigC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
  // if copy is true, a copy is made of string ntext.
  };

  //: Exception: Out of Range
  // Thrown if an operation in someway exceeds the allowed value.
  // Examples: Access outside the range of an array, or
  // one to many pop's from a stack

  class ExceptionOutOfRangeC : public ExceptionC {
  public:
    ExceptionOutOfRangeC(const char *ndesc)
      : ExceptionC(ndesc)
      {}
    //: Constructor.

    ExceptionOutOfRangeC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
    // if copy is true, a copy is made of string ntext.
  };


  //: Exception: Assertion Failed
  // Thrown if an assertion failed during the running of the program.
  // these should only be thrown if an internal inconsitancy
  // has been detected.

  class ExceptionAssertionFailedC : public ExceptionC {
  public:
    ExceptionAssertionFailedC(const char *ndesc)
      : ExceptionC(ndesc)
      {}
    //: Constructor.

    ExceptionAssertionFailedC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
  // if copy is true, a copy is made of string ntext.
  };

  //: Exception: Numerical exception.
  // May be thrown where an operation failes for
  // a numerical reason, such as taking the Sqrt(-1) or
  // inverting a singular matrix.

  class ExceptionNumericalC : public ExceptionC {
  public:
    ExceptionNumericalC(const char *ndesc)
      : ExceptionC(ndesc)
      {}
    //: Constructor.

    ExceptionNumericalC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
    // if copy is true, a copy is made of string ntext.
  };

  //! userlevel=Normal
  //: Exception thrown when end of stream found.

  class ExceptionEndOfStreamC
    : public ExceptionC
  {
  public:
    ExceptionEndOfStreamC(const char *ntext)
      : ExceptionC(ntext)
      {}
    //: Constructor

    ExceptionEndOfStreamC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
    // if copy is true, make a copy of ntext.
  };


}



#endif
