// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Lines/PPHT.cc"

#include "Ravl/Image/PPHT.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Image/PixelMapSearch.hh"
#include "Ravl/Random.hh"
#include "Ravl/Angle.hh"
#include "Ravl/Collection.hh"
#include "Ravl/ScalMath.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/SobolImage.hh"
#include "Ravl/String.hh" 
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/DeadLineTimer.hh"
#include "Ravl/IO.hh"
#include "Ravl/Statistics.hh"
#include "Ravl/SobolSequence.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif


namespace RavlImageN {

#ifdef __sgi__
  // Help the compiler a bit...
  static DPOPortBodyC<Curve2dLineSegmentC> out1;
  static DPIPortBodyC<Curve2dLineSegmentC> out2;
  static DPOPortBodyC<ImageC<ByteT> > out3;
#endif
  
  /////////////////////////////////////////////////////////////////////////////////
  
  // Construct new do-da.
  
  PPHoughTransformBodyC::PPHoughTransformBodyC(Point2dC nRes,RealT fp,RealT angRange,RealT maxPTime,bool xUseSobol,RealT nsFract,bool nfullDir)
    : useMagSort(false),
      cWidth(3),
      maxGap(6),
      minLength(8),
      dynthresh(0.001),
      gradEstNeigh(6),
      p(600),       // Just an estimate....
      falsep(fp),  // 0.9999999
      maxTime(maxPTime), // For ever ! 
      doSHT(false),
      res(nRes),
      //    accum
      cachv(-2),
      cachr(-2),
    useSobol(xUseSobol),
      sFract(nsFract),
      fullDir(nfullDir)
  { 
    IntT arrSize; 
    if(!fullDir) {
      arrSize = (IntT) ((RavlConstN::pi/2)/ res[0]); 
      radsPerBin = (RavlConstN::pi/2) / ((RealT) arrSize); // Allow for rounding.
      ONDEBUG(cerr << "Using half dir. Bins:" << arrSize << " \n");
    } else {
      arrSize = (IntT) ((RavlConstN::pi)/ res[0]);
      radsPerBin = RavlConstN::pi / ((RealT) arrSize); // Allow for rounding.
      ONDEBUG(cerr << "Using full dir. Bins:" << arrSize << " \n");
    }
    accumArrSize = arrSize;
    accum = Array2dC<IntT>(IndexRangeC(-arrSize,arrSize),
			   IndexRangeC(-512,512)); 
    
    angleCount = Array1dC<IntT>(IndexRangeC(-arrSize,arrSize));
    
    AngRange = ((angRange / 360) * RavlConstN::pi ) / radsPerBin; 
    
    Precompute();
  }
  
  // Copy constructor.
  
  PPHoughTransformBodyC::PPHoughTransformBodyC(const PPHoughTransformBodyC &oth)
    : useMagSort(oth.useMagSort),
      cWidth(oth.cWidth),
      maxGap(oth.maxGap),
      minLength(oth.minLength),
      dynthresh(oth.dynthresh),
      gradEstNeigh(oth.gradEstNeigh),
      p(oth.p),
      falsep(oth.falsep),
      AngRange(oth.AngRange),
      maxTime(oth.maxTime),
      doSHT(oth.doSHT),
      res(oth.res),
      accum(oth.accum.Rectangle()),
      angleCount(oth.angleCount.Range()),
      tCos(oth.tCos),
      tSin(oth.tSin),
      usedMap(oth.usedMap.Rectangle()),
      pixMap(oth.pixMap.Rectangle()),
      sobelImg(oth.sobelImg),
      cachv(-2),
      cachr(-2),
      accumArrSize(oth.accumArrSize),
      useSobol(oth.useSobol),
      sFract(1),
      fullDir(oth.fullDir),
      radsPerBin(oth.radsPerBin),
      threshTab(oth.threshTab)
  { 
    //cerr << "PPHoughTransformBodyC::PPHoughTransformBodyC() Copied. \n";
    Precompute(); 
  }
  
