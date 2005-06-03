// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IO.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/RealHistogram1d.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Image/ImagePointFeatureSet.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

using namespace RavlImageN;

 // a list of all XML files to use to build models
DListC<StringC> xmlFileNameList;

bool AlreadyAdded(StringC fileName)
{
  for(DLIterC<StringC> it(xmlFileNameList);it;it++)
    if(fileName == *it)  {
      return true;
      cerr << "file " << fileName << "already added" << endl;
    }
  return false;			    
}

bool AddXmlList(DListC<StringC> & xmlList) 
{  
  for(DLIterC<StringC> it(xmlList);it;it++) {
    if(AlreadyAdded(*it)) return true;
    xmlFileNameList.InsLast(*it);
  }  
  return true;
}

DListC<StringC> ExtractList(StringC fileName)
{
  TextFileC textFile(fileName);
  DListC<StringC> resultList;
  if(textFile.IsLoaded()) {
    DListC<TextFileLineC> lineList = textFile.Lines();
    for(DLIterC<TextFileLineC> it(lineList);it;it++) resultList += it->Text().TopAndTail();
  }
  else cerr << "failed to load text file " << fileName << endl ;
  return resultList;
}


int compareFeatureSet(int argc, char **argv)
{  
  OptionC   opt(argc,argv);

  //: The input XML data
  DListC<StringC> FromCLXmlList = opt.List("x","[xmlFile1]....[xmlFileN]");
  DListC<StringC> FromCLXmlFileNameList = opt.List("xl","[xmlFileList1]....[xmlFileListN]");
  DListC<StringC> ToCLXmlDir = opt.List("dir","[dir1]....[dirN]");

  FilenameC     Histo = opt.String("hist", "histogram.strm", "output distances into a histogem");
  //: Additional stuff
  opt.Check();


  //: Get list of files
  ////////////////////
  //: adds the xml files from the command line option "-x"
  AddXmlList(FromCLXmlList); 
  
  //: adds the xml file list from the text files following the command line option "-xl"
  for(DLIterC<StringC> it(FromCLXmlFileNameList);it;it++) {
    DListC<StringC> tempList = ExtractList(*it);
    AddXmlList(tempList);
  }


  RCHashC<StringC, DListC<RealT> >distances;

  for(ConstDLIterC<StringC>It(xmlFileNameList);It.IsElm();It.Next()) {
    FilenameC fromFile(It.Data());
    FilenameC toFile;
    for(ConstDLIterC<StringC>dirIt(ToCLXmlDir);dirIt;dirIt++) {
      toFile = FilenameC(dirIt.Data() + "/" + fromFile.NameComponent());
      if(toFile.Exists()) break;
    }
        
    ONDEBUG(cout << "Loading in XML files: " << It.Data() << endl);
    
    //: Load in the two feature sets to compare
    ImagePointFeatureSetC fromSet;
    if(!Load(fromFile, fromSet)) {
      cerr << "error loading XML feature set file: " << fromFile << endl;
      exit(-1);
    }

    ImagePointFeatureSetC toSet;
    if(!Load(toFile, toSet)) {
      cerr << "error loading corresponding XML file: " << toFile << endl;
      exit(-1);
    }

    //: Next we want to work out the Eulcidean Distances for each feature point
    //: and store them
    
    ImagePointFeatureC ft;
    for(HashIterC<IntT, ImagePointFeatureC>hsh(fromSet.FeatureIterator());hsh.IsElm();hsh.Next()) {
      StringC desc =  hsh.Data().Description();
      toSet.Feature(desc, ft);
      RealT dist = hsh.Data().EuclidDistance(ft);
      cout << dist << endl;
      distances[desc].InsLast(dist);
    }
  }
  
  RealHistogram1dC histo(0, 50, 250);
  //: OK, now we can the analysis of how the two feature sets differ
  for(HashIterC<StringC, DListC<RealT> >hsh(distances);hsh.IsElm();hsh.Next()) {
    RealT sum = 0.0;
    for(ConstDLIterC<RealT>It(hsh.Data());It.IsElm();It.Next()) {
      RealT v = It.Data();
      sum+=v;
      if(v>50) histo.Vote(49.9);
      else histo.Vote(v);
    }
    cout << hsh.Key()  << " dist: " << sum << endl;
  }
  
  //: Output the histogram
  OStreamC ofs(Histo);
  RealT step = 50./250.;
  UIntT i=0;
  for(SArray1dIterC<UIntC>it(histo);it;it++) {
    RealT place = (RealT)i*step;
    ofs << place  << " " << *it << endl;
    i++;
  }
  
  return 0;
}

//: This puts a wrapper around the main program that catches
//: exceptions and turns them into readable error messages.


RAVL_ENTRY_POINT(compareFeatureSet);
