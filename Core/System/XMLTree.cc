// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/XMLTree.cc"

#include "Ravl/XMLTree.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlN {
  
  static StringC xmlContentKey("?content");
  static StringC xmlContentAttrib(".");
  //: Construct from an XMLStream.
  
  XMLTreeBodyC::XMLTreeBodyC(XMLIStreamC &in) 
    : isPI(false)
  {
    Read(in);
  }

  //: Read from a stream using this node as the root.
  
  bool XMLTreeBodyC::Read(XMLIStreamC &in) {
    if(!in)
      return false;
#if 0
    XMLTagOpsT thisTag = in.ReadTag(name);
    if(thisTag == XML_PI)
      isPI = true;
#endif
    while(in) {
      StringC name;
      RCHashC<StringC,StringC> attr;
      
      StringC content;
      in >> content;
      content = content.TopAndTail();
      
      if(!content.IsEmpty()) {
	XMLTreeC cn(xmlContentKey);
	cn.Data()[xmlContentAttrib] = content;
	Add(xmlContentKey,cn);
      }
      
      XMLTagOpsT tt = in.ReadTag(name,attr);
      
      
      if(tt == XMLContent) {
	ONDEBUG(cerr << "Found tag '" << name << "' XMLContent \n");
	continue;
      }
      if(tt == XMLEndTag ) {
	ONDEBUG(cerr << "Found end tag '" << name << "' \n");
	break;
      }
      XMLTreeC subtree(name,attr);
      
      if(tt == XMLBeginTag) {
	ONDEBUG(cerr << "Found begin tag '" << name << "' \n");
	subtree.Read(in);
      }
      Add(name,subtree);
    }
    
    return true;
  }

  //: Add subtree to node.
  
  bool XMLTreeBodyC::Add(const StringC &name,const XMLTreeC &subtree) {
    children.InsLast(subtree);
    return HashTreeBodyC<StringC,RCHashC<StringC,StringC> >::Add(name,subtree,true);
  }
  
  ostream &XMLTreeBodyC::Indent(ostream &out,int level) {
    for(int i = 0;i < level;i++)
      out << ' ';
    return out;
  }
  
  //: Dump tree in a human readable format.
  
  ostream &XMLTreeBodyC::Dump(ostream &out,int level) const {
    XMLTreeC me(const_cast<XMLTreeBodyC &>(*this));
    Indent(out,level) << '<' << Name() << ' ';
    for(HashIterC<StringC,StringC> ita(Data());ita;ita++) {
      out << ita.Key() << "=\"" << ita.Data() << "\" ";
    }
    if(me.Children().IsEmpty()) {
      out << "/>\n";
    } else {
      out << ">\n";
      for(DLIterC<XMLTreeC> it(me.Children());it;it++) {
	it.Data().Dump(out,level+1);
      }
      Indent(out,level) << "</" << Name() << ">\n";
    }
    return out;
  }

}