  //////////////////////////////
  // Vote for a pixel.
  
  inline 
  bool PPHoughTransformBodyC::Vote(Index2dC pix,Point2dC &peak,IntT &thresh)
  { return Vote(pix,peak,gradimg[pix],AngRange,thresh); }
  
  
  ////////////////////////////////////////
  // Remove votes for a pixel.
  
  inline 
  bool PPHoughTransformBodyC::UnVote(Index2dC pix) 
  { return UnVote(pix,gradimg[pix],AngRange); }
  
  //: Calculate threshold for accumulator.
  
  inline IntT PPHoughTransformBodyC::GetThresh(IntT votes) {
    UIntT ind = votes >> 3;
    if(ind > threshTab.Size()) {
      cerr << "Warning... Over spill from threshold cache..." << ind << " \n";
      return CalcThresh(votes);
    }
    return threshTab[ind];
  }
  
  
  //////////////////////////////
  //: Creat a copy of this object.
  
  RCBodyVC &PPHoughTransformBodyC::Copy() const 
  { return *new PPHoughTransformBodyC(*this); }
  
  // Do a single PPHT cycle.
  
  bool PPHoughTransformBodyC::PPHTStep(Index2dC at) {
    if(pixMap[at] == 0)
      return false;
    allvotes++;
    IntT thresh = GetThresh(tvotes);
    Point2dC peak;
    if(!Vote(at,peak,thresh)) 
      return false;
    // Found point.
    // row theta.
    IntT theta = (IntT) peak[0];
    bool ret = PPHTTest(Curve2dLineC(tSin[theta],tCos[theta],-peak[1]),
			Point2dC(at),
			theta,
			Round(peak[1]),
			0,
			thresh);
    
    //ONDEBUG(if(!ret) cout << ret << " " << thresh << "\n";);
    
    return ret;
  }
  
  //: Test this line segment hypothesis.
  // if the hypothesis is good, extract the line and return true.
  
  bool PPHoughTransformBodyC::PPHTTest(const Curve2dLineC &newline,Point2dC at,IntT lineAngle,IntT prho,IntT lMinLen,RealT threshHold)
  {   
    // Collect pixels in the corridor.
    
    RealT minsl,maxsl;
    newline.GetLimits(minsl,maxsl,pixMap.Rectangle());
    PixelMapSearchC<Curve2dLineC> pixsearch(pmap,cWidth,newline,minsl,maxsl,pixMap);
    PCPixelListC res = pixsearch.Collect(at);
    //RavlAssert(res.IsOk()); // Check its valid.
    if(!res.IsValid()) {
      cerr << "PPHoughTransformBodyC::PPHTTest(), No pixels found! \n";
      //RavlAssert(res.IsValid());
      return false;
    }
    
    // Filter pixels for gradient, and being used already.
    ONDEBUG(cerr << "Init pixs " << res.Size() << "\n"); 
    
    RealT MeanDist;
    PCPixelListC itit = res;
    
    GradFilterPoints(pixMap,res,lineAngle);
    
    //IntT rsize = res.Size();
    ONDEBUG(cerr << "After Grad trim pixs " << res.Size() << "\n"); 
    
    // Get longest segment in window matching criteria.
    
    IntT pixs = res.TrimLongest(maxGap,MeanDist); 
    itit = res;
    ONDEBUG(cerr << "After trim longest " << res.Size() << "\n"); 
    
    if(pixs < minLength || pixs < lMinLen)
      return false;
    
    // Remove pixels from accumulator.
    
#if 0
    SArray1dC<IntT> threshData(6);
    threshData[5] = threshHold;
    for(int i = 0;i < 5;i++) {
      threshData[i] = accum[lineAngle][prho + i - 2];
      cout << accum[lineAngle][prho + i - 2] << " ";
    }
    cout <<"\n";
#else
    SArray1dC<IntT> threshData(1);
    threshData[0] = Round(threshHold);
#endif
    
    PCPixelListC pit(res);
    for(pit.First();pit.IsElm();pit.Next())
      UnVote(pit.Data());
    res.RemoveFromImage(pixMap);
    
    Curve2dLineSegmentC aline(res.PointList()); // Fit line to remaining points.
    
    // Tell everyone about our descovery...
    //cout << allvotes << " " << res.Size() << "\n";
    //cerr << "Detect:" << threshData << "\n";
    lines.InsFirst(PCPixMapC<Curve2dLineSegmentC>(aline,res,threshData));
    if(earlyOut.IsValid())
      earlyOut.Put(aline); 
    return true;
  }
  
