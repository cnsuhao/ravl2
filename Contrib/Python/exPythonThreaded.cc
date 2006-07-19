// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: exFFmpeg.cc 5123 2005-09-27 08:39:26Z ees1wc $"
//! lib = RavlPython
//! author = "Warren Moore"
//! file = "Ravl/Contrib/Python/exPython.cc"

#include "Ravl/Option.hh"
#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/String.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN;

bool startThread(const IntT num)
{
  PythonC python(true);
  
  // Initialise the python module
  python.AppendSystemPath(".");
  
  // Import a module
  bool ret = python.Import("ravlexample");
  cerr << "(" << num << ") Importing 'ravlexample': " << (ret ? "OK" : "FAIL") << endl;
  
  //  Build the arguments list
  PythonObjectC name = python.NewObject();
  name.BuildString(StringC(num));
  DListC<PythonObjectC> argList;
  argList.InsLast(name);
  PythonObjectC args = python.NewObject();
  args.BuildTuple(argList);
  
  // Call the example function and display the results
  cerr << "(" << num << ") Calling 'ravlexample.myprint(" << name.String() << ")'" << endl;
  PythonObjectC res = python.Call("ravlexample", "myprint", args);
  cerr << "(" << num << ") Result valid: " << (res.IsValid() ? "YES" : "NO") << endl;
  if (res.IsString())
    cerr << "(" << num << ") Result(string): " << res.String() << endl;

  // Run a script from a string
  StringC script("print 'hello'\nx = ");
  script += StringC(num);
  cerr << "Calling script from string" << endl;
  if (python.Run(script))
  {
    // Read the globals from the script
    PythonObjectC x = python.GetGlobal("x");
    cerr << "Found 'x': " << (x.IsValid() ? "YES" : "NO") << endl;
    if (x.IsInt())
      cerr << "'x'= " << x.Int() << endl;
    else
      cerr << "'x' not an int" << endl;
  }
  else
    cerr << "Failed to run script" << endl;
  
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
