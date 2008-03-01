// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_XMLTREE_HEADER
#define RAVL_XMLTREE_HEADER 1
////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.XML"
//! example=exXMLTree.cc
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/XMLTree.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/XMLStream.hh"
#include "Ravl/HashTree.hh"
#include "Ravl/RCHash.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  class XMLTreeC;
  template<typename DataT> class HSetC;
  
  //! userlevel=Develop
  //: XML parse tree.
  
  class XMLTreeBodyC
    : public HashTreeBodyC<StringC,RCHashC<StringC,StringC> >
  {
  public:
    XMLTreeBodyC()
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >(),
	isPI(false)
    {}
    //: Default constructor.
    
    XMLTreeBodyC(const StringC &nname,RCHashC<StringC,StringC> &attrs,bool _isPI = false) 
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >(attrs),
	isPI(_isPI),
	name(nname)
    {}
    //: Construct from a name and an attribute table.
    
    XMLTreeBodyC(const StringC &nname) 
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >(),
	isPI(false),
	name(nname)
    {}
    //: Construct from a name and an attribute table.
    
    explicit XMLTreeBodyC(XMLIStreamC &in);
    //: Construct from an XMLStream.
    
    bool Read(IStreamC &in) 
      { XMLIStreamC ins(in); return Read(ins); }
    //: Read from a stream

    bool Read(XMLIStreamC &in);
    //: Read from an XML stream using this node as the root.
    
    bool Read(XMLIStreamC &in,HSetC<StringC> &includedFiles);
    //: Read from an XML stream using this node as the root.
    
    bool Write(OStreamC &out, int level=0) const;
    //: Write to a stream using this node as the root.
    // !param level - level of the XML tree for indenting / formatting purposes 
    
    const StringC &Name() const
    { return name; }
    //: Access name.

    ostream &Dump(ostream &out,int level= 0) const;
    //: Dump tree in a human readable format.
    
    bool IsPI() const
    { return isPI; }
    //: Is this a processing instruction.
    
    bool Add(const StringC &name,const XMLTreeC &subtree);
    //: Add subtree to node.
    // Obsolete; use Add(const XMLTreeC &subtree).
    
    bool Add(const XMLTreeC &subtree);
    //: Add subtree to node.
    
    bool AddContent(const StringC &content);
    //: Add some text to the tree
    
    DListC<XMLTreeC> &Children()
    { return children; }
    //: Access list of children.
    
    const DListC<XMLTreeC> &Children() const
    { return children; }
    //: Access list of children.
    
    bool Child(const StringC &key,XMLTreeC &child) const;
    //: lookup child in tree.
    // Returns true and updates parameter 'child' if child is found.
    
    StringC AttributeString(const StringC &name,const StringC &defaultValue = StringC("")) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return *value;
    }
    //: Access attribute.
    
    UIntT AttributeUInt(const StringC &name,UIntT defaultValue = 0) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return value->UIntValue();
    }
    //: Access attribute.
    
    IntT AttributeInt(const StringC &name,IntT defaultValue = 0) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return value->IntValue();
    }
    //: Access attribute.
    
    RealT AttributeReal(const StringC &name,RealT defaultValue = 0) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return value->RealValue();
    }
    //: Access attribute.

    UInt64T AttributeUInt64(const StringC &name,UInt64T defaultValue = 0) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return value->UInt64Value();
    }
    //: Access attribute.

    Int64T AttributeInt64(const StringC &name,Int64T defaultValue = 0) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      return value->Int64Value();
    }
    //: Access attribute.
    
    bool AttributeBool(const StringC &name,bool defaultValue = false) const {
      const StringC *value = Data().Lookup(name);
      if(value == 0) return defaultValue;
      StringC tmp = RavlN::downcase(*value);
      if(tmp == "1" || tmp == "t" || tmp == "true" || tmp == "yes")
	return true;
      if(tmp == "0" || tmp == "f" || tmp == "false" || tmp == "no")
	return false;
      RavlIssueWarning(StringC("Expected boolean value, got '") + tmp + "' for attribute " + name + " in node '" + Name() + "' ");
      return defaultValue;
    }
    //: Access attribute.
    
    
  protected:
    bool ProcessInclude(XMLTreeC &subtree,HSetC<StringC> &doneFiles);
    //: Process xi:include directive
    
    bool ProcessIncludeFallback(XMLTreeC &subtree,HSetC<StringC> &doneFiles);
    //: Look for fallback
    
    static ostream &Indent(ostream &out,int level);
    bool isPI; // Is this a processing instruction ?
    StringC name;
    DListC<XMLTreeC> children; // Ordered list of children.
  };
  
  //! userlevel=Normal
  //: Parses XML and stores as a tree
  // <code>XMLTreeC</code> is a hash tree, templated on strings for key and data.
  // <ul>
  // <li> The top-level element is a container for the remaining XML - typically it has the name of the XML file.  The contents start at the next level down.
  // <li> The elements contained within an element (children) can be accessed either as a list, as a hash table, or individually by name.
  // <li> Attributes of an element can be accessed as a hash table, using the attribute name as the key.  Attributes are called <code>Data()</code> in this class (for reasons of inheritance).
  // </ul>
  // <p> To summarise: an XML tree node typically has a <code>Name()</code>, <code>Data()</code> (i.e. attributes) and <code>Children()</code> (i.e. contents).</p>

  class XMLTreeC
    : public HashTreeC<StringC,RCHashC<StringC,StringC> >
  {
  public:
    XMLTreeC()
    {}
    //: Default constructor.
    // Creats an invalid handle.
    
    explicit XMLTreeC(bool)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC())
    {}
    //: Constructor.
    
    explicit XMLTreeC(const char *name)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(StringC(name)))
    {}
    //: Constructor.
    
    XMLTreeC(const StringC &name,RCHashC<StringC,StringC> &attrs,bool _isPI = false)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(name,attrs,_isPI))
    {}
    //: Constructor.
    
    explicit XMLTreeC(const StringC &name)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(name))
    {}
    //: Constructor.
    
    explicit XMLTreeC(XMLIStreamC &in)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(in))
    {}
    //: Constructor.

    XMLTreeC(HashTreeC<StringC,RCHashC<StringC,StringC> > &oth)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(dynamic_cast<const XMLTreeBodyC *>(BodyPtr(oth)))
    {}
    //: Construct from a base class.
    // An invalid handle is created if it failes.
    
  protected:
    XMLTreeC(XMLTreeBodyC &bod)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(bod)
    {}
    //: Body constructor.
    
    XMLTreeBodyC &Body()
    { return static_cast<XMLTreeBodyC &>(HashTreeNodeC<StringC,RCHashC<StringC,StringC> >::Body()); }
    //: Access body.

    const XMLTreeBodyC &Body() const
    { return static_cast<const XMLTreeBodyC &>(HashTreeNodeC<StringC,RCHashC<StringC,StringC> >::Body()); }
    //: Access body.
    
  public:
    
    bool Read(IStreamC &in)
    { return Body().Read(in); }
    //: Read from a stream using this node as the root.

    bool Read(XMLIStreamC &in)
    { return Body().Read(in); }
    //: Read from an XML stream using this node as the root.
    
    bool Read(XMLIStreamC &in,HSetC<StringC> &includedFiles)
    { return Body().Read(in,includedFiles); }
    //: Read from an XML stream using this node as the root.
    
    bool Write(OStreamC &out, int level=0) const
    { return Body().Write(out, level); }
    //: Write to a stream using this node as the root.
    
    const StringC &Name() const
    { return Body().Name(); }
    //: Access name.
    
    bool IsPI() const
    { return Body().IsPI(); }
    //: Is this a processing instruction.

    bool Add(const StringC &name,const XMLTreeC &subtree)
    { return Body().Add(name,subtree); }
    //: Add subtree to node.
    // <font color="#880088"> Obsolete</font>; use Add(const XMLTreeC &subtree).
    
    bool Add(const XMLTreeC &subtree)
    { return Body().Add(subtree); }
    //: Add subtree to node.

    bool AddContent(const StringC &content)
    { return Body().AddContent(content); }
    //: Add some text to the tree
    
    DListC<XMLTreeC> &Children()
    { return Body().Children(); }
    //: Access list of children.
    
    const DListC<XMLTreeC> &Children() const
    { return Body().Children(); }
    //: Access list of children.
    
    bool Child(const StringC &key,XMLTreeC &child) const
    { return Body().Child(key,child); }
    //: lookup child in tree.
    // Returns true and updates parameter 'child' if child is found.
    
    StringC AttributeString(const StringC &name,const StringC &defaultValue = StringC("")) const 
    { return Body().AttributeString(name,defaultValue); }
    //: Access attribute.
    
    UIntT AttributeUInt(const StringC &name,UIntT defaultValue = 0) const 
    { return Body().AttributeUInt(name,defaultValue); }
    //: Access attribute.
    
    IntT AttributeInt(const StringC &name,IntT defaultValue = 0) const 
    { return Body().AttributeInt(name,defaultValue); }
    //: Access attribute.
    
    RealT AttributeReal(const StringC &name,RealT defaultValue = 0) const 
    { return Body().AttributeReal(name,defaultValue); }
    //: Access attribute.
    
    UInt64T AttributeUInt64(const StringC &name,UInt64T defaultValue = 0) const 
    { return Body().AttributeUInt64(name,defaultValue); }
    //: Access attribute.
    
    Int64T AttributeInt64(const StringC &name,Int64T defaultValue = 0) const 
    { return Body().AttributeInt64(name,defaultValue); }
    //: Access attribute.

    bool AttributeBool(const StringC &name,bool defaultValue = false) const 
    { return Body().AttributeBool(name,defaultValue); }

    friend class XMLTreeBodyC;
  };
  
  
  
}

#endif
