#ifndef RAVL_SOCKETADDR_HEADER
#define RAVL_SOCKETADDR_HEADER 1

#include "Ravl/String.hh"
// Some forward declarations to avoid including extra header
// files.

struct sockaddr_in;
struct sockaddr;

namespace RavlN {
  
  bool GetHostByName(const char *name,struct sockaddr_in &sin);
  //: Attempt to get info about named host.
  // returns true on success.

  bool GetHostByAddr(struct sockaddr &sin,int sinLen,StringC &name);
  //: Attempt to find hostname by the address.
  // returns true on success and assignes the hostname to name.
  
}

#endif

