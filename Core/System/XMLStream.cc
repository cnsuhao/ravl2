// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/XMLStream.cc"

#include "Ravl/XMLStream.hh"
#include "Ravl/HashIter.hh"
#include <stdlib.h>
#include <ctype.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif


namespace RavlN {

  static UByteT  xmlCharacters[256] = 
  /*             0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15 */
  { /*   0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*  16 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*  32 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    /*  48 */ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*  64 */ 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    /*  80 */ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
    /*  96 */ 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    /* 112 */ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 128 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 144 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 160 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 176 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 192 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 208 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 224 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 240 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  
  static inline bool IsXMLIDChar(ByteT c) {
    return (xmlCharacters[c] & 0x01) != 0;
  }
  
  ///// XMLBaseBodyC ////////////////////////////////////////////////
  
  //: Constructor.
  
  XMLBaseBodyC::XMLBaseBodyC()
    : strict(false),
      contents(false)
  {
    //context.Push(XMLElementC("**ROOT CONTEXT**"));
  }
  
  ///// XMLBaseC ////////////////////////////////////////////////
  
  //: Convert a string into a form that will not confuse XML.
  
  StringC XMLBaseC::EncodeLitteral(const StringC &str) {
    StringC ret(str.Copy());
    ret.gsub("&","&amp;");    // Has to go first!!
    ret.gsub("\"","&quot;");  // Needed for quoted text
    //ret.gsub("#","&num;");   
    //ret.gsub("$","&dollar;");
    ret.gsub("%","&percnt;"); // Needed for quoted text
    ret.gsub("\'","&apos;");  // Needed for quoted text
    ret.gsub("!","&excl;");
    ret.gsub("<","&lt;");     // Needed.
    ret.gsub(">","&gt;");
    //ret.gsub(" ","&#32;");
    return ret;
  }
  
  //: Decode a string from its XML encoding to the original string.
  
  StringC XMLBaseC::DecodeLitteral(const StringC &str) {
    StringC ret(str.Copy());
    ret.gsub("&amp;","&");    // Has to go first!!
    ret.gsub("&quot;","\"");  // Needed for quoted text
    ret.gsub("&percnt;","%"); // Needed for quoted text
    ret.gsub("&apos;","\'");  // Needed for quoted text
    ret.gsub("&excl;","!");
    ret.gsub("&lt;","<");     // Needed.
    ret.gsub("&gt;",">");
    return ret;
  }

  //// XMLIStreamC //////////////////////////////////////////////////////////
  
  //: Construct from an ordinary stream.
  
  XMLIStreamC::XMLIStreamC(IStreamC &is)
    : IStreamC(is)
  {
    XMLIStreamC *ptr;
    if((ptr = dynamic_cast<XMLIStreamC *>(&is)) != 0) 
      ((XMLBaseC &)*this) = *ptr;
    else
      ((XMLBaseC &)*this) = XMLBaseC(true);
  }
  
  StringC XMLIStreamC::ReadID() {
    StringC ret;
    char c = SkipWhiteSpace();
    for(;IsXMLIDChar(c);c = GetChar()) 
      ret += c;
    is().putback(c);
    return ret;
  }
  
  //: Read a tag from a stream.
  // returns true if one is found or false if end of group found.
  
  XMLTagOpsT XMLIStreamC::ReadTag(StringC &name,RCHashC<StringC,StringC> &attr) {
    char c;
    bool gotTag = false;
    bool endOfTag = false;
    bool emptyTag = false;
    bool foundEndTag = false;
    StringC id;
    try {
      
      while(*this && !endOfTag) {
	// Search for start of tag.
	gotTag = false;
	foundEndTag = false;
	c = GetChar();
	if(c != '<')
	  continue; // Skip non-tag characters.
	gotTag = true;
	// Work out what sort of tag we've got.
	c = GetChar();
	switch(c) 
	  {
	  case '?': // Processing instruction.
	    ONDEBUG(cerr << "XMLIStreamC::ReadTag(), Found processing instruction. \n");
	    SkipTo("?>"); // Skip it.
	    continue; // Start searching for a tag again.
	  case '!':  // Comment or DTD
	    {
	      char nc = GetChar();
	      if(nc == '-') {
		char anc = GetChar();
		if(anc == '-') { // Comment...
		  ONDEBUG(cerr << "XMLIStreamC::ReadTag(), Found comment. \n");
		  SkipTo("-->");
		  continue; // Start searching for a tag again.
		}
	      }
	      // This may have to be more clever.
	      ONDEBUG(cerr << "XMLIStreamC::ReadTag(), Found DTD info. \n");
	      SkipTo('>');
	      // Start searching for a tag again.
	    }
	    break;
	  case '>':
	    cerr << "WARNING: Found an empty tag (<>) in XML stream. \n";
	    continue; // Empty <> probably illegal ??
	  case '/':
	    foundEndTag = true;
	    emptyTag = true;
	    break;
	  default:
	    is().putback(c);
	  }
	
	id = ReadID();
	
	if(!emptyTag) { // Is an end tag, don't push a new context.
	  ONDEBUG(cerr << "XMLIStreamC::ReadTag(), Found tag start '" << id << "'\n");
	  StartContext(id);
	} else {
	  ONDEBUG(cerr << "XMLIStreamC::ReadTag(), Found tag end '" << id << "'\n");
	}
	
	// Check for attributes.
	while(!endOfTag) {
	  c = SkipWhiteSpace();
	  switch(c) 
	    {
	    case '/':
	      c = GetChar();
	      if(c != '>') {
		ONDEBUG(cerr << "ERROR: Unexpected character '"  << c << "' in XML tag. \n");
		throw ExceptionInvalidStreamC("Unexpected end of XML tag. ");
	      }
	      emptyTag = true;
	      /* FALL THROUGH */
	    case '>':
	      endOfTag = true;
	      continue;
	    default: // An attribute.
	      is().putback(c);
	      ReadAttrib();
	      break;
	    }
	}
      }
    } catch(ExceptionEndOfStreamC &) {
      if(gotTag)
	throw ExceptionInvalidStreamC("Unexpected end of XML stream. ");
    }
    if(IsContext())
      attr = Context().Attributes();
    if(emptyTag) {
      EndOfContext(id);
      name = id;
      if(!foundEndTag)
	return XMLEmptyTag;
      return XMLEndTag;
    }
    if(!gotTag)
      return XMLContent;
    name = id;
    if(foundEndTag)
      return XMLEndTag;
    return XMLBeginTag;
  }

  //: Skip to after the end of the current element.
  
  bool XMLIStreamC::SkipElement() {
    StringC curCtxt = Context().Name();
    StringC name;
    int level = 0;
    while(*this) {
      XMLTagOpsT tt = ReadTag(name); 
      if(tt == XMLEndTag) {
	// Found end tag.
	if(level == 0)
	  break;
	level--;
	continue;
      }
      if(tt == XMLBeginTag) {     // Found open tag.
	level++;
	continue;
      }
      RavlAssertMsg(tt == XMLEmptyTag,"Unexpected tag type. ");
    }
    if(name != curCtxt) {
      cerr << "WARNING: End tag name mismatch, got '" << name << "' expected '" << curCtxt << "'\n";
      return false;
    }
    return true;
  }

  //: Skip to named element.
  // This will skip to the next tag of the given name.
  // if the Current context ends it will return XMLEndTag.

  XMLTagOpsT XMLIStreamC::SkipToElement(const StringC &elementName,RCHashC<StringC,StringC> &attr) {
    StringC name;
    RCHashC<StringC,StringC> tattr;
    while(*this) {
      XMLTagOpsT tt = ReadTag(name,tattr);
      if(name == elementName) {
	attr = tattr;
	return tt;
      }
      if(tt == XMLBeginTag)
	SkipElement();
      if(tt == XMLEndTag)
	break;
    }
    return XMLEndTag;
  }

  //: Read attribute and add it to the current context.
  
  StringC XMLIStreamC::ReadAttrib() {
    StringC id = ReadID();
    char c = SkipWhiteSpace();
    if(c != '=') {
      ONDEBUG(cerr << "ERROR: Unexpected character "  << c << "in XML attribute. \n");
      throw ExceptionInvalidStreamC("Unexpected character in XML attribute. ");
    }
    c = SkipWhiteSpace();
    StringC val;
    if(c != '\"') { // Quoted string ?
      is().putback(c);
      val += ReadID();
    } else {
      val = ClipTo('\"');
      // Unescape string ??
    }
    Context().Attributes()[id] = val;
    ONDEBUG(cerr << "XMLOStreamC::ReadAttrib(), Got '" << id << "' = '" << val << "' in " << Context().Name() << "\n");
    return id;
  }
  
  //: Get an integer attribute for entity.
  // This can only be called between StartTag and StartContents.
  // This returns true if attribute is set.
  
  bool XMLIStreamC::GetAttrib(const StringC &name,IntT &val) {
    StringC tv;
    if(!GetAttrib(name,tv))
      return false;
    val = atoi(tv);
    return true;
  }
  
  //: Get an unsigned integer attribute for entity.
  // This can only be called between StartTag and StartContents.
  // This returns true if attribute is set.
  
  bool XMLIStreamC::GetAttrib(const StringC &name,UIntT &val) {
    StringC tv;
    if(!GetAttrib(name,tv))
      return false;
    StrIStreamC(tv) >> val;
    return true;
  }
  
  //: Get a real valued attribute for entity.
  // This can only be called between StartTag and StartContents.
  // This returns true if attribute is set.
  
  bool XMLIStreamC::GetAttrib(const StringC &name,RealT &val) {
    StringC tv;
    if(!GetAttrib(name,tv))
      return false;
    val = atof(tv);
    return true;
  }
  
  //// XMLOStreamC //////////////////////////////////////////////////////////

  //: Construct from an ordinary stream.
  
  XMLOStreamC::XMLOStreamC(OStreamC &os)
    : OStreamC(os)
  {
    XMLOStreamC *ptr;
    if((ptr = dynamic_cast<XMLOStreamC *>(&os)) != 0) 
      ((XMLBaseC &)*this) = *ptr;
    else
      ((XMLBaseC &)*this) = XMLBaseC(true);
  }
  
  //: Begin writting a tag with the given attributes.
  
  void XMLOStreamC::StartTag(const StringC &name,const RCHashC<StringC,StringC> &attribs,bool emptyTag) {
    StartContext(name,attribs,emptyTag);
  }
  
  //: Begin writting a tag with the given attributes.
  
  void XMLOStreamC::StartTag(const StringC &name,bool emptyTag) {
    RCHashC<StringC,StringC> none;
    StartTag(name,none,emptyTag);
  }
  
  //: Call before writting contents of entity to stream.
  
  void XMLOStreamC::StartContents() {
    //ONDEBUG(cerr << "XMLOStreamC::StartContents(), Name:'" << Context().Name() << "' \n");
    if(IsContent()) {
      cerr << "XMLOStreamC::StartContents(), ERROR: Contents already started in '" << Context().Name() << "' \n";
      return;
    }
    (*this) << '<' << Context().Name();
    for(HashIterC<StringC,StringC> it((RavlN::HashC<RavlN::StringC,RavlN::StringC> &)Context().Attributes());it;it++)
      (*this) << ' ' << it.Key() << "=\"" << it.Data() << "\"";
    if(Context().IsEmptyTag()) 
      (*this) << "/>";
    else
      (*this) << '>';
    SetContent(true);
  }
  
  //: End writting a tag.
  // if strict checking is enabled, name will be check against that of the open tag.
  
  void XMLOStreamC::EndTag(const StringC &name) {
    //ONDEBUG(cerr << "XMLOStreamC::EndTag(StringC) : '" << name << "'\n");
    if(Context().IsEmptyTag())
      cerr << "XMLOStreamC::EndTag(), ERROR: EndTag Called on empty tag. '" << Context().Name() << "'\n";
    (*this) << "</" << name << ">";
    if(IsStrict()) {
      if(!EndOfContext(name)) {
	ONDEBUG(cerr << "XMLOStreamC::EndTag()");
	cerr << "ERROR: Not end of named entity '" << name << "' Currently its '" << Context().Name() << "'\n";
      }
    } else
      EndOfContext();
  }
  
  //: End writting current entity.
  
  void XMLOStreamC::EndTag() {
    //ONDEBUG(cerr << "XMLOStreamC::EndTag() : '" << Context().Name() << "'\n");
    (*this) << "</" << Context().Name() << ">";
    EndOfContext();
  }

  //: Indent the following line appropriatly.
  
  void XMLOStreamC::Indent(int off) {
    (*this) << '\n';
    UIntT lvl = LevelsNested() + off;
    // Could do something with tabs to make files smaller ?
    for(UIntT i = 0;i < lvl;i++) 
      (*this) << ' ';
  }

  
  //: Set attribute for entity.
  // This can only be called between StartTag and StartContents.
  
  void XMLOStreamC::SetAttrib(const StringC &name,const IntT &val) {
    SetAttrib(name,StringC(val));
  }

  //: Set attribute for entity.
  // This can only be called between StartTag and StartContents.
  
  void XMLOStreamC::SetAttrib(const StringC &name,const UIntT &val) {
    SetAttrib(name,StringC(val));
  }
  
  //: Set attribute for entity.
  // This can only be called between StartTag and StartContents.
  
  void XMLOStreamC::SetAttrib(const StringC &name,const char * &val) {
    SetAttrib(name,StringC(val));
  }
  
  //: Set attribute for entity.
  // This can only be called between StartTag and StartContents.
  
  void XMLOStreamC::SetAttrib(const StringC &name,const RealT &val) {
    SetAttrib(name,StringC(val));
  }
  
  //// Globals //////////////////////////////////////////////////////////
  
  //: Do an output stream op.
  XMLOStreamC &operator<<(XMLOStreamC &strm,const XMLTagOpsT &elem) { 
    //cerr << "operator<<(XMLOStreamC &strm,const XMLTagOpsT &elem), Called with :" << ((int) elem) << "\n";
    switch(elem) 
      {
      case XMLEndTag:
	strm.EndTag();
	break;
      case XMLEmptyTag:
	strm.Context().SetEmptyTag(true);
	strm.StartContents();
	strm.EndOfContext();
	//strm.EndTag();
	break;
      case XMLContent:
	strm.StartContents(); 
	break;
      case XMLIndent: strm.Indent(); break;
      case XMLIndentDown: strm.Indent(-1); break;
	
      case XMLBeginTag:
      case XMLComment:
	RavlAssertMsg(0,"XMLOStreamC & operator<<(XMLTagOpsT) Illegal tag op. ");
	break;
      }
    return strm;
  }

  //: Do an input stream op.
  XMLIStreamC &operator>>(XMLIStreamC &strm,const XMLTagOpsT &elem) {
    switch(elem) 
      {
      case XMLEndTag:
	{
	  StringC name;
	  for(;;) {
	    if(strm.ReadTag(name) == XMLEndTag)
	      break;
	    cerr << "Unexpected start tag '" << name << "' found, skipping. \n";
	    strm.SkipElement();
	  }
	}
	break;
	
      case XMLContent:
      case XMLIndent: 
      case XMLIndentDown: 
	break; // Ignore.
	
      case XMLEmptyTag:
      case XMLBeginTag:
      case XMLComment: // Issue error.
	RavlAssertMsg(0,"XMLIStreamC & operator>>(XMLTagOpsT) Illegal tag op. ");
	break;
      }
    return strm;
  }
  
}
