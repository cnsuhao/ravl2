// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Array2d.i"
%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/IO.i"
%include "Ravl/Swig/String.i"
%include "Ravl/Swig/Polygon2d.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/DrawPolygon.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {
  %template(ByteRGBArray2dC) Array2dC<RavlImageN::ByteRGBValueC>;
  %template(RealRGBArray2dC) Array2dC<RavlImageN::RealRGBValueC>;
}

namespace RavlImageN {
  using namespace RavlN;

  class RealRGBValueC {
  public:
    RealRGBValueC(RealT r,RealT g,RealT b);

    RealT Red() const;
    RealT Green() const;
    RealT Blue() const;
  };

  class ByteRGBValueC {
  public:
    ByteRGBValueC(IntT r,IntT g,IntT b);

    IntT Red() const;
    IntT Green() const;
    IntT Blue() const;
  };


  template<typename PixelT>
  class ImageC
    : public RavlN::Array2dC<PixelT>
  {
  public:
    ImageC();
    ImageC(SizeT rows,SizeT cols);
    ImageC(const IndexRange2dC &range);
    ImageC(SizeT rows, SizeT cols, PixelT * data, bool deletable = true);    
    ImageC(const ImageC<PixelT> &img,const IndexRange2dC &range);
    // Take a sub image.

    SizeT Rows() const;
    SizeT Cols() const;
    PixelT * Row(IndexC row);
    IntT Stride() const;

#ifdef SWIGPYTHON

    %extend
    {
      PyObject* DataAsString()
      {
        if (self->Rows() <= 0 || self->Cols() <= 0)
          return NULL;

        if (!self->IsContinuous())
          return NULL;

        RavlN::BufferAccessC<PixelT> rowAccess = self->RowPtr(0);
        const char* imageData = reinterpret_cast<const char*>(rowAccess.ReferenceVoid());
        if (imageData == NULL)
          return NULL;

        const int imageSize = self->Rows() * self->Stride() * sizeof(PixelT);
        return PyString_FromStringAndSize(imageData, imageSize);
      }
    }

    %extend
    {
      PyObject* DataAsStringTriple()
      {
        if (self->Rows() <= 0 || self->Cols() <= 0)
          return NULL;

        if (!self->IsContinuous())
          return NULL;

        RavlN::BufferAccessC<PixelT> rowAccess = self->RowPtr(0);
        const char* imageData = reinterpret_cast<const char*>(rowAccess.ReferenceVoid());
        if (imageData == NULL)
          return NULL;

        const int imageSize = self->Rows() * self->Stride() * sizeof(PixelT);
        const int outImageSize = imageSize * 3;
        char* outImageData = new char[outImageSize];
        if (outImageData)
        {
          const char* srcImagePtr = imageData;
          char* dstImagePtr = outImageData;
          for (int index = 0; index < imageSize; index++)
          {
            *dstImagePtr = *srcImagePtr;
            ++dstImagePtr;

            *dstImagePtr = *srcImagePtr;
            ++dstImagePtr;

            *dstImagePtr = *srcImagePtr;
            ++dstImagePtr;

            ++srcImagePtr;
          }
          PyObject* pyObject = PyString_FromStringAndSize(outImageData, outImageSize);
          delete [] outImageData;
          return pyObject;
        }
        return NULL;
      }
    }

#endif
  };

  %template(ImageByteRGBValueC) ImageC<ByteRGBValueC>;
  %template(ImageByteC) ImageC<ByteT>;

  bool Save(StringC,const ImageC<ByteT> &);
  bool Load(StringC,ImageC<ByteT> &);
  bool Save(StringC,const ImageC<RealT> &);
  bool Load(StringC,ImageC<RealT> &);
  bool Save(StringC,const ImageC<ByteRGBValueC> &);
  bool Load(StringC,ImageC<ByteRGBValueC> &);
  bool Save(const char *,const ImageC<ByteRGBValueC> &);
  bool Load(const char *,ImageC<ByteRGBValueC> &);

  void DrawPolygon(Array2dC<ByteRGBValueC> &,const ByteRGBValueC &,const Polygon2dC &poly,bool fill=false);
  void DrawPolygon(Array2dC<ByteT> &,const ByteT &,const Polygon2dC &poly,bool fill=false);
}



