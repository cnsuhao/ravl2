//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.OS.File System"

#include "Ravl/OS/Filename.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  FilenameC filename = opt.String("",".","Filename");
  opt.Check();
  
  cout << "Exists=" << filename.Exists() << "\n";
  cout << "Filesize=" << filename.FileSize() << "\n";
  return 0;
}
