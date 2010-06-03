#ifndef ARRSTACK_HH
#define ARRSTACK_HH
/////////////////////////////////////////////////////////////
//! file="amma/Contain/Array/Array1/ArrStack.hh"
//! lib=Marr1
//! author="Radek Marik"
//! date="10.01.1994"
//! docentry="Ravl.Core.Stacks"
//! rcsid="$Id: ArrayStack.hh 7563 2010-02-18 16:41:12Z craftit $"

#include <assert.h>
#include <new.h>

#include "amma/StdType.hh"
#include "amma/RCHandle.hh"

//========================================================================
//================= ArrayStackC ==========================================
//========================================================================
 
template <class DataC> class ArrayStackC;
template <class DataC> class ArrayStackIterC;

//! userlevel=Develop
//: Stack, array based. 
// This is good if you know the maximum depth of your stack
// in advance. <p>
//  BIG OBJECT

template <class DataC>
class ArrayStackBodyC
  : public BodyRefCounterC
{ 
public:
  ArrayStackBodyC(const SizeT sizeStack);
  //: Construct a stack of a give size.

  ~ArrayStackBodyC();
  //: Destructor.
    
  inline void Push(const DataC & data);
  //: Push data into the stack
  
  inline void Pop(DataC & data);
  //: Pop data from the stack

  inline DataC Pop();
  //: Pop data from the stack
  
  inline ArrayStackBodyC<DataC> & operator<<(const DataC & data);
  //: Push data into the stack

  inline ArrayStackBodyC<DataC> & operator>>(DataC & data);
  //: Pop data from the stack
  
  inline void Empty();
  //: Empty the stack
  
  inline BooleanT IsEmpty() const;
  //: Return TRUE if the stack doesn't contain any item
  
  ArrayStackC<DataC> Copy() const;
  //: Create a new physical copy of the stack
  
  SizeT Size() const;
  //: Get the number of data elements in the stack.
  
  SizeT Depth() const;
  //: Get the total size of stack.
  
protected:
  DataC    *data;      // array of items
  DataC    *top;        // Top of stack. (First empty.)
  DataC    *end;        // End of stack.

  friend class ArrayStackIterC<DataC>;
};

//! userlevel=Normal
//: Stack, array based.
// This is good if you know the maximum depth of your stack
// in advance. <p>
//  BIG OBJECT

template <class DataC>
class ArrayStackC
  : public RCHandleC<ArrayStackBodyC<DataC> >
{ 
public:
  ArrayStackC()
    {}
  //: Create an empty handle.
  // Usefull for arrays etc.
  
  ArrayStackC(const SizeT sizeStack)
    : RCHandleC<ArrayStackBodyC<DataC> >(*new ArrayStackBodyC<DataC>(sizeStack))
    {}
  //: Create a stack with the size 'sizeStack'
  
protected:
  ArrayStackC(ArrayStackBodyC<DataC> &bod)
    : RCHandleC<ArrayStackBodyC<DataC> >(bod)
    {}
  //: Body constructor.
  
public:  
  inline
  ArrayStackC<DataC> & Push(const DataC & data)
    { 
      Body().Push(data); 
      return *this;
    }
  //: Push data into the stack
  
  inline
  ArrayStackC<DataC> & Pop(DataC & data)
    {
      Body().Pop(data); 
      return *this;
    }
  //: Pop data from the stack

  inline DataC Pop()
    { return Body().Pop(); }
  //: Pop data from the stack
  
  inline
  ArrayStackC<DataC> & operator<<(const DataC & data)
    {
      Body().operator<<(data);
      return *this;
    }
  //: Push data into the stack

  inline
  ArrayStackC<DataC> & operator>>(DataC & data)
    {
      Body().operator>>(data);
      return *this;
    }
  //: Pop data from the stack
  
  inline void Empty()
    { Body().SetEmpty(); }
  //: Empty the stack
  
  inline ArrayStackC<DataC> & SetEmpty() {
      Body().SetEmpty();
      return *this;
    }
  //: Empty the stack
  
  inline
  BooleanT IsEmpty() const
    { return Body().IsEmpty(); }
  //: Return TRUE if the stack doesn't contain any item
  
  ArrayStackC<DataC> Copy() const
    { return Body().Copy(); }
  //: Create a new physical copy of the stack
  
  SizeT Size() const
    { return Body().Size(); }
  //: Get the number of data elements in the stack.
  
  SizeT Depth() const
    { return Body().Depth(); }
  //: Get the total size of stack.
  
  inline
  const ArrayStackC<DataC> & ArrayStack() const
    { return *this; }
  //: Access to the stack
  
  inline
  ArrayStackC<DataC> & ArrayStack()
    { return *this; }
  //: Access to the stack  
  
  friend class ArrayStackBodyC<DataC>;
  friend class ArrayStackIterC<DataC>;
};

