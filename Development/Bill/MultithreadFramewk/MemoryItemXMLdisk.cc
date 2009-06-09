#include "Ravl/Threads/MemoryItemXMLdisk.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/IO.hh"
#include "Ravl/OS/Filename.hh"

//! docentry="Ravl.API.Threading Framework.Memory"
//! userlevel=Normal

//-----------------------------------------------------------------------------
//: Copy from MemoryItemBodyC constructor
MemoryItemXMLDiskBodyC::MemoryItemXMLDiskBodyC(const MemoryItemBodyC& Item)
  : MemoryItemBodyC(Item)
{
}

//-----------------------------------------------------------------------------
MemoryItemXMLDiskBodyC::~MemoryItemXMLDiskBodyC()
{
//  cout << ".";
}
//-----------------------------------------------------------------------------
//: make a deep copy of memory item
MemoryItemBodyC* MemoryItemXMLDiskBodyC::Copy(MemoryItemBodyC* Storage) const
{
  MemoryItemXMLDiskBodyC* newItem = Storage ? dynamic_cast<MemoryItemXMLDiskBodyC*> (Storage)
                                            : new MemoryItemXMLDiskBodyC();
  if(!newItem)
    cerr << "MemoryItemXMLDiskBodyC::Copy:can't make copy\n";
  MemoryItemBodyC::Copy(newItem);
  newItem->savePrefix = savePrefix;
  newItem->imageInfos = imageInfos.Copy();
  return newItem;
}

//-----------------------------------------------------------------------------
//: Returns the image from item
const ImageC<ByteRGBValueC>& MemoryItemXMLDiskBodyC::GetImage(const StringC& AttrName) const
{
  if(imageAttrs.IsElm(AttrName)) //image is present in memory
  {
    return imageAttrs[AttrName];
  }
  else if(imageInfos.IsElm(AttrName)) //image possble to load
  {
    const ImageInfoC& imgInfo = imageInfos[AttrName];
    //cout << "filename:" << imgInfo.fileName << " frame:" << imgInfo.frame << endl;
    ImageC<ByteRGBValueC> image;
    if(!imgInfo.fileName.IsEmpty())
    {
      // load image to [0,0]
      if(imgInfo.frame.Rows() != 0 && imgInfo.frame.Cols() != 0)
      {
        if(!RavlN::Load(savePrefix + imgInfo.fileName, image))
          throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::GetImage:Can't read image from file");
      }

      // shift image to original origin & check frame integrity
      image.ShiftArray(imgInfo.frame.TopLeft());
      if(image.Frame() != imgInfo.frame)
      {
        cerr << "MemoryItemXMLDiskBodyC::GetImage:Image frame from xml " << imgInfo.frame << 
                " differs to the one in file " << image.Frame() << endl <<
                "for file " << savePrefix + imgInfo.fileName << endl;
        throw ExceptionC("MemoryItemXMLDiskBodyC::GetImage:Image frame from xml differs to one in file");
      }
    }
    else
    {
      image = ImageC<ByteRGBValueC>(0, 0);
    }

    //put image to hash
    ((MemoryItemXMLDiskBodyC*)this)->imageAttrs.Insert(AttrName, image);

    //remove info from hash
    ((MemoryItemXMLDiskBodyC*)this)->imageInfos.Del(AttrName);
    return imageAttrs[AttrName];
  }
  else
  {
    cerr << "MemoryItemXMLDiskBodyC::GetImage:no image attribute " << AttrName << " found" << endl;
    throw ExceptionC("MemoryItemXMLDiskBodyC::GetImage:no image attribute found!");
  }
}
//-----------------------------------------------------------------------------
//: Returns Byte image from item
const ImageC<ByteT>& MemoryItemXMLDiskBodyC::GetByteImage(const StringC& AttrName) const
{
  if(byteImageAttrs.IsElm(AttrName)) //image is present in memory
  {
    return byteImageAttrs[AttrName];
  }
  else if(imageInfos.IsElm(AttrName)) //image possble to load
  {
    const ImageInfoC& imgInfo = imageInfos[AttrName];
    //cout << "filename:" << imgInfo.fileName << " frame:" << imgInfo.frame << endl;
    ImageC<ByteT> image;
    if(!imgInfo.fileName.IsEmpty())
    {
      // load image to [0,0]
      if(imgInfo.frame.Rows() != 0 && imgInfo.frame.Cols() != 0)
      {
        if(!RavlN::Load(savePrefix + imgInfo.fileName, image))
          throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::GetByteImage:Can't read image from file");
      }

      // shift image to original origin & check frame integrity
      image.ShiftArray(imgInfo.frame.TopLeft());
      if(image.Frame() != imgInfo.frame)
      {
        cerr << "MemoryItemXMLDiskBodyC::GetImage:Image frame from xml " << imgInfo.frame << 
                " differs to the one in file " << image.Frame() << endl <<
                "for file " << savePrefix + imgInfo.fileName << endl;
        throw ExceptionC("MemoryItemXMLDiskBodyC::GetByteImage:Image frame from xml differs to one in file");
      }
    }
    else
    {
      image =  ImageC<ByteT>(0, 0);
    }
    //put image to hash
    ((MemoryItemXMLDiskBodyC*)this)->byteImageAttrs.Insert(AttrName, image);

    //remove info from hash
    ((MemoryItemXMLDiskBodyC*)this)->imageInfos.Del(AttrName);
    return byteImageAttrs[AttrName];
  }
  else
  {
    cerr << "MemoryItemXMLDiskBodyC::GetByteImage:no image attribute " << AttrName << " found" << endl;
    throw ExceptionC("MemoryItemXMLDiskBodyC::GetByteImage:no image attribute found!");
  }
}

