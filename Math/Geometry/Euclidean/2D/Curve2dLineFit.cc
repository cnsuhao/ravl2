
#include "Ravl/Math.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Curve2dLine.hh"
#include "Ravl/IndexRange2d.hh"

namespace RavlN {
  
  /////////////////////////////
  // Make a line that fits points.

  RealT Curve2dLineC::FitLSQ(const SArray1dC<Point2dC> &Pnts) {
#if 0
    LinearSums2dC Sums;
    for(IndexT i = 0;i < Pnts.N();i++)
      Sums += Pnts[i];
    
    if(Sums.N() < 2) {
      cerr << "Curve2dLineC::FitLSQ(), Can't fit with less than two points.\n";
      return -1;
    }
    (*this) = Sums.LineABCxy();
    ONDEBUG(printf("FELineC::OptimiseLSQ(),  OldQ:%f NewQ:%f N:%ld \n",Quality(),(RealT) AssessFit(NewLine),Sums.N()));
    //if(Quality() >= (AssessFit(NewLine) + 0.05))
    //  return NULL; // No better.  
    //  return new FELineC(NewLine,AStart);
    return AssessFit(Pnts); // FIXME :- Must be better way !
#else
    return 0;
#endif
  }
  
  // Measure error for fit.
  
  RealT Curve2dLineC::AssessFit(const SArray1dC<Point2dC> &pnts) {
    RealT Err = 0;
    for(BufferAccessIterC<Point2dC> it(pnts);it;it++)
      Err += Distance(*it);
    return Err/pnts.Size();
  }
}
