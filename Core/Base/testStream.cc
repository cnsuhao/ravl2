// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/testStream.cc"

// Do a quick test of stream functionality.  We don't
// have any OS file functions so unfortunatly we can't
// clear up after ourselves.


#include "Ravl/Types.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/TFVector.hh"
#include "Ravl/String.hh"
#include <unistd.h>

using namespace RavlN;

int SimpleTest();
int VectorTest();

StringC testFile = "/tmp/testStream" + StringC((IntT) getpid());

int main() {
  int errLine;
  OStreamC tf(testFile);
  if(tf) {
    cerr << "ERROR: File " << testFile << " exits, test could not be performed. \n";
    // FIXME:- Do something clever here, and generate a new filename ?
    return 0; // Pretend it passed.
  }
  if((errLine = SimpleTest()) != 0) 
    cerr << "Stream test failed line: " << errLine << "\n";

  if((errLine = VectorTest()) != 0) 
    cerr << "Stream vector test failed line: " << errLine << "\n";
  cerr << "Test passed. \n";
  return 0;
}

int VectorTest() {
  TFVectorC<ByteT,3> val;
  
  val[0] = 1;
  val[1] = 2;
  val[2] = 3;
  {
    BinOStreamC os(testFile);
    if(!os.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    
    os << val;
  }
  
  val[0] = 4;
  val[1] = 4;
  val[2] = 4;
  {
    BinIStreamC is(testFile);
    if(!is.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    is >> val;
    if(val[0] != 1 || val[1] != 2 || val[2] != 3) {
      cerr << "Test failed. \n";
      return __LINE__; 
    }
  }
  return 0;
  
}


int SimpleTest() {
  ByteT val;

  val = 1;
  {
    BinOStreamC os(testFile);
    if(!os.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    
    os << val;
  }
  
  val = 2;
  {
    BinIStreamC is(testFile);
    if(!is.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    is >> val;
    if(val != 1) {
      cerr << "Test failed. \n";
      return __LINE__; 
    }
  }
  return 0;
}
