
#include "Ravl/Vector.hh"
#include "Ravl/Option.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray2d.hh"
#include "Ravl/OS/Date.hh"

template<typename DataT>
void RefMatrixMulVector(const DataT *matrix, 
                        const DataT *vec, // Must be 'col' entries
                        unsigned int rows,
                        unsigned int cols,         
                        int stride,         // Stride of matrix.
                        DataT *result       // Must have 'rows' entries
                        ) 
{
  RavlAssert(rows > 0);
  RavlAssert(cols > 0);
  const DataT *rowStart = matrix;
  for(unsigned int i = 0;i < rows;i++,rowStart += stride) {
    register DataT accum = rowStart[0]*vec[0];
    for(unsigned int j = 1;j < cols;j++)
      accum += rowStart[j]*vec[j];
    result[i] = accum;
  }
}

// Small program useful for checking SSE usage

int main (int nargs,char **argv) {
  RavlN::OptionC opts(nargs,argv);
  bool testFloat = opts.Boolean("f",false,"Test floats");
  int rows = opts.Int("r",24,"Vector length. ");
  int cols = opts.Int("c",24,"Vector length. ");
  int loops = opts.Int("l",100000,"Test loops. ");
  bool lengthTest = opts.Boolean("lt","Do length test. ");
  opts.Check();
  
  using namespace RavlN;
  if(testFloat) 
    std::cerr << "Testing float. \n";
  else
    std::cerr << "Testing double. \n";
  std::cerr << "Rows=" << rows << " Cols=" << cols << " \n";
  
  int startLen = 1;
  if(!lengthTest)
    startLen = cols;
  
  for(int vl = startLen;vl <= cols;vl++) {
    int ucols = vl;
    RavlN::DateC start = RavlN::DateC::NowUTC();
    if(testFloat) {
      SArray1dC<float> a = SArray1dC<float>::ConstructAligned(ucols,16);
      RavlN::SArray2dC<float> b = SArray2dC<float>::ConstructAligned(rows,ucols,16);
      SArray1dC<float> c = SArray1dC<float>::ConstructAligned(rows,16);
      for(int i = 0;i < rows;i++)
        for(int j = 0;j < ucols;j++) 
          b[i][j] = i % 5 + j % 11 + 1;
      a.Fill(0.96);
      for (IntT i=0; i<loops; ++i) {
        RavlBaseVectorN::MatrixMulVector(&b[0][0], 
                                         &a[0],
                                         rows,
                                         ucols,         
                                         b.Stride(),        
                                         &c[0]
                                         );  
      }
    } else {
      SArray1dC<double> a =SArray1dC<double>::ConstructAligned(ucols,16);
      RavlN::SArray2dC<double> b = SArray2dC<double>::ConstructAligned(rows,ucols,16);
      SArray1dC<double> c =SArray1dC<double>::ConstructAligned(rows,16);
      for(int i = 0;i < rows;i++)
        for(int j = 0;j < ucols;j++) 
          b[i][j] = i % 5 + j % 11 + 1;
      a.Fill(0.96);
      for (IntT i=0; i<loops; ++i) {
        RavlBaseVectorN::MatrixMulVector(&b[0][0], 
                                         &a[0],
                                         rows,
                                         ucols,         
                                         b.Stride(),        
                                         &c[0]
                                         );  
      }
    }
    RavlN::DateC finish = RavlN::DateC::NowUTC();
    RavlN::DateC startr = RavlN::DateC::NowUTC();
    if(testFloat) {
      SArray1dC<float> a = SArray1dC<float>::ConstructAligned(ucols,16);
      RavlN::SArray2dC<float> b = SArray2dC<float>::ConstructAligned(rows,ucols,16);
      SArray1dC<float> c = SArray1dC<float>::ConstructAligned(rows,16);
      for(int i = 0;i < rows;i++)
        for(int j = 0;j < ucols;j++) 
          b[i][j] = i % 5 + j % 11 + 1;
      a.Fill(0.96);
      for (IntT i=0; i<loops; ++i) {
        RefMatrixMulVector(&b[0][0], 
                           &a[0],
                           rows,
                           ucols,         
                           b.Stride(),        
                           &c[0]
                           );  
      }
    } else {
      SArray1dC<double> a =SArray1dC<double>::ConstructAligned(ucols,16);
      RavlN::SArray2dC<double> b = SArray2dC<double>::ConstructAligned(rows,ucols,16);
      SArray1dC<double> c =SArray1dC<double>::ConstructAligned(rows,16);
      for(int i = 0;i < rows;i++)
        for(int j = 0;j < ucols;j++) 
          b[i][j] = i % 5 + j % 11 + 1;
      a.Fill(0.96);
      for (IntT i=0; i<loops; ++i) {
        RefMatrixMulVector(&b[0][0], 
                           &a[0],
                           rows,
                           ucols,         
                           b.Stride(),        
                           &c[0]
                           );  
      }
    }
    RavlN::DateC finishr = RavlN::DateC::NowUTC();
    
    std::cout << " " << vl << " SSE:" << (finish - start).Double() << " Original:" << (finishr - startr).Double() << "\n";
  }
  
}
