/*  complex.h    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 */
#ifdef __cplusplus
extern "C" {
#endif
#ifndef CPX
struct complex {double re,im;};
typedef struct complex Cpx;
#define CPX  1
#endif
#include <math.h>
struct complex cadd(Cpx a,Cpx b),csub(Cpx a,Cpx b);
struct complex cmul(Cpx a,Cpx b),cdiv(Cpx a,Cpx b);
struct complex crmu(double x,Cpx a),cimu(double y,Cpx a);
struct complex ccng(Cpx c),cdef(double r,double i);
#ifndef __sgi__
double cabs(Cpx a);
#endif
double cnrm(Cpx a);
struct complex csqrt(Cpx a),cexp(Cpx a),clog(Cpx a);
struct complex csin(Cpx a),ccos(Cpx a),ctan(Cpx a);
struct complex casin(Cpx f),cacos(Cpx f),catan(Cpx f);
struct complex csinh(Cpx h),ccosh(Cpx h),ctanh(Cpx h);
struct complex casinh(Cpx g),cacosh(Cpx g),catanh(Cpx g);
#ifdef __cplusplus
}
#endif