  //: Test this line hypothesis.
  // if the hypothesis is good, extract the line and return true.
  // 'at' should be a point on the line.
  
  bool PPHoughTransformBodyC::PPHTTest(const Curve2dLineSegmentC &seg) { 
    RavlAssert(0); // Not fixed yet.
    return PPHTTest((const Curve2dLineC &) seg,
		    seg.MidPnt(),
		    0, // Should be line angle.
		    0, // Should be line rho
		    (IntT)((RealT) seg.Length() * 0.90));
  }
  
  /////////////////////////////////////////
  // Trim out points that have already been used.
  
  void PPHoughTransformBodyC::TrimOutUsed(const  ImageC<ByteT> &img,PCPixelListC &pnts) {
    cout << "PPHoughTransformBodyC::TrimOutUsed(), Before " << pnts.Size() << " \n";
    if(pnts.IsElm()) {
      while(!img[pnts.Data()]) {
	pnts.Next();
	if(!pnts.IsElm())
	  break;
      }
      if(!pnts.IsElm()) {
	pnts.First();
	while(!img[pnts.Data()]) {
	  pnts.Next();
	  if(!pnts.IsElm())
	    break;
	}
      }
    }
    
    DLIterC<PCIndex2dC> It(pnts);
    for(It.First();It.IsElm();It.Next()) {
      if(!img[It.Data()])
	It.Del();
    }
    cout << "PPHoughTransformBodyC::TrimOutUsed(), After " << pnts.Size() << " \n";
  }
  
  ///////////////////////////////////////
  // Trim out points that have already been used, and those that
  // don't match the gradient constraints.
  
  IntT PPHoughTransformBodyC::GradFilterPoints(const  ImageC<ByteT> &inimg,PCPixelListC &pnts,RealT lineAngle) {
    IntT fnd = 0;
    DLIterC<PCIndex2dC> It(pnts);
    RealT dim_the = accum.Range1().Size(); // Get number of theta bins.
    AngleC within(lineAngle,dim_the);
    for(It.First();It.IsElm();It.Next()) {
      if(inimg[It.Data()] == 0 ||
	 (fabs(within.Diff(AngleC(gradimg[It.Data()],dim_the))) > AngRange)
	 )  {
	//cout << (int) gradimg[It.Data()] <<  " " << lineAngle << " Diff:" << within.Diff(AngleC(gradimg[It.Data()]-1,254)) << "  Lim:" << AngRange << endl;
	if(pnts == It) {
	  pnts.Last(); // Backward safer cause we processed that point already.
	  if(!pnts.IsElm()) { // Oh well, try forward.
	    pnts.Iter() = It;
	    pnts.Next();
	  }
	}
	It.Del();
      }
      else
	fnd++;
    }
    return fnd;  
  }
  
  //////////////////////////////////////////
  // Filter out points that are already used.
  // Return: number of points left.
  
  IntT PPHoughTransformBodyC::FilterPoints( ImageC<ByteT> &inimg,PCPixelListC &pnts) {
    IntT fnd = 0;
    DLIterC<PCIndex2dC> It(pnts);
    for(It.First();It.IsElm();It.Next()) {
      if(inimg[It.Data()] == 0) {
	if(pnts == It) {
	  pnts.Last(); // Backward safer cause we processed that point already.
	  if(!pnts.IsElm()) { // Oh well, try forward.
	    pnts.Iter() = It;
	    pnts.Next();
	  }
	}
	It.Del();
      }
      else
	fnd++;
    }
    return fnd; 
  }
  
#define USE_DYNAMICTHRESH 0
#if USE_DYNAMICTHRESH 
#define ONDYNTHRESH(x) x
#else
#define ONDYNTHRESH(x)
#endif

