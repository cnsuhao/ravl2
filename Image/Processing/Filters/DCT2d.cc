// This file is part of RAVL, Recognition And Vision Library 
//
// Based on code from ImageLib, original copyright.
//  
//    This file forms a part of ImageLib, a C++ class library for image 
//    processing.
//
//    Copyright (C) 1998-2003 Brendt Wohlberg  <brendt@dip.ee.uct.ac.za>
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! license=own

// Modified by Charles Galambos

#include "Ravl/Image/DCT2d.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/StdConst.hh"

#define PIO2 1.5707966327

namespace RavlImageN {
  using namespace RavlConstN;
  
  static inline RealT Alpha(IndexC u, unsigned int N) {
    if (u == 0)
      return Sqrt(1/double(N));
    else if ((u > 0) && (u < N))
      return Sqrt(2/double(N));
    else
      return 0.0;
  }
  
  
  void DCT(const ImageC<RealT> & src, ImageC<RealT> & dest) {
    RavlAssertMsg(src.Rows() == src.Cols(),"DCT(): Images must be square.");
    
    if(dest.Frame() != src.Frame())
      dest = ImageC<RealT>(src.Frame());
    IndexC i,j,k;
    RealT sum;
    // Transform in x direction
    ImageC<RealT> horizontal(src.Frame());
    IndexRangeC rowRange = src.Range1();
    IndexRangeC colRange = src.Range2();
    for(Array2dIterC<RealT> it(horizontal);it;it++) {
      Index2dC at = it.Index();
      IntT i = at[0].V();
      IntT j = at[1].V();
      sum = 0.0;
      for (k = rowRange.Min(); k <= rowRange.Max(); k++)
	sum += src[k][j] * Cos(RealT(2*k+1)*pi*RealT(i)/(RealT(2*src.Cols())));
      *it = sum;
    }
    
    // Transform in y direction
    for(Array2dIterC<RealT> it(dest);it;it++) {
      Index2dC at = it.Index();
      IntT i = at[0].V();
      IntT j = at[1].V();
      sum = 0.0;
      for (k = colRange.Min(); k <= colRange.Max(); k++)
	sum += horizontal[i][k] * Cos(RealT(2*k+1)*pi*RealT(j)/(RealT(2*src.Rows()))); 
      *it = Alpha(i,src.Cols()) * Alpha(j,src.Rows())*sum; 
    }
  }
  
  void IDCT(const ImageC<RealT>& src, ImageC<RealT>& dest) {
    RavlAssertMsg(src.Rows() == src.Cols(),"IDCT(): Images must be square.");
    if(dest.Frame() != src.Frame())
      dest = ImageC<RealT>(src.Frame());
    IndexC i,j,k;
    IndexRangeC rowRange = src.Range1();
    IndexRangeC colRange = src.Range2();
    RealT sum;
    // Transform in x direction
    ImageC<RealT> horizontal(src.Frame());
    for(Array2dIterC<RealT> it(horizontal);it;it++) {
      Index2dC at = it.Index();
      IntT i = at[0].V();
      IntT j = at[1].V();
      sum = 0.0;
      for (k = rowRange.Min(); k <= rowRange.Max(); k++)
	sum += Alpha(k,src.Cols())*src[k][j]*Cos(RealT(2*i+1)*pi*RealT(k)/(RealT(2*src.Cols())));  
      *it = sum;
    }
    
    // Transform in y direction
    for(Array2dIterC<RealT> it(dest);it;it++) {
      Index2dC at = it.Index();
      IntT i = at[0].V();
      IntT j = at[1].V();
      sum = 0.0;
      for (k = colRange.Min(); k <= colRange.Max(); k++)
	sum += Alpha(k, src.Rows())*horizontal[i][k]*Cos(RealT(2*j+1)*pi*RealT(k)/(RealT(2*src.Rows()))); 
      *it = sum;
    }
  }
  
  

  /***************************************************************************

  class ChanDCTC is an encapsulation of sofware written by
  Charilaos A. Christopoulos (Email:chchrist@etro.vub.ac.be) - see
  header file for further details

  ***************************************************************************/

  ChanDCTC::ChanDCTC(unsigned int size)
  {
    m = (unsigned int)Ceil(Log(size)/log(2.0));
    N = (unsigned int)Pow(2.0, m);
    cosines = new float [N];
    makecosinetable();

    scaleDC = 1.0/(float)N;
    scaleMix = sqrt(2.0)/(float)N;
    scaleAC = 2.0 * scaleDC;
  }

