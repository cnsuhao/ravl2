
#include "Ravl/Option.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/SourceTools/BuildInfo.hh"

using namespace RavlN;

bool verb;
BuildInfoC info;

static bool CheckDirectory(StringC &dir,DefsMkFileC &defs) {
  if(verb)
    cerr << "Checking '" << dir << "' \n";
  info.ScanDirectory(dir,defs);
  if(defs.IsDefined("PLIB")) {
    StringC lib = defs["PLIB"];
    cerr << lib << " :";
    for(DLIterC<StringC> it(info.LibDepends(lib));it;it++)
      cerr << " " << *it;
    cerr << "\n";
  }
  return true;
}

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC fn = opt.String("",".","Start directory. ");
  verb = opt.Boolean("-v",false,"Verbose mode. ");
  opt.Check();
  
  SourceCodeManagerC chkit(fn);
  if(verb)
    chkit.SetVerbose(true);  
  chkit.ForAllDirs(CallFunc2C<StringC,DefsMkFileC,bool>(&CheckDirectory),false);

  return 0;
}
