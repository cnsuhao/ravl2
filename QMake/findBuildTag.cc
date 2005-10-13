// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;


int main(int nargs,char **argv) {
  if(nargs < 2) {
    printf("No arg. \n");
    return 1;
  }
  
  const char *pwd = argv[1];
  int strLen = strlen(pwd);
  char buffer[1024];
  char testName[1024];
  const char *tagNameFile ="/buildTag";
  strcpy(testName,pwd);
  //printf("Original '%s' \n",testName);
  
  for(int i = strLen;i >= 0;i--) {
    // Found a marker.
    if(pwd[i] == '/' || pwd[i] == 0) {
      strcpy(&(testName[i]),tagNameFile);
      FILE *fh = fopen(testName,"r");
      if(fh != 0) {
        int len = fread(buffer,1,511,fh);
        fclose(fh);
        if(len > 0) {
          buffer[len] = 0;
          printf("%s\n",buffer);
          return 0;
        }
      }
    }
  }
  
  return 1;
}
