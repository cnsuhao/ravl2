// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// Python is used under the terms of the Python License 
// Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! file = "Ravl/Contrib/Python/exPythonThreaded.cc"
//! lib = RavlPython
//! author = "Warren Moore"
//! docentry = "Ravl.API.Python"

#include "Ravl/Option.hh"
#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/PythonException.hh"
#include "Ravl/String.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN;

void displayError(const IntT num, const char *errorMessage)
{
  cerr << "#### Error" << endl;
  cerr << "## " << errorMessage << endl;
}

void displayException(const IntT num, PythonExceptionC &e)
{
  cerr << "#### Error" << endl;
  cerr << "##  Type:  " << e.Type() << endl;
  cerr << "##  Value: " << e.Value() << endl;
  cerr << "##  Trace: " << endl << e.Trace() << endl;
}

bool startThread(const IntT num)
{
  try
  {
    PythonC python(true);

    // Initialise the python module
    if (!python.AppendSystemPath("."))
    {
      displayError(num, "Failed to append system path");
      return false;
    }

    // Import a module
    cerr << "(" << num << ") Importing 'ravlexample'" << endl;
    if (!python.Import("ravlexample"))
    {
      displayError(num, "Failed to import 'ravlexample'");
      return false;
    }

    // Build the arguments list
    PythonObjectC name = python.NewObject();
    name.BuildString(StringC(num));

    DListC<PythonObjectC> argList;
    argList.InsLast(name);
    PythonObjectC args = python.NewObject();
    args.BuildTuple(argList);

    // Call the example function and display the results
    cerr << "(" << num << ") Calling 'ravlexample.myprint(" << name.String() << ")'" << endl;
    PythonObjectC res = python.Call("ravlexample", "myprint", args);
    if (res.IsValid())
    {
	    if (res.IsString())
      {
	      cerr << "Result(string): " << res.String() << endl;
      }
      else
      {
        displayError(num, "'ravlexample.myprint' did not return a string");
        return false;
      }
    }
    else
    {
      displayError(num, "Failed to call 'ravlexample.myprint'");
      return false;
    }

    // Run a script from a string
    StringC script("print 'hello'\nx = ");
    script += StringC(num);
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
          cerr << "'x' not an int" << endl;
        }
      }
    }
    else
    {
      displayError(num, "Failed to run script");
      return false;
    }
  }
  catch (PythonExceptionC &e)
  {
    displayException(num, e);
    return false;
  }
  
  return true;
}

int main(int argc, char **argv)
{
  // Cmd line options
  OptionC opts(argc, argv);
  IntT threads = opts.Int("n", 100, "Number of threads");
  opts.Check();
  
  {
    // Create an initial Python object to ensure it intialises the Python interpreter
    // Create it in a local scope so we can ensure it is destroyed first
    PythonC mainPython(true);
    
    // Launch several other threads
    for (IntT i = 0; i < threads; i++)
    {
      LaunchThread(&startThread, i);
    }
  }
  
  // Wait until the threads have completed
  Sleep(1);
  
  return 0;
}
