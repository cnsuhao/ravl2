
#include "Ravl/Hash.hh"
#include "Ravl/HashIter.hh"

using namespace RavlN;

int main() {

  HashC<int,char *> hashTable;

  hashTable[2] = "a 2.";
  hashTable[3] = "a 3.";
  hashTable[10] = "a 10.";
  
  cout << "Lookup of 3 gives " << hashTable[3] << "\n";
  
  for(HashIterC<int,char *> it(hashTable);it;it++)
    cout << " Key=" << it.Key() << " Data=" << it.Data() << "\n";
  
  return 0;
}
