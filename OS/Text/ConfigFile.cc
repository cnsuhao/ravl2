// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlOS

#include "Ravl/Text/ConfigFile.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/HSet.hh"
//#include "Ravl/HSetExtra.hh"
#include "Ravl/Stack.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Default constructor.
  ConfigFileBodyC::ConfigFileBodyC()
    : ordCount(0)
  {}

  //: Sub-section. constructor.
  
  ConfigFileBodyC::ConfigFileBodyC(TextFileC &af,const StringC &nname) 
    : name(nname),
      ordCount(0)
  {
    ONDEBUG(cerr << "ConfigFileBodyC::ConfigFileBodyC(TextOFileC,StringC), Called \n");
  }
  
  //: Load a def file.
  
  bool ConfigFileBodyC::Load(StringC fn,bool doChecking)  {
    TextFileC af(fn);  
    if(!af.IsLoaded()) {
      cerr << "ERROR: Failed to load config file :'" << fn << "'\n";
      return false;
    }
    return Load(af,doChecking);
  }
  
  ConfigFileC ConfigFileBodyC::Section(const StringC &tag) {
    return sec[tag];
  }
  
  //: Add section.
  
  void ConfigFileBodyC::AddSection(const StringC &tag,ConfigFileC &cf,const TextFragmentC &nf) {
    sec[tag] = cf.Abstract();
    if(!frags.IsElm(tag)) {
      frags[tag] = nf;
      order[tag] = ordCount++;
    }
  }

  static SArray1dC<bool> ConfigFile_SkipSpace = TextCursorC::BuildClipTable(" \t\r\n");
  
  ///////////////////////
  // Load a def file.
  
  bool ConfigFileBodyC::Load(TextFileC &af,bool doChecking) {
    bool ret = true;
    tab.Empty();
    //  af.Dump(cout);
    
    bool ignore = false;
    bool addTo = false;
    
    StackC<ConfigFileC> scope;
    scope.Push(ConfigFileC(*this));
    
    TextCursorC tc(af);
    while(tc.IsElm()) {
      tc.SkipWhite();
      if(!tc.IsElm())
	break;
      if(tc.Char() == '#') { // Comment...
	if(!tc.NextLine())
	  break;
	continue;
      }
      RavlAssert(scope.Top().IsValid());
      if(tc.Char() == '}') { // End of section.
	ONDEBUG(cerr << "Got close scope. \n");
	scope.Pop();
	tc.NextChar();
	if(scope.IsEmpty()) {
	  cerr << "ERROR: Too many '}',  at " << tc.PositionTxt() << "\n";
	  return false;
	}
	continue;
      }
      ONDEBUG(cout << "Doing line:" << tc.LineText());
      StringC tag,data;
      tag = tc.ClipID();
      if(tag.IsEmpty()) {
	cerr << "ERROR: reading tag at " << tc.PositionTxt() << "\n";
	return false;
      }
      if(!tc.IsElm())
	break;
      if(doChecking && !ignore) { // Check tags ?
	if(!CheckTag(tag)) {
	  cerr << "ERROR: unrecognised tag '" << tag <<"' at " << tc.PositionTxt() << "\n";
	  cerr << "Line :'" << tc.LineText().before('\n') << "'" << endl;
	  ret = false; // Check failed...
	}
      }
      tc.SkipWhite();
      if(!tc.IsElm()) 
	break;
      
      addTo = false;
      switch(tc.Char()) 
	{
	case '=':
	  break;
	case '{': // Open named scope.
	  {
	    ONDEBUG(cerr << "ConfigFile: Got a section '" << tag << "'\n");
	    RavlAssert(scope.Top().IsValid());
	    tc.NextChar();
	    ConfigFileC conf;
	    if(!scope.Top().Body().sec.IsElm(tag)) {
	      conf = ConfigFileC(af,tag);
	      scope.Top().AddSection(tag,conf,TextFragmentC(tc,tc));
	    } else
	      conf = ConfigFileC(scope.Top().Body().sec[tag]);
	    RavlAssert(conf.IsValid());
	    scope.Push(conf);
	  }
	  continue;
	case '+':
	  if(tc.NextChar()) {
	    if(tc.Char() == '=') {
	      addTo = true;
	      break;
	    }
	  }
	default:
	  cerr << "ERROR: assignment expected at " << tc.PositionTxt() << "\n";
	  ret = false;
	  tc.NextLine(); 
	  continue; // Skip line.
	}
      if(sec.IsElm(tag)) {
	cerr << "ERROR: repeated definition of variable '" << tag <<"' at " << tc.PositionTxt() << " as section \n";
	tc.NextLine();
	continue;
      }
      
      RavlAssert(scope.Top().IsValid());
      if(!addTo && scope.Top().IsDefined(tag)) {
	cerr << "ERROR: repeated definition of variable '" << tag <<"' at " << tc.PositionTxt() << "  Value:" << tab[tag] << endl;
	return false;
      }
      TextCursorC startData = tc; // Mark start of data.
      tc.NextChar();
      if(!tc.IsElm())
	break;
      
      tc.SkipChars(ConfigFile_SkipSpace);
      if(!tc.IsElm()) {
	if(!ignore)
	  scope.Top().SetVar(tag,StringC(),TextFragmentC(startData,startData));
	break;
      }
      if(tc.ColNum() == 0) { // Must have got a newline.
	if(!ignore)
	  scope.Top().SetVar(tag,StringC(),TextFragmentC(startData,startData));
	continue;
      }
      
      //cout << tag << "=";
      bool done = false;
      
      TextFragmentC nf(startData,tc);
      bool inQuotes = false;
      int quoteStart = 0;
      while(tc.IsElm()) {
	switch(tc.Char())
	  {
	  case '"':
	    quoteStart = tc.LineNo();  
	    inQuotes = !inQuotes;
	    break;
	  case '\\':
	    tc.NextChar();
	    if(!tc.IsElm()) {
	      done = true;
	      break;
	    }
	    if(tc.Char() != '\n') {
	      if(tc.Char() != '"' && tc.Char() != '$') {
		cerr << "Escaped : " <<  ((int) tc.Char()) << " " << ((int) '\\') << endl;
		cerr << " '" << tc.LineText() << "'\n";
		for(unsigned int i = 0;i < tc.LineText().length();i++) {
		  cerr << (int) tc.LineText()[i] << " ";
		}
		cerr << endl;
	      }
	      data += tc.Char(); // Added escaped charactor.
	    }
	    break;
	  case '#':
	    if(!inQuotes)
	      tc.NextLine();
	  case '\n':
	    if(!inQuotes) {
	      nf.End() = tc;
	      nf.End().PrevChar();
	      done = true;
	      break;
	    }
	  default:
	    //cout << tc.Char();
	    data += tc.Char();
	  }
	if(done)
	  break;
	tc.NextChar();
      }
      if(inQuotes) {
	cerr << "ERROR: End of config file found without closing quotes from line " << quoteStart << "\n";
      }
      //cout << "\n";
      if(!ignore) {
	RavlAssert(scope.Top().IsValid());
	if(addTo) {
	  scope.Top().AddVar(tag,data,nf);
	  addTo = false;
	} else
	  scope.Top().SetVar(tag,data,nf);
	ONDEBUG(cerr << tag << " = " << data << endl);
      }
    }
    return ret;
  }
  
  //////////////////////////
  // Check if a tag is valid.
  
  bool ConfigFileBodyC::CheckTag(StringC tag) 
  { return true; }

  //: Make a list of sections.
  
  DListC<StringC> ConfigFileBodyC::ListSections() {
    DListC<StringC> ret;
    for(HashIterC<StringC,RCAbstractC> it(sec);it;it++)
      ret += it.Key();
    return ret;
  }


  //: Dump contents of file to 'out'.
  
  void ConfigFileBodyC::Dump(ostream &out,int depth) {
    
    for(ConfigFileIterVarC it(IterVars());it;it++) {
      for(int i =0; i < depth;i++)
	out << ' ';
      out << it.Key() << "='" << it.Data() <<"'\n";
    }
    DListC<StringC> lst = ListSections();
    for(DLIterC<StringC> it(lst);it;it++) {
      for(int i =0; i < depth;i++)
	cerr << ' ';
      out << *it << "={";
      ConfigFileC cf = Section(*it);
      if(cf.IsValid()) {
	out << "\n";
	cf.Dump(out,depth+1);
      }
      for(int i =0; i < depth;i++)
	cerr << ' ';
      out << "}\n";
    }
  }
  
}
