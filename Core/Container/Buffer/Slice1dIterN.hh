
  //: Vector iterator for 'Elems' different vectors. 
  // Iterates through the elements in a set of vectors.
  
  template<class DataT,UIntT Elems>
  class Slice1dIterNC {
  public:
    Slice1dIterNC()
      : end(0)
      { place[0] = 0; }
    //: Creates an invalid iterator.
    
    Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2);
    //: Creates an invalid iterator.

    Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2,const Slice1dC<DataT> &nv3);
    //: Creates an invalid iterator.
    
    Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2,const Slice1dC<DataT> &nv3,const Slice1dC<DataT> &nv4);
    //: Creates an invalid iterator.
    
    void First();
    //: Goto first element.

    operator bool() const
      { return place[0] != end; }
    //: Test if we're at a valid element.
    
    void operator++(int) { 
      for(int i = 0;i < Elems;i++)
	place[i] += vec[i].Stride(); 
    }
    //: Goto next element in all vectors
    
    DataT &Data(UIntT i = 0)
      { return *place[i]; }
    //: Access data at current element.

    const DataT &Data(UIntT i = 0) const
      { return *place[i]; }
    //: Access data at current element.

    DataT &operator*() 
      { return *place[0]; }
    //: Access data.
    
    const DataT &operator*() const
      { return *place[0]; }
    //: Access data.

    DataT &operator[](UIntT i) { 
      RavlAssert(i < Elems);
      return *place[i]; 
    }
    //: Access data.
    
    const DataT &operator[](UIntT i) const { 
      RavlAssert(i < Elems);
      return *place[i]; 
    }
    //: Access data.
    
    IntT Index(UIntT i = 0) const
      { return (place[i] - &vec[i].First())/vec[i].Stride(); }
    //: Calculate current index.
    
  protected:
    DataT *place[Elems],*end;
    Slice1dC<DataT> vec[Elems];
  };

  /// Slice1dIterNC ///////////////////////////////////////////////////////////////////

  template<class DataT,UIntT Elems>
  void Slice1dIterNC<DataT,Elems>::First() {
    if(vec[0].Size() < 0) {
      place[0] = 0;
      return;
    }
    for(int i =0;i < Elems;i++)
      place[i] = &vec[i].First();
  }

  template<class DataT,UIntT Elems>
  Slice1dIterNC<DataT,Elems>::Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2)
  {
    RavlAssert(Elems == 2);
    vec[0] = nv1;
    vec[1] = nv2;
    end = &vec[0].First() + (IntT) vec[0].Size() * vec[0].Stride();
    First();
  }
  
  template<class DataT,UIntT Elems>
  Slice1dIterNC<DataT,Elems>::Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2,const Slice1dC<DataT> &nv3)
  {
    RavlAssert(Elems == 3);
    vec[0] = nv1;
    vec[1] = nv2;
    vec[2] = nv3;
    end = &vec[0].First() +((IntT) vec[0].Size() * vec[0].Stride());
    First();
  }

  template<class DataT,UIntT Elems>
  Slice1dIterNC<DataT,Elems>::Slice1dIterNC(const Slice1dC<DataT> &nv1,const Slice1dC<DataT> &nv2,const Slice1dC<DataT> &nv3,const Slice1dC<DataT> &nv4)
{
    RavlAssert(Elems == 3);
    vec[0] = nv1;
    vec[1] = nv2;
    vec[2] = nv3;
    vec[3] = nv4;
    end = &vec[0].First()[(IntT) vec[0].Size() * vec[0].Stride()];
    First();
  }
