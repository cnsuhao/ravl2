// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLXMLSTREAM_HEADER
#define RAVLXMLSTREAM_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! docentry="Ravl.Core.XML"
//! author="Charles Galambos"
//! file="Ravl/Core/System/XMLStream.hh"

#include "Ravl/Stream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/String.hh"
#include "Ravl/Stack.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlN {

  enum XMLTagOpsT 
  { XMLEndTag, XMLContent, XMLIndent,XMLIndentDown, XMLEmptyTag, XMLBeginTag, XMLComment };
  
  //! userlevel=Normal
  //: Exception issued when an parse error occurs.
  
  class ExceptionInvalidStreamC 
    : public ExceptionC
  {
  public:
    ExceptionInvalidStreamC(const char *ntext)
      : ExceptionC(ntext)
      {}
    //: Constructor
    
    ExceptionInvalidStreamC(const char *ntext,bool copy)
      : ExceptionC(ntext,copy)
      {}
    //: Constructor.
    // if copy is true, make a copy of ntext.
  };
  
  //! userlevel=Advanced
  //: Class for handling XML attributes.
  // SMALL object. <p>
  // Note: This only keeps a refrence to the data, not an
  // actual copy.
  
  template<class DataT>
  class XMLAttributeC {
  public:
    XMLAttributeC(const StringC &nm,DataT &ndat)
      : name(nm),
      dat(ndat)
      {}
    //: Constructor.
    
    StringC &Name()
      { return name; }
    //: Access name of attribute.
    
    const StringC &Name() const
      { return name; }
    //: Access name of attribute.
    
    DataT &Data()
      { return dat; }
    //: Access data in attribute.
    
    const DataT &Data() const
      { return dat; }
    //: Access data in attribute.
    
  protected:
    StringC name;
    DataT &dat;
  };
  
  //! userlevel=Develop
  //: Information about the current element being processed.
  
  class XMLElementBodyC 
    : public RCBodyC
  {
  public:
    XMLElementBodyC()
      {}
    //: Constructor.

    XMLElementBodyC(const StringC &nm,bool anEmptyTag = false)
      : name(nm),
        emptyTag(anEmptyTag)
      {}
    //: Constructor.
    
    XMLElementBodyC(const StringC &nm,const RCHashC<StringC,StringC> &attrs,bool anEmptyTag = false)
      : name(nm),
        attribs(attrs),
        emptyTag(anEmptyTag)
      {}
    //: Constructor.
    
    StringC &Name()
      { return name; }
    //: Name of context.
    
    const StringC &Name() const
      { return name; }
    //: Name of context.
    
    RCHashC<StringC,StringC> &Attributes()
      { return attribs; }
    //: Get the current attributes.
    
    const RCHashC<StringC,StringC> &Attributes() const
      { return attribs; }
    //: Get the current attributes.
    
    void SetEmptyTag(bool v)
      { emptyTag = v; }
    //: Set empty tag flag.
    
    bool IsEmptyTag() const
      { return emptyTag; }
    //: Is tag empty ?
    
  protected:
    StringC name;
    RCHashC<StringC,StringC> attribs;
    bool emptyTag;
  };
  
  //! userlevel=Advanced
  //: Information about the current element being processed.
  
  class XMLElementC 
    : public RCHandleC<XMLElementBodyC>
  {
  public:
    XMLElementC()
      {}
    //: Constructor.

    XMLElementC(const StringC &nm,bool anEmptyTag = false)
      : RCHandleC<XMLElementBodyC>(*new XMLElementBodyC(nm,anEmptyTag))
      {}
    //: Constructor.
    
    XMLElementC(const StringC &nm,const RCHashC<StringC,StringC> &attrs,bool anEmptyTag = false)
      : RCHandleC<XMLElementBodyC>(*new XMLElementBodyC(nm,attrs,anEmptyTag))
      {}
    //: Constructor.
    
    StringC &Name()
      { return Body().Name(); }
    //: Name of context.
    
    const StringC &Name() const
      { return Body().Name(); }
    //: Name of context.
    
    RCHashC<StringC,StringC> &Attributes()
      { return Body().Attributes(); }
    //: Get the current attributes.
    
    const RCHashC<StringC,StringC> &Attributes() const
      { return Body().Attributes(); }
    //: Get the current attributes.
    
    bool IsEmptyTag() const
      { return Body().IsEmptyTag(); }
    //: Is tag empty ?
    
    void SetEmptyTag(bool v)
      { Body().SetEmptyTag(v); }
    //: Set empty tag flag.
    
  };

  //! userlevel=Develop
  //: Common XML operations.
  // Stuff common to handling XML input and output.

  class XMLBaseBodyC 
    : public RCBodyVC
  {
  public:
    XMLBaseBodyC();
    //: Constructor.
    
    XMLElementC &Context()
      { return context.Top(); }
    //: Access current context.
    
    bool IsContext() const
    { return !context.IsEmpty(); }
    //: Are we in a valid context ? 
   
    const XMLElementC &Context() const
      { return context.Top(); }
    //: Access current context.

    bool EndOfContext(const StringC &nm) {
      // Check name here ?
      if(context.IsEmpty())
	return false;
      context.DelTop();
      return true;
    };
    //: End the current context.

    bool EndOfContext() {
      if(context.IsEmpty())
	return false;
      context.DelTop();
      return true;
    };
    //: End the current context.
    
    bool StartContext(const StringC &str,bool emptyTag = false) {
      context.Push(XMLElementC(str,emptyTag));
      SetContent(false);
      return true;
    };
    //: Start a context.
    
    bool StartContext(const StringC &str,const RCHashC<StringC,StringC> &attrs,bool emptyTag = false) {
      context.Push(XMLElementC(str,attrs,emptyTag));
      SetContent(false);
      return true;
    };
    //: Start a context.
    
    bool StartContext(const XMLElementC &elem) {
      context.Push(elem);
      SetContent(false);
      return true;
    };
    //: Start a context.
    
    bool IsStrict() const
      { return strict; }
    //: In strict mode ?
    // if true issue errors if XML consitancy check fails in reading or writing.
    
    bool IsContent() const
      { return contents; }
    //: Got content ?
    // True if content has been found.
    
    void SetContent(bool cont)
      { contents = cont; }
    //: Set got content.
    
    UIntT LevelsNested() const
      { return context.Size(); }
    //: Number of open elements in the stack.
    
    bool GetAttib(const StringC &name,StringC &val) {
      RavlAssert(!context.IsEmpty());
      StringC *sv = context.Top().Attributes().Lookup(name);
      if(sv == 0)
	return false;
      val = *sv;
      return true;
    }
    //: Set string attribute.
    
    void SetAttrib(const StringC &value,const StringC &val) { 
      RavlAssert(!context.IsEmpty());
      context.Top().Attributes()[value] = val; 
    }
    //: Set a string valued attribute.
    
  protected:
    bool strict; // Be strict about usage.
    StackC<XMLElementC> context;
    
    bool contents;
  };
  
  //! userlevel=Advanced
  //: Common XML operations.
  // Stuff common to handling XML input and output.
  
  class XMLBaseC 
  : public RCHandleC<XMLBaseBodyC>
  {
  public:
    XMLBaseC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    XMLBaseC(bool)
      : RCHandleC<XMLBaseBodyC>(*new XMLBaseBodyC())
      {}
    //: Constructor.
    
    static StringC EncodeLitteral(const StringC &str);
    //: Convert a string into a form that will not confuse XML.
    
    static StringC DecodeLitteral(const StringC &str);
    //: Decode a string from its XML encoding to the original string.
    
    XMLElementC &Context()
      { return Body().Context(); }
    //: Access current context.

    bool IsContext() const
    { return Body().IsContext(); }
    //: Are we in a valid context ? 

    StringC ContextName() const {
      if(!IsContext())
	return StringC();
      return Context().Name();
    }
    //: Get the name of the current context (the last open tag.)
    
    const XMLElementC &Context() const
      { return Body().Context(); }
    //: Access current context.

    bool StartContext(const StringC &str,bool emptyTag = false) 
      { return Body().StartContext(str,emptyTag); }
    //: Start a new element.
    
    bool StartContext(const StringC &str,const RCHashC<StringC,StringC> &attrs,bool emptyTag = false) 
      { return Body().StartContext(str,attrs,emptyTag); }
    //: Start a new element
    
    bool StartContext(const XMLElementC &elem) 
      { return Body().StartContext(elem); }
    //: Start a new element
    
    bool EndOfContext(const StringC &nm) 
      { return Body().EndOfContext(nm); }
    //: End the current context.
    
    bool EndOfContext() 
      { return Body().EndOfContext(); }
    //: End the current context.
    
    bool IsStrict() const
      { return Body().IsStrict(); }
    //: In strict mode ?
    // if true issue errors if XML consitancy check fails in reading or writing.
    
    bool IsContent() const
      { return Body().IsContent(); }
    //: Got content ?
    // True if content has been found.
    
    void SetContent(bool cont)
      { Body().SetContent(cont); }
    //: Set got content.

    UIntT LevelsNested() const
      { return Body().LevelsNested(); }
    //: Number of open elements in the stack.
    
    bool GetAttrib(const StringC &name,StringC &val) 
      { return Body().GetAttib(name,val); }
    //: Set string attribute.
    
    void SetAttrib(const StringC &name,const StringC &val) 
      { Body().SetAttrib(name,val); }
    //: Set a string valued attribute.
    
  protected:
  };

  //! userlevel=Normal
  //: XML Input Stream.
  // Provides extra functionality for parsing of XML streams.
    
  class XMLIStreamC 
    : public IStreamC,
      public XMLBaseC
  {
  public:
    XMLIStreamC(IStreamC &is);
    //: Construct from an ordinary stream.
    
    XMLIStreamC(const StringC &fn)
      : IStreamC(fn),
        XMLBaseC(true)
      {}
    //: Construct from an ordinary stream.

    
    XMLTagOpsT ReadTag(StringC &name,RCHashC<StringC,StringC> &attr);
    //: Read a tag from a stream.
    // returns XMLBeginTag, XMLEndTag or XMLEmptyTag.
    // This will skip comments and DTD info, and anything else it doesn't understand.
    
    XMLTagOpsT ReadTag(StringC &name) {
      RCHashC<StringC,StringC> attr;
      return ReadTag(name,attr);
    }
    //: Read a tag from a stream.
    // returns XMLBeginTag, XMLEndTag or XMLEmptyTag.
    // This will skip comments and DTD info, and anything else it doesn't understand.
    
    bool SkipElement();
    //: Skip to after the end of the current element.
    
    XMLTagOpsT SkipToElement(const StringC &elementName,RCHashC<StringC,StringC> &attr);
    //: Skip to named element.
    // This will skip to the next tag of the given name.
    // if the Current context ends it will return XMLEndTag.
    
    StringC ReadID();
    //: Read an ID from the stream.
    // This will skip any intial white space, but will
    // return an empty string if an invalid charactors is found.
    
    bool GetAttrib(const StringC &name,StringC &val)
      { return XMLBaseC::GetAttrib(name,val); }
    //: Get a string attribute for entity.
    // This can only be called between StartTag and StartContents.
    // This returns true if attribute is set.
    
    bool GetAttrib(const StringC &name,IntT &val);
    //: Get an integer attribute for entity.
    // This can only be called between StartTag and StartContents.
    // This returns true if attribute is set.
    
    bool GetAttrib(const StringC &name,UIntT &val);
    //: Get an unsigned integer attribute for entity.
    // This can only be called between StartTag and StartContents.
    // This returns true if attribute is set.
    
    bool GetAttrib(const StringC &name,RealT &val);
    //: Get a real valued attribute for entity.
    // This can only be called between StartTag and StartContents.
    // This returns true if attribute is set.
    
    template<class DataT>
    bool GetAttrib(const StringC &name,const DataT &val) {
      StringC strval;
      if(!XMLBaseC::GetAttrib(name,strval))
	return false;
      StrIStreamC istr(strval);
      istr >> val;
      return true;
    }
    //: Get an abitary valued attribute for entity.
    // This can only be called between StartTag and StartContents.
    // The attribute value is stored using its default streaming 
    // operators. (ostream and istream)
    
  protected:
    
    StringC ReadAttrib();
    //: Read attribute and add it to the current context.
    // returns the name of the attrbute read.
    
  };
  
  //! userlevel=Normal
  //: XML Output Stream.
  // Provides extra functionality for generation of XML streams.
  
  class XMLOStreamC 
    : public OStreamC,
      public XMLBaseC
  {
  public:
    XMLOStreamC(OStreamC &os);
    //: Construct from an ordinary stream.
    
    XMLOStreamC(const StringC &fn)
      : OStreamC(fn),
      XMLBaseC(true)
      {}
    //: Construct from an ordinary stream.
    
    void StartTag(const StringC &name,
		  const RCHashC<StringC,StringC> &attribs,
		  bool emptyTag = false);
    //: Begin writting a tag with the given attributes.
    
    void StartTag(const StringC &name,
		  bool emptyTag = false);
    //: Begin writting a tag with the given attributes.
    
    void StartContents();
    //: Call before writting contents of entity to stream.
    
    void EndTag(const StringC &name);
    //: End writting a tag.
    // if strict checking is enabled, name will be check against that of the open tag.
    
    void EndTag();
    //: End writting current entity.
    
    void Indent(int off = 0);
    //: Indent the following line appropriatly.

    template<class DataT>
    void SetAttrib(const StringC &name,const DataT &val) {
      StrOStreamC ostr;
      ostr << val;
      XMLBaseC::SetAttrib(name,ostr.String());
    }
    //: Set an abitary valued attribute for entity.
    // This can only be called between StartTag and StartContents.
    // The attribute value is stored using its default streaming 
    // operators. (ostream and istream)

    void SetAttrib(const StringC &name,const StringC &val)
      { XMLBaseC::SetAttrib(name,val); }
    //: Set an integer attribute for entity.
    // This can only be called between StartTag and StartContents.
    
    void SetAttrib(const StringC &name,const IntT &val);
    //: Set an integer attribute for entity.
    // This can only be called between StartTag and StartContents.
    
    void SetAttrib(const StringC &name,const UIntT &val);
    //: Set an unsigned integer attribute for entity.
    // This can only be called between StartTag and StartContents.

    void SetAttrib(const StringC &name,const char * &val);
    //: Set a 'C' string attribute for entity.
    // This can only be called between StartTag and StartContents.
    
    void SetAttrib(const StringC &name,const RealT &val);
    //: Set a real valued attribute for entity.
    // This can only be called between StartTag and StartContents.
    
  };
  
  inline
  XMLOStreamC &operator<<(XMLOStreamC &strm,const XMLElementC &elem) { 
    strm.StartContext(elem);
    return strm;
  }
  //: Output a element, well start to.

  inline
  ostream &operator<<(ostream &strm,const XMLTagOpsT &elem) { 
    RavlAssertMsg(0,"XMLTagOpsT saved to non-xml stream. \n");
    return strm;
  }
  //: Catch silly mistakes.
  
  XMLOStreamC &operator<<(XMLOStreamC &strm,const XMLTagOpsT &elem);
  //: Do an output stream op.

  XMLIStreamC &operator>>(XMLIStreamC &strm,const XMLTagOpsT &elem);
  //: Do an input stream op.
  
  template<class DataT>
  inline
  XMLOStreamC &operator<<(XMLOStreamC &strm,const XMLAttributeC<DataT> &elem) { 
    strm.SetAttrib(elem.Name(),elem.Data());
    return strm;
  }
  //: Write out an attribute.

  template<class DataT>
  inline
  XMLIStreamC &operator>>(XMLIStreamC &strm,const XMLAttributeC<DataT> &elem) { 
    strm.GetAttrib(elem.Name(),const_cast<XMLAttributeC<DataT> &>(elem).Data());
    return strm;
  }
  //: Write out an attribute.
  
  template<class DataT>
  XMLAttributeC<DataT> XMLAttribute(const StringC &nm,const DataT &dat)
  { return XMLAttributeC<DataT>(nm,const_cast<DataT &>(dat)); }
  //: Setup an XML attribute.
  
  inline
  XMLElementC XMLStartTag(const StringC &name)  
  { return XMLElementC(name); }
  //: Start writing a XML start tag.


  template<class DataT>
  XMLOStreamC &operator<<(XMLOStreamC &strm,const SArray1dC<DataT> &arr) {
    strm << XMLStartTag("array")  << XMLAttribute("size",arr.Size()) << XMLContent;
    for(SArray1dIterC<DataT> it(arr);it;it++) {
      strm << XMLIndent << XMLStartTag("data") << XMLContent << *it;
      strm << XMLEndTag;
    }
    strm << XMLIndentDown << XMLEndTag;
    return strm;
  }

  
  template<class DataT>
  XMLIStreamC &operator>>(XMLIStreamC &strm,SArray1dC<DataT> &arr) {
    UIntT size = 0;
    StringC name;
    if(strm.ReadTag(name) != XMLBeginTag)
      throw ExceptionInvalidStreamC("Unexpected tag when reading SArray1dC ");
    strm >> XMLAttribute("size",size);
    SArray1dC<DataT> ret(size);
    for(SArray1dIterC<DataT> it(ret);it;it++) {
      XMLTagOpsT tt = strm.ReadTag(name);
      if(tt == XMLEndTag) {
	//cerr << "Found end:" << name << "\n";
	break; // Found end of array tag.
      }
      if(tt == XMLEmptyTag )
	throw ExceptionInvalidStreamC("Unexpected tag when reading SArray1dC ");
      if(name != "data") {
	cerr << "WARNING: Read array ignoring tag '" << name << "'\n";
	strm.SkipElement();
	continue;
      }
      strm >> *it;
      //cerr << "Got data " << *it << "\n";
      strm >> XMLEndTag;
    }
    //cerr << "Read of " << size << " items complete.\n";
    arr = ret;
    return strm;
  }


  template<class KeyT,class DataT>
  XMLOStreamC &operator<<(XMLOStreamC &strm,const HashC<KeyT,DataT> &elem) {
    strm << XMLIndent << XMLStartTag("hashmap") 
	 << XMLAttribute("class",TypeName(typeid(HashC<KeyT,DataT>)))
	 << XMLContent;
    
    for(HashIterC<KeyT,DataT> it(elem);it;it++) {
      strm << XMLIndent << XMLStartTag("map") << XMLContent;
      strm << XMLIndent << XMLStartTag("key") << XMLContent << it.Key();
      strm << XMLEndTag;
      strm << XMLIndent << XMLStartTag("data")  << XMLContent << it.Data();
      strm << XMLEndTag;
      strm << XMLIndentDown << XMLEndTag;
    }
    strm << XMLIndentDown << XMLEndTag;
    return strm;
  } 
  //: Write out a hash table.
  // This also serves as an example.

  template<class KeyT,class DataT>
  XMLIStreamC &operator>>(XMLIStreamC &strm,HashC<KeyT,DataT> &elem) {
    // Assume we've got the open tag.
    for(;;) {
      
    }
    return strm;
  } 
  //: Read in a hash table.
  // This also serves as an example.
  
}

#endif
