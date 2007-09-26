// This file is part of QMake, Quick Make System 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/QMake/SysConf.cc"
//! date="6/12/1996"
//! docentry="Ravl.QMake.sysconf"

//  A Utility to retrieve some imformation about the
// machine this utility is run on.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int narg,char **argv) {
  int i;
  long Ret;
  long int val;
//  std::cerr << "Arg:" <<_SC_NPROCESSORS_ONLN<<"\n";
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
	  val = 1;  /* One Porcessor default */
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
