// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCCMATH_HEADER
#define RAVLCCMATH_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/CCMath/CCMath.hh"

extern "C" {
  
  int minv(double *a,int n) ;
  int psinv(double *v,int n) ;
  int ruinv(double *a,int n) ;
  int solv(double *a,double *b,int n) ;
  int solvps(double *s,double *x,int n) ;
  int solvru(double *a,double *b,int n) ;
  void solvtd(double *a,double *b,double *c,double *x,int m) ;
  void eigen(double *a,double *eval,int n) ;
  void eigval(double *a,double *eval,int n) ;
  double evmax(double *a,double *u,int n) ;
  int svdval(double *d,double *a,int m,int n) ;
  int sv2val(double *d,double *a,int m,int n) ;
  int svduv(double *d,double *a,double *u,int m,double *v,int n) ;
  int sv2uv(double *d,double *a,double *u,int m,double *v,int n) ;
  int svdu1v(double *d,double *a,int m,double *v,int n) ;
  int sv2u1v(double *d,double *a,int m,double *v,int n) ;
  void mmul(double *mat,double *a,double *b,int n) ;
  void rmmult(double *mat,double *a,double *b,int m,int k,int n) ;
  void vmul(double *vp,double *mat,double *v,int n) ;
  double vnrm(double *u,double *v,int n) ;
  void matprt(double *a,int n,int m,char *fmt) ;
  void trnm(double *a,int n) ;
  void mattr(double *a,double *b,int m,int n) ;
  void otrma(double *at,double *u,double *a,int n) ;
  void otrsm(double *st,double *u,double *s0,int n) ;
  void mcopy(double *a,double *b,int m) ;
  void ortho(double *evc,int n) ;
  void smgen(double *a,double *eval,double *evec,int n) ;
  
}

#endif
