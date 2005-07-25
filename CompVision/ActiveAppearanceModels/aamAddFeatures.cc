
#include "Ravl/Option.hh"
#include "Ravl/IO.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/Image/ImagePointFeatureSet.hh"

using namespace RavlImageN;
using namespace RavlN;

int main(int nargs,char **argv) {

  OptionC opt(nargs,argv);
  DirectoryC inDir = opt.String("i",".","Input directory. ");
  DirectoryC outDir = opt.String("o",".","Output directory. ");
  StringC ext = opt.String("e","xml","Extention to expect on markup files. ");
  opt.Check();
  
  DListC<StringC> files;
  bool singleFile = false;
  if(inDir.IsDirectory()) {
    files = inDir.List("",StringC(".") + ext);
  } else {
    singleFile = true;
    files.InsLast(inDir);
  }
  
  ImagePointFeatureC f1(125,"Forehead-0",10,10);
  ImagePointFeatureC f2(126,"Forehead-1",10,50);
  ImagePointFeatureC f3(127,"Forehead-2",10,90);
  
  DListC<IntT> subset;
  subset.InsFirst(0);
  subset.InsFirst(125);
  subset.InsFirst(126);
  subset.InsFirst(127);
  subset.InsFirst(26);
  
  for(DLIterC<StringC> it(files);it;it++) {
    ImagePointFeatureSetC fs;
    StringC featureSetFile;
    if(!singleFile)
      featureSetFile = inDir + '/' + *it;
    else
      featureSetFile = *it;
    
    if(!Load(featureSetFile,fs)) {
      cerr << "WARNING: Failed to load file '" << featureSetFile << "' \n";
      continue;
    }
    
    fs.AddFeature(f1);
    fs.AddFeature(f2);
    fs.AddFeature(f3);
    
    fs.AddSubset("Forehead",subset);
    
    //: Add a new feature to the set.
    
    StringC of = outDir + '/' + *it;
    if(!Save(of,fs)) {
      cerr << "WARNING: Failed to save file '" << of << "' \n";
      continue;
    }
    
  }
  return 0;
}