  ChanDCTC::~ChanDCTC()
  {
    delete [] cosines;
  }
  
  void ChanDCTC::dct_in_place(ImageC<RealT>& dest) const
  {
    int n1,k,j,i,i1,l,n2,rows,cols,p;
    double c,xt;

    rowsinputmapping(dest);
    for (rows=0; rows<N; rows++) {
      p=0;
      n2 = N;
      for (k=1; k<m; k++) {
	n1 = n2;
	n2 = n2 >>1;
	for (j=0; j<n2; j++) {
	  c=cosines[p++];
	  for (i=j; i<N; i+=n1) {
	    l = i+n2;
	    xt = dest[rows][i] - dest[rows][l];
	    dest[rows][i] = dest[rows][i] + dest[rows][l];
	    dest[rows][l] = 2*xt * c;
	  }
	}
      }
      c = cosines[p++];
      for (i=0; i<N; i+=2) {
	i1 = i+1;
	xt = dest[rows][i];
	dest[rows][i] += dest[rows][i1];
	dest[rows][i1] = (xt-dest[rows][i1])* c;
      }
    }/* end of for rows */
    rowsbitreversal(dest);
    rowspostadditions(dest);

    columnsinputmapping(dest);	
    for (cols=0; cols<N; cols++) {
      p=0;
      n2 = N;
      for (k=1; k<m; k++) {
	n1 = n2;
	n2 = n2 >>1;
	for (j=0; j<n2; j++) {
	  c=cosines[p++];
	  for (i=j; i<N; i+=n1) {
	    l = i+n2;
	    xt = dest[i][cols] - dest[l][cols];
	    dest[i][cols] = dest[i][cols] + dest[l][cols];
	    dest[l][cols] = 2*xt * c;
	  }
	}
      }
      c = cosines[p++];
      for (i=0; i<N; i+=2) {
	i1 = i+1;
	xt = dest[i][cols];
	dest[i][cols] += dest[i1][cols];
	dest[i1][cols] = (xt-dest[i1][cols])* c;
      }
    }/* end of for cols */
    columnsbitreversal(dest);
    columnspostadditions(dest);
    
    //Scale coefficients
    dest[0][0] *= scaleDC;
    for (i = 1; i < N; i++)
      dest[i][0] *= scaleMix;
    for (j = 1; j < N; j++)
      dest[0][j] *= scaleMix;
    for (i = 1; i < N; i++)
      for (j = 1; j < N; j++)
	dest[i][j] *= scaleAC;
  }
  
  void ChanDCTC::DCT(const ImageC<RealT>& src, ImageC<RealT>& dest) const
  {
    RavlAssert( src.Cols() == (SizeT) N && src.Rows() == (SizeT) N ); 
    dest = src;
    dct_in_place(dest);
  }

  ImageC<RealT> ChanDCTC::DCT(const ImageC<RealT>& im) const
  {
    ImageC<RealT> ret(im);
    dct_in_place(ret);
    return ret;
  }

  void ChanDCTC::makecosinetable()
  {
    int n1,k,j,n2,p;
    double e;

    n2 = N;
    p=0;
    for (k=1; k<m; k++) {
      n1 = n2;
      n2 = n2 >>1;
      e = pi/(n1<<1);
      for (j=0; j<n2; j++) {
	cosines[p++] = Cos(((j<<2)+1)*e);
      }
    }
    cosines[p++] = Cos (pi_4);
  }

  void ChanDCTC::columnspostadditions(ImageC<RealT>& fi) const
  {
    int step,loops,k,ep,j,i,l,cols;

    for (cols=0; cols<N; cols++) {
      step =N;
      loops = 1;
      for (k=1; k<m; k++)  {
	step = step>>1;
	ep = step>>1;
	loops = loops <<1;
	for (j=0; j<(step>>1); j++) {
	  l=ep;
	  fi[l][cols] = fi[l][cols]/2;

	  for (i=1; i<loops; i++)  {
	    fi[l+step][cols] = fi[l+step][cols] - fi[l][cols];
	    l =l+step;
	  }
	  ep +=1;
	}
      }
    }
  }