  /////////////////////////////////////////
  // Vote for a pixel, return true if it exceeds the threshold.
  
  bool PPHoughTransformBodyC::Vote(Index2dC pix,Point2dC &peak,RealT grad,RealT rng,IntT &thresh) {
    bool found(false);
    usedMap[pix] = 2;
    tvotes++;
    IntT dim_the = accum.Range1().Size(); // Get number of theta bins.
    RealT maxy = 0;
    IntT tmp,maxk = 0;
#if USE_DYNAMICTHRESH 
    IntT maxval = 2;
#else
    IntT maxval = thresh;
#endif
    IntT Startk = (IntT) ((RealT) grad - rng);
    IntT Endk   = (IntT) ((RealT) grad + rng);
    //cout << "PPHoughTransformBodyC::Vote(), " << Startk << "  " << Endk << "  Dim:" << dim_the << " G:" << ((IntT) grad)  << " R:" << ((IntT) rng) << "\n";
    
    RealT pixR = pix.Row();
    RealT pixC = pix.Col();

    const IntT MinA = MinAccAngle();
    const IntT MaxA = MaxAccAngle();
    
    if(Endk > MaxA) {
      IntT ne = Endk - dim_the;
      Endk = MaxA;
      for(IntT k = MinA;k < ne;k++) {
	RealT y = pixR * tSin[k] + pixC * tCos[k];
	ONDYNTHRESH(angleCount[k]++);
	//cout << "Vote:" << at << "\n";
	tmp = ++(accum[k][Round(y)]);
	if(tmp > maxval) {
	  maxk = k;
	  maxy = y;
	  maxval = tmp;
	  found = true;
	}
      }
    }
    
    if(Startk < MinA) {
      IntT nst = Startk + dim_the;
      Startk = MinA;
      for(IntT k = nst;k < MaxA;k++) {
	RealT y = pixR * tSin[k] + pixC * tCos[k];
	ONDYNTHRESH(angleCount[k]++);
	if((tmp = ++accum[k][Round(y)]) > maxval) {
	  maxk = k;
	  maxy = y;
	  maxval = tmp;
	  found = true;
	}
      }
    }
    
    for (IntT k=Startk; k<Endk; k++) {
      RealT y = pixR * tSin[k] + pixC * tCos[k];
      //cout << "Vote:" << at << "\n";
      ONDYNTHRESH(angleCount[k]++);
      if((tmp = ++accum[k][Round(y)]) > maxval) {
	maxk = k;
	maxy = y;
	maxval = tmp;
	found = true;
      }
    }
    
    if(found) {
#if USE_DYNAMICTHRESH 
      thresh = GetThresh(angleCount[maxk]);
      if(maxval <= thresh)
	found = false;
#endif
      peak = Point2dC(maxk,maxy);
    }
    return found;
  }
  
  //////////////////////////////////////////////////
  // Remove votes for a pixel.
  
  bool PPHoughTransformBodyC::UnVote(Index2dC pix,RealT grad,RealT rng) {
    if(usedMap[pix] != 2)
      return  false;
    usedMap[pix] = 1;
    tvotes--;
    
    IntT Startk = (IntT) ((RealT) grad - rng); 
    IntT Endk   = (IntT) ((RealT) grad + rng);
    
    const IntT MinA = MinAccAngle();
    const IntT MaxA = MaxAccAngle();
    const IntT dim_the = accum.Range1().Size(); // Get number of theta bins.
    
    RealT pixR = pix.Row();
    RealT pixC = pix.Col();
    
    if(Endk > MaxA) {
      IntT ne = Endk - dim_the;
      Endk = MaxA;
      for(IntT k = MinA;k < ne;k++) {
	--accum[k][Round(pixR * tSin[k] + pixC * tCos[k])];
	ONDYNTHRESH(angleCount[k]--);
      }
    }
    
    if(Startk < MinA) {
      IntT nst = Startk + dim_the;
      Startk = MinA;
      for(IntT k = nst;k < MaxA;k++) {
	--accum[k][Round(pixR * tSin[k] + pixC * tCos[k])];
	ONDYNTHRESH(angleCount[k]--);
      }
    }
    for (IntT k=Startk;k < Endk; k++) {
      --accum[k][Round(pixR * tSin[k] + pixC * tCos[k])];
      ONDYNTHRESH(angleCount[k]--);
    }
    return true;
  }
  
  
  
