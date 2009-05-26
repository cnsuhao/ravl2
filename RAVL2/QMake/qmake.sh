
# Where is QMake installed ?
QMAKE_INSTALL=/vol/vssp/local/Ravl/Tools/QMake
RAVL_INSTALL=/vol/vssp/local/Ravl
#define project area if not already set (for binaries, libs, *.hh etc.)
if test -z ${PROJECT_OUT} ; then
  PROJECT_OUT=${HOME}/build ;
  LD_LIBRARY_PATH=${RAVL_INSTALL}/lib/RAVL/${ARC}/shared\:${LD_LIBRARY_PATH}
fi
if test -x ${QMAKE_INSTALL}/config.arc ; then 
  ARC=`${QMAKE_INSTALL}/config.arc` ;
else
  echo "Could not set up QMAKE environment correctly"
fi
PATH=${PATH}\:${PROJECT_OUT}/bin ;

# The USERBUILD=1 in the following causes USERLIBS = Auto to be used by default.

# can use this alias for making
alias qm='gmake -f ${QMAKE_INSTALL}/QMake.mk USERBUILD=1'

