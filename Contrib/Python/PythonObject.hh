// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
#ifndef RAVL_PYTHONOBJECT_HEADER
#define RAVL_PYTHONOBJECT_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id: Combo.hh 5423 2006-03-20 17:34:52Z robowaz $"
//! file="Ravl/Contrib/Python/PythonObject.hh"
//! lib=RavlPython
//! author="Warren Moore"

#include "Python.h"
#include "Ravl/Python.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"

namespace RavlN
{
  
  class PythonC;

  //! userlevel=normal
  //: Class encapsulating a Python object
  
  class PythonObjectC
  {
  public:
    PythonObjectC(const PythonObjectC &copy);
    //: Copy constructor
    
    ~PythonObjectC();
    //: Destructor
    
    bool IsValid()
    { return m_object != NULL; }
    //: Is the object valid?
    
    PythonObjectC &operator= (const PythonObjectC &rhs);
    //: Assignment
  
    bool BuildInt(const IntT val);
    //: Make the object represent an int
    
    bool BuildInt64(const Int64T val);
    //: Make the object represent a 64-bit int
    
    bool BuildReal(const RealT val);
    //: Make the object represent a real
    
    bool BuildString(const StringC &val);
    //: Make the object represent a string
    
    bool BuildTuple(const DListC<PythonObjectC> &valList);
    //: Make the object represent a list of python objects
    
    bool IsInt();
    //: Does the object represent an int?
    
    IntT Int();
    //: Get the int object value
    
    bool IsInt64();
    //: Does the object represent a 64-bit int?
    
    Int64T Int64();
    //: Get the 64-bit int object value
    
    bool IsReal();
    //: Does the object represent a real?
    
    RealT Real();
    //: Get the real object value
    
    bool IsString();
    //: Does the object represent a string?
    
    StringC String();
    //: Get the string object value
    
    bool IsTuple();
    //: Does the object represent a tuple?
    
    DListC<PythonObjectC> Tuple();
    //: Get the tuple object list
    
  private:
    PythonObjectC();
    //: Constructor
    // Private and undefined as cannot be created without an interpreter handle
    
    PythonObjectC(const PythonC &interpreter, PyObject *object = NULL);
    //: Constructor
    // Construct with an interpreter handle and optionally an existing object
    
    PyObject *GetObject() const
    { return m_object; }
    //: Get the object handle
    
  private:
    PythonC m_interpreter;
    PyObject *m_object;
    
    friend class PythonBodyC;
  };

  
  
}

#endif

