
typedef double RealT;
//: Some ..

//! docentry="Ravl.TestCode"
//! date="12/02/2001"
//! author="Charles Galambos"
//! file="amma/Util/CxxDoc/test3.cc"
//! lib=NotHere
//! example="Test.cc"
//! userlevel=Normal
//: Base class for lots of daftness.
// Some comments about just how daft it is.

template<class DataC>
class MyDaftAccessC {
 public:
  void DoDa(ADaft<DataC> &datT);
  //: Copy access.
  //!bug="Ha! this is only a pretend class."
  // for the brave only.
  
  void Fill(const DataC &dat);
  //: Fill the array.
  // very slowly and painfully.
  
  void CopyFrom(const MyDaftAccessC<DataC> &dat);
  //: Copy from another access.
  // well wouldn't you ?
};

//! userlevel=Basic
//: Some stupid array template
// Dobedo...

template<class DataT>
class MyDaftArrayC 
  : public MyDaftAccessC<DataT>
{
 public:
  MyDaftArrayC(const DataT &dat);
  //: Constructor.

  
  MyDaftArrayC<DataT> Copy() const;
  //: Copy the array.
  // some more meanless comments
  
  void Multiply(const DataT &dt);
  //:....
};

//! userlevel=Normal
//: A nested daft class.
// Lalalal

template<class NestT>
class MyDaftNestedVectorC  
  : public MyDaftArrayC<MyDaftArrayC<NestT> >
{
 public:
  MyDaftVectorC();
  //: Constructor

  operator int();
  //: Convert to an int.
  
  operator MyDaftArrayC<NestT>();
  //: Convert to something else.
  
  int Frap();
  //: Frap it up.
  //! bug="This doesn't have a hope in hell of working."
};

//: A Vector of reals.
// This class is set to go far.

class MyDaftVectorC  
  : public MyDaftArrayC<RealT>
{
 public:
  MyDaftVectorC();
  //: Constructor
  
};

//: The daft matrix class.

class MyDaftMatrixC  
: public MyDaftNestedVectorC<RealT>
{
  MyDaftMatrixC()
    {}
  //: Constructor.
  
  MyDaftNestedVectorC<RealT> &Igloos();
  //: Find the igloo in the matrix.
  
};

