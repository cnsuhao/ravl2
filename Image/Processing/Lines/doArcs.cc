
#include "Ravl/Image/ArcDetector.hh"
#include "Ravl/Image/EdgeDetector.hh"
#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"

using namespace RavlImageN;
using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC option(nargs,argv);
  bool verb = option.Boolean("v",false,"Verbose. ");
  StringC inType = option.String("it","","Input file type. ");
  StringC outType = option.String("ot","","Output file type. ");
  RealT hystLower = option.Real("hl",10,"Lower hysterisis threshold. ");
  RealT hystUpper = option.Real("hu",17,"Upper hysterisis threshold. ");
  StringC inFile = option.String("","img.pgm","Input filename. ");
  StringC outFile = option.String("","edges.abs","Output filename");
  option.Check();
  
  DPIPortC<ImageC<RealT> > in;
  if(!OpenISequence(in,inFile,inType,verb)) {
    cerr << "Failed to open input '" << inFile << "' \n";
    return 1;
  }
  
#if 0
  DPIPortC<DListC<Arc2dC> > out;
  if(!OpenOSequence(in,outFile,outType,verb)) {
    cerr << "Failed to open input '" << inFile << "' \n";
    return 1;
  }
#endif
  
  // Setup edge detector.
  EdgeDetectorC edgeDet(true,hystLower,hystUpper);

  // Setup arc detector.
  ArcDetectorC arcDet;
  
  ImageC<RealT> img;
  EdgeLinkC edgeLnk;
  while(1) {
    if(!in.Get(img))
      break;
    edgeDet.Apply(img,edgeLnk);
    DListC<DListC<Index2dC> > edgeChains = edgeLnk.LinkEdges();
    cerr << "Edge chains=" << edgeChains.Size() << "\n";
    DListC<Arc2dSegmentC> arcs = arcDet.Apply(edgeChains);
    cerr << "Found " << arcs.Size() << " arcs:\n";
#if 0
    for(DLIterC<Arc2dSegmentCC> it(arcs);it;it++) {
      cerr << " " << it->Centre() << " " << it->Radius() << "\n";
    }
#endif
  }
  cerr << "Done sequence. \n";
  return 0;
}
