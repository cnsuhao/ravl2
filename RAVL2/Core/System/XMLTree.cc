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
#include "Ravl/TypeName.hh"
#include "Ravl/HSet.hh"
#include "Ravl/StringList.hh"

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

  
  //: Read from an XML stream using this node as the root.
  
  bool XMLTreeBodyC::Read(XMLIStreamC &in) {
    HSetC<StringC> includedFiles;
    includedFiles += in.Name();
    return Read(in,includedFiles);
  }
  
  //: Read from an XML stream using this node as the root.
  
  bool XMLTreeBodyC::Read(XMLIStreamC &in,HSetC<StringC> &includedFiles) {
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
      
      // Process includes using XInclude syntax.
      XMLTreeC subtree(name,attr,tt == XML_PI);
      if(tt == XMLBeginTag) {
	ONDEBUG(cerr << "Found begin tag '" << name << "' \n");
	if(!subtree.Read(in,includedFiles))
	  return false;
      }
      
      if(name == "xi:include") {
	if(!ProcessInclude(subtree,includedFiles,in.Name()))
	  return false;
	continue;
      }
      
      Add(subtree.Name(),subtree);
    }
    
    return true;
  }

  static StringC FilePathComponent(const StringC &filename) {
    if(filename.IsEmpty())
      return filename;
#ifdef VISUAL_CPP
    // paths can contain / and \ which confuse this routine, so lets sort that out first!
    StringC str = filename.Copy();
    str.gsub("/", "\\");
    str.gsub("\\\\", "\\");
    return str.before("\\",-1);
#else
    return const_cast<StringC &>(filename).before("/",-1);
#endif
  }
  
  //: Process xi:xinclude directive.
  
  // TODO:
  //  Support xpointer.
  
  bool XMLTreeBodyC::ProcessInclude(XMLTreeC &subtree,HSetC<StringC> &doneFiles,const StringC &parentFilename) {
    StringC xi_href;
    
    if(!subtree.Data().Lookup("href",xi_href) || xi_href.IsEmpty()) {
      // Include nothing, this is used where the fallback is to include nothing.
      subtree.Invalidate();
      return true;
    }
    
    // Check for recursive includes.
    if(doneFiles[xi_href]) {	
      RavlIssueWarning(StringC("Recursive include of file='" + xi_href +"'"));
      return false;
    }
    doneFiles += xi_href;
    
    // Check if we're being asked to parse the file as text.
    StringC xi_parse;
    if(subtree.Data().Lookup("parse",xi_parse)) {
      xi_parse = downcase(xi_parse);
      if(xi_parse == "text") {
	// Load file as simple text.
	StrOStreamC strOut;
	IStreamC inFile;
        
        // Try an include from original directory first.
        if(xi_href.firstchar() != '/') {
          StringC parentDir = FilePathComponent(parentFilename);
          StringC newFn = parentDir + '/' + xi_href;
          ONDEBUG(std::cerr << "Trying text file '" << newFn << "' from '" << parentDir << "'\n");
          inFile = IStreamC(newFn);
        }
        
        // Try current directory.
        if(!inFile.IsOpen()) {
          ONDEBUG(std::cerr << "Trying text file '" << xi_href << "'\n");
          inFile = IStreamC(xi_href);
        }
        
	if(!inFile.IsOpen()) {
	  if(!ProcessIncludeFallback(subtree,doneFiles,parentFilename)) {
	    RavlIssueWarning(StringC("Failed to open file='" + xi_href +"'"));
	    return false;
	  }
	  return true;
	}
	inFile.CopyTo(strOut);
	AddContent(strOut.String());
	subtree.Invalidate();
	return true;
      }
      
      if(xi_parse!="xml") {
	RavlIssueWarning(StringC("Unexpected value for parse='" + xi_parse +"'"));
	return false;
      }
    }
    
    // Load the file as XML.

    // Look in the directory of the current file first, Unless we've been given an absolute path.
    IStreamC newIStream;
    if(xi_href.firstchar() != '/') {
      StringC parentDir = FilePathComponent(parentFilename);
      if(!parentDir.IsEmpty()) {
        StringC newFn = parentDir + '/' + xi_href;
        ONDEBUG(std::cerr << "Trying '" << newFn << "' from '" << parentDir << "'\n");
        newIStream = IStreamC(newFn);
      }
    }
    
    // Try opening from the current directory.
    if(!newIStream.IsOpen()) {
      ONDEBUG(std::cerr << "Trying '" << xi_href << "'\n");      
      newIStream = IStreamC(xi_href);
    }
    
    XMLIStreamC newStream(newIStream);
    if(!newIStream.IsOpen()) {
      if(!ProcessIncludeFallback(subtree,doneFiles,parentFilename)) {
	RavlIssueWarning(StringC("Failed to open file='" + xi_href +"' from '" + parentFilename + "' "));
	return false;
      }
      return true;
    }
    
    XMLTreeC newTree(true);
    if(!newTree.Read(newStream,doneFiles)) {
      // Assume error has already been reported.
      return false;
    }
    
    // There can't be a recursive include anymore.
    doneFiles -= xi_href;
    
    // Basic xpointer support.
    StringC xi_xpointer;
    if(subtree.Data().Lookup("xpointer",xi_xpointer)) {
      DListC<XMLTreeC> children;
      if(!newTree.FollowPath(xi_xpointer,children))
	return false;
      for(DLIterC<XMLTreeC> it(children);it;it++) 
	Add(it->Name(),*it);
      return true;
    }
    
    // Look for first non processing directive.
    subtree.Invalidate();
    for(DLIterC<XMLTreeC> it(newTree.Children());it;it++) {
      if(!it->IsPI())
	Add(it->Name(),*it);
    }
    
    return true;
  }

  //: Look for fallback
  
  bool XMLTreeBodyC::ProcessIncludeFallback(XMLTreeC &subtree,HSetC<StringC> &doneFiles,const StringC &parentFilename) {
    if(subtree.Children().IsEmpty())
      return false;
    XMLTreeC childTree = subtree.Children().First();
    if(childTree.Name() != "xi:fallback") {
      RavlIssueWarning(StringC("Unexpected xi:include child, '" + childTree.Name() +"'"));
      return false;
    }
    if(!ProcessInclude(childTree,doneFiles,parentFilename)) {
      return false;
    }
    subtree = childTree;
    return true;
  }
  
  // : Write (sub)tree as valid XML file
  bool XMLTreeBodyC::Write(OStreamC &out,int level) const {
    XMLTreeC me(const_cast<XMLTreeBodyC &>(*this));
    if (level == 0) {  // no tag at top level
      for(DLIterC<XMLTreeC> it(me.Children());it;it++) {
	it.Data().Write(out,level+1);
      }
    }
    else if (Name() == "?content") Indent(out,level) << Data()["."] << "\n";
    else {
      Indent(out,level) << '<' << Name();
      for(HashIterC<StringC,StringC> ita(Data());ita;ita++) {
	out << ' ' << ita.Key() << "=\"" << ita.Data() << "\"";
      }
      if(me.Children().IsEmpty()) {
	out << "/>\n";
      } 
      else {
	out << ">\n";
	for(DLIterC<XMLTreeC> it(me.Children());it;it++) {
	  it.Data().Write(out,level+1);
	}
	Indent(out,level) << "</" << Name() << ">\n";
      }
    }
    return true;
  }

  //: Give list of nodes matching the given path.
  
  bool XMLTreeBodyC::FollowPath(const StringC &path,DListC<XMLTreeC> &nodes) {
    StringListC steps(path,"/");
    return FollowPath(steps,nodes);
  }
  
  //: Give list of nodes matching the given path.
  
  bool XMLTreeBodyC::FollowPath(const DListC<StringC> &path,DListC<XMLTreeC> &nodes) {
    HSetC<XMLTreeC> current;
    HSetC<XMLTreeC> newNodes;
    newNodes += XMLTreeC(*this);
    
    for(DLIterC<StringC> sit(path);sit;sit++) {
      current = newNodes;
      newNodes = HSetC<XMLTreeC>();
      
      int axisAt = sit->index("::");
      StringC axis = "child";
      StringC spec = *sit;
      if(axisAt >= 0) {
	axis = sit->before(axisAt);
	spec = sit->after(axisAt+1);
	if(spec.IsEmpty())
	  spec = "*";
      }
      
      if(axis == "child") {
	if(spec == "*") {
	  // Just include all children.
	  for(HSetIterC<XMLTreeC> cit(current);cit;cit++) {
	    for(DLIterC<XMLTreeC> it(cit->Children());it;it++) {
	      newNodes += *it;
	    }
	  }
	  continue;
	}
	
	// Include children with matching names.
	for(HSetIterC<XMLTreeC> cit(current);cit;cit++) {
	  for(DLIterC<XMLTreeC> it(cit->Children());it;it++) {
	    if(it->Name() == spec)
	      newNodes += *it;
	  }
	}
	continue;
      }
      
      RavlIssueWarning(StringC("Unsuppored axis specifier='" + axis +"'"));
      
      return false;
    }
    
    for(HSetIterC<XMLTreeC> cit(newNodes);cit;cit++)
      nodes.InsLast(*cit);
    return true;
  }
  

  //: Add subtree to node.
  
  bool XMLTreeBodyC::Add(const StringC &name,const XMLTreeC &subtree) {
    children.InsLast(subtree);
    return HashTreeBodyC<StringC,RCHashC<StringC,StringC> >::Add(name,subtree,true);
  }

  
  //: Add subtree to node.
  
  bool XMLTreeBodyC::Add(const XMLTreeC &subtree) {
    children.InsLast(subtree);
    return HashTreeBodyC<StringC,RCHashC<StringC,StringC> >::Add(subtree.Name(),subtree,true);
  }
  
  //: Add content to node.

  bool XMLTreeBodyC::AddContent(const StringC &content){
    RCHashC<StringC,StringC> attr;
    attr["."] = content;
    XMLTreeC item("?content", attr);
    children.InsLast(item);
    return HashTreeBodyC<StringC,RCHashC<StringC,StringC> >::Add(item.Name(),item,true);
  }
  
  //: lookup child in tree.
  // Returns true and updates parameter 'child' if child is found.
  
  bool XMLTreeBodyC::Child(const StringC &key,XMLTreeC &child) const {
    return const_cast<XMLTreeBodyC*>(this)->HashTreeBodyC<StringC,RCHashC<StringC,StringC> >::Child(key,child);
  }

  //: Indents the XML listing

  ostream &XMLTreeBodyC::Indent(ostream &out,int level) {
    for(int i = 0;i < level;i++)
      out << ' ';
    return out;
  }
  
  //: Dump tree in a human readable format.
  
  ostream &XMLTreeBodyC::Dump(ostream &out,int level) const {
    XMLTreeC me(const_cast<XMLTreeBodyC &>(*this));
    Indent(out,level) << '<' << Name();
    for(HashIterC<StringC,StringC> ita(Data());ita;ita++) {
      out << ' ' << ita.Key() << "=\"" << ita.Data() << "\"";
    }
    if(me.Children().IsEmpty()) {
      out << "/>\n";
    } 
    else {
      out << ">\n";
      for(DLIterC<XMLTreeC> it(me.Children());it;it++) {
	it.Data().Dump(out,level+1);
      }
      Indent(out,level) << "</" << Name() << ">\n";
    }
    return out;
  }
  
  static TypeNameC type0(typeid(XMLTreeC),"RavlN::XMLTreeC");
  
  
}
