
#include "Ravl/BinaryTree.hh"
#include "Ravl/BinaryTreeUpIter.hh"
#include "Ravl/BinaryTreeDownIter.hh"
#include <iostream.h>

using namespace RavlN;

int main() {
  
  BinaryTreeC<int,char *> tree(true);
  
  // Put some data into the tree.
  
  tree.Insert(4,"c");
  tree.Insert(2,"a");
  tree.Insert(3,"b");
  
  // Go through the tree from the smallest to largest
  // key values.
  
  cout << "Up....\n";
  for(BinaryTreeUpIterC<int,char *> it(tree);it;it++) 
    cout << "Key=" << it.Key() <<" Data=" << it.Data() << "\n";
  
  // Go through the tree from the largest to smallest 
  // key values.
  
  cout << "Down....\n";
  for(BinaryTreeDownIterC<int,char *> it(tree);it;it++) 
    cout << "Key=" << it.Key() <<" Data=" << it.Data() << "\n";

  return 0;
}
