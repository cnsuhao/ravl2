#ifndef MEMORY_ITEM_HH
#define MEMORY_ITEM_HH

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/String.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/Hash.hh"
#include "Ravl/Pair.hh"
#include "Ravl/TimeCode.hh"
#include "Ravl/XMLStream.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Normal

using namespace RavlN;
using namespace RavlImageN;

//: Duration of a memory item
class DurationC : PairC<TimeCodeC> {
 public:
  DurationC()
    : PairC<TimeCodeC>(TimeCodeC(0,0), TimeCodeC(0,0))
    {}
  //: Default constructor

  DurationC(const TimeCodeC& Start, const TimeCodeC& End)
    : PairC<TimeCodeC>(Start, End)
    {}
  //: Constructor from start and end times

  DurationC(const TimeCodeC& Time)
    : PairC<TimeCodeC>(Time, Time)
    {}
  //: Constructor for item of 1 frame duration

  TimeCodeC& Start()
    { return A(); }
  //: Access start time of memory item

  const TimeCodeC& Start() const
    { return A(); }
  //: Returns start time of memory item

  TimeCodeC& End() 
    { return B(); }
  //: Access end time of memory item

  const TimeCodeC& End() const
    { return B(); }
  //: Returns end time of memory item

  bool operator==(const DurationC& d) const
    { return ((Start() == d.Start()) && (End() == d.End())); }

  StringC ToText() const
    { return Start().ToText() + " ... " + End().ToText(); }

  bool IsValid() const
    { return Start().IsValid(); }
  //: Check if duration is valid  
};


//! userlevel=Develop
//: Body for MemoryItemC
class MemoryItemBodyC : public RCBodyC
{
 public:
  // ------------  Constructors ----------------------------------------------
  MemoryItemBodyC()
    : eof(false), duration(-1)
    {}
  //: Default constructor with negative time (means invalid memory item)

  MemoryItemBodyC(const TimeCodeC& Time)
    : eof(true), duration(Time)
    {}
  //: Constructor for end-of-memory item

  MemoryItemBodyC(const DurationC& Duration)
    : eof(false), duration(Duration)
    {}
  //: Constructor for general use. Use SetAttr and SetImage functions to set data.

  virtual ~MemoryItemBodyC()
    {}
  //: destructor
  
  // -------------  copy functions  ------------------------------------------
  virtual MemoryItemBodyC* Copy(MemoryItemBodyC* Storage = NULL) const;
  //: make a deep copy of memory item
  
  MemoryItemBodyC* DeepCopy(UIntT) const
    { return Copy(); }
  //: make a deep copy of memory item
    
  // -------------  data access functions  -----------------------------------
  template <class typeT> typeT GetAttr(const StringC& AttrName) const;
  //: Gets an attribute from a memory item as an object

  template <class typeT> void SetAttr(const StringC& AttrName, const typeT& Obj);
  //: Sets an attribute to a memory item as an object

  virtual const ImageC<ByteRGBValueC>& GetImage(const StringC& AttrName) const;
  //: Returns the image from item

  virtual void SetImage(const StringC& AttrName, const ImageC<ByteRGBValueC>& Image);
  //: Set the image 

  virtual const ImageC<ByteT>& GetByteImage(const StringC& AttrName) const;
  //: Returns byte image from item

  virtual void SetByteImage(const StringC& AttrName, const ImageC<ByteT>& Image);
  //: Set byte image

  virtual StringC Dump(int MaxLen = -1) const;
  //: Dump contents of memory item

  // --------------------   parameters access  ------------------------------
  bool Eof() const
    { return eof; }
  //: True then this is the last item in the memory. It is a null item

  bool IsValid() const
    { return duration.Start().IsValid(); }
  //: Check if current elem has been properly constructed (not by default constructor)

  bool IsAttr(const StringC& AttrName) const
    { return stringAttrs.IsElm(AttrName); }

  TimeCodeC& Start()
    { return duration.Start(); }
  //: Get start time from memory item

  const TimeCodeC& Start() const
    { return duration.Start(); }
  //: Get start time from memory item

  TimeCodeC& End()
    { return duration.End(); }
  //: Get end time from memory item

  const TimeCodeC& End() const
    { return duration.End(); }
  //: Get end time from memory item

  DurationC& Duration()
    { return duration; }
  //: Get time bounds from memory item

  const DurationC& Duration() const
    { return duration; }
  //: Get time bounds from memory item

 protected:
  bool eof;                //true only then this is eof item
  DurationC duration;      //duration of memory item
  RCHashC<StringC, StringC>    stringAttrs; //string attributes
  RCHashC<StringC, ImageC<ByteRGBValueC> > imageAttrs;  //image attributes
  RCHashC<StringC, ImageC<ByteT> > byteImageAttrs;  //byte image attributes
};


//! userlevel=Normal
//: One item of a memory module storage unit

// Storage for data of one category at one time slot, including:<ul>
//<li>  XML text string </li>
//<li>  optional image(s)</li>
//<li>  time stamp</li></ul>

// A list of these forms the memory for a <a href="MemModuleC.html">MemModuleC</a> memory module, 
// and provides input data for other modules.