//------------------------------------------------------------------------
//: Set the image
void MemoryItemXMLDiskBodyC::SetImage(const StringC& AttrName, const ImageC<ByteRGBValueC>& Image)
{
  ImageC<ByteRGBValueC>* imgPtr = imageAttrs.Lookup(AttrName);
  if(imgPtr) //image is in RAM
  {
    *imgPtr = Image;
  }
  else if(imageInfos.IsElm(AttrName)) // only info is in RAM
  {
    imageInfos.Del(AttrName);

    imageAttrs.Insert(AttrName, Image);
  }
  else
  {
    imageAttrs.Insert(AttrName, Image);
  }
}

//------------------------------------------------------------------------
//: Set the image
void MemoryItemXMLDiskBodyC::SetByteImage(const StringC& AttrName, const ImageC<ByteT>& Image)
{
  ImageC<ByteT>* imgPtr = byteImageAttrs.Lookup(AttrName);
  if(imgPtr) //image is in RAM
  {
    *imgPtr = Image;
  }
  else if(imageInfos.IsElm(AttrName)) // only info is in RAM
  {
    imageInfos.Del(AttrName);
    
    byteImageAttrs.Insert(AttrName, Image);
  }
  else
  {
    byteImageAttrs.Insert(AttrName, Image);
  }
}

//------------------------------------------------------------------------
//: saves item to XML stream.
void MemoryItemXMLDiskBodyC::Save(XMLOStreamC& Strm) const
{
  if(Eof())
  {
    throw ExceptionC("MemoryItemC::Save:memory item is eof");
  } 

  //save images to files (ignore constness)
  ((MemoryItemXMLDiskBodyC*)this)->DumpImages();
  
  Strm.StartTag("item");
  Strm.StartContents();

  //write timecode element
  Strm.StartTag("time");
  Strm.SetAttrib("framerate", IntT(Start().FrameRate()));
  Strm.SetAttrib("beg", Start().getFrameCount());
  Strm.SetAttrib("end", End().getFrameCount());
  Strm.SetAttrib("start", Start().ToText());
  Strm.EndTag();

  //write main part: attributes
  Strm.StartTag("data", stringAttrs);
  Strm.EndTag();

  //save images imfo in XML
  for(HashIterC<StringC, ImageInfoC> infoIter(imageInfos); infoIter; infoIter++)
  {
    Strm.StartTag("image");
    Strm.SetAttrib("name", infoIter.Key());
    Strm.SetAttrib("fileName", infoIter.Data().fileName);
    Strm.SetAttrib("frame", infoIter.Data().frame);
    Strm.EndTag();    
  }
  Strm.EndTag();//end of 'item' tag
}

