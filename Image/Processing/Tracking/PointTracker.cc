// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/PointTracker.cc"
//! lib=RavlImageProc

#include "Ravl/Image/PointTracker.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Matching.hh"
#include "Ravl/IO.hh"
#include "Ravl/SquareIter.hh"
#include "Ravl/Image/PeakDetector.hh"
#include "Ravl/Image/CornerDetectorSusan.hh"
#include "Ravl/Image/CornerDetectorHarris.hh"

#define DODEBUG 0
#if DODEBUG 
#include "Ravl/Image/DrawCross.hh"
#include "Ravl/Image/DrawFrame.hh"
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  template<class DataT,class SumT>
  static SumT SearchGradientDecent(const Array2dC<DataT> &tmpl,const Array2dC<DataT> &img,const Index2dC &start,Point2dC &rat,SumT &rminScore) {
    SumT minScore;
    IndexRange2dC sarea(start,50,50);
    sarea.ClipBy(img.Frame() - tmpl.Frame());
    //cerr << "Img=" << img.Frame() << " SArea=" << sarea << "\n";
    if(!sarea.Contains(start)) {
      rat = Point2dC(-1,-1);
      minScore = 100000000;
      return minScore;
    }
    Array2dC<SumT> scoreMap(sarea);
    scoreMap.Fill(-1);
    MatchSumAbsDifference(tmpl,img,start,minScore);
    Index2dC minAt = start;
    scoreMap[minAt] = minScore;
    
    Index2dC lastMin;
    do {
      //cerr << "Center at " << minAt << "\n";
      lastMin = minAt;
      for(SquareIterC it(4,minAt);it;it++) {
	if(!sarea.Contains(*it) || scoreMap[*it] > 0)
	  continue;
	SumT score;
	//cerr << "Checking " << *it << "\n";
	MatchSumAbsDifference(tmpl,img,*it,score);
	scoreMap[*it] = score;
	if(score < minScore) {
	  minScore = score;
	  minAt = *it;
	}
      }
    } while(minAt != lastMin);
    rat = LocatePeakSubPixel(scoreMap,minAt,0.25);
    rat = minAt;
    rminScore = minScore;
    return minScore;
  }
  
  //: Constructor.
  
  PointTrackerC::PointTrackerC(int cthreshold,int cwidth,int nmthreshold,int nmwidth,int nlifeTime,int nsearchSize,int nnewFreq)
    : idAlloc(1),
      newFreq(nnewFreq),
      frameCount(1),
      cornerDet(CornerDetectorHarrisC(cthreshold,cwidth)),
      //cornerDet(CornerDetectorSusanC(cthreshold)),
      mwidth(nmwidth),
      mthreshold(nmthreshold),
      lifeTime(nlifeTime),
      searchSize(nsearchSize)
  {}

  //: Returns a list of tracks.
  
  DListC<PointTrackC> PointTrackerC::Apply(const ImageC<ByteT> &img) {
    DListC<PointTrackC> ret;
    Update(img);
    IntT removeThresh = Sqr(mwidth) * mthreshold;
    for(DLIterC<PointTrackModelC> itt(tracks);itt;itt++) {
      if(itt->Frame() != frameCount)
	continue; // Ignore those not seen in this frame.
      RealT conf = 1-((itt->MatchScore() / removeThresh) * 0.75); // Gives number between 0.25 and 1
      ret.InsLast(PointTrackC(itt->ID(),itt->Location(),conf));
    }
    return ret;
  }

  
  //: Init tracks
  void PointTrackerC::Init(const ImageC<ByteT> &img, ImageC<ByteT>* debugimg) {

    // Detect corners
    DListC<CornerC> cl;
    cl = cornerDet.Apply(img);

    // Drop corners that are too close to existing tracks
    for(DLIterC<PointTrackModelC> itt(tracks);itt;itt++) {
      for(DLIterC<CornerC> it(cl);it;it++) {
	// Is corner too close to one already being tracked ? 
	Point2dC cat = it->Location();
	if(itt->Location().SqrEuclidDistance(cat) < Sqr(mwidth)) {
	  ONDEBUG(DrawFrame(*debugimg,(ByteT) 0,IndexRange2dC(it->Location(),mwidth,mwidth)));
	  it.Del(); // Remove it.
	}
      }
    }

    // Make tracks for good corners
    for(DLIterC<CornerC> it(cl);it;it++) {
      IndexRange2dC fr(it->Location(),mwidth,mwidth);
      if(!img.Frame().Contains(fr))
         continue;
      Array2dC<ByteT> templ(img,fr,Index2dC(-mwidth/2,-mwidth/2));
      tracks.InsLast(PointTrackModelC(idAlloc++,it->Location(),frameCount,templ));
      ONDEBUG(DrawFrame(*debugimg,(ByteT) 255,IndexRange2dC(it->Location(),mwidth,mwidth)));
    }
    
    
  }

  //: Update tracks.
  IntT PointTrackerC::Update(const ImageC<ByteT> &img) {

    ONDEBUG(ImageC<ByteT> timg(img.Copy()));
    //ONDEBUG(ImageC<ByteT> timg(img.Frame()); timg.Fill(0));

    IntT removeThresh = Sqr(mwidth) * mthreshold;
    frameCount++; 
    for(DLIterC<PointTrackModelC> itt(tracks);itt;itt++) {
      Point2dC lookAtp =itt->EstimateLocation(frameCount);
      Index2dC lookAt(Round(lookAtp[0]),Round(lookAtp[1]));
      //cerr << "Vel=" << itt->Velocity() << "\n";
      if(!img.Frame().Contains(lookAt)) { // Has point left the image ?
	itt->SetLive(false);
	itt.Del();
	continue;
      }
      Point2dC at;
      IntT score = 100000000;
#if 0
      IndexRange2dC searchArea(lookAt,searchSize,searchSize);
      searchArea.ClipBy(img.Frame());
      SearchMinAbsDifference(itt->Template(),img,searchArea,at,score);
#else
      SearchGradientDecent(itt->Template(),img,lookAt,at,score);
#endif
      //cerr <<"Score=" << score << " At=" << at << " Thresh=" << removeThresh << "\n";
      if(score > removeThresh) {
	// Lost track of the object.
	if(itt->Frame() < (frameCount - lifeTime)) {
	  itt->SetLive(false);
	  itt.Del();  // Haven't seen it for a while, it can go!
	}
	ONDEBUG(DrawCross(timg,(ByteT) 0,itt->Location()));
	continue;
      }
      itt->Update(at,frameCount,score);
      ONDEBUG(DrawCross(timg,(ByteT) 255,at));
    }

    // If we're on the right frame, add new tracks
    if((frameCount-1) % newFreq == 0)
#if DODEBUG
      Init(img,&timg);
#else
      Init(img,NULL);
#endif
    
    ONDEBUG(Save("@X:Track",timg));
    return 1;
  }


  
}
