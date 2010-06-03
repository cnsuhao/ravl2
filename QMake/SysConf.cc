// This file is part of QMake, Quick Make System 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! rcsid="$Id: SysConf.cc 6381 2007-10-07 10:17:49Z craftit $"
//! file="Ravl/QMake/SysConf.cc"
//! date="6/12/1996"
//! docentry="Ravl.QMake.sysconf"

//  A Utility to retrieve some imformation about the
// machine this utility is run on.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if !defined(_SC_NPROCESSORS_ONLN) && !defined(_SC_NPROC_ONLN)
// MACOSX
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

int main(int narg,char **argv) {
  int i;
  long Ret;
  long int val;
  for(i = 1;i < narg;i++) {
    if(argv[i][0] == '-') {
      switch(argv[i][1]) 
	{
	case 'a':
#ifdef _SC_NPROCESSORS_ONLN
	  val = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
	  val = sysconf(_SC_NPROC_ONLN);  /* One Porcessor default */
#else
	  {
	    // The follow works on MACOSX
	    size_t len = sizeof(int);
	    int ncpu = 1;
	    if(sysctlbyname("hw.ncpu",&ncpu,&len,NULL,0) == 0) {
	      val = ncpu;
	    } else
	      val = 1;  /* One Processor default */
	  }
#endif
	  printf("%ld\n",val);
	  break;
	case 'h':
	  printf("Help: Option -a prints the number of processors on this system. \n");
	  break;
	}
    } else {
      Ret = sysconf(atoi(argv[i]));
      if(Ret == -1)
	printf("Unknown type:%s \n",argv[i]);
      else
	printf("%s = %ld \n",argv[i],Ret);
    }
  }
  return 0;
}
