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

#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/String.hh"

using namespace RavlN;

void displayError(PythonC &interpreter)
{
	cerr << "#### Error" << endl;
	StringC exType, exValue, exTrace;
	interpreter.GetError(exType, exValue, exTrace);
	cerr << "##  Type:  " << exType << endl;
	cerr << "##  Value: " << exValue << endl;
	cerr << "##  Trace: " << endl << exTrace << endl;
}

int main(int argc, char **argv)
{
  // Initialise the python module
  PythonC python(true);
  
  if (!python.Initialised())
  {
    cerr << "Failed to initialise interpreter" << endl;
    displayError(python);
    return -1;
  }
    
  cerr << "Appending '.' to system path" << endl;
  if (!python.AppendSystemPath("."))
  {
    displayError(python);
    return -1;
  }
  
  cerr << "Importing 'ravlexample'" <<endl;
  if (!python.Import("ravlexample"))
  {
    displayError(python);
    return -1;
  }
  
  //  Build the arguments list
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
      cerr << "Result(string): " << res.String() << endl;
  }
  else
  {
    displayError(python);
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
    if (x.IsValid() && x.IsInt())
      cerr << "'x'= " << x.Int() << endl;
    else
      cerr << "'x' not an int" << endl;
  }
  else
  {
    displayError(python);
    return -1;
  }

  return 0;
}