  void ChanDCTC::rowspostadditions(ImageC<RealT>& fi) const
  {
    int step,loops,k,ep,j,i,l,rows;

    /* Postaditions for the columns */
    for (rows=0; rows<N; rows++) {
      step =N;
      loops = 1;
      for (k=1; k<m; k++)  {
	step = step>>1;
	ep = step>>1;
	loops = loops <<1;
	for (j=0; j<(step>>1); j++) {
	  l=ep;
	  fi[rows][l]= fi[rows][l]/2;
	  for (i=1; i<loops;i++)  {
	    fi[rows][l+step] = fi[rows][l+step]- fi[rows][l];
	    l =l+step;
	  }
	  ep +=1;
	}
      }
    }
        
  }

  void ChanDCTC::rowsbitreversal(ImageC<RealT>& fi) const
  {
    int v1, v2, v3,i,j,k,cols;
    double xt;

    /* revesre rows */
    for (cols =0; cols<N; cols ++) {   
      v1 = (m+1)/2; 
      v2 = 1 << v1; 
      v3 = N-1-v2;
      j=0;
      for(i=1; i<=v3; i++){
	k= N>>1;
	while(k<=j){
	  j=j-k; 
	  k=k>>1;
	}
	j +=k;
	if(i<j){
	  xt=fi[cols][j];
	  fi[cols][j]= fi[cols][i];
	  fi[cols][i]=xt;
	}
      }
    }
  }

  void ChanDCTC::columnsbitreversal(ImageC<RealT>& fi) const
  {
    int v1, v2, v3,i,j,k,rows;
    double xt;
    /* reverse columns */
    for (rows =0; rows<N; rows ++) {   
      v1 = (m+1)/2; 
      v2 = 1 << v1; 
      v3 = N-1-v2;
      j=0;
      for(i=1; i<=v3; i++){
	k= N>>1;
	while(k<=j){
	  j=j-k; 
	  k=k>>1;
	}
	j +=k;
	if(i<j){
	  xt=fi[j][rows];
	  fi[j][rows] =fi[i][rows];
	  fi[i][rows] =xt;
	}
      }
    }
  }

  void ChanDCTC::columnsinputmapping(ImageC<RealT>& fi) const
  {
    int n1,n2,rows,n;
    ImageC<RealT> s(fi.Frame()); //double s[512][512];

    for(n1=0; n1 < N; n1++) 
      for (n2=0; n2<N; n2++ ) 
	s[n1][n2] = fi[n1][n2];

    for (rows=0; rows<N; rows++) {
      for(n=0; n < N/2; n++) {
	fi[n][rows]     = s[2*n][rows];
	fi[N-n-1][rows] = s[2*n+1][rows];
      }
    }
  }
  
  void ChanDCTC::rowsinputmapping(ImageC<RealT>& fi) const
  {
    int n1,n2,cols,n;
    ImageC<RealT> s(fi.Frame()); //double s[512][512];

    for(n1=0; n1 < N; n1++) 
      for (n2=0; n2<N; n2++ )
	s[n1][n2] = fi[n1][n2];

    for (cols=0; cols<N; cols++) {
      for(n=0; n < N/2; n++) {
	fi[cols][n]     = s[cols][2*n];
	fi[cols][N-n-1] = s[cols][2*n+1];
      }
    }
	
  }

  /***************************************************************************

  class VecRadDCT is an encapsulation of sofware written by
  Charilaos A. Christopoulos (Email:chchrist@etro.vub.ac.be) - see
  header file for further details

  ***************************************************************************/
  
  VecRadDCTC::VecRadDCTC(unsigned int size, unsigned int pts)
  {
    Initialise(size, pts);
  }

  VecRadDCTC::VecRadDCTC()
  {
    m = 0;
    N = 0;
    N0 = 0;
  }

  void VecRadDCTC::Initialise(unsigned int size, unsigned int pts)
  {
    m = (unsigned int)Ceil(Log(size)/Log(2.0));
    N = (unsigned int)Pow(2.0, (float)m);
    N0 = (unsigned int)Pow(2.0, Ceil(Log(pts)/Log(2.0))); // must be power of 2
    
    int i;
    r = new unsigned int * [N];
    for (i = 0; i < N; i++)
      r[i] = new unsigned int [N];
    cosine_array = new float [N*m];
    ct = new float [N];
    ct2d = new float [N*N*m];
 
    MASK[0] = 0;
    MASK[1] = ~((-1) << m);

    lut_of_cos();
    expand1d_lookup_table();
    make2Darray();

    scaleDC = 1.0/(float)N;
    scaleMix = sqrt(2.0)/(float)N;
    scaleAC = 2.0 * scaleDC;
  }

