
#include "Ravl/XMLTree.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC ifn = opt.String("i","test.xml","Input file. ");
  StringC ofn = opt.String("o","-","Output file. ");
  opt.Check();
  
  XMLIStreamC ins(ifn);
  if(!ins) {
    cerr << "Failed to open file '" << ifn << "' \n";
    return 1;
  }

  XMLTreeC tree(true);

  tree.Read(ins);
  
  OStreamC out(ofn);
  tree.Dump(out);
  return 0;
}
