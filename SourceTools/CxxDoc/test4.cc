
template<class DataT>
class MyDaftArrayC 
{
 public:
  MyDaftArrayC(const DataT &dat);
  //: Constructor.
  
  MyDaftArrayC<DataT> Copy() const;
  //: Copy the array.

  void Multiply(const DataT &dt);
  //:....
};


template<class NestT>
class MyDaftNestedVectorC  
  : public MyDaftArrayC<MyDaftArrayC<RealT> >
{
 public:
  MyDaftVectorC();
  //: Constructor
  
  int Frap();
};
