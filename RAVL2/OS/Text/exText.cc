////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Stream.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int main(int nargs,char *args[])
{
  OptionC option(nargs,args);
  StringC fname = option.String("i","exText.cc","Input filename. ");
  option.Check();
  
  TextFileC in(fname);
  
  if(in.IsReadonly()) 
    cerr << "File is read only. \n";
  else
    cerr << "File is writable. \n";
  if(in.IsLoaded()) 
    cerr << "File is loaded. \n";
  if(!in.IsModified()) 
    cerr << "File is not modified. \n";
  
  in.Dump(cout);
  
  return 0;
}
