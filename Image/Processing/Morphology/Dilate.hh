// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/Image/Image.hh"
//! rcsid="$Id$"
//! lib=RavlImage

namespace RavlImageN
{
  template<class DataT> void Dilate(ImageC<DataT>& result, const ImageC<DataT>& image, const ImageC<DataT>& kernel)
  {
    RavlAssert(result.Cols() == image.Cols());
    RavlAssert(result.Rows() == image.Rows());
    RavlAssert(kernel.Cols() % 2 == 1); // odd number of cols
    RavlAssert(kernel.Rows() % 2 == 1); // odd number of rows

    UIntT sx = image.Cols();
    UIntT sy = image.Rows();

    UIntT kx = kernel.Cols() / 2;
    UIntT ky = kernel.Rows() / 2;
    
    UIntT i_end_max = sx - kx - 1;
    UIntT j_end_max = sy - ky - 1;

    for (UIntT y = 0; y < sy; y++)
    {
      UIntT j_start = ((y < ky) ? 0 : (y-ky));
      UIntT j_end = ((y > j_end_max) ? j_end_max : (y+ky));

      for (UIntT x = 0; x < sx; x++)
      {
	UIntT i_start = ((x < kx) ? 0 : (x-kx));
	UIntT i_end = ((x > i_end_max) ? i_end_max : (x+kx));

	result[y][x] = 0;

	for (UIntT j = j_start; j <= j_end && !result[y][x]; j++)
	{
	  for (UIntT i = i_start; i <= i_end && !result[y][x]; i++)
	  {
	    if (kernel[ky+j-y][kx+i-x] && image[j][i])
	      result[y][x] = 255;
	  }
	}
      }
    }
  }
  //: image dilation

}
