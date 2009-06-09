#ifndef MEMORY_ITEM_XML_DISK_HH
#define MEMORY_ITEM_XML_DISK_HH

#include "Ravl/Threads/MemoryItem.hh"

#include "Ravl/XMLStream.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/IO.hh"

//! docentry="Ravl.API.OS.Multithreading Framework"

//! userlevel=Develop

class MemoryItemXMLDiskBodyC : public MemoryItemBodyC
{
 public:
  // ------------  Constructors ----------------------------------------------
  MemoryItemXMLDiskBodyC() 
    : MemoryItemBodyC()
    {}
  //: Default constructor with negative time (means invalid memory item)

  MemoryItemXMLDiskBodyC(const MemoryItemBodyC& Item);
  //: Copy from MemoryItemBodyC constructor

  virtual ~MemoryItemXMLDiskBodyC();
  //: destructor

  void SetPrefix(const StringC& SavePrefix)
    { savePrefix = SavePrefix; }
  //: Set prefix for loading and saving images

  // -------------  copy functions  ------------------------------------------
  virtual MemoryItemBodyC* Copy(MemoryItemBodyC* Storage = NULL) const;
  //: make a deep copy of memory item
  
  // -------------  data access functions  -----------------------------------
  virtual const ImageC<ByteRGBValueC>& GetImage(const StringC& AttrName) const;
  //: Returns the RGB image from item

  virtual const ImageC<ByteT>& GetByteImage(const StringC& AttrName) const;
  //: Returns the Byte image from item

  virtual void SetImage(const StringC& AttrName, const ImageC<ByteRGBValueC>& Image);
  //: Set RGB image

  virtual void SetByteImage(const StringC& AttrName, const ImageC<ByteT>& Image);
  //: Set Byte image

  virtual StringC Dump(int MaxLen = -1) const;
  //: Dump contents of memory item

  //---------------- IO functions ------------------------------------------
  void Save(XMLOStreamC& Strm) const;
  //: saves item to XML stream.

  void Load(XMLIStreamC& Strm);
  //: loads item from XML stream.

  void DumpImages(const StringC& format = "png");
  //: dump all images into files

  template <class PixelT>
  void DumpImages(const RCHashC<StringC, ImageC<PixelT> >& imageAttrs, const StringC& format);
  //: dump all images of type PixelT into files

 protected:
  //! userlevel=Develop
  //: Information about MemoryItemC image
  struct ImageInfoC 
  {
    StringC fileName; 
    IndexRange2dC frame;
    ImageInfoC() {} 
    ImageInfoC(const StringC& FN, const IndexRange2dC& F) : fileName(FN), frame(F) {}
  };
  StringC savePrefix; //directory for saving and loading images
  RCHashC<StringC, ImageInfoC> imageInfos; //image file names if attr present in hash it is saved in file
};


using namespace RavlN;
//: dump all images of type PixelT into files
template <class PixelT>
void MemoryItemXMLDiskBodyC::DumpImages(const RCHashC<StringC, ImageC<PixelT> >& imageAttrs, const StringC& format) {
  for(HashIterC<StringC, ImageC<PixelT> > imageIter(imageAttrs); imageIter; )
  {
    //find image not saved on disk
    if(!imageInfos.IsElm(imageIter.Key()))
    {
      //save image 
      if(imageIter.Data().IsValid())
      {
        StringC imageName;
        if(imageIter.Data().Rows() != 0 && imageIter.Data().Cols() != 0)
        {
          int dirNum = int(Start().getFrameCount() / 10000);
          FilenameC dir = savePrefix + StringC(dirNum);
          dir.MakeDir();
          char buf[21];
          snprintf(buf, 20, "%06i", int(Start().getFrameCount()));
          imageName = StringC(dirNum) + "/" + imageIter.Key() + StringC(buf) + "." + format;
          RavlN::Save(savePrefix + imageName, imageIter.Data());
        }
        imageInfos.Insert(imageIter.Key(), ImageInfoC(imageName, imageIter.Data().Frame()));
      }
      else
      { 
        cerr << "MemoryItemXMLDiskBodyC::DumpImages:Invalid image!\n";
      }    
      
      //remove image from memory and go to next element
      imageIter.Del();
    }
    else
    {
      cerr << "MemoryItemXMLDiskBodyC::DumpImages:Image present in both hashes!\n";
      imageIter++;
    }
  }

}



#endif
