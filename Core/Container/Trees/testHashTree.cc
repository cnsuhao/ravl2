
#include "Ravl/String.hh"
#include "Ravl/HashTree.hh"

using namespace RavlN;

int main() {
  
  HashTreeC<int,StringC> tree(true);
  
  tree.Add(1,StringC("Hello"));
  
  cerr << tree;
  return 0;
}

template class HashTreeC<int,StringC>;
