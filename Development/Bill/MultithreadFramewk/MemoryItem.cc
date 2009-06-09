#include "Ravl/Threads/MemoryItem.hh"

#include "Ravl/HashIter.hh"

//-----------------------------------------------------------------------------
//: make a deep copy of memory item
MemoryItemBodyC* MemoryItemBodyC::Copy(MemoryItemBodyC* Storage) const
{
  MemoryItemBodyC* newItem = Storage ? Storage : new MemoryItemBodyC();
  newItem->eof = eof;                
  newItem->duration = duration;      
  newItem->stringAttrs = stringAttrs.DeepCopy();
  newItem->imageAttrs = imageAttrs.Copy(); //wanted DeepCopy but ByteRGBValueC does not have one
  newItem->byteImageAttrs = byteImageAttrs.Copy(); //wanted DeepCopy but ByteRGBValueC does not have one
  return newItem;
}
  
//-----------------------------------------------------------------------------
//: Returns the image from item
const ImageC<ByteRGBValueC>& MemoryItemBodyC::GetImage(const StringC& AttrName) const
{
  const ImageC<ByteRGBValueC>* imgPtr = imageAttrs.Lookup(AttrName);
  if(imgPtr) //image is present
  {
    return *imgPtr;
  }
  else
  {
    cerr << "MemoryItemBodyC::GetImage:no image attribute " << AttrName << " found" << endl;
    throw ExceptionC("MemoryItemBodyC::GetImage:no image attribute found!");
  }
}

//-----------------------------------------------------------------------------
//: Returns byte image from item
const ImageC<ByteT>& MemoryItemBodyC::GetByteImage(const StringC& AttrName) const
{
  const ImageC<ByteT>* imgPtr = byteImageAttrs.Lookup(AttrName);
  if(imgPtr) //image is present
  {
    return *imgPtr;
  }
  else
  {
    cerr << "MemoryItemBodyC::GetByteImage:no image attribute " << AttrName << " found" << endl;
    throw ExceptionC("MemoryItemBodyC::GetByteImage:no image attribute found!");
  }
}

//-----------------------------------------------------------------------------
//: Set the image
void MemoryItemBodyC::SetImage(const StringC& AttrName, const ImageC<ByteRGBValueC>& Image)
{
  imageAttrs[AttrName] = Image;
}

//-----------------------------------------------------------------------------
//: Set byte image
void MemoryItemBodyC::SetByteImage(const StringC& AttrName, const ImageC<ByteT>& Image)
{
  byteImageAttrs[AttrName] = Image;
}

//-----------------------------------------------------------------------------
//: Dump contents of memory item
StringC MemoryItemBodyC::Dump(int MaxLen) const 
{ 
  ostringstream oss;
  oss.imbue(locale("C"));
  if(eof) 
  {
    oss << "---END ---";
  } 
  else 
  {
    bool empty(true);
    for(HashIterC<StringC, ImageC<ByteRGBValueC> > i(imageAttrs); i; ++i) 
    {
      oss << "img " << i.Key() << " = \"" << i.Data().Frame() << "\" ";
      empty = false;
    }
    for(HashIterC<StringC, ImageC<ByteT> > i(byteImageAttrs); i; ++i)
    {
      oss << "img " << i.Key() << " = \"" << i.Data().Frame() << "\" ";
      empty = false;
    }
    for (HashIterC<StringC, StringC> i(stringAttrs); i; ++i)
    {
      oss << i.Key() << " = \"" << i.Data() << "\" ";
      empty = false;
    }
    if(empty)
    {
      oss << "empty";
    }
  }
  oss << endl;
  if(MaxLen >= 0 && int(oss.str().size()) >= MaxLen) {
    string dump(oss.str());
    return StringC(dump.substr(0, MaxLen-1).c_str());
  } else {
    return StringC(oss.str().c_str());
  }
}
