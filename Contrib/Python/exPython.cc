// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// Python is used under the terms of the Python License 
// Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! file = "Ravl/Contrib/Python/exPython.cc"
//! lib = RavlPython
//! author = "Warren Moore"

#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/PythonException.hh"
#include "Ravl/String.hh"

using namespace RavlN;

void displayError(const char *errorMessage)
{
  cerr << "#### Error" << endl;
  cerr << "## " << errorMessage << endl;
}

void displayException(PythonExceptionC &e)
{
  cerr << "#### Error" << endl;
  cerr << "##  Type:  " << e.Type() << endl;
  cerr << "##  Value: " << e.Value() << endl;
  cerr << "##  Trace: " << endl << e.Trace() << endl;
}

int main(int argc, char **argv)
{
  try 
  {
    // Initialise the python module
    PythonC python(true);

    cerr << "Initialising interpreter" << endl;
    if (!python.Initialised())
    {
      displayError("Failed to initialise interpreter");
      return -1;
    }

    cerr << "Appending '.' to system path" << endl;
    if (!python.AppendSystemPath("."))
    {
      displayError("Failed to append system path");
      return -1;
    }
  
  	cerr << "Importing 'ravlexample'" <<endl;
  	if (!python.Import("ravlexample"))
    {
      displayError("Failed to import 'ravlexample'");
      return -1;
    }
  
	  // Build the arguments list
	  PythonObjectC name = python.NewObject();
	  name.BuildString("your-name-here");
    
	  DListC<PythonObjectC> argList;
	  argList.InsLast(name);
	  PythonObjectC args = python.NewObject();
	  args.BuildTuple(argList);
  
	  // Call the example function and display the results
	  cerr << "Calling 'ravlexample.myprint(" << name.String() << ")'" << endl;
	  PythonObjectC res = python.Call("ravlexample", "myprint", args);
	  if (res.IsValid())
	  {
	    if (res.IsString())
      {
	      cerr << "Result(string): " << res.String() << endl;
      }
      else
      {
        displayError("'ravlexample.myprint' did not return a string");
        return -1;
      }
	  }
    else
    {
      displayError("Failed to call 'ravlexample.myprint'");
      return -1;
    }
     
	  // Run a script from a string
	  const char* script = "print 'hello again'\nx = 5";
	  cerr << "Calling script from string" << endl;
    if (python.Run(script))
    {
      // Read the globals from the script
      PythonObjectC x = python.GetGlobal("x");
      cerr << "Found 'x': " << (x.IsValid() ? "YES" : "NO") << endl;
      if (x.IsValid())
      {  
        if (x.IsInt())
        {
          cerr << "'x'= " << x.Int() << endl;
        }
        else
        {
          cerr << "'x' is not an int" << endl;
        }
      }
    }
    else
    {
      displayError("Failed to run script from string");
      return -1;
    }
  }
  catch (PythonExceptionC &e)
  {
    displayException(e);
  	return -1;
  }

  return 0;
}
