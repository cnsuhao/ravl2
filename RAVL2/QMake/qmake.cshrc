
# Where is QMake installed ?
setenv QMAKE_INSTALL /vol/vssp/local
setenv RAVL_INSTALL /vol/vssp/local
#define project area if not already set (for binaries, libs, *.hh etc.)
if (! $?PROJECT_OUT) setenv PROJECT_OUT $HOME/build

if (-x $QMAKE_INSTALL/config.arc) then ;
  setenv ARC `$QMAKE_INSTALL/config.arc` ;
  setenv LD_LIBRARY_PATH ${RAVL_INSTALL}/lib/RAVL/${ARC}/shared\:${LD_LIBRARY_PATH}
  # add project binaries dir to path
else
  echo "Could not set up QMAKE environment correctly"
endif
set path = ( $path $PROJECT_OUT/bin )

# The USERBUILD=1 in the following causes USERLIBS = Auto to be used by default.
# can use this alias for making
alias qm "gmake -f $QMAKE_INSTALL/QMake.mk USERBUILD=1 \!* && rehash"

