// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_PPHT_HEADER
#define RAVLIMAGE_PPHT_HEADER 1
//////////////////////////////////////////////////////
//! file="Ravl/Image/Processing/Lines/PPHT.hh"
//! userlevel=Normal
//! docentry="Ravl.API.Images.Lines"
//! lib=RavlImageProc
//! author="Charles Galambos"
//! rcsid="$Id$"
//! date="07/01/1999"
//! example="doPPHT.cc"

#include "Ravl/Image/Image.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/Curve2dLineSegment.hh"
#include "Ravl/Image/PCPixelList.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/Collection.hh"
#include "Ravl/Image/PixelMap.hh"
#include "Ravl/Image/Edgel.hh"
#include "Ravl/Image/PCMapping.hh"
#include "Ravl/Array1d.hh"

#define SHTDEBUG 1

namespace RavlImageN {

  //! userlevel=Develop
  //: Line segment extraction engine.
  
  class PPHoughTransformBodyC
    : public RCBodyVC
  {
  public:
    PPHoughTransformBodyC(Point2dC nRes = Point2dC(0.01,1),RealT fp = 0.999999,RealT angRange = 90,
			RealT maxPTime = -1,bool useSobol = false,RealT nsFract = 1,
			bool fullDir = false);
    // Construct new do-da.
    
    PPHoughTransformBodyC(const PPHoughTransformBodyC &oth);
    //: Copy constructor.
    
    bool PPHTStep(Index2dC pix);
    //: Do a single PPHT cycle starting from a pixel.
    
    bool PPHTTest(const Curve2dLineC &seg,Point2dC at,IntT lineAngle,IntT rho,IntT lMinLen = 0,RealT threshData = -1);
    //: Test this line hypothesis.
    // if the hypothesis is good, extract the line and return true.
    // 'at' should be a point on the line. <p>
    // lineAngle, is the expected angle of the line. (in accumulator co-ords)
    // lMinLen must be greater than minLength to have any effect.
    
    bool PPHTTest(const Curve2dLineSegmentC &seg);
    //: Test this line hypothesis.
    // if the hypothesis is good, extract the line and return true.
    
    bool Setup(const DListC<EdgelC > &dat);
    //: Setup PPHT with the data.
    
    inline void SetCorridor(RealT width) { cWidth = width; }
    //: Set width of corridor.
    
    inline void SetMaxGap(IntT maxgap) { maxGap = maxgap; }
    //: Set maximum gap in line.
    
    inline void SetMinLineLength(IntT Len) { minLength = Len; }
    //: Minimum line length.
    
    void SetDynamicThresh(RealT val) { dynthresh = val; }
    //: Set Dynamic threshold.
    
    void SetFalseP(RealT fpth) { falsep = fpth; }
    //: Set false positive thres.
    
    void SetAngleRange(IntT range) { AngRange = range; }
    //: 0-255. 0-90 degrees.
    
    IntT CalcThresh(IntT votes);
    //: Calculate threshold for accumulator.
    
    IntT CalcThresh2(IntT votes);
    //: Calculate threshold for accumulator.
    
    void SetGradEstNeigh(IntT size) { gradEstNeigh = size; }
    //: Gradient estimate neighhood size.
    
#if 0
    void SaveAccum(StringC filename);
    //: Save accumulator.
#endif
    
    void SetImage(const  ImageC<ByteT> &apixMap) { pixMap = apixMap; }
    //: Set input image.
    
    void SetFeedback(bool sfb)
    { feedBack = sfb; }
    //: Enabled feed back.
    
    PCPixMappingC<Curve2dLineSegmentC> &Lines() { return lines; }
    //: List of found lines.
    
    inline bool WriteGF(ostream &out);
    //: Write GF file.
    
    PCPixMappingC<Curve2dLineSegmentC> Apply(const DListC<EdgelC > &dat);
    //: Apply operation.
    
    PCPixMappingC<Curve2dLineSegmentC> SHT(const DListC<EdgelC > &dat);
    //: Perform SHT.
    
    virtual RCBodyVC &Copy() const;
    //: Creat a copy of this object.
        
    void SetMaxTime(RealT atime) { maxTime = atime; }
    //: Set maxium time to run. -1 = Infinite.
    
    void SetSFract(RealT fract) { sFract = fract; }
    //: Set maxium time to run. -1 = Infinite.
    
    void SetEarlyOut(const DPOPortC<Curve2dLineSegmentC> &to) { earlyOut = to; }
    //: Set early output of lines.
    
    DPOPortC<Curve2dLineSegmentC> &EarlyOut() { return earlyOut; }
    //: Early output of lines.
    
    void SetMagSort(bool val)
    { useMagSort = val; }
    //: Set magmitude sort.
  
    void SetDoSHT(bool val)
    { doSHT = val; }
    //: Do SHT, used for performance comparisons.
    
  protected:  
    
    CollectionC<Index2dC> SetupApply(const DListC<EdgelC > &dat);
    //: Setup everthing ready for procesing.
    
    IntT FilterPoints( ImageC<ByteT> &inimg,PCPixelListC &pnts);
    // Filter out points that are already used.
    // inimg must have 1 in each place.
    // Return: number of points left.
    
    IntT GradFilterPoints(const  ImageC<ByteT> &img,PCPixelListC &pnts,RealT lineAngle);
    //: Gradient filter points.
    
    void TrimOutUsed(const  ImageC<ByteT> &img,PCPixelListC &pnts);
    // Trim out points that have already been used.
    
    void GradTrimOutUsed(const  ImageC<ByteT> &img,PCPixelListC &pnts,IntT angle);
    // Trim out points that have already been used, and those that
    // don't match the gradient constraints.
    
    inline IntT MaxAccAngle() const
    { return accum.Range1().Max().V(); }
    //: Get max position in accum.
    
    inline IntT MinAccAngle() const
    { return accum.Range1().Min().V(); }
    //: Get max position in accum.
    
    bool Vote(Index2dC pix,Point2dC &peak,IntT &thresh);
    // Vote for a pixel, return true if it exceeds the threshold.
    
    bool UnVote(Index2dC pix);
    // Remove votes for a pixel.
    
    bool Vote(Index2dC pix,Point2dC &peak,RealT grad,RealT rng,IntT &thresh);
    //: Vote for a pixel with an angle.
    // return true if it exceeds the threshold.  
    //   grad 1-254 == 0-180 Degree.
    //   rnd  0-255 == 0-90  Degree.
    
    bool UnVote(Index2dC pix,RealT grad,RealT rng);
    //: Remove votes for a pixel, with an angle.
    // grad 1-254 == 0-180 Degree.
    // rnd  0-255 == 0-90  Degree.
    
    IntT GetThresh(IntT votes);
    //: Calculate threshold for accumulator.
    
    void Precompute();
    //: Pre compute sin and cos tables.
    //: and thresholds.
    
    bool useMagSort;
    RealT cWidth; // Corridor width.
    IntT maxGap;
    IntT minLength;
    IntT tvotes; // Total number of votes currently in accumulator.
    IntT allvotes; // Total number of votes done till now.
    RealT dynthresh;
    IntT gradEstNeigh; // Gradient estimation neighberhood size.
    IntT p;
    RealT falsep;
    RealT AngRange; // Range of angles to consider.
    RealT maxTime;  // Maximum time to take in line extraction.
    bool doSHT; 
  private:
    Point2dC res;
    Array2dC<IntT> accum;      // Accumulator.
    Array1dC<IntT> angleCount; // Number of votes in each column.
    Array1dC<RealT> tCos;      // Cos.
    Array1dC<RealT> tSin;      // Sin.
    ImageC<ByteT> usedMap;        // Map of user pixels.
    ImageC<ByteT> pixMap;         // Pixel map.
    ImageC<RealT> gradimg;      // Gradiant image.
    ImageC<RealT> gradacc;      // Gradiant accuracy image.
    ImageC<UIntT> sobelImg;        // Image of sobel numbers.
    PCPixMappingC<Curve2dLineSegmentC> lines; // List of found lines.
    bool feedBack;                   // true= Use feedback processing.
    PCPixMappingC<Curve2dLineSegmentC> lastLines; // List of found lines.
    PixelMapC pmap;  
    int total; // Total pixels in current input.
    IntT cachv;
    IntT cachr;
    IntT accumArrSize;
    bool useSobol; // Use sobol sampling.
    RealT sFract;
    bool fullDir;  // Use full direction, not gradient.
    DPOPortC<Curve2dLineSegmentC> earlyOut; // Anyone want line segments early ?
    RealT radsPerBin;  // Radians per bin. r/nb
    
    SArray1dC<IntT> threshTab;
  };

  
  //////////////////////////////////
  