template <class DataC>
ostream & 
operator<<(ostream & s, const ArrayStackC<DataC> & stack);
// print stack into the stream 's'

template <class DataC>
istream & 
operator>>(istream & s, ArrayStackC<DataC> & stack);
// assign the values into the stack 'stack'

///////////////////////////////////////////////////////////////

//! userlevel=Normal
//: Array stack iterator.
// Small object.

template <class DataC>
class ArrayStackIterC
{
public:
  ArrayStackIterC(ArrayStackC<DataC> &astack)
    : stack(astack),
      place(stack.Body().data)
    {}
  //: Constructor.
  
  DataC &Data() { return *place; }
  //: Access data.

  const DataC &Data() const { return *place; }
  //: Access data.
  
  BooleanT IsValid() const { return stack.IsValid(); }
  //: Is valid iterator.
  
  void Next()
    { place++; }
  //: Goto next element.
  // Call only when IsElm(), is TRUE!
  
  BooleanT IsElm() const { place != stack.Body().end; }
  //: At valid element ?
  
  void First() 
    { place = stack.Body().data; }
  //: Goto first element.
  
private:
  ArrayStackC<DataC> stack;
  DataC *place;
};

///////////////////////////////////////////////////////////////

#include <iostream.h>

template <class DataC>
ArrayStackBodyC<DataC>::ArrayStackBodyC(SizeT sizeStack)
{
  // Setup stack.
  data = (DataC *) new char [sizeof(DataC) * sizeStack];
  top = data;
  end = &data[sizeStack];
}

template <class DataC>
ArrayStackBodyC<DataC>::~ArrayStackBodyC()
{
  Empty();
  delete [] ((char *) data);
}

template <class DataC>
inline
void ArrayStackBodyC<DataC>::Push(const DataC & data)
//==========================================
{
  assert(top != end); // Check for overflow.
  new((void *)top++) DataC(data);
}

template <class DataC>
inline
void ArrayStackBodyC<DataC>::Pop(DataC & sdata)
{
  assert(top != data); // Check for underflow.
  sdata = *(--top);
  top->~DataC(); // Destroy element.
}

//: Pop data from the stack

template <class DataC>
inline DataC ArrayStackBodyC<DataC>::Pop()
{
  assert(top != data); // Check for underflow.
  DataC ret = *(--top);
  top->~DataC(); // Destroy element.
  return ret;
}

template <class DataC>
inline
ArrayStackBodyC<DataC> & 
ArrayStackBodyC<DataC>::operator<<(const DataC & sdata)
{ 
  Push(sdata); 
  return *this;
}

template <class DataC>
inline
ArrayStackBodyC<DataC> & ArrayStackBodyC<DataC>::operator>>(DataC & data)
{ 
  Pop(data);
  return *this;
}

template <class DataC>
inline
bool ArrayStackBodyC<DataC>::IsEmpty() const
{ return top == data; }

template <class DataC>
inline
void ArrayStackBodyC<DataC>::Empty()
{
  while(!IsEmpty()) 
    (--top)->~DataC(); // Destroy elements in reverse order.
}

template <class DataC>
inline
SizeT ArrayStackBodyC<DataC>::Size() const
{ return (size_t) (((char *)top) - ((char *) data))/sizeof(DataC); }

template <class DataC>
inline
SizeT ArrayStackBodyC<DataC>::Depth() const
{ return (size_t) (((char *)end) - ((char *) data))/sizeof(DataC); }


template <class DataC>
ArrayStackC<DataC> 
ArrayStackBodyC<DataC>::Copy() const
//==============================
{
  ArrayStackC<DataC> ret(Size());
  for(ArrayStackIterC<DataC> it(ArrayStackC<DataC>(*this));
      it.IsElm();it.Next()) 
    ret.Push(it.Data());
  return ret;
}

template <class DataC>
ostream &
operator<<(ostream & s, const ArrayStackC<DataC> & stack)
//=======================================================
{
  s << stack.Depth() << " " << stack.Size() << "\n";
  for(ArrayStackIterC<DataC> it(ArrayStackC<DataC>(stack));
      it.IsElm();it.Next()) 
    s << it.Data() << "\n";
}

template <class DataC>
istream &
operator>>(istream & s, ArrayStackC<DataC> & stack)
//=================================================
{
  SizeT sizeStack = 0;
  SizeT first     = 0;
  s >> sizeStack >> first;
  if(stack.Size() < sizeStack)
    stack = ArrayStackC<DataC>(sizeStack);
  else
    stack.Empty();
  for (UIntT i = 0; i < first; ++i) {
    DataC tmp;
    s >> tmp;
    stack.Push(tmp);
  }
  return s;
}

#endif

// IAPS - Image analysis program system.
// End of include file ArrStack.hh