  /////////////////////////////////////////////
  // Calculate threshold for accumulator.
  
#define USETHRESHCACHE 0
  
  IntT PPHoughTransformBodyC::CalcThresh(IntT votes) {
    //cerr << "CalcThresh() Called. \n";
#if 0
    return CalcThresh2(votes);
#else  
    
#if USETHRESHCACHE
    //IntT rang = votes / 20;
    IntT rang = votes / 5;
    if(rang == cachv || rang == cachv-1)
      return cachr;
    cachv = rang;
    votes = (rang+1) * 20;
#endif
    IntT k;
    RealT sum = 0;
    //sum += Exp((RealT) 1/p) * Pow((i/p),k) / ExtMathC::Factorial(k);
    RealT oop =  ((RealT) 1.0/p);
    for(k = 0;k < votes;k++) {
      sum += BinomalCoeff(votes,k) * Pow(oop,k) * Pow(1.0-oop,votes - k);
      //cout << "PPHoughTransformBodyC::CalcThresh() " << k << " Sum:" << sum << " oop:" << oop << " RBC:" << ExtMathC::RBinomCoeff(votes,k) <<" \n";
      if(sum > falsep)
	break;
    }
    //cout << "PPHoughTransformBodyC::CalcThresh(); rang:" << rang<<" k:" << k << " Sum:" << sum << " Votes:" << votes << "\n";
#if USETHRESHCACHE
    cachr = k+1;
#if 1
    // Never put the threshold below minimum line length.
    if(cachr < (minLength-1))
      cachr = (minLength-1);
#else
    // Never put the threshold below 2.
    if(cachr < 2)
      cachr = 2;
#endif
    return cachr;
#else
    if(k+1 >= 2)
      return k+1;
    else
      return 2;
#endif
#endif
  }
  
  IntT PPHoughTransformBodyC::CalcThresh2(IntT votes) {
#if USE_DYNAMICTHRESH
    RealT nbins = 500 ; // * accum.Range1().Size();
    RealT n = votes;
#else
    RealT nbins = 500 * accum.Range1().Size();
    RealT n = votes * AngRange;
#endif
    RealT prob = 1/ (RealT) nbins;
    //cerr << "Prob:" << prob << " Nbins:" << nbins << "\n";
    RealT fp = (1 - falsep);
    IntT k;
    
    for(k = 1;k < 1000;k++) {
#if 1
      if(StatBetaQ(prob,k,n-k+1) > fp)
	break;
#else
#if 1
      if(Betai(k,n-k+1,prob) < fp) // Binomial
	break;
#else
      if(GammaQ(k,n/nbins) > falsep) // Poisson.
	break;
#endif
#endif
    }
    //cerr << "PPHoughTransformBodyC::CalcThresh2(), " << votes << " k=" << k << "\n";
    return k;
  }
  
  
  //: Save accumulator.
  
#if 0
  void PPHoughTransformBodyC::SaveAccum(StringC filename) {
    ImageRectangleC ir(accum.Range1().Min(),
		       accum.Range1().Max(),
		       accum.Range2().Min(),
		       accum.Range2().Max());
    ImageC<ByteT> out(ir);
    IndexC at1,at2;
    for(at1 = accum.Range1().Min();at1 < accum.Range1().Max();at1++) {
      for(at2 = accum.Range2().Min();at2 < accum.Range2().Max();at2++) {
	if(accum[at1][at2] > 255) // Clip.
	  out[at1][at2] = 255;
	else
	  out[at1][at2] = accum[at1][at2];
      }
    }
    RavlN::Save(filename,out);
  }
#endif
  