  VecRadDCTC::~VecRadDCTC()
  {
    int i;
    for (i = 0; i < N; i++)
      delete [] r[i];
    delete [] r;
  
    delete [] cosine_array;
    delete [] ct;
    delete [] ct2d;
  
  }


  void VecRadDCTC::dct_in_place(ImageC<RealT>& dest) const
  {
    int stage,q,bB;
    int i,j;
    int k1,k2,yi,yi1,yi2,xj,xj1,xj2,mmax,istep,step;
    double S0,S1,S2,S3;
    float sum1,sum2,diff1,diff2;

    firo3(dest);
 	
    /* decimation in time DCT */

    /* Perform the first stage of the transform */
    istep=2;
    step=0;
 
    for (yi=0; yi<N; yi+=2) {
      yi1 = yi;
      yi2 = yi1+1;
      for (xj=0; xj<N; xj +=2) {
	xj1=xj;
	xj2=xj1+1;
 
	S0=dest[yi1][xj1]; 
	S1=dest[yi2][xj1];
	S2=dest[yi1][xj2];
	S3=dest[yi2][xj2];  
	
	sum1 = S0 + S1;
	sum2 = S2 + S3;
	diff1= S0 - S1;
	diff2= S2 - S3;
 
	dest[yi1][xj1] = sum1+sum2;
	dest[yi2][xj1] = (diff1+diff2)*ct2d[step++];
	dest[yi1][xj2] = (sum1-sum2)* ct2d[step++];
	dest[yi2][xj2] = (diff1-diff2)*ct2d[step++] ;
      }
    }
 
    /* Perfrom the remaining stages of the transform */
    stage=0;
    bB=1;
    mmax=2;
    while (N>mmax) {
      stage++;
      bB=bB<<2;
      q=N0*N0/bB;
      istep=2*mmax;
      
      for (k1=0; k1<mmax; k1++) {
	for (k2=0; k2<mmax; k2++) {
	  for (yi=k1; yi<N; yi+=istep) {
	    yi1=yi; 
	    yi2=yi1+mmax;
	    for (xj=k2; xj<N; xj+=istep) {
	      xj1=xj;
	      xj2=xj1+mmax;
		
	      S0=dest[yi1][xj1];
	      S1=dest[yi2][xj1];
	      S2=dest[yi1][xj2];
	      S3=dest[yi2][xj2];

	      sum1=S0+S1;
	      sum2 = S2+S3;
	      diff1=S0-S1;
	      diff2 = S2-S3;

	      if (q<=1) {
		dest[yi1][xj1] = sum1+sum2;
		step += 3;
	      }

	      if (q>1) {
		dest[yi1][xj1] = sum1+sum2;
		dest[yi2][xj1]=(diff1+diff2)*ct2d[step++];
		dest[yi1][xj2]=(sum1-sum2)*ct2d[step++] ;
		dest[yi2][xj2]=(diff1-diff2)*ct2d[step++] ;
	      }
	    }  
	  }  
	}  
      }  
      mmax = istep;
    }  

    post_adds(dest);
    //Scale coefficients
    dest[0][0] *= scaleDC;
    for (i = 1; i < N0; i++)
      dest[i][0] *= scaleMix;
    for (j = 1; j < N0; j++)
      dest[0][j] *= scaleMix;
    for (i = 1; i < N0; i++)
      for (j = 1; j < N0; j++)
	dest[i][j] *= scaleAC;
    
    dest = ImageC<RealT>(dest,IndexRange2dC(0,N0,0, N0)); //Inefficient
  }

  void VecRadDCTC::DCT(const ImageC<RealT>& src, ImageC<RealT>& dest) const {
    RavlAssert( src.Cols() == (SizeT) N && src.Rows() == (SizeT)N );
    dest = src;
    dct_in_place(dest);
  }

  ImageC<RealT> VecRadDCTC::DCT(const ImageC<RealT>& im) const {
    ImageC<RealT> ret(im);
    dct_in_place(ret);
    return ret;
  }

