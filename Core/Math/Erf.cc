#ifdef VISUAL_CPP

//  VCPP does not have an implementation of erf or erfc
//  so we have to provide our own.  In fact it is borrowed from GSL.

#include"amma/StdMath.hh"
#include "gsl/gsl_sf_erf.h"

double erf(double x)
{
  gsl_sf_result res;
  gsl_sf_erf_impl(x, &res);
  return res.val;
}

double erfc(double x)
{
  gsl_sf_result res;
  gsl_sf_erfc_impl(x, &res);
  return res.val;
}

#endif