  //////////////////////////////////
  //: Pre compute sin and cos tables.
  
  void PPHoughTransformBodyC::Precompute() {
    const IntT mina = MinAccAngle();
    const IntT maxa = MaxAccAngle();
    //cerr << "Min: " << mina << "  Max:" << maxa <"\n";
    tCos = Array1dC<RealT>(IndexRangeC(mina,maxa));
    tSin = Array1dC<RealT>(IndexRangeC(mina,maxa));
    
    for (IntT k=mina; k < maxa; k++) {
      RealT theta = (RealT) k * radsPerBin;
      tCos[k] = cos(theta);
      tSin[k] = sin(theta);
    }
    
    // Threholds.
    
    threshTab = SArray1dC<IntT>(1200);
    for(unsigned int i = 0;i < threshTab.Size();i++) {
      threshTab[i] = CalcThresh((i+1) << 3);
      //cerr << ((i+1) << 3) << " " << threshTab[i] << "\n";
    }
  }
  
#define ARRSOBEL 0
#include "Ravl/SobolSequence.hh"
  //#include "Ravl/Image/PixelMapNeigh.hh"

  ImageC<UIntT> cheatSobolImg;
  
  static bool PPHTCompair(const EdgelC &p1,const EdgelC &p2) 
  { return cheatSobolImg[p1.At()] <= cheatSobolImg[p2.At()]; }
  
  static bool LessOrEqualGradInfo(const EdgelC & el1, const EdgelC & el2)
  { return (el1.Magnitude() > el2.Magnitude());  }
  
  //: Setup everthing ready for procesing.
  
  CollectionC<Index2dC> PPHoughTransformBodyC::SetupApply(const DListC<EdgelC > &dat)  {
    pmap.Empty();
    total = 0;
    allvotes = 0;
    ImageRectangleC rect(0,0,0,0);
    // Look at incoming data.
    DLIterC<EdgelC > it(const_cast<DListC<EdgelC > &>(dat));
    for(;it;it++) {
      Index2dC at = it.Data().At();
      pmap.Insert(at);
      rect.Involve(at);
      total++;
#if 0
      if(useMagSort)
	it.Data().Magnitude() += Random1() ;
#endif
    }
    
    DListC<EdgelC > sortIt(dat);
    
    if(useMagSort)
      sortIt.MergeSort(LessOrEqualGradInfo);
    
    // Need to resize images ?
    if(!rect.Contains(pixMap.Rectangle())) {
      rect.Involve(pixMap.Rectangle());
      if(useSobol)
	sobelImg = SobolImage(rect);
      gradimg = ImageC<RealT>(rect); 
      //gradacc = ImageC<RealT>(rect);
      pixMap = ImageC<ByteT>(rect);
      usedMap = ImageC<ByteT>(rect);
      p = Max(rect.Rows(),rect.Cols()); 
      
      // Sort out accumulator.
      IntT maxVal = ((IntT) Sqrt(Sqr(rect.Rows()) + Sqr(rect.Cols()))) + 1;
      accum = Array2dC<IntT>(IndexRangeC(-accumArrSize,accumArrSize),
			     IndexRangeC(-maxVal,maxVal));
      //    cerr << "Accumulator size: " << maxVal << "\n";
    }
    
    if(useSobol) {
      //cerr << "Using sorted edgles (1) \n";
      cheatSobolImg = sobelImg;    
      sortIt.MergeSort(PPHTCompair);
    }
    
    // Setup data.
    CollectionC<Index2dC> bag(total+1);
    //pixMap.Fill(0);
    ONDYNTHRESH(angleCount.Fill(0));
    
    for(it = sortIt;it;it++) {
      Index2dC at = it.Data().At();
      
      if(!useSobol && !useMagSort)
	bag.Insert(it.Data().At());
      
      // Calculates gradients, shift and scale so's to be 0 to dim_the.
      RealT ev = it.Data().Direction();
      ev *= -1;
      //ev += RavlConstN::pi_2;
      // Normalise the angle.
      if(!fullDir) {
	while(ev > (RavlConstN::pi_2))
	  ev -= (RavlConstN::pi);
	while(ev < (-RavlConstN::pi_2))
	  ev += (RavlConstN::pi);
      }
      gradimg[at] = ev / radsPerBin;
      pixMap[at] = 1;
      usedMap[at] = 0;
    }
    //SetupGradImage(pixMap);
    lines = PCPixMappingC<Curve2dLineSegmentC>();
    tvotes = 0;
    accum.Fill(0);
    
    return bag;
  }
  
