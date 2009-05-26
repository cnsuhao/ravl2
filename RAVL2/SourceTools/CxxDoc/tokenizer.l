
%Start COMMENT PREPARSER PPCOMMENT

%{

  class MyLexer : public yyFlexLexer
  {
    public:
     //  char *gettext() { return yytext; };
  };

  #include "Ravl/Stream.hh"
  #include "Ravl/CxxDoc/Object.hh"
  #include "Ravl/CxxDoc/Strings.hh"
   
  #define YYSTYPE RavlCxxDocN::ObjectC

  #include <stdlib.h>
  #include "cxx.tab.h"

#if RAVL_VISUALCPP_NAMESPACE_BUG  
  using RavlN::StringC;
#endif

  using namespace RavlN;

  namespace RavlCxxDocN {
    ObjectC hookCommentObj;
  };
  

  extern RavlCxxDocN::ObjectC yylval;
  
  RavlCxxDocN::CommentInfoC comment;
  RavlCxxDocN::CommentInfoC commentLast;
  
  inline void CommentUpdate(RavlCxxDocN::ObjectC &obj,bool setSymb = true,int alineno = 0) 
   {
     if(setSymb)
       obj = RavlCxxDocN::ObjectC(true);
     obj.StartLineno() = alineno;
     obj.EndLineno() = alineno;
     commentLast = comment;
     obj.SetComment(comment);
     comment.Reset();
  }

  inline void CommentUpdate(RavlCxxDocN::ObjectC &obj,const char *name,int alineno = 0) 
   {
     obj = RavlCxxDocN::ObjectC(name);
     obj.StartLineno() = alineno;
     obj.EndLineno() = alineno;
     commentLast = comment;
     obj.SetComment(comment);
     comment.Reset();
  }

  inline void CommentUpdate(RavlCxxDocN::ObjectC &obj,const StringC &name,int alineno = 0) 
   {
     obj = RavlCxxDocN::ObjectC(name);
     obj.StartLineno() = alineno;
     obj.EndLineno() = alineno;
     commentLast = comment;
     obj.SetComment(comment);
     comment.Reset();
  }


%}


WS           [[:blank:]\r]+
LETTER       [A-Za-z_]
DIGIT        [0-9]
NUM          {DIGIT}+
FLOAT        {DIGIT}+\.{DIGIT}*
ID           {LETTER}+({LETTER}|{DIGIT})*