//-----------------------------------------------------------------------------
//: loads item from XML stream.
void MemoryItemXMLDiskBodyC::Load(XMLIStreamC& Strm)
{
  bool timeTagRead = false;
//  bool imageTagRead = false;
  bool mainTagRead = false;
  bool inItem = false;

  for(;;)
  {
    StringC tagName;
    XMLTagOpsT readTagRes;
    RCHashC<StringC,StringC> curAttr;

    readTagRes = Strm.ReadTag(tagName, curAttr);

    //parse tag
    if(inItem)
    {
      if(readTagRes != XMLBeginTag)
      {
        if(readTagRes == XMLEndTag) // must be </item> tag
          break;
        else
          throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:Error in reading stream.");
      }
      if(tagName == "time")
      {
        RealT frameRate = curAttr["framerate"].RealValue();
        if(frameRate == 0)
          throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:frameRate == 0");

        //TimeCodeC needs big fix
        //Start() = MakeTimeCode(curAttr["start"].chars(), frameRate);
        //End() = MakeTimeCode(curAttr["end"].chars(), frameRate);
        Start() = TimeCodeC(curAttr["beg"].IntValue(), frameRate);
        End() = TimeCodeC(curAttr["end"].IntValue(), frameRate);
        timeTagRead = true;
      }
      else if(tagName == "image")
      {      
        IndexRange2dC frame;
        const StringC& frameAttr = curAttr["frame"];
        StrIStreamC(frameAttr) >> frame;
        imageInfos.Insert(curAttr["name"], ImageInfoC(curAttr["fileName"], frame));
        //imageTagRead = true;
      }
      else if(tagName == "data")
      {
        stringAttrs = curAttr;
        mainTagRead = true;
      }
      else
      {
        cerr << "MemoryItemXMLDiskBodyC::Load:Unknown tag:" << tagName << endl;
        throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:Unknown tag");
      }

      //read closing tag
      readTagRes = Strm.ReadTag(tagName);
      if(readTagRes != XMLEndTag) 
        throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:Missed 'end' tag");  
    }
    else // !inItem
    {
      if(readTagRes != XMLBeginTag)
        throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:Missed 'begin' tag");
      if(tagName != "item") 
        throw ExceptionInvalidStreamC("MemoryItemXMLDiskBodyC::Load:Missed <item> tag");

      inItem = true;
    }
  }

  //check what was read
  if(!timeTagRead || !mainTagRead)
    throw ExceptionC("MemoryItemXMLDiskBodyC::Load:Memory item was not read properly.");  
}

//-----------------------------------------------------------------------------
void MemoryItemXMLDiskBodyC::DumpImages(const StringC& format)
{
  DumpImages<ByteRGBValueC>(imageAttrs, format);
  DumpImages<ByteT>(byteImageAttrs, format);
}

//-----------------------------------------------------------------------------
//: Dump contents of memory item
StringC MemoryItemXMLDiskBodyC::Dump(int MaxLen) const 
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
    for(HashIterC<StringC, ImageInfoC> i(imageInfos); i; i++)
    {
      oss << "img* " << i.Key() << " = \"" << i.Data().frame << "\" ";
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
  if(MaxLen >= 0 && int(oss.str().size()) >= MaxLen)
  {
    string dump(oss.str());
    return StringC(dump.substr(0, MaxLen-1).c_str());
  }
  else
  {
    return StringC(oss.str().c_str());
  }
}
