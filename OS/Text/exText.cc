////////////////////////////////////////////////////
//! rcsid="$Id$"

#include <iostream.h>
#include "amma/TxtPFile.hh"
#include "amma/Option.hh"

int main(int nargs,char *args[])
{
  OptionC option(nargs,args,TRUE);
  StringC fname = option.String("i","exText.cc","Input filename. ");
  option.Check();
  
  TextPFileC in(fname);
  
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
