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
// clear up after ourselves very well.


#include "Ravl/Types.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/TFVector.hh"
#include "Ravl/String.hh"

#include "Ravl/fdstreambuf.hh"
#include "Ravl/fdstream.hh"

#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif
#if RAVL_HAVE_PROCESS_H
#include <process.h>
#endif

using namespace RavlN;

int SimpleTest();
int VectorTest();
int StringTest();
int StrStreamTest();
int testRawFD(); /* NB. This is only usefull on some platforms. */
int testFDStream();

StringC testFile = "/tmp/testStream" + StringC((IntT) getpid());

int main() {
  int errLine;
  // NOTE: test may fail if file exits and belongs to someone else!!
  if((errLine = SimpleTest()) != 0) {
    cerr << "Stream test failed line: " << errLine << "\n";
    return 1;
  }
  if((errLine = VectorTest()) != 0) {
    cerr << "Stream vector test failed line: " << errLine << "\n";
    return 1;
  }
  if((errLine = StringTest()) != 0) {
    cerr << "Stream string test failed line: " << errLine << "\n";
    return 1;
  }
  if((errLine = StrStreamTest()) != 0) {
    cerr << "String stream test failed line: " << errLine << "\n";
    return 1;
  }
  if((errLine = testFDStream()) != 0) {
    cerr << "test failed line: " << errLine << "\n";
    return 1;
  }
  if((errLine = testRawFD()) != 0) {
    cerr << "test failed line: " << errLine << "\n";
    return 1;
  }
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

int StringTest() {
  
  StringC strings[] = {"Hello", "this", "is", "a", "test"};
  {
    OStreamC os(testFile);
    if(!os) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    for (int i=0; i<5; i++) {
      os << i << " " << strings[i] << " ";
    }
    if(!os) {
      cerr << "Failed output stream bad after write. \n";
      return __LINE__;
    }
  }
  
  {
    IStreamC is(testFile);
    if(!is) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    for (int i=0; i<5; i++) {
      IntT ii;
      StringC str;
      is >> ii >> str;
      if (ii != i || str != strings[i]) {
	cerr << "Test failed on string " << i << " = " << ii << ", '" << str << "'\n";
	return __LINE__; 
      }
      else {
	cerr << str << " ";
      }
    }
    cerr << "\n";
  }
  return 0;
  
}


int SimpleTest() {
  ByteT val;
  RealT rval = 0.5;
  FloatT fval = 0.7;
  val = 1;
  {
    BinOStreamC os(testFile);
    if(!os.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    os << val << rval << fval;
  }
  val = 2;
  RealT nval;
  FloatT nfval;
  {
    BinIStreamC is(testFile);
    if(!is.Stream()) {
      cerr << "Failed to open output. \n";
      return __LINE__;
    }
    is >> val >> nval >> nfval;
    if(val != 1) {
      cerr << "Test failed. " << ((int) val) << "\n";
      return __LINE__; 
    }
  }
  if(Abs(nval - rval) > 0.00000001)  return __LINE__;
  if(Abs(nfval - fval) > 0.00000001) return __LINE__;
  return 0;
}

int StrStreamTest() {
  {
    // Test write of a simple string.
    StrOStreamC sos;
    StringC hello("hello");
    sos << hello;
    if(sos.String() != hello)
      return __LINE__;
  }
  {
    StrOStreamC sos;
    StringC hello("hello");
    sos << hello << ' ' << hello << "zyz" << flush << "x";
    sos << hello.before('o');
    sos << hello.after('h');
    OStreamC *tmp = new OStreamC(sos);
    delete tmp;
    StringC got = sos.String();
    cerr << "'" << got << "'\n";
    if(got != "hello hellozyzxhellello") {
      cerr << " Got:'" << got << "'\n";
      return __LINE__;
    }
  }
  {
    StrOStreamC sos;
    StringC hello("Greetings");
    SubStringC rol = hello.from(0);
    sos << rol;
    StringC ret = sos.String();
    cerr << "'" << ret << "'\n";
    
  }  
  return 0;
}

int testFDStream() {
#if RAVL_COMPILER_GCC3
  cerr << "testFDStream(), Started. \n";
  int fds[2];
  pipe(fds);
  char let = 'a';
  cerr << "Writting data... \n";
  
  ofdstream os(fds[1]);
  if(!os)  return __LINE__;
  os << let << let;
  os.flush();
  
  cerr << "Read data... \n";
  
  char rlet1 = 0,rlet2 = 0;
  
  ifdstream is(fds[0]);
  if(!is)  return __LINE__;
  cerr << "Reading byte1 \n";
  is >> rlet1;
  cerr << "Reading byte1 done. Let=" << (int) rlet1 <<" \n";
  if(!is)  return __LINE__;  
  is >> rlet2;
  if(!is)  return __LINE__;  
  
  cerr << "Let=" << (int) let << " RLet1=" << (int) rlet1 << " RLet2=" << (int) rlet2 << "\n";
  
  if(let != rlet1) return __LINE__;
  if(let != rlet2) return __LINE__;
#endif  
  return 0;
}

int testRawFD() {
  int fds[2];
  pipe(fds);
  
  char let = 'a';
  cerr << "Writting data... \n";
  
#if 0
  write(fds[1],&let,1);
  write(fds[1],&let,1);
#else
  OStreamC os(fds[1],true,false);
  if(!os)  return __LINE__;
  os << let << let;
  os.os().flush();
#endif
  cerr << "Read data... \n";
  
  char rlet1 = 0,rlet2 = 0;
  
#if 0
  FILE *inf = fdopen(fds[0],"r");
  fread(&rlet1,1,1,inf);
  fread(&rlet2,1,1,inf);
  fclose(inf);
#elif 0
  read(fds[0],&rlet1,1);
  read(fds[0],&rlet2,1);
#else
  IStreamC is(fds[0],true,false);
  if(!is)  return __LINE__;
  cerr << "Reading byte1 \n";
  is >> rlet1;
  cerr << "Reading byte1 done. Let=" << (int) rlet1 <<" \n";
  if(!is)  return __LINE__;  
  is >> rlet2;
  if(!is)  return __LINE__;  
#endif
  cerr << "Let=" << (int) let << " RLet1=" << (int) rlet1 << " RLet2=" << (int) rlet2 << "\n";
  
  if(let != rlet1) return __LINE__;
  if(let != rlet2) return __LINE__;
  return 0;
}