  //////////////////////////////////
  //: Apply operation.
  
  PCPixMappingC<Curve2dLineSegmentC> PPHoughTransformBodyC::Apply(const DListC<EdgelC > &dat) {
    //cerr << "PPHoughTransformBodyC::Apply(), called " << ((void *) this) << "\n";
    DeadLineTimerC dlt(maxTime,false); // Virtual timer.
    
    CollectionC<Index2dC> bag = SetupApply(dat);
    
    if(doSHT)
      return SHT(dat);
    
    int s;
#if 0
    IntT MaxThresh = CalcThresh(total);
    IntT stopat = (IntT)((RealT) total * ((RealT)MaxThresh / minLength)); 
    if(stopat > total)
      stopat = total;
#else
    IntT stopat = total + 1;
#endif
    
    //cout << "#Stopat:" << stopat << " MaxThresh:" << MaxThresh << " Pixels:" << total <<" Minlength:" << minLength <<"\n" <<flush;
    
    if(feedBack) {
      // Look for matches in last results....
      for(DLIterC<PCPixMapC<Curve2dLineSegmentC> > it(lastLines);it.IsElm();it.Next())
	PPHTTest(it.Data().Curve());
    }
    
    if(!useSobol || 1) {
      if(useMagSort || useSobol) {
	s = 0;
	DListC<EdgelC > sortIt(dat);
	//cerr << "Using sorted edgles  \n";
	for(DLIterC<EdgelC> it(sortIt);s < stopat && it.IsElm() && !dlt.IsTimeUp();it.Next(),s++) {
	  //cerr << "Using sorted edgles " << it.Data().Magnitude() << " \n";
	  PPHTStep(it.Data().At());
	}
      } else {
	for(s =0;s < stopat && !bag.IsEmpty() && !dlt.IsTimeUp();s++) 
	  PPHTStep(bag.Pick());
      }
    } else {
      int seqn = 0;
      ImageRectangleC rect(usedMap.Rectangle());
      for(SobolSequenceC seq(2);seq.IsElm() && seqn < (stopat-3) && !dlt.IsTimeUp();seq.Next()) {
	SArray1dC<RealT> s = seq.Data();
	Point2dC at(((RealT) s[0] * rect.Rows()) + rect.Origin().Row(),((RealT)s[1] * rect.Cols())+ rect.Origin().Col());
#if 1      
	for(DLIterC<Index2dC> it(pmap.Bin(at));it.IsElm();it.Next()) {
	  if(usedMap[it.Data()] == 0) {
	    seqn++;
	    PPHTStep(it.Data());	  
	    break;
	  }
	}
#else
	Index2dC pat(Floor(at.X()),Floor(at.Y()));
	if(pixMap[pat] == 0)
	continue;
	if(usedMap[pat] != 0)
	  continue;
	seqn++;
	PPHTStep(pat);  
#endif
      }
    }
    PCPixMappingC<Curve2dLineSegmentC> ret = lines;
    if(feedBack)
      lastLines = lines;
    lines = PCPixMappingC<Curve2dLineSegmentC>();   // Make sure there's no refrence left to muck up multithreading.
    return ret;
  }
  
