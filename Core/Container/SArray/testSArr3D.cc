/////////////////////////////////////////////
//! rcsid="$Id: testSArr3D.cc 5996 2006-12-04 15:05:44Z ees1wc $"

#include "Ravl/SArray3d.hh"
#include "Ravl/SArray3dIter2.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

// Some fair basic 3D array tests....

int main() 
{
  SArray3dC<int> arr(10,10,10);
  arr.Fill(0);
  arr[Index3dC(1,1,1)] = 1;
  arr[Index2dC(1,1)][(IndexC) 2] = 2;
  arr[(IndexC) 1][(IndexC) 2][(IndexC) 3] = 3;
  if(arr[Index3dC(1,1,1)] != 1) {
    cerr << "TestSArr3D, failed 1 \n";
    return 1; 
  }
  
  if(arr[Index3dC(1,1,2)] != 2) {
    cerr << "TestSArr3D, failed 2 \n";
    return 1; 
  }
  
  if(arr[Index3dC(1,2,3)] != 3) {
    cerr << "TestSArr3D, failed 3 \n";
    return 1; 
  }
  if(arr[Index3dC(1,2,4)] != 0) {
    cerr << "TestSArr3D, failed 4 \n";
    return 1; 
  }
  
  SArray3dC<int> arr2(arr.Copy());
  if(arr2[Index3dC(1,1,1)] != 1) {
    cerr << "TestSArr3D, failed 5 \n";
    return 1; 
  }
  if(arr2[Index3dC(1,1,2)] != 2) {
    cerr << "TestSArr3D, failed 6 \n";
    return 1; 
  }
  if(arr2[Index3dC(1,2,3)] != 3) {
    cerr << "TestSArr3D, failed 7 \n";
    return 1; 
  }
  if(arr2[Index3dC(1,2,4)] != 0) {
    cerr << "TestSArr3D, failed 8 \n";
    return 1; 
  }
  arr.Fill(5);
  if(arr[Index3dC(1,1,2)] != 5) {
    cerr << "TestSArr3D, failed 9 \n";
    return 1; 
  }  
  if(arr2[Index3dC(1,2,3)] != 3) {
    cerr << "TestSArr3D, failed 10 \n";
    return 1; 
  }  
  //Array3dC<int> arr3(10,10,10);
  
  // Check the dual iter.
  for(SArray3dIter2C<int,int> it(arr,arr2);it;it++) 
    it.Data1() = it.Data2();
  //cerr << typeid(arr[(IndexC) 1]).name() << "\n";
  //cerr << typeid(arr3[(IndexC) 1]).name();
  cerr << "TestSArr3D, Test passed. \n";
  
  return 0;
}