  void VecRadDCTC::lut_of_cos()
  {
    int e,i,k,l,p,t,inc,len,mm1;

    unsigned int *et = new unsigned int [N];
    p=0; mm1=m-1; e=1;

    for(k=0; k<m; k++)
      {
	len=1; inc=N; i=0;
	et[i]=e; i++; ct[p]=2 * Cos(PIO2 * e / N); p++;
	for(t=0; t<mm1; t++)
	  {
	    for(l=0; l<len; l++)
	      {
		et[i] = et[l] + inc;
		ct[p] = 2 * Cos(et[i] * PIO2 /N);
		i++;  p++;
	      }
	    len = len << 1; inc=inc >> 1;
	  }
	e = e << 1; mm1=mm1-1;
      }

    delete [] et;
  }

  void VecRadDCTC::expand1d_lookup_table()
  {
    int i,j,k,l,p,q,r,Bs, bB,bls,ble,ncb = 0,value,step;
    double c;
    value=0;

    Bs = N;  bB = bls = 1;  p = 0; step=0;

    for(k=0; k<m; k++)
      {
	Bs=Bs>>1; q=N/bB; r=N%bB; ble=step; bls=bls<<1;

	if(q==1) {ncb=r;}
	if(q<1)  {ncb=0;} 
	if(q>1)  {ncb=bB;}

	for(j=0; j<Bs; j++)
	  {
	    l=ble; c=ct[p]; p++;
	    for(i=0; i<ncb; i++)
	      {
		cosine_array[l+step] = 1.0;
		cosine_array[step+l+bB]=c;
		value++;
		l++;
	      }

	    ble += bls;
	  }
	bB=bB<<1;
	step += N/2;
      }
  }

  void VecRadDCTC::make2Darray()
  {
    int ND1,MD1;
    int k1,k2,yi,yi1,yi2,xj,xj1,xj2,mmax,istep,cos_step,step;
 
    ND1=0;
    MD1=0;
    cos_step=0;
    step=0;
 
    for (yi=0; yi<N; yi+=2) {
      yi1 = yi+MD1;
      yi2 = yi1+1;
      for (xj=0; xj<N; xj +=2) {
	xj1=xj+ND1;
	xj2=xj1+1;
	ct2d[step ++] =  cosine_array[yi2]*cosine_array[xj1];
	ct2d[step ++] =  cosine_array[yi1]*cosine_array[xj2];
	ct2d[step ++] =  cosine_array[yi2]*cosine_array[xj2];
      }
    }
    /* Find cosines for the remaining stages of the transform */
    mmax=2;
    while (N>mmax) {
      cos_step +=N;
      istep=2*mmax;

      for (k1=0; k1<mmax; k1++) {
	for (k2=0; k2<mmax; k2++) {
	  for (yi=k1; yi<N; yi+=istep) {
	    yi1=yi+MD1; 
	    yi2=yi1+mmax;
	    for (xj=k2; xj<N; xj+=istep) {
	      xj1=xj+ND1;
	      xj2=xj1+mmax;
		 			
	      ct2d[step ++]=cosine_array[cos_step+yi2]*
		cosine_array[cos_step+xj1];
	      ct2d[step ++]=cosine_array[cos_step+yi1]*
		cosine_array[cos_step+xj2];
	      ct2d[step ++]=cosine_array[cos_step+yi2]*
		cosine_array[cos_step+xj2];

	    } /* x*/
	  } /*y */
	} /* k2 */
      } /* k1 */
      mmax = istep;
    } /* while */
  
  }

