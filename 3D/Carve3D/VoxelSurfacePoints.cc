#include "Ravl/3D/VoxelSurfacePoints.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"

namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;

  PointSetC VoxelSurfacePoints(const VoxelSetC vox,
			       SArray1dC< ImageC<ByteRGBAValueC> > image,
			       const Pinhole0ArrayC& camera,
			       const Vector3dC& viewpoint)
  {
    // lists for surface points
    DListC<Vector3dC> listPosition;
    DListC<Vector3dC> listNormal;
    DListC<ByteRGBValueC> listColour;

    // number of voxels per side
    int n = vox.Array().Range1().Size();

    // occupied threshold
    ByteT mask = vox.OccupiedThreshold();

    // transform to world co-ords from voxels
    Matrix3dC R = vox.R() * vox.voxelSize();
    Vector3dC t = vox.R().TMul(vox.t()) * -1.0;
   
    bool colour = (image.Size() > 0 && camera.Size() > 0) ? true : false;
   
    UIntT sx(0), sy(0);
    if (colour)
    {
      sx = image[0].Cols();
      sy = image[0].Rows();
    }

#if 0
    // add all points
    for (UIntT i = 0; i < n; i++)
      for (UIntT j = 0; j < n; j++)
	for (UIntT k = 0; k < n; k++)
	  if (vox[i][j][k] == mask)
	    listPosition.InsLast( R*Vector3dC(i,j,k) + t);
#endif


#if 1
    int n_minus_1 = n - 1;
    int n2 = n*n;
    const ByteT* p0 = &vox.Array()[0][0][0];

    p0 += n2; // avoid first slice
    for (int i = 1; i < n_minus_1; i++)
    {
      p0 += n; // avoid first row
      for (int j = 1; j < n_minus_1; j++)
      {
	p0++; // avoid first cell
	for (int k = 1; k < n_minus_1; k++, p0++)
	{
	  // cerr << "i j k: " << i << " " << j << " " << k << endl;

	  if (*p0 == mask && 
	      (*(p0+1)  != mask || *(p0-1)  != mask ||
	       *(p0+n)  != mask || *(p0-n)  != mask ||
	       *(p0+n2) != mask || *(p0-n2) != mask))
	  {
	    // compute normal
	    int nx(0), ny(0), nz(0);
	    for (int ci = -1; ci <= 1; ci++)
	      for (int cj = -1; cj <= 1; cj++)
		for (int ck = -1; ck <= 1; ck++)
		  if (*(p0+(n2*ci + n*cj + ck)) == mask)
		  {
		    nx -= ci;
		    ny -= cj;
		    nz -= ck;
		  }

	    if (nx || ny || nz)
	      {
	    

#if 0
	      // normal computation: 6-connected
	      
	      if (*(p0-1) == mask)
		nz++;
	      
	      if (*(p0+1) == mask)
		nz--;
	      
	      if (*(p0-n) == mask)
		ny++;
	      
	      if (*(p0+n) == mask)
		ny--;
	      
	      if (*(p0-n2) == mask)
		nx++;
	      
	      if (*(p0+n2) == mask)
		nx--;
#endif

	      // FIXME: transformation should not really be applied here 
	      //        should be done only during rendering
	      // surface voxel
	      RealT r_norm = 1.0 / sqrt(nx*nx + ny*ny + nz*nz);
	      Vector3dC x = R*Vector3dC(i,j,k) + t;
	      Vector3dC n = R*Vector3dC(nx*r_norm,ny*r_norm,nz*r_norm);
	      
	      // insert into lists
	      listNormal.InsLast(n);
	      listPosition.InsLast(x);

	      if (colour)
	      {
		// compute colour
		RealT sum_weight(0.0);
		RealT r(0.0), g(0.0), b(0.0);
		for (UIntT iview = 0; iview < camera.Size(); iview++)
		{
		  const PinholeCamera0C& cam_view = camera[iview];
		  Vector3dC origin;
		  cam_view.Origin(origin);
		  RealT weight = Vector3dC(origin-x).Unit().Dot(Vector3dC(viewpoint-x).Unit());
		  if (weight <= 0.0)
		    continue;

		  // project voxel into camera plane
		  Vector2dC z;
		  if (!cam_view.ProjectCheck(z, x))
		    continue;
		  if (z[0] < 1 || z[0] >= sx ||
		      z[1] < 1 || z[1] >= sy)
		    continue;

		  // FIXME: this should use a bilinear sample of colour at z
		  ByteRGBAValueC& col = 
		    image[iview][(UIntT)(z[1]+0.5)][(UIntT)(z[0]+0.5)];

		  // weighted colour value
		  r += weight*col[0];
		  g += weight*col[1];
		  b += weight*col[2];

		  // sum weights
		  sum_weight += weight;
		}

		if (sum_weight > 0.0)
		{
		  listColour.InsLast(ByteRGBValueC((ByteT)(r/sum_weight+0.5),
						   (ByteT)(g/sum_weight+0.5),
						   (ByteT)(b/sum_weight+0.5)));
		}
		else
		{
		  listColour.InsLast(ByteRGBValueC(0,0,0));
		}
	      }
	    } 
	  }
	}
	p0++; // skip last cell
      }
      p0 += n; // skip last row
    }
#endif

    PointSetC points(listPosition.Size(), colour);
    UIntT count = 0;
    DLIterC<Vector3dC> ipoint(listPosition);
    DLIterC<Vector3dC> inorm(listNormal);
    DLIterC<ByteRGBValueC> icolour(listColour);
    for (; ipoint; ipoint++, inorm++, count++)
    {
      points.Vertices()[count].Position() = *ipoint;
      points.Vertices()[count].Normal() = *inorm;
      if (colour)
      {
	points.Colours()[count] = *icolour;
	icolour++;
      }
    }
    return points;
  }
}
