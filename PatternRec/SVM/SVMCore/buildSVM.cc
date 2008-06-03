#include "Ravl/String.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Option.hh"

#include "Ravl/PatternRec/CommonKernels.hh"
#include "Ravl/PatternRec/DesignClassifierSvmSmo.hh"
#include "Ravl/PatternRec/SvmClassifier.hh"


using namespace RavlN;

void MyCallbackFunc(void *, int N)
{
  static int n = 0;
  if(N != n)
  {
    n = N;
    cout << n << "   \r";
  }
}


int main(int argc, char **argv)
{

  OptionC option(argc, argv);

  const RealT C_penalty = option.Real("c1", 1000, "Penalty for misclassifieation of training objects");
  const IntT kernelType = option.Int("kt", 0, "Kernel type (0 - linear; "
                                              "1 - polynimial; 2 - RBF)");
  const RealT par1 = option.Real("par1", 1, "Kernel parameter 1 (Scale for "
                                            "linear and polynomial kernels; Gamma for RBF)");
  const RealT par2 = option.Real("par2", 0, "Kernel parameter 2 (B for polynomial "
                                            "kernel)");
  const RealT par3 = option.Real("par3", 0, "Kernel parameter 3 (Power for "
                                            "polynomial kernel)");
  const bool doLeaveOneOutTest = option.Boolean("dl", false, "do leave-one-out test or not");
  const bool saveClassifier = option.Boolean("sc", false, "save trained classifier to file or not");

  StringC inFile  = option.String("if", "in.dat", "where to find the training data");
  StringC outFile = option.String("of", "out.cls", "where to output the trained classifier");

  option.Check();

  cout << "Penalty for missclassification:" << C_penalty << endl;

  IStreamC in(inFile);

  const UIntT trainingSetSize = 14800;
  SampleC<VectorC> trVec(trainingSetSize);
  SampleC<UIntT> trLab(trainingSetSize);
  SArray1dC<IndexC> vecIDs(trainingSetSize);

  for(UIntT i = 0; i < trainingSetSize; i++) {

    VectorC tmpVec(16);
    for(UIntT j = 0; j <= 15; j++) {
      in >> tmpVec[j];
    }


    UIntT label;
    in >> label;

    // cout << tmpVec << '\t' << label << endl;

    // cout << "Enter char: ";
    // cout.flush();
    // char cr;
    // cin >> cr;

    trVec.Append(tmpVec);
    trLab.Append(label);
    vecIDs[i] = i;
  }

  cout << "Number of objects in training set:" << trVec.Size() << endl;

  //cout << trVec << endl;
  //cout << trLab << endl;
  //cout << vecIDs << endl;

  DateC startTime(true);

  //create kernel
  KernelFunctionC kernel;

  switch(kernelType)
  {
  case 0:
    cout << "Linear kernel: K(X1, X2) = <X1, X2> * " << par1 << endl;
    kernel = LinearKernelC(par1);
    break;
  case 1:
    cout << "Polynomial kernel: K(X1, X2) = (<X1, X2> * " << par1 <<
            " + " << par2 << ") ^ " << par3 << endl;
    kernel = PolynomialKernelC(par3, par1, par2);
    break;
  case 2:
    cout << "RBF kernel: K(X1, X2) = exp(- ||X1 - X2|| ^ 2 / " << par1 << ")" << endl;
    kernel = RBFKernelC(par1);
    break;
  }


  DesignSvmSmoC dsvm(kernel, C_penalty, C_penalty);//, 1e-9, 1e-11, 1e-13);
  dsvm.SetCallbackFunc(MyCallbackFunc, NULL);

  cout << "creating rule\n";
  ClassifierC svm = dsvm.Apply(trVec, trLab);

  if(saveClassifier)
  {
    OStreamC out(outFile);
    out << svm << endl;
  }

  SArray1dC<RealT> lambdas = dsvm.GetLambdas();

  int numOutliers = 0;
  int numSV = 0;
  int numErrors = 0;
  for(UIntT i = 0; i < lambdas.Size(); i++)
  {
    if(fabs(lambdas[i] - C_penalty) < 1e-2)
    {
      numOutliers++;
    }
    if(lambdas[i] > 0)
    {
      numSV++;

      UIntT d = svm.Classify(trVec[i]);
      if(d != trLab[i])
      {
        //cout << "Object:" << i << "  class:" << trLab[i] << "  df:" << d << endl;
        numErrors++;
      }
    }
  }
  cout << "Num outliers:" << numOutliers << endl;
  cout << "Num support vectors:" << numSV << endl;
  cout << "Num errors:" << numErrors << endl;

  DateC endTime(true);
  cout << "Time used:" << endTime.Double() - startTime.Double() << endl;

  if(doLeaveOneOutTest)
  {
    int leaveOneOutRes = dsvm.LeaveOneOutTest();
    cout << "Result of leave-one-out test:" << leaveOneOutRes << endl;
    // cout << "Ratio:" << double(leaveOneOutRes) / double(trainingSetSize) << endl;
    DateC endTime2(true);
    cout << "Total time used:" << endTime2.Double() - startTime.Double() << endl << endl;
  }

  return 0;
}
