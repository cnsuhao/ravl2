///////////////////////////////////////////////////////////
//! rcsid="$Id$"
// Test arbitary hash.

#include "Ravl/String.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/Hash.hh"
#include "Ravl/IntC.hh"

#include <iostream.h>

using namespace RavlN;

int main(int nargs,char *argv[]) {
  cout << "Counting..... \n";
  
  // Creat the table...
  
  HashC<StringC,IntC> wordFreq;

  // Read a the standard input one word at a time.
  
  StringC word;
  while(!cin.eof()) {
    cin >> word;
    wordFreq[word.Copy()]++;
    // Because the Word buffer is overwritten by
    // successive reads we have to make a copy of it
    // when its used as a key in the hash table.
  }
  
  // Print out the results.
  
  cout << wordFreq.Size() << " Unique words found: \n";
  
  // Print out the number of times we've seen each word.
  
  for(HashIterC<StringC,IntC> it(wordFreq);it.IsElm();it.Next())
    cout << "'" << it.Key() <<  "' " << it.Data() << " \n";
}
