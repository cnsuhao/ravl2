// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"

%{
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
%}

namespace RavlN {

  template<typename DataT>
  class DListC {
  public:
    DListC();
    void Empty();
    void InsFirst(const DataT &dat);
    void InsLast(const DataT &dat);
    DataT PopFirst();
    DataT PopLast();
    void MoveFirst(DListC<DataT> & lst);
    void MoveLast(DListC<DataT> & lst);
    DataT First();
    DataT Last();
    bool Del(const DataT &x);
    bool Contains(const DataT &x);
    DataT Nth(int n);
  };

  template<class DataT> 
  class DLIterC {
  public:
    DLIterC();
    DLIterC(const DListC<DataT> &lst);
    bool IsValid() const;
    void First();
    void Last();
    bool IsElm() const;
    bool IsFirst() const;
    bool IsLast() const;
    void Next();
    void Prev();
    void NextCrc();
    void PrevCrc();
    void Nth(IntT n);    
    DataT NextData();
    DataT PrevData();
    DataT NextCrcData();
    DataT PrevCrcData();
    DListC<DataT> Tail();
    DListC<DataT> Head();
    DListC<DataT> InclusiveTail();
    DListC<DataT> InclusiveHead();    
    DataT Data();
    DataT *operator->();
  };

  %template(DListInt64C) DListC<Int64T>; 
  %template(DLIterInt64C) DLIterC<Int64T>;

}