  //: Perform SHT.
  
  PCPixMappingC<Curve2dLineSegmentC> PPHoughTransformBodyC::SHT(const DListC<EdgelC > &ndat) {
    DListC<EdgelC > dat(ndat);
    int maxPeaks = 0;
    Point2dC dummy;
    for(DLIterC<EdgelC> it(dat);it.IsElm();it.Next()) {
      int x = 10000;
      Vote(it.Data().At(),dummy,x);
      maxPeaks++;
    }
    //SaveAccum("accum.pgm");
    
    ONDEBUG(cerr << "Voting done.\n");
    maxPeaks /= minLength;
    while(maxPeaks-- > 0) {
      // Search for a peak in the accumulator space.
      IntT peak = 0;
      IndexC at1,at2;
      IntT maxk = 0,maxy = 0;
      for(at1 = accum.Range1().Min();at1 <= accum.Range1().Max();at1++) {
	for(at2 = accum.Range2().Min();at2 <= accum.Range2().Max();at2++) {
	  IntT val = accum[at1][at2];
	  if(val > peak) {
	    peak = val;
	    maxk = at1.V();
	    maxy = at2.V();
	  }
	}
      }
      // Peaks below minimum length threshold ??
      if(peak < minLength)
	break;
      ONDEBUG(cerr << "Peak: " << maxk << " " << maxy << " Value:" << peak << "\n");
      IntT theta = (IntT) maxk;
      Curve2dLineC newline(tSin[theta],tCos[theta],-maxy);
      
      // Collect pixels in the corridor.
      
      RealT minsl,maxsl;
      newline.GetLimits(minsl,maxsl,pixMap.Rectangle());
      ONDEBUG(cerr << "Min:" <<  newline.Point(minsl) << " Mid:" << newline.Point((minsl+maxsl)/2) << " Max:" << newline.Point(maxsl) <<"\n");
      
      PixelMapSearchC<Curve2dLineC> pixsearch(pmap,cWidth,newline,minsl,maxsl,pixMap);
      
      PCPixelListC res = pixsearch.Collect(newline.Point((minsl+maxsl)/2));
      //RavlAssert(res.IsOk()); // Check its valid.
      if(!res.IsValid()) {
	cerr << "PPHoughTransformBodyC::SHT(), No pixels found! \n";
	//RavlAssert(res.IsValid());
	break;
      }
      
      // Filter pixels for gradient, and being used already.
      //ONDEBUG(cerr << "Init pixs " << res.Size() << "\n"); 
      
      RealT MeanDist;
      PCPixelListC itit = res;
      
      GradFilterPoints(pixMap,res,theta);
      
      //IntT rsize = res.Size();
      //ONDEBUG(cerr << "After Grad trim pixs " << res.Size() << "\n"); 
      
      // Get longest segment in window matching criteria.
      
      IntT pixs = res.TrimLongest(maxGap,MeanDist); 
      itit = res;
      //ONDEBUG(cerr << "After trim longest " << res.Size() << "\n"); 
      
      // Remove pixels from accumulator.
      
      PCPixelListC pit(res);
      for(pit.First();pit.IsElm();pit.Next())
	UnVote(pit.Data());
      res.RemoveFromImage(pixMap);
      
      ONDEBUG(cerr << "Done remove...\n"); 
      
      if(pixs < minLength)
	continue;
      
      Curve2dLineSegmentC aline(res.PointList()); // Fit line to remaining points.
      
      // Tell everyone about our descovery...
      //cout << allvotes << " " << res.Size() << "\n";
      lines.InsFirst(PCPixMapC<Curve2dLineSegmentC>(aline,res));
    }
    PCPixMappingC<Curve2dLineSegmentC> ret = lines;
    lines = PCPixMappingC<Curve2dLineSegmentC>();   // Make sure there's no refrence left to muck up multithreading.
    //cerr << angleCount;
    
    return ret;
  }
  
}