  inline 
  bool PPHoughTransformBodyC::WriteGF(ostream &out) { 
    lines.WriteGF(out);
    return true;
  }

  //! userlevel=Normal
  //: Progressive Probablistic Hough Transform.
  // This algorithm extracts line segments from a set of edges.
  
  class PPHoughTransformC
    : public RCHandleC<PPHoughTransformBodyC>
  {
  public:
    PPHoughTransformC()
    {}
    //: Default constructor.
    
    PPHoughTransformC(Point2dC nRes,RealT fp = 0.999999,RealT angRange = 90,RealT maxPTime = -1,bool useSobol = false,RealT sFract = 1,bool fullDir = false)
      : RCHandleC<PPHoughTransformBodyC>(*new PPHoughTransformBodyC(nRes,fp,angRange,maxPTime,useSobol,sFract,fullDir))
    {}
    //: Constructor.
    
  protected:
    
    PPHoughTransformBodyC &Body()
    { return RCHandleC<PPHoughTransformBodyC>::Body(); }
    //: Access body.
    
    const PPHoughTransformBodyC &Body() const
    { return RCHandleC<PPHoughTransformBodyC>::Body(); }
    //: Access body.
    
  public:

    PCPixMappingC<Curve2dLineSegmentC> Apply(const DListC<EdgelC > &dat)
    { return Body().Apply(dat); }
    //: Do a hough transform.
    
    PCPixMappingC<Curve2dLineSegmentC> SHT(const DListC<EdgelC > &dat)
    { return Body().SHT(dat); }
    //: Perform a Standard Hough Transform.
    
    void SetCorridor(RealT width)
    { Body().SetCorridor(width); }
    //: Set width of corridor.
    
    void SetMaxGap(IntT maxgap)
    { Body().SetMaxGap(maxgap); }
    //: Set maximum gap in line.
    
    void SetMinLineLength(IntT len)
    { Body().SetMinLineLength(len); }
    //: Minimum line length.
    
    void SetMagSort(bool val)
    { Body().SetMagSort(val); }
    //: Set magnitude sort flag.
    
    void SetDoSHT(bool sht)
    { Body().SetDoSHT(sht); }
    //: Do sht instread
    
  };

}

#endif