SIMPLE_ESCAPE [abfnrtv'"?\\]
OCTAL_ESCAPE  [0-7]{1,3}
HEX_ESCAPE "x"[0-9a-fA-F]+

ESCAPE_SEQUENCE [\\]({SIMPLE_ESCAPE}|{OCTAL_ESCAPE}|{HEX_ESCAPE})
CCHAR [^'\\\n]|{ESCAPE_SEQUENCE}
SCHAR [^"\\\n]|{ESCAPE_SEQUENCE}

%option yylineno
%option C++ yymore
%option noyywrap

%%
    /*==============> Strip whitespace <==============*/
<INITIAL,PREPARSER>{WS}         {}

    /*==============> Special keyword <==============*/

<INITIAL>"class"         { CommentUpdate(yylval,STR(class) ,yylineno); return SCSPEC; }
<INITIAL>"struct"        { CommentUpdate(yylval,STR(struct),yylineno); return SCSPEC; }
<INITIAL>"union"         { CommentUpdate(yylval,STR(union) ,yylineno); return SCSPEC; }

<INITIAL>"public"        { CommentUpdate(yylval,STR(public)   ,yylineno); return PUBLIC;     }
<INITIAL>"protected"     { CommentUpdate(yylval,STR(protected),yylineno); return PROTECTED;  }
<INITIAL>"private"       { CommentUpdate(yylval,STR(private)  ,yylineno); return PRIVATE;    }
<INITIAL>"const"         { CommentUpdate(yylval,STR(const)    ,yylineno); return CV_QUALIFIER;  }
<INITIAL>"static"        { CommentUpdate(yylval,STR(static)    ,yylineno); return CV_QUALIFIER;  }
<INITIAL>"virtual"       { CommentUpdate(yylval,STR(virtual)  ,yylineno); return CPVIRTUAL;  }

<INITIAL>"enum"          { CommentUpdate(yylval,STR(enum)     ,yylineno); return ENUM;     }
<INITIAL>"typedef"       { CommentUpdate(yylval,STR(typedef)  ,yylineno); return CPTYPEDEF;  }
<INITIAL>"friend"        { CommentUpdate(yylval,STR(friend)   ,yylineno); return CPFRIEND;   }
<INITIAL>"operator"      { CommentUpdate(yylval,STR(operator) ,yylineno); return CPOPERATOR; }
<INITIAL>"template"      { CommentUpdate(yylval,STR(template) ,yylineno); return TEMPLATE; }
<INITIAL>"throw"         { CommentUpdate(yylval,STR(throw)    ,yylineno); return CPTHROW;    }
<INITIAL>"catch"         { CommentUpdate(yylval,STR(throw)    ,yylineno); return CPCATCH;    }
<INITIAL>"try"           { CommentUpdate(yylval,STR(throw)    ,yylineno); return CPTRY;    }
<INITIAL>"namespace"     { CommentUpdate(yylval,STR(namespace),yylineno); return NAMESPACE;  }
<INITIAL>"typename"      { CommentUpdate(yylval,STR(typename) ,yylineno); return TYPENAME_KEYWORD; }
<INITIAL>"using"         { CommentUpdate(yylval,STR(using)    ,yylineno); return USING;    }
<INITIAL>"extern"        { CommentUpdate(yylval,STR(extern)   ,yylineno); return EXTERN;   }
<INITIAL>"asm"           { CommentUpdate(yylval,STR(asm)      ,yylineno); return ASM_KEYWORD;   }

   /* ==== Cheat and pick up some compatility macro's ==== */

<INITIAL>"RAVL_THROW"         { CommentUpdate(yylval,yytext,yylineno); return CPTHROW;    }
<INITIAL>"RAVL_THROW2"        { CommentUpdate(yylval,yytext,yylineno); return CPTHROW;    }
<INITIAL>"RAVL_THROW3"        { CommentUpdate(yylval,yytext,yylineno); return CPTHROW;    }


    /*==============> Ignored stuff <==============*/
<INITIAL>"Q_EXPORT"       {}
<INITIAL>"Q_EXPORTH"      {}
<INITIAL>"__BEGIN_DECLS"  {}
<INITIAL>"__END_DECLS"    {}
<INITIAL>"inline"         {}
<INITIAL>"mutable"        {}
<INITIAL>"MyInline"       {} /* Temp fix until eliminated. */
<INITIAL>"volatile"       {}
<INITIAL>"afx_msg"        {}


    /*==============> Normal operators <==============*/
<INITIAL>":"          { CommentUpdate(yylval,RavlCxxDocN::strp_Colon     ,yylineno); return ':';}
<INITIAL>"::"         { CommentUpdate(yylval,RavlCxxDocN::strp_ColonColon,yylineno); return CLCL;}
<INITIAL>"~"          { CommentUpdate(yylval,RavlCxxDocN::strp_Tilda     ,yylineno); return '~'; }
<INITIAL>"="          { return '='; }
<INITIAL>"<"          { return '<'; }
<INITIAL>">"          { return '>'; }
<INITIAL>"&"          { return '&'; }
<INITIAL>"+"          { return '+'; }
<INITIAL>"-"          { return '-'; }
<INITIAL>"*"          { return '*'; }
<INITIAL>"/"          { return '/'; }
<INITIAL>"%"          { return '%'; }
<INITIAL>"|"          { return '|'; }
<INITIAL>"^"          { return '^'; }
<INITIAL>"!"          { return '!'; }
<INITIAL>"<<"         { yylval = StringC(yytext); return BINOP; }
<INITIAL>">>"         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"->"         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"->*"        { yylval = StringC(yytext); return BINOP; }
<INITIAL>"+="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"-="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"*="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"&="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"|="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"/="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"<="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>">="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>">>="        { yylval = StringC(yytext); return BINOP; }
<INITIAL>"<<="        { yylval = StringC(yytext); return BINOP; }
<INITIAL>"%="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"&&"         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"||"         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"=="         { yylval = StringC(yytext); return BINOP; }
<INITIAL>"!="         { yylval = StringC(yytext); return BINOP; }

    /*==============> End of Phrase <==============*/
<INITIAL>";"          { CommentUpdate(yylval,true,yylineno);  return ';'; }

    /*==============> Comma <==============*/
<INITIAL>","          { return ','; }

    /*==============> Paranthesis <==============*/
<INITIAL>"("          { return '('; }
<INITIAL>")"          { return ')'; }

    /*==============> Brackets <==============*/
<INITIAL>"{"          { CommentUpdate(yylval,true,yylineno); return '{'; }
<INITIAL>"}"          { CommentUpdate(yylval,true,yylineno); return '}'; }
<INITIAL>"["          { return '['; }
<INITIAL>"]"          { return ']'; }

<INITIAL>"unsigned"   { CommentUpdate(yylval,STR(unsigned),yylineno); return TYPEQUAL; }
<INITIAL>"signed"     { CommentUpdate(yylval,STR(signed)  ,yylineno); return TYPEQUAL; }
<INITIAL>"long"       { CommentUpdate(yylval,STR(long)    ,yylineno); return TYPEQUAL; }
<INITIAL>"short"      { CommentUpdate(yylval,STR(short)   ,yylineno); return TYPEQUAL; }
<INITIAL>"int"        { CommentUpdate(yylval,STR(int)     ,yylineno); return BUILTIN; }
<INITIAL>"float"      { CommentUpdate(yylval,STR(float)   ,yylineno); return BUILTIN; }
<INITIAL>"double"     { CommentUpdate(yylval,STR(double)  ,yylineno); return BUILTIN; }
<INITIAL>"char"       { CommentUpdate(yylval,STR(char)    ,yylineno); return BUILTIN; }
<INITIAL>"bool"       { CommentUpdate(yylval,STR(bool)    ,yylineno); return BUILTIN; }
<INITIAL>"void"       { CommentUpdate(yylval,STR(void)    ,yylineno); return BUILTIN; }

    /*==============> Identifiers <==============*/
<INITIAL>{ID}         { CommentUpdate(yylval,yytext,yylineno);
                        return IDENTIFIER; 
                      }

    /*==============> Numbers <==============*/

<INITIAL>{NUM}           { yylval = StringC(yytext); return CONSTANT; }
<INITIAL>{FLOAT}         { yylval = StringC(yytext); return CONSTANT; }
<INITIAL>{FLOAT}"e-"{NUM} { yylval = StringC(yytext); return CONSTANT; }
<INITIAL>{FLOAT}"e"{NUM} { yylval = StringC(yytext); return CONSTANT; }

<INITIAL>"L"?[']{CCHAR}+[']   { yylval = StringC(yytext); return CONSTANT; }
<INITIAL>"L"?["]{SCHAR}*["]   { yylval = StringC(yytext); return STRING;   }
<INITIAL>"..."                { return ELLIPSIS; }

    /*==============> Strip // comments <==============*/

<INITIAL>"//:-"(.)*[\n<<EOF>>] { CommentUpdate(yylval,&yytext[4],yylineno); 
				 return DOCSECTION; 
                               }
<INITIAL>"//:"(.)*[\n<<EOF>>] { StringC txt(&(yytext[3]));
                                txt.gsub("\n"," ");
                                if(!comment.Text().IsEmpty()) {
                                  comment.Text() = StringC();
                                  comment.Header() = StringC();
                                }
				if(comment.StartLine() < 0)
				  comment.SetStartLine(yylineno-1);
                                comment.Header() += txt;
				comment.SetEndLine(yylineno-1);
                              }
<INITIAL>"//!"(.)*[\n<<EOF>>] { StringC txt(&(yytext[3]));
                                if(txt.length() > 0) {
				  if(comment.StartLine() < 0)
				    comment.SetStartLine(yylineno-1);
                                  comment.SetEndLine(yylineno-1);
                                  switch(txt.firstchar()) {
                                  case ' ': {
                                    int at = txt.index('=');
                                    if(at < 0)
                                      break;
                                    StringC varNm = txt.before(at).TopAndTail();
                                    StringC value = txt.after(at).TopAndTail();
                                    value.gsub("\"","");// Now get rid of quotes.
                                    comment.SetVar(varNm,value);
                                    //cout << "Setting var '" << varNm << "' to '" << value << "'\n"; 
                                    break;
                                    }
                                  default: {
                                    int atc = txt.index(':');
                                    if(atc < 0) {
                                      // Error message ?
                                      break;
                                    }
                                    StringC lvarname = txt.before(atc).TopAndTail();
                                    comment.Locals()[lvarname] += txt.after(atc);
                                    //cout << "Setting local var '" << lvarname << "' to '" << comment.Locals()[lvarname] << "'\n"; 
                                    break ;
                                    }
                                  }
                                }
                              }
<INITIAL>"//"(.)*[\n<<EOF>>]  { comment.Text() += &yytext[2]; 
				if(comment.StartLine() < 0)
				  comment.SetStartLine(yylineno-1);
                                comment.SetEndLine(yylineno-1);
			      }

    /*==============> Skip preprocessor directives <==============*/
<INITIAL>"#"[acdeimpsuwl ] { BEGIN (PREPARSER); }
<PREPARSER>"/*"		   { BEGIN (PPCOMMENT); }
<PPCOMMENT>"*/"            { BEGIN (PREPARSER); }
<PREPARSER>"\\\n"	   {}
<PREPARSER>.	           {}
<PREPARSER>"\n"	           { BEGIN (INITIAL); }


    /*==============> Strip comments <==============*/
<INITIAL>"/*"        { BEGIN (COMMENT);}
<COMMENT>"*/"        { BEGIN (INITIAL); }

<COMMENT,PPCOMMENT>[\n\r]  {}
<COMMENT,PPCOMMENT>.       {}

    /*==============> All other characters are ignored <==============*/
<INITIAL>[\n]  	{}
<INITIAL>.  		{}

%%
