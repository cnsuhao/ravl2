#ifndef RAVL_XMLTREE_HEADER
#define RAVL_XMLTREE_HEADER 1
////////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! example=exXMLTree.cc

#include "Ravl/RefCounter.hh"
#include "Ravl/XMLStream.hh"
#include "Ravl/HashTree.hh"
#include "Ravl/RCHash.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: XML parse tree.
  
  class XMLTreeBodyC
    : public HashTreeBodyC<StringC,RCHashC<StringC,StringC> >
  {
  public:
    XMLTreeBodyC()
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >()
    {}
    //: Default constructor.
    
    XMLTreeBodyC(const StringC &nname,RCHashC<StringC,StringC> &attrs) 
      : HashTreeBodyC<StringC,RCHashC<StringC,StringC> >(attrs),
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
    
  protected:
    static ostream &Indent(ostream &out,int level);
    
    StringC name;
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

    friend class XMLTreeBodyC;
  };
  
  
  
}

#endif
