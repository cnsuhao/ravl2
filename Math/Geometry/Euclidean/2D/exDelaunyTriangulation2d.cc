// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/DelaunyTriangulation2d.hh"
#include "Ravl/Option.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/THEMeshFaceIter.hh"
#include "Ravl/Random.hh"
#include "Ravl/IO.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC file = opt.String("f","@X","Output file. ");
  IntT npnts = opt.Int("p",5,"Number of points to use. ");
  IntT seed = opt.Int("rs",1,"Random number seed. ");
  Index2dC size = opt.Index2d("s",300,300,"Size of image. ");
  opt.Check();
  
  RandomSeedDefault(seed);
  
  ImageC<ByteT> img(size[0],size[1]);
  img.Fill(0);
  
  SArray1dC<Point2dC> pnts(npnts);
  
  // Generate a point set.
  for(UIntT i = 0;i < pnts.Size();i++)
    pnts[i] = Point2dC(Random1() * size[0],Random1() * size[1]);
  
  HEMesh2dC mesh = DelaunyTriangulation(pnts);
  
  for(THEMeshFaceIterC<Point2dC> mit(mesh.Faces());mit;mit++) {
    for(THEMeshFaceEdgeIterC<Point2dC> eit(*mit);eit;eit++)
      RavlImageN::DrawLine(img,(ByteT) 255,
			   Index2dC((*eit).Vertex().Data()),
			   Index2dC((*eit).Prev().Vertex().Data()));
  }
  
  Save(file,img);
  return 0;
}
