PACKAGE = Ravl

DESCRIPTION= LAPACK hooks for linear algebra 

REQUIRES = LAPACK

SOURCES = LAHooksLAPACK.cc

MUSTLINK = linkLAHooksLAPACK.cc

PLIB=RavlLapack

USESLIBS = RavlMath RavlLapackWraps

TESTEXES=testMatrixLapack.cc
