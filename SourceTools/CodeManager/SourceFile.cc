// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! lib=RavlSourceTools
//! rcsid="$Id$"

#include "Ravl/SourceTools/SourceFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/OS/Filename.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  static HashC<StringC,StringC> GenerateCommentStr() {
    HashC<StringC,StringC> ret;
    ret["Unknown"] = "";
    ret["C"] = "/*";
    ret["CH"] = "/*";
    ret["C++H"] = "//";
    ret["C++"] = "//";
    ret["Lex"] = "/*";
    ret["Yacc"] = "/*";
    ret["Java"] = "//";
    ret["Make"] = "#";
    ret["Perl"] = "#";
    ret["Html"] = "<!--";
    return ret;
  }

  static HashC<StringC,StringC> GenerateCommentEndStr() {
    HashC<StringC,StringC> ret;
    ret["Unknown"] = " \n";
    ret["C"] = " */\n";
    ret["CH"] = " */\n";
    ret["C++H"] = "\n";
    ret["C++"] = "\n";
    ret["Lex"] = " */\n";
    ret["Yacc"] = " */\n";
    ret["Java"] = "\n";
    ret["Make"] = "\n";
    ret["Perl"] = "\n";
    ret["Html"] = " -->\n";
    return ret;
  }
  
  static HashC<StringC,StringC> GenerateExtentionMap() {
    HashC<StringC,StringC> ret;
    // C
    ret["c"] = "C";
    ret["h"] = "CH";
    // C++ 
    ret["cc"] = "C++";
    ret["C"] = "C++";
    ret["cpp"] = "C++";
    ret["hh"] = "C++H";
    ret["hpp"] = "C++H";
    
    ret["mk"] = "Make";
    ret["pl"] = "Perl";
    ret["java"] = "Java";
    ret["Lex"] = "Lex";
    ret["Yacc"] = "Yacc";    
    ret["html"] = "Html";    
    ret["htm"] = "Html";    
    return ret;
  }
  
  HashC<StringC,StringC> SourceFileBodyC::extToType = GenerateExtentionMap();
  HashC<StringC,StringC> SourceFileBodyC::commentString = GenerateCommentStr();
  HashC<StringC,StringC> SourceFileBodyC::commentEndString = GenerateCommentEndStr();
  //: Default constructor.
  
  SourceFileBodyC::SourceFileBodyC()
    : fileType("Unknown")
  {}
  
  //: Constructor from a file.
  
  SourceFileBodyC::SourceFileBodyC(const StringC &filename)
    : TextFileBodyC(filename),
      fileType("Unknown")
  {
    fileType = IdFile();
  }
  
  //: Construct from a string. 
  // concat, if true don't split lines, 
  // otherwise do.
  
  SourceFileBodyC::SourceFileBodyC(const StringC &text,bool noFinalRet,bool concat = false)
    : TextFileBodyC(text,noFinalRet,concat),
      fileType("Unknown")
  {
    fileType = IdFile();
  }
  
  //: Constructor from a stream.
  
  SourceFileBodyC::SourceFileBodyC(istream &fin)
    : TextFileBodyC(fin),
      fileType("Unknown")
  {}
  
  //: Id the current file.
  
  StringC SourceFileBodyC::IdFile() {
    FilenameC fn = Filename();
    StringC ext = fn.Extension();
    //ONDEBUG(cerr << "SourceFileBodyC::IdFile(), File '" << fn << "' of type '" <<extToType[ext] << "' Loaded\n");
    return extToType[ext];
  }

  //: Load from file.
  
  bool SourceFileBodyC::Load(const StringC &filename) {
    bool ret = TextFileBodyC::Load(filename);
    fileType = IdFile();
    return ret;
  }


  //: Check variable exists in hdr file.
  // if 'force' is true then update variable regardless if is there 
  // already or not.
  
  bool SourceFileBodyC::CheckDocVar(const StringC &var,const StringC &value,bool force)  {
    IntT atline;
    const StringC &comStr = commentString[fileType];
    const StringC &comEndStr = commentEndString[fileType];
    if(comStr.IsEmpty()) {
      ONDEBUG(cerr << "SourceFileBodyC::CheckDocVar() Comment str not know for :" << fileType << "\n");
      return false; // Don't know the comment string for this filetype.
    }
    StringC newline =  comStr + "! " + var + '=' + value + comEndStr;
    ONDEBUG(cerr << "SourceFileBodyC::CheckDocVar() Newline :" << newline);
    if((atline = FindLineMatch(comStr + "! " + var)) >= 0) {
      StringC &theLine = (*this)[atline];
      //cerr << "(Found " + var +") ";
      bool update = force;
      if(!update) {
	int eqAt = theLine.index("=");
	if(eqAt > 0) {
	  StringC tmp = theLine.after(eqAt);
	  tmp = tmp.TopAndTail();
	  if(tmp == "")  // Empty ?
	    update = true;
	}
      }
      
      if(update) {
	if(theLine != newline) {
	  theLine = comStr + "! " + var + '=' + value + '\n';
	  SetModified();
	}
      }
      return true;
    }
    SourceFileC me(*this);
    TextCursorC at((TextFileC &)me);
    while(at.IsElm()) {
      if(at.LineText().contains("#",0) > 0) {
	//cerr << "Skip1:" << at.LineText();
	at.NextLine();
	continue; // After other macro defs a top of file.
      }
      if(at.LineText().contains("/*",0) > 0) {
	at.NextLine();
	continue; // After comment bar.
      }
      if(at.LineText().contains(comStr,0) > 0) {
	//cerr << "Skip2:" << at.LineText();
	at.NextLine();
	continue; // After comment bar.
      }
      if(at.LineText().contains(comStr + "! ",0) > 0) {
	//cerr << "Skip3:" << at.LineText();
	at.NextLine();
	continue; // After other variables.
      }
      break;
    }
    return at.InsertLine(newline);
  }
  
  bool SourceFileBodyC::CheckDocVarSub(const StringC &var,const StringC &subs,const StringC &value,bool force) {
    IntT atline;
    const StringC &comStr = commentString[fileType];
    const StringC &comEndStr = commentEndString[fileType];
    if(comStr.IsEmpty())
      return false; // Don't know the comment string for this filetype.
    StringC newline =  comStr + "! " + var + '=' + value + comEndStr;
    cerr << "SourceFileBodyC::CheckDocVarSub() Newline :" << newline;
    if((atline = (*this).FindLineMatch(comStr + "! " + var)) >= 0) {
      StringC &theLine = (*this)[atline];
      bool update = force;
      //    cerr << "(Found " + var +") ";
      if(!update) {
	int eqAt = theLine.index("=");
	if(eqAt > 0) {
	  if(theLine.after(eqAt).TopAndTail() == "")  // Empty ?
	    update = true;
	}
      }
      if(update) {
	if(theLine != newline) {
	  theLine = newline;
	  SetModified();
	}
      }
      return true;
    }
    if((atline = FindLineMatch(subs)) >= 0) {
      //cerr << "Doing subst on " << subs << " " << buff[atline] <<endl;
      (*this)[atline] = newline;
      SetModified();
      return true;    
    }
    SourceFileC me(*this);
    TextCursorC at((TextFileC &)me);
    while(at.IsElm()) {
      if(at.LineText().contains("#",0) > 0) {
	//cerr << "Skip1:" << at.LineText();
	at.NextLine();
	continue; // After other macro defs a top of file.
      }
      if(at.LineText().contains("/*",0) > 0) {
	at.NextLine();
	continue; // After comment bar.
      }
      if(at.LineText().contains(comStr,0) > 0) {
	//cerr << "Skip2:" << at.LineText();
	at.NextLine();
	continue; // After comment bar.
      }
      if(at.LineText().contains(comStr + "! ",0) > 0) {
	//cerr << "Skip3:" << at.LineText();
	at.NextLine();
	continue; // After other variables.
      }
      break;
    }
    return at.InsertLine(newline);
  }
  
  ////////////////////////////
  //: Extract variable value.
  // Returns empty string if not found.
  
  StringC SourceFileBodyC::GetDocValue(const StringC &var) {
    IntT atline;
    const StringC &comStr = commentString[fileType];
    const StringC &comEndStr = commentEndString[fileType];
    if(comStr.IsEmpty()) {
      return false; // Don't know the comment string for this filetype.
    }
    StringC prefix = comStr + "! ";
    //ONDEBUG(cerr << "SourceFileBodyC::CheckDocVarSub() prefix :" << prefix << "\n");
    StringC matchline = prefix + var;
    if((atline = FindLineMatch(matchline)) < 0)
      return StringC(); // Not found.
    StringC &theLine = (*this)[atline];
    if(StringC(theLine.after(prefix)).before('=') != var)
      return StringC();
    StringC data = theLine.after('=');
    if(!(comEndStr.length() == 1 && comEndStr.lastchar() == '\n')) {
      StringC end = comEndStr.Copy().before('\n');
      data = data.before(end);
    }
    data = data.TopAndTail();
    if(data.length() < 1)
      return StringC();
    if(data.firstchar() == '"') { // Quoted ?
      // FIXME :- Tackle quoted strings.
      data = data.after('"');
      return data.before('"');
    }
    // Maybe just return data ??
    if(!data.contains(' '))
      return data;
    return data.before(' ');
  }
  
  //: Check a header is on file.
  
  bool SourceFileBodyC::CheckHeader(const TextBufferC &hdr,const StringC &ceoh,const StringC &name,const StringC &desc,const StringC &org) {
    StringC eoh(ceoh);
    // Setup default end of header value.
    if(eoh.IsEmpty()) {
      eoh = const_cast<TextBufferC &>(hdr).Lines().Last().Text().Copy();
      if(eoh.lastchar() == '\n')
	eoh = eoh.before('\n');
    }
    if(eoh.IsEmpty() || eoh == "\n") {
      cerr << "ERROR: End of file marker is an empty string. \n";
      return false;
    }
    ONDEBUG(cerr << "Using marker:'" << eoh << "' \n");
    DLIterC<TextFileLineC> it1(const_cast<TextBufferC &>(hdr).Lines());
    DLIterC<TextFileLineC> it2(Lines());
    bool ok = true;
    for(;it1 && it2;it1++,it2++) {
      if(it1->Text() != it2->Text()) {
	ok = false;
	break;
      }
    }
    if(!it1) 
      return false; // Header is present and correct.
    int eohAt = FindLineMatch(eoh); // Look for end of header marker.
    if(eohAt >= 0) { // Found end of header marker.
      if(eohAt > 30) {
	cerr << "WARNING: End of header marker more than 30 lines into the file. (" << eohAt <<") \n";
	return false;
      }
      it2.Nth(eohAt).Head(); // Goto the last line, and remove the head of the list.
    }
    // Copy in new section.
    it2.First();
    for(it1.First();it1;it1++) {
      if(it1->Text().contains("%")) {
	StringC newLine = it1->Text().Copy();
	newLine.gsub("%name%",name);
	newLine.gsub("%desc%",desc);
	newLine.gsub("%org%",org);
	it2.InsertBef(TextFileLineC(0,newLine));
      } else
	it2.InsertBef(*it1);
    }
    SetModified();    
    return true;
  }
}
