// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id: TemplateComplex.cc 7624 2010-03-01 11:54:32Z alexkostin $"
//! lib=RavlOS
//! file="Ravl/OS/Text/TemplateComplex.cc"

#include "Ravl/Text/TemplateComplex.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/StringList.hh"
#include "Ravl/SubStringList.hh"
#include "Ravl/OS/Filename.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  TemplateComplexBodyC::TemplateComplexBodyC(TextFileC &ntemplFile) 
    : templFile(ntemplFile)
  {
    templateDir = FilenameC(ntemplFile.Filename()).PathComponent();
    vars.Push(RCHashC<StringC,StringC>(true) ); // Push base variables.
    InitCommands();
  }
  
  //: Constructor.
  
  TemplateComplexBodyC::TemplateComplexBodyC(const StringC &fname)
    : templFile(fname)
  {
    templateDir = FilenameC(fname).PathComponent();
    vars.Push(RCHashC<StringC,StringC>(true) ); // Push base variables.
    InitCommands();
  }

  //: Start build of document, write results to given stream.
  
  bool TemplateComplexBodyC::BuildToStream(OStreamC &out) {
    output.Push(out);
    incDepth = 0;
    bool ret = BuildSub(templFile);
    output.DelTop();
    return ret;
  }
  
  //: Start build of document.
  
  bool TemplateComplexBodyC::Build(StringC &fn) {
    //if(verbose)
    ONDEBUG(cerr << "Building file:'" << fn <<"'\n");
    FilenameC dirComp = FilenameC(fn).PathComponent();
    SetVar("thisFilename",FilenameC(fn).NameComponent());
    if(dirComp != "") { // Extra directory specified ?
      if(!dirComp.IsDirectory()) {
	if(!dirComp.MakeDir()) {
	  cerr << "Failed to make directory '" << dirComp  <<"' for file '" << fn << "'\n";
	  return false;
	}
      }
    }
    OStreamC outs(fn);
    if(!outs.good()) {
      cerr << "Failed to open output file '" << fn << "'\n";
      return false;
    }
    return BuildToStream(outs);
  }
  
  //: Setup command func.
  
  void TemplateComplexBodyC::SetupCommand(const StringC &cmd,bool (TemplateComplexBodyC::* func)(StringC &arg)) {
    StringC empty;
    //commands[cmd] = CallMethod1C<TemplateComplexBodyC &,StringC &,bool>(*this,func,empty);
    commands[cmd] = TriggerR(*this,func,empty);
  }
  
  //: Setup default commands.
  
  void TemplateComplexBodyC::InitCommands() {
    commands["FilePattern"] = CallFunc1C<StringC &,bool>(false); // Not need here, ignore it.
    commands["FileObject"] = CallFunc1C<StringC &,bool>(false);  // Not need here, ignore it.
    commands["//"] = CallFunc1C<StringC &,bool>(false);          // Comment, ignore.
    SetupCommand("set",&TemplateComplexBodyC::DoSet);
    SetupCommand("for",&TemplateComplexBodyC::DoFor);
    SetupCommand("if",&TemplateComplexBodyC::DoIf);
    SetupCommand("ifset",&TemplateComplexBodyC::DoIfSet);
    SetupCommand("else",&TemplateComplexBodyC::DoElse);
    SetupCommand("include",&TemplateComplexBodyC::DoInclude);
    SetupCommand("sub",&TemplateComplexBodyC::DoSub);
    SetupCommand("subc",&TemplateComplexBodyC::DoSubCopy);
    SetupCommand("subst",&TemplateComplexBodyC::DoSubst);
    SetupCommand("define",&TemplateComplexBodyC::DoDefine);
    SetupCommand("htmlsafe",&TemplateComplexBodyC::HtmlSafe);
    SetupCommand("uppercase",&TemplateComplexBodyC::DoUpperCase);
    SetupCommand("lowercase",&TemplateComplexBodyC::DoLowerCase);
    SetupCommand("silent",&TemplateComplexBodyC::DoSilent);
    SetupCommand("print",&TemplateComplexBodyC::DoErrPrint);
    SetupCommand("before",&TemplateComplexBodyC::DoBefore);
    SetupCommand("after",&TemplateComplexBodyC::DoAfter);
    SetupCommand("truncate",&TemplateComplexBodyC::DoFirstN);
    SetupCommand("marktruncate",&TemplateComplexBodyC::DoMarkFirstN);
  }
  
  //: Print a message to stderr.
  // Put the text on the stderr.
  
  bool TemplateComplexBodyC::DoErrPrint(StringC &txt) {
    //cerr << "TemplateComplexBodyC::DoErrPrint(), Called '" << txt <<"'\n";
    cerr << Interpret(txt);
    return true;
  }
  
  //: Get initialise information from template file.
  
  bool TemplateComplexBodyC::Scan(StringC &fn) {
    TextFileC templ(fn);
    return Scan(templ);
  }

  bool TemplateComplexBodyC::Scan(TextFileC &templ) {  
    OStreamC toutput("/dev/null");
    TemplateFileC master(templ ,toutput);
    while(master.IsElm()) {
      StringC &ip = master.Next();
      int at = ip.index(':');
      if(at < 0)
	continue;
      StringC var = ip.before(at);
      //cerr << "Got data:'" << ip <<"'  Var: '" << var << "'\n";
      if(!presets.IsMember(var))
	continue;
      StringC value = ip.after(at);
      vars.Top()[var] = value;    
    }  
    return true;
  }

  //: Interpret string 'str' and return the result.
  
  StringC TemplateComplexBodyC::Interpret(const StringC &str) {
    StrOStreamC outStr;
    output.Push(outStr);
    TextFileC subTextBuff(str,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << str << "' in template '" << templFile.Filename() << "' failed.\n";
    StringC ret = outStr.String();
    ONDEBUG(cerr << "TemplateComplexBodyC::Interpret(), '" << str << "' -> '" << ret << "'\n");
    output.DelTop();
    return ret;
  }
  
  
  //: Set variable.
  
  bool TemplateComplexBodyC::DoSet(StringC &data) {
    ONDEBUG(cerr << "Set '" << data << "'\n");
    int eqSign = data.index('=');
    if(eqSign < 0) {
      cerr << "Malformed set '" << data << "'\n";
      return false;
    }
    StringC varName = data.before(eqSign).TopAndTail();
    if(varName == "") {
      cerr << "ERROR: Empty variable name in '" << data << "'\n";
      return false;
    }
    
    StringC value = data.after(eqSign).TopAndTail();
    ONDEBUG(cerr << "Value='" << value << "'\n");
    if(value != "") 
      vars.Top()[varName] = Interpret(value);
    else
      vars.Top().Del(varName); // Remove variable.
    return true;
  }
  
  //: Look over a list.
  
  bool TemplateComplexBodyC::DoFor(StringC &data) {
    int startList = data.index(':');
    if(startList < 0) {
      cerr << "Malformed 'for' in template. '" << data << "' no list \n";
      return false;
    }
    int startTmpl = data.index(':',startList+1);
    if(startTmpl < 0) {
      cerr << "Malformed 'for' in template. '" << data << "' no template \n";
      return false;
    }
    
    StringC sep = data.before(startList);
    SubStringC list = data.at(startList+1,(startTmpl - startList)-1).TopAndTail();
    
    //cerr << "DoFor: Sep='" << sep << "' List='" << list << "'\n";
    
    if(list.length() < 1)  // Nothing in list ?
      return true;
    if(list.firstchar() == '$') {
      //ONDEBUG(cerr << "Subst param1 '" << param1  << "' -> '" << obj.Var(param1) << "'\n");
      StringC val = list.after(0);
      if(!Lookup(val,val)) {
	cerr << "Unknown variable in for. '" << val << "'\n";
	return false;
      }
      list = val;
    }
    SubStringListC strList(list,sep);
    SubStringC subtempltxt = data.after(startTmpl);
    for(DLIterC<SubStringC> it(strList);it.IsElm();it.Next()) {
      StringC tb = subtempltxt;
      tb.gsub("%arg%",*it);
      //cerr << "For value : '" << *it << "' Res:'" << tb <<"'\n";
      TextFileC subTextBuff(tb,true,true);
      BuildSub(subTextBuff);
    }
    return true;
  }
  
  //: Check if a condition is met.
  
  bool TemplateComplexBodyC::CheckCondition(const SubStringC &ccond) {
    SubStringC &cond = const_cast<SubStringC &>(ccond);
    
    // Treat list like a set of minterms.
    
    if(cond.contains('|')) { // Any or's ?
      SubStringListC sl(cond,"|");
      for(DLIterC<SubStringC> it(sl);it.IsElm();it.Next()) {
	if(CheckCondition(it.Data()))
	  return true;
      }
      return false;
    }
    
    if(cond.contains('&')) { // And ands ?
      SubStringListC sl(cond,"&");
      for(DLIterC<SubStringC> it(sl);it.IsElm();it.Next()) {
	if(!CheckCondition(it.Data()))
	  return false;
      }
      return true;
    }
    
    // Find condition.
    
    SubStringC param1;
    SubStringC param2;
    
    IntT at = cond.index("!=");
    bool ifnot = true;
    if(at >= 0) {
      param1 = cond.before(at);
      param2 = cond.after(at+1);
    } else { // Equals ?
      at = cond.index('=');
      if(at < 0) {
	cerr << "Unrecognised condition '" << cond << "'\n";
	return false;
      }    
      param1 = cond.before(at);
      param2 = cond.after(at);
      ifnot = false;
    }
    
    // Sort out paramiters.
    
    param1=param1.TopAndTail();
    param2=param2.TopAndTail();  
    
    if(param1.length() > 0) {
      if(param1.firstchar() == '$') {
	param1 = param1.after(0);
	//ONDEBUG(cerr << "Subst param1 '" << param1  << "' -> '" << obj.Var(param1) << "'\n");
	StringC val = param1;
	if(!Lookup(val,val)) {
	  cerr << "Unknown variable in if. '" << param1 << "'\n";
	  return false;
	}
	param1 = val;
      }
    }
    
    if(param2.length() > 0) {
      if(param2.firstchar() == '$') {
	param2 = param2.after(0);
	StringC val = param2;
	//ONDEBUG(cerr << "Subst param2 '" << param2  << "' -> '" << obj.Var(param2) << "'\n");
	if(!Lookup(val,val)) {
	  cerr << "Unknown variable in if. '" << param1 << "'\n";
	  return false;
	}
	param2 = val;
      }
    }
    
    // Do test.
    
    if(!ifnot) 
      return (param1 == param2);   
    return (param1 != param2);
  }
  
  //: If true.
  
  bool TemplateComplexBodyC::DoIf(StringC &data) {
    ONDEBUG(cerr << "If '" << data << "'\n");
    
    int templStart = data.index(':');
    if(templStart < 0) {
      cerr << "Malformed 'if' in template. '" << data << "' ignoring \n";
      return false;
    }
    SubStringC condition = data.before(templStart);
    if(!CheckCondition(condition)) {
      lastIf = false;
      return true;
    }
    
    // Test passed.
    
    StringC subtempltxt = data.after(templStart);
    TextFileC subTextBuff(subtempltxt,true,true);
    BuildSub(subTextBuff);
    lastIf = true;
    return true;
  }
  
  //: If variable set
  
  bool TemplateComplexBodyC::DoIfSet(StringC &data) {
    ONDEBUG(cerr << "IfSet '" << data << "'\n");
    int templStart = data.index(':');
    if(templStart < 0) {
      cerr << "Malformed 'ifset' in template. '" << data << "' ignoring \n";
      return false;
    }
    SubStringC condition = data.before(templStart);
    StringC tmp;
    switch(condition.firstchar()) 
      {
      case 0:
	cerr << "Malformed 'ifset' in template, no condition. '" << data << "' ignoring \n";
	return false; 
      case '!': 
	{
	  StringC x = condition.after(0);
	  if(Lookup(x,tmp)) {
	    lastIf = false;
	    return true;
	  }
	  if(commands.IsElm(x)) {
	    lastIf = false;
	    return true;
	  }
	}
	break;
      default: 
	{
	  StringC x = condition;
	  if(!Lookup(x,tmp)) {
	    if(!commands.IsElm(x)) {
	      lastIf = false;
	      return true;
	    }
	  }
	}
      }
    // Test passed.
    
    StringC subtempltxt = data.after(templStart);
    TextFileC subTextBuff(subtempltxt,true,true);
    BuildSub(subTextBuff);
    lastIf = true;
    return true;
  }
  
  //: 
  
  bool TemplateComplexBodyC::DoElse(StringC &data) {
    ONDEBUG(cerr << "Else '" << data << "'\n");
    if(lastIf)
      return true;
    TextFileC subTextBuff(data,true,true);
    BuildSub(subTextBuff);  
    return true;
  }
  
  //: Include file.
  
  bool TemplateComplexBodyC::DoInclude(StringC &data) {
    ONDEBUG(cerr << "Include '" << data << "'\n");
    if(incDepth > 100) {
      cerr << "ERROR: Include depth to great, " << incDepth << " Ignoring.\n";
      return false;
    }
    data = Interpret(data);
    ONDEBUG(cerr << "Include after interpret '" << data << "'\n");
    TextFileC subTextBuff;
    TextFileC *stb = component.Lookup(data);
    if(stb == 0) {
      FilenameC fn(data);
      if(templateDir != "") {
	if(fn.firstchar() != '/') {
	  if(fn.firstchar() == '@')
	    fn = fn.after('@');
	  else
	    fn = templateDir + '/' + fn;
	}
      }
      if(!fn.Exists()) {
	cerr << "Can't find include file '" << data << "' \n";
	return false;
      }
      ONDEBUG(cerr << "Including '" << fn << "' \n");
      subTextBuff = TextFileC(fn);
      component[data] = subTextBuff;
    } else
      subTextBuff = *stb;
    incDepth++;
    BuildSub(subTextBuff);
    incDepth--;
    return true;
  }
  
  //: Make a sub context.
  
  bool TemplateComplexBodyC::DoSub(StringC &txt) {
    ONDEBUG(cerr << "Sub '" << txt << "'\n");
    
    vars.Push(RCHashC<StringC,StringC>(true) ); // Push base variables.
    TextFileC subTextBuff(txt,true,true);
    BuildSub(subTextBuff);
    vars.DelTop(); // Restore old set.
    return true;
  }
  
  //: Make a sub context, copy old context.
  
  bool TemplateComplexBodyC::DoSubCopy(StringC &txt) {
    ONDEBUG(cerr << "SubCopy '" << txt << "'\n");
    
    // Push copy of vars.
    vars.Push(RCHashC<StringC,StringC>(vars.Top().Copy()));
    TextFileC subTextBuff(txt,true,true);
    BuildSub(subTextBuff);
    vars.DelTop(); // Restore old set.  
    return true;
  }
  
  //: Substitution
  
  bool TemplateComplexBodyC::DoSubst(StringC &txt) {
    
    int arg1s = txt.index(':');
    if(arg1s < 0) {
      cerr << "Malformed 'subst' in template. '" << txt << "' ignoring \n";
      return false;
    }
    int arg2s = txt.index(':',arg1s+1);
    if(arg2s < 0) {
      cerr << "Malformed 'subst' in template. '" << txt << "' ignoring \n";
      return false;
    }
    SubStringC arg1 = txt.before(arg1s);
    SubStringC arg2 = txt.at(arg1s+1,(arg2s-arg1s)-1);
    StringC value = txt.after(arg2s);
    
    ONDEBUG(cerr << "DoSubst '" << arg1 << "' '" << arg2 << "' '" << value << "' \n");
    
    StringC resultStr = Interpret(value);
    resultStr.gsub(arg1,arg2);
    Output() << resultStr;
    return true;
  }
  
  //: 
  
  bool TemplateComplexBodyC::DoDefine(StringC &data) {
    int templStart = data.index(':');
    if(templStart < 0) {
      cerr << "Malformed 'define' in template. '" << data << "' ignoring \n";
      return false;
    }
    StringC macroNm = data.before(templStart); // Get name of macro.
    StringC macroVal = data.after(templStart); // Get string for macro.
    ONDEBUG(cerr << "DoDefine '" << macroNm << "' Val:'" << macroVal << "'\n");
    StringC empty;    
    //commands[macroNm] = CallMethod2C<TemplateComplexBodyC &,StringC &,StringC &,bool>(*this,&TemplateComplexBodyC::DoMacro,empty,macroVal);
    commands[macroNm] = TriggerR(*this,&TemplateComplexBodyC::DoMacro,empty,macroVal);
    return true;
  }
  
  //: 
  
  bool TemplateComplexBodyC::DoMacro(StringC &arg,StringC &macro) {
    ONDEBUG(cerr << "DoMacro '" << macro << "' Arg:'" << arg << "'\n");
    if(incDepth > 100) {
      cerr << "ERROR: Recurse depth to great, " << incDepth << " Ignoring.\n";
      return false;
    }
    
    StringC submacro = macro.Copy();
    submacro.gsub("%arg%",arg);
    TextFileC subTextBuff(submacro,true,true);
    incDepth++;
    BuildSub(subTextBuff);
    incDepth--;
    return true;
  }
  
  
  //: Make all text upper case.
  
  bool TemplateComplexBodyC::DoUpperCase(StringC &txt) {
    StrOStreamC outStr; 
    output.Push(outStr);
    TextFileC subTextBuff(txt,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << txt << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    Output() << upcase(outStr.String());
    return true;
  }
  
  //: Make all text lower case.
  
  bool TemplateComplexBodyC::DoLowerCase(StringC &txt) {
    StrOStreamC outStr;    
    output.Push(outStr);
    TextFileC subTextBuff(txt,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << txt << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    Output() << downcase(outStr.String());
    return true;
  }
  
  //: Make all text lower case.
  // Redirect output to /dev/null

  bool TemplateComplexBodyC::DoSilent(StringC &txt) {
    OStreamC outStr("/dev/null");
    output.Push(outStr);
    TextFileC subTextBuff(txt,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << txt << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    return true;
  }

  //: Return the first N charactors of a string.
  
  bool TemplateComplexBodyC::DoFirstN(StringC &txt) {
    int arg1s = txt.index(':');
    if(arg1s < 0) {
      cerr << "Malformed 'truncate' in template. '" << txt << "' ignoring \n";
      return false;
    }
    SubStringC arg1 = txt.before(arg1s);
    StringC value = txt.after(arg1s);
    IntT n = arg1.IntValue();
    
    StrOStreamC outStr;    
    output.Push(outStr);
    TextFileC subTextBuff(value,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << value << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    StringC outs = outStr.String(); 
    if(outs.Size() > (UIntT) n)
      Output() << outs(0,n);
    else
      Output() << outs;
    return true;
  }
  
  //: Return the first N charactors of a string, if the string is truncated indicate it with a marker.
  
  bool TemplateComplexBodyC::DoMarkFirstN(StringC &txt) {
    int arg1s = txt.index(':');
    if(arg1s < 0) {
      cerr << "Malformed 'marktruncate' in template. '" << txt << "' ignoring \n";
      return false;
    }
    int arg2s = txt.index(':',arg1s+1);
    if(arg2s < 0) {
      cerr << "Malformed 'marktruncate' in template. '" << txt << "' ignoring \n";
      return false;
    }
    SubStringC arg1 = txt.before(arg1s);
    SubStringC arg2 = txt.at(arg1s+1,(arg2s-arg1s)-1);
    StringC value = txt.after(arg2s);
    
    IntT n = arg1.IntValue();
    if(n < (IntT) arg2.Size()) {
      cerr << "WARNING: Marker larger than truncation size, expanding to marker size. '" << txt << "'. \n";
      n = arg2.Size();
    }
    StrOStreamC outStr;    
    output.Push(outStr);
    TextFileC subTextBuff(value,true,true);
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << value << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    StringC outs = outStr.String(); 
    if(outs.Size() > (UIntT) n) {
      Output() << outs(0,n-arg2.Size()) << arg2;
    } else
      Output() << outs;
    return true;
  }
  
  //: Make string suitable for use in plain html.
  
  StringC TemplateComplexBodyC::MakeHtml(const SubStringC &name) {
    cerr << "TemplateComplexBodyC::MakeHtml(SubStringC&) called, '" << name << "' \n";
    StringC ret = StringC(name);
    ret.gsub("&","&amp;");
    ret.gsub("<","&lt;");
    ret.gsub(">","&gt;");    
    return ret;
  }

  StringC TemplateComplexBodyC::MakeHtml(const StringC &str) {
    StringC ret = str.Copy();
    ret.gsub("&","&amp;");
    ret.gsub("<","&lt;");
    ret.gsub(">","&gt;");    
    return ret;
}
  
  //: Make sure text will be taken literally in html.
  
  bool TemplateComplexBodyC::HtmlSafe(StringC &value) {
    ONDEBUG(cerr << "HtmlSafe '" << value << "'\n");  
    if(value == "") 
      return true;
    
    StrOStreamC outStr;    
    output.Push(outStr);
    TextFileC subTextBuff(value,true,true);
    
    if(!BuildSub(subTextBuff))
      cerr << "WARNING: BuildSub of '" << value << "' in template '" << templFile.Filename() << "' failed. \n";
    output.DelTop();
    StringC tmp = outStr.String();
    output.Top() << MakeHtml(tmp);
    return true;
  }

  //: Return text before a string.
  
  bool TemplateComplexBodyC::DoBefore(StringC &txt) {
    int arg1s = txt.index(':');
    if(arg1s < 0) {
      cerr << "Malformed 'before' in template '" << txt << "' ignoring \n";
      return false;
    }
    SubStringC arg1 = txt.before(arg1s);
    StringC value = txt.after(arg1s);
    StringC resultStr = Interpret(value);
    if(resultStr.contains(arg1))
      Output() << resultStr.before(arg1);
    else
      Output() << resultStr;
    return true;
  }
  
  //: Return text after a string.
  
  bool TemplateComplexBodyC::DoAfter(StringC &txt) {
    int arg1s = txt.index(':');
    if(arg1s < 0) {
      cerr << "Malformed 'after' in template '" << txt << "' ignoring \n";
      return false;
    }
    SubStringC arg1 = txt.before(arg1s);
    StringC value = txt.after(arg1s);
    StringC resultStr = Interpret(value);
    if(resultStr.contains(arg1))
      Output() << resultStr.after(arg1);
    else
      Output() << resultStr;
    return true;
  }
  
  //: Lookup variable.
  // if found put value into 'buff' and return true.
  // otherwise return false.
  
  bool TemplateComplexBodyC::Lookup(const StringC &varname,StringC &buff) {
    StringC *valPtr = vars.Top().Lookup(varname);
    if(valPtr == 0)
      return false;
    buff = *valPtr;
    return true;
  }
  
  void InitCommands();
  
  //: Start build of document.
  
  bool TemplateComplexBodyC::BuildSub(TextFileC &subtempl) {
    TemplateFileC tf(subtempl ,output.Top());
    bool ret = true;
    while(tf.IsElm()) {
      StringC &ip = tf.Next();
      if(ip.IsEmpty())
	break;
      int at = ip.index(':');
      //cerr << "Value:'" << ip <<"'\n";
      if(at == -1) {
	StringC buff;
	if(Lookup(ip,buff)) {
	  ONDEBUG(cerr << "TemplateComplexBodyC::BuildSub(), Adding '" << buff << "'\n");
	  output.Top() << buff;
	  continue;
	}
	cerr << "Unknown variable: '" << ip <<"' in template '" << templFile.Filename() << "'\n";
	continue;
      }
      
      // Prefixed command.
      CallFunc1C<StringC &,bool> &com = commands[ip.before(at)];
      if(!com.IsValid()) {
	cerr << "Unknown command: '" << ip.before(at) << "' in template '" << templFile.Filename() << "' \n";
	continue;
      }
      StringC arg(ip.after(at));
      ret &= com.Call(arg);
    }
    
    //ONDEBUG(cerr << "DocumentBodyC::BuildSub(), Completed for  '" << obj.Name() << "' \n");
    return ret;
  }
  
}
