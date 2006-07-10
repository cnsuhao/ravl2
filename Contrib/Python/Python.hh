// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the MIT
// License. See http://www.opensource.org/licenses/mit-license.html
// file-header-ends-here
#ifndef RAVL_PYTHON_HEADER
#define RAVL_PYTHON_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id: Combo.hh 5423 2006-03-20 17:34:52Z robowaz $"
//! file="Ravl/Contrib/Python/Python.hh"
//! lib=RavlPython
//! author="Warren Moore"

#include "Python.h"
#include "Ravl/RefCounter.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/Hash.hh"

namespace RavlN
{

  //! userlevel=develop
  //: Class managing a Python interpreter
  
  class PythonBodyC :
    public RCBodyC
  {
  public:
    PythonBodyC();
    //: Constructor
    
    ~PythonBodyC();
    //: Destructor
    
    void AppendSystemPath(const StringC &path);
    //: Append a string to 'sys.path'
    
    bool Import(const StringC &module);
    //: Load a module using Python 'import' notation
    
    PythonObjectC Call(const StringC &module, const StringC &name, PythonObjectC args = PythonObjectC());
    //: Call a function with arguments
    //!param: args - Must represent a tuple containing all the required arguments
    // Returns an invalid object on failure
    
    bool Run(const StringC &script);
    //: Load a Python script into the main environment and execute immediately
    // Has no access to modules loaded through PythonC::Import
    
    PythonObjectC GetGlobal(const StringC &name);
    //: Get a result object called 'name' from the globals
    
  private:
    PyObject *GetModuleDictionary(const StringC &name);
    //: Get a dictionary from the named module, NULL if none
    
  private:
    PyGILState_STATE m_lock;
    HashC<StringC, PyObject*> m_modules;
  };
  
  //! userlevel=normal
  //: Class containing a Python interpreter
  
  class PythonC :
    public RCHandleC<PythonBodyC>
  {
  public:
    PythonC();
    //: Default constructor
    // Creates an invalid handle
    
    PythonC(bool) :
      RCHandleC<PythonBodyC>(*new PythonBodyC())
    {}
    //: Constructor
    
    void AppendSystemPath(const StringC &path)
    { Body().AppendSystemPath(path); }
    //: Append a string to 'sys.path'
    
    bool Import(const StringC &module)
    { return Body().Import(module); }
    //: Load a module using Python 'import' notation
    
    PythonObjectC Call(const StringC &module, const StringC &name, PythonObjectC args = PythonObjectC())
    { return Body().Call(module, name, args); }
    //: Call a function with arguments
    //!param: args - Must represent a tuple containing all the required arguments
    // Returns an invalid object on failure
    
    bool Run(const StringC &script)
    { return Body().Run(script); }
    //: Load a Python script into the main environment and execute immediately
    // Note: has no access to modules loaded through PythonC::Import
    
    PythonObjectC GetGlobal(const StringC &name)
    { return Body().GetGlobal(name); }
    //: Get a result object called 'name' from the globals
    
  private:
    PythonC(PythonBodyC &body) : 
      RCHandleC<PythonBodyC>(body)
    {}
    //: Body constructor. 
    
    PythonBodyC& Body()
    { return static_cast<PythonBodyC &>(RCHandleC<PythonBodyC>::Body()); }
    //: Body Access. 
    
    const PythonBodyC& Body() const
    { return static_cast<const PythonBodyC &>(RCHandleC<PythonBodyC>::Body()); }
    //: Body Access. 
  };

  
  
}

#endif

