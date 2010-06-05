#include <stdio.h>
#include "Ravl/Matrix.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/OS/Date.hh"

#include "Omni/Lapack/lapack.hh"
#include "Omni/Lapack/blas2.hh"

using namespace RavlN;


int main()
{
  cout << "Testing outer product\n";
  int dim = 5000;
  MatrixRUTC rutsMat(dim);
  rutsMat.Fill(0.);
  DateC startOP(true);
  VectorC vec = RandomVector(dim);
  for(int i = 0; i < 200; i++)
  {
    BlasN::AddOuterProduct(rutsMat, vec);
    //rutsMat.AddOuterProduct(vec);
  }
  cout << "Time:" << DateC(true).Double() - startOP.Double() << endl;

  cout << "Testin Eigen vectors:Generating matrix\n";
  MatrixC test = RandomSymmetricMatrix(100);
  //test[0][0] = 4; test[0][1] = 6;
  //test[1][0] = 6; test[1][1] = 6;
  //cout << "test:" << test << endl;
  cout << "Calculating eigen vectors\n";
  DateC start(true);
  //VectorMatrixC vm = EigenVectors(test);
  VectorMatrixC vm = LapackN::EigenVectorsSymmetric(test);
  cout << "Time:" << DateC(true).Double() - start.Double() << endl;

  cout << "Checking\n";
  VectorC D = vm.Vector();
  MatrixC E = vm.Matrix();
  //cout << "D:" << D << endl;
  //cout << "E:" << E << endl;

  MatrixC md(D.Size(),D.Size());
  md.Fill(0);
  md.SetDiagonal(D);
  //cout << "md:" << md << endl;

  MatrixC m = E * md * E.Inverse();
  //cout << "m:" << m << endl;

  if((m - test).SumOfSqr() > 0.01)
    cerr << "Big error\n";
  else
    cout << "Everything is OK\n";

  return 0;
}