  void VecRadDCTC::firo3(ImageC<RealT>& fi) const
  {
    int i,j,eo,group,nog,p,q,F,M,a,b,rows,cols;
    double t;

    M=m;
    bitreversalrows();
 
    for (rows=0; rows<N; rows++) {
      M=m;
      eo = M%2; M = m>>1;
      group = nog = 1<<M;
      if(eo==1) M++;

      /*..................... M=even/odd ..........................*/

      for(i=0; i<(nog-1); i++)
	{
	  F=0; q=i<<M; p=q>>1;
	  for(j=1; j<group; j++)
	    {
	      F=1-F; q++;
	      a=((r[p][rows]<<1)^MASK[F]); /* CC*/
	      b=q;  /*CC*/
	      t=fi[a][rows]; /*CC*/
	      fi[a][rows] = fi[b][rows]; /*CC*/
	      fi[b][rows] = t;/*CC*/
	      p += F;
	    }
	  group--;
	}

      if(eo==0) ; else

	/*....................... M=odd ..........................*/

	{ group=nog;

	for(i=1; i<nog; i++)
	  {
	    F=0; q=i<<M; p=q>>1; p--; q--;
	    for(j=1; j<group; j++)
	      {
		q--;
		a=((r[p][rows]<<1)^MASK[F]); /* CC*/
		b=q;  /*CC*/
		t=fi[a][rows]; /*CC*/
		fi[a][rows] = fi[b][rows]; /*CC*/
		fi[b][rows] = t;/*CC*/

		F=1-F;   p -= F;
	      }
	    group--;
	  }
	} /* end of 'if' statement */
    } /* end for rows */
  
    bitreversalcolumns();
 
    /* Input reordering for the columns */
    for (cols=0; cols<N; cols++) {
      M=m;
      eo = M%2; M = m>>1;
      group = nog = 1<<M;
      if(eo==1) M++;

      /*..................... M=even/odd ..........................*/

      for(i=0; i<(nog-1); i++)
	{
	  F=0; q=i<<M; p=q>>1;
	  for(j=1; j<group; j++)
	    {
	      F=1-F; q++;
	      a=((r[cols][p]<<1)^MASK[F]); /* CC*/
	      b=q;  /*CC*/
	      t=fi[cols][a]; /*CC*/
	      fi[cols][a] = fi[cols][b]; /*CC*/
	      fi[cols][b] = t;/*CC*/
	      p += F;
	    }
	  group--;
	}

      if(eo==0) ; else

	/*....................... M=odd ..........................*/

	{ group=nog;

	for(i=1; i<nog; i++)
	  {
	    F=0; q=i<<M; p=q>>1; p--; q--;
	    for(j=1; j<group; j++)
	      {
		q--;
		a=((r[cols][p]<<1)^MASK[F]); /* CC*/
		b=q;  /*CC*/
		t=fi[cols][a]; /*CC*/
		fi[cols][a] = fi[cols][b]; /*CC*/
		fi[cols][b] = t;/*CC*/

		/*swap( ((r[cols][p]<<1)^MASK[F]), q );*/
		F=1-F;   p -= F;
	      }
	    group--;
	  }
	} /* end of 'if' statement */
    } /* end for rows */
  }

  void VecRadDCTC::bitreversalrows() const
  {
    int i,j,l,rows;

    for (rows=0; rows<N; rows++) {
      l=1; 
      r[0][rows]=0;
      for(i=1; i < m; i++)
	{
	  for(j=0; j < l; j++) {r[j][rows]<<= 1; r[j+l][rows]=r[j][rows] + 1; }
	  l <<= 1;
	}
    } /* end for rows */
  }

  void VecRadDCTC::bitreversalcolumns() const
  {
    int i,j,l,cols;
    for (cols=0; cols<N; cols++) {
      l=1; 
      r[cols][0]=0;
      for(i=1; i < m; i++)
	{
	  for(j=0; j < l; j++) {r[cols][j]<<= 1;r[cols][j+l]=r[cols][j] +  1;}
	  l <<= 1;
	}
    } /* end for cols */
  }
  
  void VecRadDCTC::post_adds(ImageC<RealT>& fi) const
  {
    int step,loops,k,ep,j,i,l,cols,rows;

    /* Do divisions by 2 */
    for (i=0; i<N; i++) 
      for (j=1; j<N; j++) 
	fi[i][j] = fi[i][j]/2;
      
    for (i=1; i<N; i++) 
      for (j=0; j<N; j++)
	fi[i][j] = fi[i][j]/2;

    /* Postadditions for the rows */
    for (cols=0; cols<N; cols++) {
      step =N;
      loops = 1;
      for (k=1; k<m; k++)  {
	step = step>>1;
	ep = step>>1;
	loops = loops <<1;
	for (j=0; j<(step>>1); j++) {
	  l=ep;
	  for (i=1; i<loops; i++)  {
	    fi[l+step][cols] = fi[l+step][cols] - fi[l][cols];
	    l =l+step;
	  }
	  ep +=1;
	}
      }
    }
      
    /* Postaditions for the columns */
    for (rows=0; rows<N; rows++) {
      step =N;
      loops = 1;
      for (k=1; k<m; k++)  {
	step = step>>1;
	ep = step>>1;
	loops = loops <<1;
	for (j=0; j<(step>>1); j++) {
	  l=ep;
	  for (i=1; i<loops; i++)  {
	    fi[rows][l+step] = fi[rows][l+step]-fi[rows][l];
	    l =l+step;
	  }
	  ep +=1;
	}
      }
    }
     
  }
}
