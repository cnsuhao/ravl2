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
//! docentry="Ravl.Core.XML"
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
    
    XMLTreeBodyC(const StringC &nname,RCHashC<StringC,StringC> &attrs) 
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >(attrs),
	isPI(false),
	name(nname)
    {}
    //: Construct from a name and an attribute table.
    
    XMLTreeBodyC(const StringC &nname) 
      : isPI(false),
	name(nname)
    {}
    //: Construct from a name and an attribute table.
    
    XMLTreeBodyC(XMLIStreamC &in);
    //: Construct from an XMLStream.
    
    bool Read(XMLIStreamC &in);
    //: Read from a stream using this node as the root.
    
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
    // Obsolete use Add(const XMLTreeC &subtree).
    
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
  protected:
    static ostream &Indent(ostream &out,int level);
    bool isPI; // Is this a processing instruction ?
    StringC name;
    DListC<XMLTreeC> children; // Ordered list of children.
  };
  
  //! userlevel=Normal
  //: XML parse tree.

  class XMLTreeC
    : public HashTreeC<StringC,RCHashC<StringC,StringC> >
  {
  public:
    XMLTreeC()
    {}
    //: Default constructor.
    // Creats an invalid handle.
    
    XMLTreeC(bool)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC())
    {}
    //: Constructor.
    
    XMLTreeC(const StringC &name,RCHashC<StringC,StringC> &attrs)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(name,attrs))
    {}
    //: Constructor.
    
    XMLTreeC(const StringC &name)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(name))
    {}
    //: Constructor.
    
    XMLTreeC(XMLIStreamC &in)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(*new XMLTreeBodyC(in))
    {}
    //: Constructor.

    XMLTreeC(HashTreeC<StringC,RCHashC<StringC,StringC> > &oth)
      : HashTreeC<StringC,RCHashC<StringC,StringC> >(oth)
    {
      if(dynamic_cast<XMLTreeBodyC *>(&HashTreeC<StringC,RCHashC<StringC,StringC> >::Body()) == 0)
	Invalidate();
    }
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
    
    bool Read(XMLIStreamC &in)
    { return Body().Read(in); }
    //: Read from a stream using this node as the root.

    const StringC &Name() const
    { return Body().Name(); }
    //: Access name.
    
    bool IsPI() const
    { return Body().IsPI(); }
    //: Is this a processing instruction.

    bool Add(const StringC &name,const XMLTreeC &subtree)
    { return Body().Add(name,subtree); }
    //: Add subtree to node.
    // Obsolete use Add(const XMLTreeC &subtree).
    
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

    friend class XMLTreeBodyC;
  };
  
  
  
}

#endif
