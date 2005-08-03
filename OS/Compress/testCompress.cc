// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Compress.hh"
#include "Ravl/SArray1dIter2.hh"

using namespace RavlN;

int main(int nargs,char **args) {
  
  SArray1dC<char> testBuff(1024);
  for(int i = 0;i < 256;i++)
    testBuff[i] = i;
  SArray1dC<char> compressedData;
  if(!CompressZLib(testBuff,compressedData)) {
    cerr << "Test failed 1 \n";
    return 1;
  }
  cerr << "Compressed size=" << compressedData.Size() << "\n";
  SArray1dC<char> testBuff2(1024);
  if(!DecompressZLib(compressedData,testBuff2,1024)) {
    cerr << "Test failed 2 \n";
    return 1;
  }
  for(SArray1dIter2C<char,char> it(testBuff,testBuff2);it;it++) {
    if(it.Data1() != it.Data2()) {
      cerr << "Test failed 3 \n";
      return 1;
    }
  }
  
  return 0;
}