class MemoryItemC : public RCHandleC<MemoryItemBodyC> 
{
 public:
  // ------------  Constructors ----------------------------------------------
  MemoryItemC(MemoryItemBodyC* Body) : RCHandleC<MemoryItemBodyC>(Body) 
    {}

  MemoryItemC() : RCHandleC<MemoryItemBodyC>(new MemoryItemBodyC() )
    {}
  //: Default constructor with negative time (means invalid memory item)

  MemoryItemC(const TimeCodeC& Time) 
    : RCHandleC<MemoryItemBodyC>(new MemoryItemBodyC(Time))
    {}
  //: Constructor for end-of-memory item

  MemoryItemC(const DurationC& Duration)
    : RCHandleC<MemoryItemBodyC>(new MemoryItemBodyC(Duration))
    {}
  //: Constructor for general use. Use SetAttr and SetImage functions to set data.

  MemoryItemC(const TimeCodeC& Start, const TimeCodeC& End)
    : RCHandleC<MemoryItemBodyC>(new MemoryItemBodyC(DurationC(Start, End)))
    {}
  //: Constructor for general use. Use SetAttr and SetImage functions to set data.

  // -------------  copy functions  ------------------------------------------
  MemoryItemC Copy() const
    { return MemoryItemC(BodyPtr()->Copy());}
  //: make a deep copy of memory item
  
  MemoryItemC DeepCopy(UIntT) const
    { return Copy(); }
  //: make a deep copy of memory item
  
  // -------------  data access functions  -----------------------------------
  template <class TypeT> TypeT GetAttr(const StringC& AttrName) const
    { return BodyPtr()->GetAttr<TypeT>(AttrName); }
  //: Gets an attribute from a memory item as an object

  template <class typeT> void SetAttr(const StringC& AttrName, const typeT& Obj)
    { BodyPtr()->SetAttr(AttrName, Obj); }
  //: Sets an attribute to a memory item as an object

  ImageC<ByteRGBValueC> GetImage(const StringC& AttrName) const
    { return BodyPtr()->GetImage(AttrName); }
  //: Returns the image from item

  void SetImage(const StringC& AttrName, const ImageC<ByteRGBValueC>& Image)
    { BodyPtr()->SetImage(AttrName, Image); }
  //: Set the image 

  ImageC<ByteT> GetByteImage(const StringC& AttrName) const
    { return BodyPtr()->GetByteImage(AttrName); }
  //: Returns byte image from item

  void SetByteImage(const StringC& AttrName, const ImageC<ByteT>& Image)
    { BodyPtr()->SetByteImage(AttrName, Image); }
  //: Set byte image

  StringC Dump(int MaxLen = -1) const
    { return BodyPtr()->Dump(MaxLen); }
  //: Dump contents of memory item

  // --------------------   parameters access  ------------------------------
  bool Eof() const
    { return BodyPtr()->Eof(); }
  //: True then this is the last item in the memory. It is a null item

  bool IsValid() const
    { return BodyPtr()->IsValid(); }
  //: Check if current elem has been properly constructed (not by default constructor)

  bool IsAttr(const StringC& AttrName) const
    { return BodyPtr()->IsAttr(AttrName); }

  TimeCodeC& Start()
    { return BodyPtr()->Start(); }
  //: Get start time from memory item

  const TimeCodeC& Start() const
    { return BodyPtr()->Start(); }
  //: Get start time from memory item

  TimeCodeC& End()
    { return BodyPtr()->End(); }
  //: Get end time from memory item

  const TimeCodeC& End() const
    { return BodyPtr()->End(); }
  //: Get end time from memory item

  DurationC& Duration()
    { return BodyPtr()->Duration(); }
  //: Get time bounds from memory item

  const DurationC& Duration() const
    { return BodyPtr()->Duration(); }
  //: Get time bounds from memory item

  MemoryItemBodyC* BodyPtr()
    { return &Body(); }
  //: access proper Body though pointer not through reference!

  const MemoryItemBodyC* BodyPtr() const
    { return &Body(); }
  //: access proper Body though pointer not through reference!
};

//-------------------- MemoryItemBodyC implementation ------------------------
template <class TypeT> 
void MemoryItemBodyC::SetAttr(const StringC& AttrName, const TypeT& Obj)
{ 
  StrOStreamC str;
  str << Obj;
  stringAttrs.Insert(AttrName, str.String());
}
//: Sets an attribute to a memory item as an object

template <class TypeT> 
TypeT MemoryItemBodyC::GetAttr(const StringC& AttrName) const
{
  if(!stringAttrs.IsElm(AttrName)) 
  {
    cerr << "No attribute '" << AttrName << "' found" << endl;
    throw ExceptionC("MemoryItemBodyC::GetAttr:Can not find attribute");
  }
  StrIStreamC str(stringAttrs[AttrName]);
  if(str.String().IsEmpty()) 
  {
    cerr << "Could not get memory item attribute:" << AttrName << endl;
    throw ExceptionC("MemoryItemBodyC::GetAttr:Empty attribute");
  }
  TypeT attr;
  str >> attr;
  return attr;
}

//! userlevel=Normal
inline ostream & operator<<(ostream &Stream, const DurationC& D)
{
  return Stream << D.Start().ToText() << " - " << D.End().ToText();
}
//: Stream operator for DurationC outputs as hh:mm:ss:ff
//
#endif

