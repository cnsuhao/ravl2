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

namespace RavlN {
  
  //: Construct from an XMLStream.
  
  XMLTreeBodyC::XMLTreeBodyC(XMLIStreamC &in) {
    Read(in);
  }

  //: Read from a stream using this node as the root.
  
  bool XMLTreeBodyC::Read(XMLIStreamC &in) {
    if(!in)
      return false;
    while(in) {
      StringC name;
      RCHashC<StringC,StringC> attr;
      XMLTagOpsT tt = in.ReadTag(name,attr);
      if(tt == XMLContent) {
	cerr << "Found tag '" << name << "' XMLContent \n";
	continue;
      }
      if(tt == XMLEndTag ) {
	cerr << "Found end tag '" << name << "' \n";
	break;
      }
      XMLTreeC subtree(name,attr);
      if(tt == XMLBeginTag) {
	cerr << "Found begin tag '" << name << "' \n";
	subtree.Read(in);
      } else {
	cerr << "Found empty tag '" << name << "' \n";
      }
      Add(name,subtree);
    }
    return true;
  }

  ostream &XMLTreeBodyC::Indent(ostream &out,int level) {
    for(int i = 0;i < level;i++)
      out << ' ';
    return out;
  }
  
  //: Dump tree in a human readable format.
  
  ostream &XMLTreeBodyC::Dump(ostream &out,int level) const {
    XMLTreeC me(const_cast<XMLTreeBodyC &>(*this));
    for(HashTreeIterC<StringC,RCHashC<StringC,StringC> > it(me);it;it++) {
      Indent(out,level) << '<' << it.Key() << ' ';
      for(HashIterC<StringC,StringC> ita(it.Data().Data().Data());ita;ita++) {
	out << ita.Key() << "=\"" << ita.Data() << "\" ";
      }
      if(it.Tree().Children().IsEmpty()) {
	out << "\\>\n";
      } else {
	out << ">\n";
	it.Data().Dump(out,level+1);
	Indent(out,level) << "<\\" << it.Key() << ">\n";
      }
    }
    return out;
  }

}
