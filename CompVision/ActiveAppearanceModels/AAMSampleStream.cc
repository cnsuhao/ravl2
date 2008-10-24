// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMSampleStream.cc"

#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Image/AAMAppearanceUtil.hh"
#include "Ravl/Image/AAMSampleStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  //: Constructor.
  AAMSampleStreamBodyC::AAMSampleStreamBodyC(const AAMAppearanceModelC &nam,
                                             const GaussConvolve2dC<RealT> &psmooth,
                                             const DListC<StringC> &pfileList,
                                             const StringC &pdir,
                                             const StringC &pmirrorFile, 
                                             const UIntT pincrSize,
                                             bool ignoreSuspect
                                             )
    : am(nam),
      smooth(psmooth),
      flit(pfileList),
      dir(pdir),
      samplesPerFrame(0),
      sampleNo(0),
      incrSize(pincrSize),
      done(false),
      m_ignoreSuspect(ignoreSuspect)
  {
    if (pmirrorFile.IsEmpty()) {
      frames = pfileList.Size();
    }
    else {
      frames = 2*pfileList.Size();
      mirror = AAMAppearanceMirrorC(pmirrorFile);
    }
    samplesPerFrame = am.Dimensions() * 2*incrSize + 1;
  }

  //: Seek to location in stream.
  bool AAMSampleStreamBodyC::Seek(UIntT off) {
    ONDEBUG(cerr << "AAMSampleStreamBodyC::Seek(), Offset=" << off << "\n");
    if(off == 0) {
      done = false;
      flit.First();
      sampleNo = 0;
      return true;
    }
    return false;
  }

  //: Find the total size of the stream. (assuming it starts from 0)
  UIntT AAMSampleStreamBodyC::Size() const
  { return frames * samplesPerFrame; }

  //: Get next piece of data.
  Tuple2C<VectorC,VectorC> AAMSampleStreamBodyC::Get() {
    Tuple2C<VectorC,VectorC> ret;
    if(!Get(ret))
      throw DataNotReadyC("Out of samples.");
    return ret;
  }

  //: Try and get next piece of data.
  bool AAMSampleStreamBodyC::Get(Tuple2C<VectorC,VectorC> &buff) {
    if(done)
      return false;
    UIntT subNo = sampleNo % samplesPerFrame;
    if(subNo == 0) { // First from frame ?
      UIntT frameNo = sampleNo/samplesPerFrame;
      
      if(sampleNo != 0) {
        if (!mirror.IsValid() || (mirror.IsValid() && frameNo%2==0)) {
          flit++;
        }
        if(!flit) {
          done = true;
          return false;
        }
      }
      
      AAMAppearanceC appear = LoadFeatureFile(*flit,dir,m_ignoreSuspect);
      if(mirror.IsValid() && frameNo%2==1) {
        appear = mirror.Reflect(appear);
      }
      
      ONDEBUG(cerr << "AAMSampleStreamBodyC::Get(), Frame=" << (sampleNo / samplesPerFrame) << " " << appear.SourceFile()  << "\n");
      
      // Sort out a real image.
      if(image.Frame() != appear.Image().Frame())
        image = ImageC<RealT>(appear.Image().Frame());
      for(Array2dIter2C<RealT,ByteT> it(image,appear.Image());it;it++)
        it.Data1() = it.Data2();
      
      // smooth the image
      image = smooth.Apply(image);
      
      // Compute true parameters.
      
      trueVec = am.Parameters(appear);
      deltaVec = trueVec.Copy();
      
      // Generate entry with no errors.
      
      buff.Data2() = VectorC(trueVec.Size());
      buff.Data2().Fill(0);
      // Compute residual error
      if(am.ErrorVector(trueVec,image,buff.Data1())==false)
        cerr << "Marked up points out of image range" << endl;
      
      sampleNo++;
      return true;
    }
    subNo--;
    UIntT paramNo = subNo / (2*incrSize);
    UIntT incrNo = subNo % (2*incrSize);
    
    RealT trueVal = trueVec[paramNo];

    RealT maxVar;
    switch (paramNo)
    {
      case 0: // tx
        maxVar = 3*am.PixelSize()[0];
        break;
      case 1: // ty
        maxVar = 3*am.PixelSize()[1];
        break;
      case 2: // sx
      case 3: // sy
      case 4: // u1
      case 5: // u2
        maxVar = 0.1 * trueVal;
        break;
      default:
        maxVar = 0.5 * Sqrt(am.EigenValues()[paramNo]);
    }

    bool isInRange;
    // Change parameters.
    do {
      deltaVec[paramNo] = trueVal + (-1.0 + incrNo*2.0/(2*incrSize - 1)) * maxVar;
      // Compute residual error.
      isInRange = am.ErrorVector(deltaVec,image,buff.Data1());
      maxVar /= 2;
    } while(isInRange==false);

    buff.Data2() = deltaVec - trueVec;
    deltaVec[paramNo] = trueVal;
    sampleNo++;
    return true;
  }

  //: Has the End Of Stream been reached ?
  // true = yes.
  bool AAMSampleStreamBodyC::IsGetEOS() const {
    return true;
  }


}
