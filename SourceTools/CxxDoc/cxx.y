/* Hacked C++ parser. */
%{
#include "Ravl/Stream.hh"
#include "Ravl/CxxDoc/CxxElements.hh"
#include "Ravl/CxxDoc/DocNode.hh"
#include "Ravl/CxxDoc/Strings.hh"

#include <stdlib.h>

#ifndef NDEBUG
#define YYDEBUG 1
#endif
  
#define YYSTYPE ObjectC 
  
  namespace RavlCxxDocN {
    extern ObjectC hookCommentObj;
    extern ObjectListC results;

  }
  
  using namespace RavlN;
  using namespace RavlCxxDocN;
  
  extern int yyerror(const char *str);
  extern int yylex();

  static int anonCount = 1;

%}

%start program

%token IDENTIFIER            /* Identifier. */

%token CLCL          /* :: */
%token PUBLIC        /* "public" */
%token PROTECTED     /* "protected" */
%token PRIVATE       /* "private" */
%token NAMESPACE     /* "namespace" */
%token STRING        /* "string" */
%token CONSTANT      /* "string" */
%token CPVIRTUAL     /* "virtual" */
%token ENUM        /* "enum" */
%token CPTYPEDEF     /* "typedef" */
%token CPFRIEND      /* "friend" */
%token CPOPERATOR    /* "operator" */
%token TEMPLATE      /* "template" */
%token CPTHROW       /* "throw" */
%token CPTRY         /* "throw" */
%token CPCATCH       /* "throw" */
%token SCSPEC        /* "class" "struct" "union" */
%token TYPENAME_KEYWORD  /* "typename" */
%token USING       /* "throw" */
%token EXTERN        /* "extern" */
%token ELLIPSIS      /* "extern" */
%token ASM_KEYWORD   /* "asm" */
%token CV_QUALIFIER        /* "extern" */
%token TYPEQUAL        /* "unsigned" or "long" or "signed"*/
%token BINOP        /* "<<" ">>" "&&" */
%token BUILTIN
%token DOCSECTION    /* Special symbol for creating  sections within scopes */

/* Some bits and pieces from gcc... maybe the'll help.*/

%nonassoc CPTHROW
%left IDENTIFIER SCSPEC CV_QUALIFIER ENUM ELLIPSIS CPOPERATOR TYPENAME_KEYWORD
%left error
%left '{' ',' ';'
%right ':'
%right '='
%left BINOP
%right  '~'
%left  '(' '['


%%

program: extdefs_opt  { results = $1; }
	;

/* --------------- Handle namespaces ------------------------ */

extdefs: extdef               { ScopeC ol(STR(extdefs)); $$=ol; ol.Append($1);  }
	| extdefs extdef      { ObjectListC ol($1); $$=$1; ol.Append($2);  }
	;

extdefs_opt: /* empty */ { ScopeC ol(STR(extdefs)); $$=ol; }
        | extdefs        { $$=$1; }
	;

extdef:   fndef            { $$=$1; }
        | datadef          { $$=$1; }
        | template_def     { $$=$1; }
        | ASM_KEYWORD '(' string ')' ';' { $$=ObjectC(); }  /* Ignore it.*/
        | NAMESPACE maybe_identifier '{' extdefs_opt '}' { 
                                                           StringC name;
                                                           if($2.IsValid())
                                                             name = $2.Name();
                                                           $$=ScopeC(name,$4); 
							   $$.UpdateComment($1.Comment());
    	                                                   $$.SetVar(STR(dectype),STR(definition));
                                                           $$.SetVar(STR(storageType),STR(namespace));
	                                                 }
	| namespace_alias  { $$=ObjectC(); }  /* Ignore it.*/
	| using_decl ';'   { $$=ObjectC(); }  /* Ignore it.*/
	| using_directive  { $$=$1; }  
	| error ';'        { $$=ObjectC(); }  /* Ignore it.*/
        | error '{' func_body_contents_list '}' { $$=ObjectC(); }  /* try and keep '{' '}' balance. */
        | ';'              { $$=ObjectC(); }  /* Ignore it.*/
        | DOCSECTION       { 
	                     $$=DocNodeC(StringC("anon?") + StringC(anonCount++)); 
          		     hookCommentObj = $$;
                           } /* Mark a section. */
;

datadef:
     type_id var_name_list ';'                   { ObjectListC ol($2);
						   ObjectListC ret(STR(varList),true);
						   for(DLIterC<ObjectC> it(ol.List());it.IsElm();it.Next()) {
						     VariableC avar($1,it.Data().Name());
						     ret.Append(avar);
						   }
          				           hookCommentObj = ret; 
                                                   $$.SetupLineNos($1,$3);
						   $$=ret;
                                                 }
   | CPTYPEDEF type_id IDENTIFIER ';'            { $$=TypedefC($3.Name(),$2);
                                                   $$.SetupLineNos($1,$4);
          				           hookCommentObj = $$; 
                                                 }

   | CPTYPEDEF type_id IDENTIFIER '[' expr_no_commas ']' ';' { $2.SetVar(STR(array),STR(1)); 
                                                               $$=TypedefC($3.Name(),$2); 
          				                       hookCommentObj = $$; 
                                                               $$.SetupLineNos($1,$7);
                                                             }
   | CPTYPEDEF function_ptr_def ';'                          { DataTypeC dt($2);
                                                               $$=TypedefC(dt.Alias(),dt);
                                                               $$.SetupLineNos($1,$3);
          				                       hookCommentObj = $$; 
                                                             } 
   | CPTYPEDEF SCSPEC maybe_identifier class_inherit_list_all '{' extdefs_opt '}' IDENTIFIER ';' 
                                                             { 
							       StringC className;
							       if($3.IsValid())
								 className = $3.Name();
							       else 
								 className = StringC("anon?") + StringC(anonCount++);
							       ClassC aclass(className,$6,$4);
                                                               aclass.SetVar(STR(dectype),STR(definition));
                                                               aclass.SetVar(STR(storageType),$2.Name());
							       TypedefC td($7.Name(),DataTypeC(className));
							       td.SetDefinition(aclass);
							       ObjectListC ret(STR(x),true);
							       ret.Append(td);
							       if($3.IsValid())
								 ret.Append(aclass);
                                                               $$.SetupLineNos($1,$9);
							       $$ = ret;
          				                       hookCommentObj = $$;
							     }
   | function_ptr_def ';'                       { $$=ObjectC(); }
   | CPTYPEDEF ENUM maybe_identifier '{' enum_name_list_opt '}' IDENTIFIER ';' { 
							       StringC enumName;
							       if($3.IsValid())
								 enumName = $3.Name();
							       else 
								 enumName = StringC("anon_enum?") + StringC(anonCount++);
                                                               EnumC anEnum(enumName,$5);
                                                               anEnum.SetVar(STR(dectype),STR(definition));
                                                               anEnum.SetVar(STR(storageType),STR(enum));
							       TypedefC td($7.Name(),DataTypeC(enumName));
							       td.SetDefinition(anEnum);
							       ObjectListC ret("x",true);
							       ret.Append(td);
							       if($3.IsValid())
								 ret.Append(anEnum);
                                                               $$.SetupLineNos($1,$8);
							       $$ = ret;
          				                       hookCommentObj = $$;
                                                             }
   | ENUM maybe_identifier '{' enum_name_list_opt '}' var_name_list_opt ';' {
                                                  if($2.IsValid())
						    $$=EnumC($2.Name(),$4);
						  else
						    $$=EnumC(StringC("anon_enum?") + StringC(anonCount++),$4);
						  hookCommentObj = $$;
                                                }
   | SCSPEC IDENTIFIER ';'                      { $$=ClassC($2.Name());
						  $$.UpdateComment($1.Comment()); 
						  $$.SetVar(STR(storageType),$1.Name());
                                                  $$.SetVar(STR(dectype),STR(forward));
                                                }
   | ENUM IDENTIFIER ';'                        { $$=EnumC($2.Name());
						  $$.UpdateComment($1.Comment()); 
						  $$.SetVar(STR(storageType),STR(enum));
                                                  $$.SetVar(STR(dectype),STR(forward));
                                                }
   | CPFRIEND type_id ';'                       { $$=$2; 
                                                  $$.SetVar(STR(dectype),STR(friend));  
                                                }
   | SCSPEC IDENTIFIER class_inherit_list_all  '{' class_lst '}' var_name_list_opt ';' 
                                                { 
						  ClassC newClass($2.Name(),$5,$3);
						  $$ = newClass;
						  $$.UpdateComment($1.Comment()); 
						  $$.SetupLineNos($1,$8);
						  newClass.SetVar(STR(dectype),STR(definition));
						  newClass.SetVar(STR(storageType),$1.Name());
						}
   | CV_QUALIFIER SCSPEC maybe_identifier class_inherit_list_all  '{' class_lst '}' var_name_list_opt ';' {
                                                  StringC nname;
						  if($3.IsValid())
						    nname = $3.Name();
						  else
						    nname = StringC("anon_struct?") + StringC(anonCount++);
						  ClassC newClass(nname,$6,$4);
						  $$ = newClass;
						  $$.UpdateComment($1.Comment()); 
						  $$.SetupLineNos($1,$8);
						  newClass.SetVar(STR(dectype),STR(definition));
						  newClass.SetVar(STR(storageType),$2.Name());
                                                }
   | EXTERN type_id var_name_list ';'           { $$=ObjectC(); }
   | EXTERN STRING '{' extdefs_opt '}'          { $$ = $4; ObjectListC ol($4); ol.SetWrapper(true); }
   | scope_resolved_id ';'                      { $$=ObjectC(); }   /* Scope change. */
;
/* ----- Enum args ---- */

enum_name_list_opt: { ObjectListC ol(STR(EnumNameList)); $$=ol; }
   |  enum_name_list { $$=$1}
;
enum_name_list: enum_name_elem { ObjectListC ol(STR(VarNameList)); ol.Append($1); $$ = ol;  }
   | enum_name_list ',' enum_name_elem { ObjectListC ol($1); ol.Append($3); $$ = ol; }
;
enum_name_elem: IDENTIFIER { $$=$1; }
   | IDENTIFIER '=' expr_no_commas_list { $$ = $1.Name() +  StringC(" = ") + $3.Name(); }
;

/* ----- misc ---- */

string:                 /* Strings may be chained.... */
	  STRING
       | string STRING 
	;

/* ------ identifiers ----- */

unqualified_id: IDENTIFIER   { $$=$1; } 
        ;

qualified_id: scope_id CLCL unqualified_id { $$ = $1.Name() + strp_ColonColon + $3.Name(); }
        | scope_id CLCL qualified_id       { $$ = $1.Name() + strp_ColonColon + $3.Name(); }
;

maybe_identifier: IDENTIFIER  { $$=$1; }
	| /* empty */         { $$=ObjectC(); }
        ;

any_id:   
 	  unqualified_id      { $$ = $1; }
	| qualified_id        { $$ = $1; }
	| CLCL qualified_id   { $$=ObjectC(strp_ColonColon + $2.Name()); } 
        | CLCL unqualified_id { $$=ObjectC(strp_ColonColon + $2.Name()); } 
        ;

/* ----- Scope id -----.  */

scope_id: IDENTIFIER                             { $$=$1; }
     | '~' IDENTIFIER                            { $$ = ObjectC(StringC("~") + $2.Name()); $$.CopyLineNo($2); }
     | IDENTIFIER '<' template_inst_args_opt '>'     { $$ = ObjectTemplateC($1.Name(),$3); }

/*     | '~' IDENTIFIER '<' template_inst_args '>' { $$ = ObjectC(StringC("~") + $2.Name() + StringC("<") + $4.Name() + ">"); } */
;
scope_resolved_id: scope_id          { ObjectListC ol($1.Name()); ol.Append($1); $$=ol; $$.CopyLineNo($1); }
   | CLCL scope_id                   { ObjectListC ol($2.Name()); 
                                       ObjectC newun(strp_ColonColon);
                                       ol.Append(newun);
				       ol.Append($2);
				       $$ = ol;
                                     }
   | scope_resolved_id CLCL scope_id { ObjectListC ol($1); 
				       ol.Append($3);
				       ol.Name() = $3.Name();  // Give name of last component to list.
				       $$ = ol;
                                     }
   ;

/* ----- namespace ----- */

namespace_alias:
          NAMESPACE IDENTIFIER '=' any_id ';'
	;

using_directive:
	  USING NAMESPACE any_id ';' {
	    InheritC inh(SAPublic,true);
	    inh.SetScopeDef($3);  
	    $$ = inh;
	  }
	;

using_decl:
	  USING qualified_id
	| USING CLCL qualified_id
	| USING CLCL unqualified_id
	;

/* ========================= Template ===================== */


/* ------ template types ------ */

template_def:
     template_header SCSPEC IDENTIFIER class_inherit_list_all  '{' class_lst '}' ';' 
                                                { $$ =  ClassTemplateC($3.Name(),$6,$4,$1);
						  $$.SetVar(STR(dectype),STR(definition));
						  $$.SetVar(STR(storageType),$2.Name());
						  $$.UpdateComment($1.Comment());
						}
   | template_header SCSPEC IDENTIFIER ';'        { $$ = ClassTemplateC($3.Name(),$1); 
						    $$.SetVar(STR(dectype),STR(forward));
						    $$.SetVar(STR(storageType),$2.Name());
						    $$.UpdateComment($1.Comment());
                                                  }
   | template_header fndef                        { $$ = $2;
                                                    ObjectListC ol1($1);
						    $$.UpdateComment($1.Comment());
                                                  }
   | template_header template_header fndef        { $$ = $3;
                                                    ObjectListC ol1($1);
                                                    ObjectListC ol2($2);
						    $$.UpdateComment($1.Comment());
                                                  }
   ;


/* ------ template definitions ------ */

template_inst_args_opt: /*empty*/ { $$=ObjectListC(STR(TemplateInstArgs)); }
     | template_inst_args { $$=$1; }
;

template_inst_args: type_id { ObjectListC ol(STR(TemplateInstArgs)); $$=ol; ol.Append($1); }
    | CONSTANT { ObjectListC ol(STR(TemplateInstArgs)); $$=ol; ol.Append($1); }
    | template_inst_args ',' type_id { ObjectListC ol($1); $$=$1; ol.Append($3); }
    | template_inst_args ',' CONSTANT { ObjectListC ol($1); $$=$1; ol.Append($3); }
;

template_header:
          TEMPLATE '<' template_parm_list '>'  { $$=$3; $$.UpdateComment($1.Comment()); } 
	| TEMPLATE '<' '>'                     { $$=ObjectListC(STR(TemplateDefArgs)); $$.UpdateComment($1.Comment()); }
	;

template_parm_list: template_parm               { ObjectListC ol(STR(TemplateDefArgs)); $$=ol; ol.Append($1); }
        | template_parm_list ',' template_parm  { $$=$1; ObjectListC ol($1); ol.Append($3); }
	;

parm: type_id maybe_identifier      { $$=$1; 
                                      if($2.IsValid()) { 
                                        DataTypeC dt($1); 
					dt.SetAlias($2.Name()); 
                                      } 
                                    }
        ;

template_type_parm:
          SCSPEC maybe_identifier           { $$= DataTypeC(STR(class),$2); }
	| TYPENAME_KEYWORD any_id { $$= DataTypeC(STR(typename),$2);  }
        | type_id '(' maybe_identifier ')' '(' func_arg_list_all ')' func_qualifier { $$= DataTypeC($1.Name() + " (" + $3.Name() + ")(" + $6.Name() + ")" + $7.Name(),$3); }
	;

template_template_parm: /* FIXME:- This isn't really handled properly. */
	  template_header SCSPEC maybe_identifier { $$=ObjectC("template<> class " + $1.Name()); }
	;

template_parm:
	/* The following rules introduce a new reduce/reduce
	   conflict on the ',' and '>' input tokens: they are valid
	   prefixes for a `structsp', which means they could match a
	   nameless parameter.  See 14.6, paragraph 3.
	   By putting them before the `parm' rule, we get
	   their match before considering them nameless parameter
	   declarations.  */
	  template_type_parm               { $$=$1; } 
        | template_type_parm '=' type_id   { $$=$1; } 
	| parm                             { $$=$1; } 
	| parm '=' expr_no_commas          { $$=$1; } 
	| template_template_parm           { $$=$1; } 
        | template_template_parm '=' type_id { $$=$1; }  /*  was "'=' template_arg", which is probably wrong too! */
	;

/*
template_arg: template_arg_item              { $$=$1; } 
       | template_arg template_arg_item      { $$=$1; $$.Name() += StringC(" ") + $2.Name(); }
;
template_arg_item: IDENTIFIER | CONSTANT |  CV_QUALIFIER | BUILTIN | STRING | SCSPEC
;
*/

/* --------------- Handle class definitions ------------------------ */

class_inherit_list_all: /*empty*/ { $$=ObjectListC(STR(classInherit)); }
   | ':' class_inherit_list { $$=$2; }
;
class_inherit_list:   
     class_inherit_list ',' class_inherit_def   { $$ = $1; ObjectListC ol($1); ol.Append($3);  }
   | class_inherit_def { ObjectListC ol(STR(classInherit),true); ol.Append($1); $$ = ol; }
;
class_inherit_mode:  PUBLIC          { $$ = InheritC(SAPublic);    $$.CopyLineNo($1); }
   | PRIVATE         { $$ = InheritC(SAPrivate);   $$.CopyLineNo($1); }
   | PROTECTED       { $$ = InheritC(SAProtected); $$.CopyLineNo($1); }
;
class_inherit_def: class_inherit_mode scope_resolved_id { $$ = $1;
							  InheritC inh($$);
							  inh.SetScopeDef($2);
							}
   | CPVIRTUAL  class_inherit_mode scope_resolved_id    { $$ = $2;
                                                          InheritC inh($$);
							  inh.SetScopeDef($3);
							  inh.SetVirtual(true);
							}
   | class_inherit_mode CPVIRTUAL  scope_resolved_id    { $$ = $1;
                                                          InheritC inh($$);
							  inh.SetScopeDef($3);
							  inh.SetVirtual(true);
							}
   | scope_resolved_id                                  { $$ = InheritC(SAPrivate);
                                                          InheritC inh($$);
							  inh.SetScopeDef($1);
							}
;

class_lst: /* empty */ { $$ = ObjectListC(STR(ClassContents)); }
   | class_lst class_def { ObjectListC ol($1); ol.Append($2); $$ = ol; }
;
class_def: PROTECTED ':'     { $$ = MarkerC(STR(protected)); $$.SetupLineNos($1,$2); }
   | PRIVATE ':'             { $$ = MarkerC(STR(private));   $$.SetupLineNos($1,$2); }
   | PUBLIC ':'              { $$ = MarkerC(STR(public));    $$.SetupLineNos($1,$2); }
   | extdef                  { $$=$1; }
   | CPVIRTUAL fndef         { $$=$2; $$.SetVar(STR(virtual),STR(1)); $$.IncludeLineNo($1) }
   /* | func_destructor_inclass */
   /*   | func_constructor_inclass */
;
expr_no_commas_list_opt: /*empty*/ { $$=ObjectC(""); }
  | expr_no_commas_list            { $$=$1; }
;
expr_no_commas_list: expr_no_commas    { $$=$1; }
  |   expr_no_commas_list expr_no_commas  { $$ = $1.Name() + ' ' +  $2.Name(); }
;
expr_no_commas: '(' arg_expr_list_all ')' { $$=ObjectC(strp_OpenBracket + $2.Name() + strp_CloseBracket); }
   | '[' expr_no_commas_list ']'          { $$=ObjectC(StringC("[") + $2.Name() + "]"); }
   | '{' expr_no_commas_list '}'          { $$=ObjectC(StringC("{") + $2.Name() + "}"); }
   | IDENTIFIER | CONSTANT|  CV_QUALIFIER | BUILTIN | STRING | BINOP
   | '<' { $$=ObjectC("<"); }
   | '>' { $$=ObjectC(">"); }
   | '=' { $$=ObjectC(strp_equals); }
   | '+' { $$=ObjectC(strp_plus); }
   | '-' { $$=ObjectC("-"); }
   | '~' { $$=ObjectC("~"); }
   | '&' { $$=ObjectC(strp_ampersand); }
   | '/' { $$=ObjectC("/"); }
   | '*' { $$=ObjectC(strp_asterisk); }
   | '%' { $$=ObjectC("%"); }
   | '|' { $$=ObjectC("|"); }
   | '^' { $$=ObjectC("^"); }
   | '!' { $$=ObjectC("!"); }
   | ':' { $$=$1; }
   | CLCL       { $$=$1; }
   | CPVIRTUAL  { $$=$1; }
   | ENUM       { $$=$1; }
   | CPTYPEDEF  { $$=$1; }
   | CPFRIEND   { $$=$1; }
   | CPOPERATOR { $$=$1; }
   | TEMPLATE   { $$=$1; }
   | CPTHROW    { $$=$1; }
   | TYPENAME_KEYWORD { $$=$1; }
   | USING      { $$=$1; }
;

/* --------------- Handle list of variable names ------------------------ */
type_id: type_id_bod                        { $$=$1; }
   | CV_QUALIFIER type_id_bod               { $$=$2; DataTypeC dt($2); dt.SetPreQual($1.Name()); }
   | CV_QUALIFIER CV_QUALIFIER type_id_bod  { $$=$3; DataTypeC dt($3); dt.SetPreQual($1.Name() + " " + $2.Name()); }
   | CV_QUALIFIER CV_QUALIFIER CV_QUALIFIER type_id_bod  { $$=$4; DataTypeC dt($4); dt.SetPreQual($1.Name() + " " + $2.Name() + " " + $3.Name()); }
   ;

type_id_bod:  scope_resolved_id type_id_qual     { $$=DataTypeC(StringC(""),$1,$2.Name()); 
	                                           $$.SetupLineNos($1,$2); 
                                                 }
        | SCSPEC scope_resolved_id type_id_qual  { $$=DataTypeC($1.Name(),$2,$3.Name()); 
	                                           $$.SetVar(STR(storageType),$1.Name());
	                                           $$.SetupLineNos($1,$2,$3); 
	                                         }
        | ENUM scope_resolved_id type_id_qual    { $$=DataTypeC($1.Name(),$2,$3.Name()); 
	                                           $$.SetVar(STR(storageType),$1.Name());
	                                           $$.SetupLineNos($1,$2,$3); 
	                                         }
        | BUILTIN type_id_qual                   { $$=DataTypeC(StringC(""),$1,$2.Name()); 
	                                           $$.SetupLineNos($1,$2);
	                                         }
        | TYPEQUAL type_id_qual                  { $$=DataTypeC(StringC(""),$1, $2.Name()); 
                                                   $$.SetupLineNos($1,$2); 
                                                 }
        | TYPEQUAL BUILTIN type_id_qual          { $$=DataTypeC($1.Name(),$2,$3.Name()); 
	                                           $$.SetupLineNos($1,$2,$3); 
	                                         }
        | TYPEQUAL TYPEQUAL type_id_qual         { $$=DataTypeC($1.Name(),$2,$3.Name()); 
	                                           $$.SetupLineNos($1,$2,$3); 
	                                         }
        | TYPEQUAL TYPEQUAL BUILTIN type_id_qual { $$=DataTypeC($1.Name() + " " + $2.Name(),$3,$4.Name()); 
	                                           $$.SetupLineNos($1,$3,$4); 
	                                         }
        | TYPEQUAL TYPEQUAL TYPEQUAL type_id_qual { $$=DataTypeC($1.Name() + " " + $2.Name(),$3,$4.Name()); 
	                                           $$.SetupLineNos($1,$3,$4);
	                                         }
	| TYPENAME_KEYWORD any_id type_id_qual { $$= DataTypeC(STR(typename),$2,$3.Name());  
	                                           $$.SetupLineNos($1,$2,$3);
	                                         }
        ;

var_name_list_opt: /*empty*/ { $$=ObjectListC(STR(VarNameList)); }
          | var_name_list    { $$=$1; }
;
var_name_list: var_name_elem                { ObjectListC ol(STR(VarNameList)); ol.Append($1); $$ = ol; }
          | var_name_list ',' var_name_elem { ObjectListC ol($1); ol.Append($3); $$ = ol; }
;
var_name_array: '[' expr_no_commas_list_opt ']'            { $$=ObjectC("[]"); }
          | var_name_array '[' expr_no_commas_list_opt ']' { $$=$1; $1.Name() += "[]" }
;
var_name_elem: IDENTIFIER                              { $$=$1; }
          | IDENTIFIER '=' expr_no_commas_list         { $$=$1; $1.Name() += StringC(" = ") + $3.Name(); }
          | IDENTIFIER var_name_array { $$=$1; $1.Name() += $2.Name(); $$.SetVar(STR(array),STR(1)); }
          | IDENTIFIER var_name_array '=' '{' func_body_contents_list '}' 
                                                       { $$=$1; $1.Name() += $2.Name(); $$.SetVar(STR(array),STR(1)); }
          | '=' expr_no_commas_list         { $$=$2; $2.Name() = StringC(" = ") + $2.Name(); }
;
type_id_qual: /*empty*/             { $$=ObjectC(""); }
	  | type_id_qual '*'        { $$=$1; $$.Name() += strp_asterisk;  }
	  | type_id_qual '&'        { $$=$1; $$.Name() += strp_ampersand;  }
	  | type_id_qual CV_QUALIFIER { $$=$1; $$.Name() += $2.Name();  }
;
/* --------------- Special Functions/Methods -------------------------------- */

base_class_constructors_list: constructor_expr
  | base_class_constructors_list ',' constructor_expr
;
constructor_expr: IDENTIFIER '(' arg_expr_list_all ')'
   | IDENTIFIER '<' template_inst_args_opt '>' '(' arg_expr_list_all ')'
;
arg_expr_list_all: /*empty*/ { $$ =ObjectC(""); }
   | arg_expr_list        { $$ = $1; }
;
arg_expr_list: arg_expr_list_item { $$=$1; }
   | arg_expr_list arg_expr_list_item { $1 = $1.Name() + $2.Name(); }
;
arg_expr_list_item:  '(' arg_expr_list_all ')' { $$=ObjectC(strp_OpenBracket + $2.Name() + strp_CloseBracket); }
   | IDENTIFIER | CONSTANT | BINOP
   | CLCL  | PUBLIC | PROTECTED | PRIVATE | NAMESPACE | CV_QUALIFIER 
   |  STRING | CPVIRTUAL | ENUM | CPTYPEDEF | BUILTIN 
   | CPFRIEND | CPOPERATOR | TEMPLATE | CPTHROW | TYPENAME_KEYWORD | USING    
   | ':' { $$=ObjectC(strp_Colon); }
   | '<' { $$=ObjectC("<"); }
   | '>' { $$=ObjectC(">"); }
   | '=' { $$=ObjectC(strp_equals); }
   | '+' { $$=ObjectC(strp_plus); }
   | '-' { $$=ObjectC("-"); }
   | '~' { $$=ObjectC(strp_Tilda); }
   | '&' { $$=ObjectC(strp_ampersand); }
   | '/' { $$=ObjectC("/"); }
   | '*' { $$=ObjectC(strp_asterisk); }
   | '%' { $$=ObjectC("%"); }
   | '|' { $$=ObjectC("|"); }
   | '^' { $$=ObjectC("^"); }
   | '!' { $$=ObjectC("!"); }
   | '[' { $$=ObjectC("["); }
   | ']' { $$=ObjectC("]"); }
   | ';' { $$=ObjectC(strp_Semicolon); }
   | ',' { $$=ObjectC(strp_Comma); }
;

/* --------------- Functions/Methods -------------------------------- */

fndef: func_def                         { $$=$1; hookCommentObj = $1;  }
     | func_decl                        { $$=$1; hookCommentObj = $1;  }
     | CPFRIEND func_decl               { $$=$2; 
                                          $$.SetVar(STR(dectype),STR(friend));
					  $$.IncludeLineNo($1);
					  hookCommentObj = $2;
                                        }
;
func_decl: func_prototype ';'           { $$ = $1; 
                                          $$.SetVar(STR(dectype),STR(prototype)); 
					  $$.IncludeLineNo($2);
                                        }
     | func_prototype '=' CONSTANT ';'  { $$=$1;   /* "=0"; */
                                          $$.SetVar(STR(dectype),STR(abstract));
					  $$.IncludeLineNo($4);
                                        }
     | EXTERN func_prototype ';'        { $$=$2; 
                                          $$.SetVar(STR(dectype),STR(extern));    
					  $$.IncludeLineNo($3);
                                        }
;
func_def:
       func_prototype func_body_opt_constr { $$ = $1;
                                             $$.SetVar(STR(dectype),STR(definition)); 
					     $$.IncludeLineNo($2);
                                           }
;
operator_types: '+' { $$=ObjectC(strp_plus); }
       | '-' { $$=ObjectC("-"); }
       | '~' { $$=ObjectC(strp_Tilda); }
       | '&' { $$=ObjectC(strp_ampersand); }
       | '/' { $$=ObjectC("/"); }
       | '*' { $$=ObjectC(strp_asterisk); }
       | '%' { $$=ObjectC("%"); }
       | '|' { $$=ObjectC("|"); }
       | '^' { $$=ObjectC("^"); }
       | '!' { $$=ObjectC("!"); }
       | '=' { $$=ObjectC(strp_equals); }
       | '<' { $$=ObjectC("<"); }
       | '>' { $$=ObjectC(">"); }
       |  '-' '-' { $$=ObjectC("--"); }
       | '+' '+'  { $$=ObjectC("++"); }
       |  '[' ']' { $$=ObjectC("[]"); }
       | '(' ')'  { $$=ObjectC("()"); }
       | BINOP      { $$=$1; }
       | IDENTIFIER { $$=$1; }
;
func_arg_templ_qual: /*empty*/        { $$ = ObjectListC(STR(EmptyArgList)); } 
    |  '<' template_inst_args_opt  '>' { $$ = $2; }
; 
func_arg_prototype:  '(' func_arg_list_all ')' 
               { $$ = $2; }
;
func_prototype: 
              type_id scope_id func_arg_prototype func_qualifier 
      { $$ = MethodC($2.Name(),DataTypeC($1),ObjectListC($3),$4); 
	$$.IncludeLineNo($1);
	$$.IncludeLineNo($2);
	$$.IncludeLineNo($3);
	$$.IncludeLineNo($4);
      }
            | type_id scope_id CLCL unqualified_id func_arg_templ_qual func_arg_prototype func_qualifier 
      { $$ = MethodC($4.Name(),DataTypeC($1),ObjectListC($6),$7);
        $$.SetScope($2);
	$$.IncludeLineNo($1);
	$$.IncludeLineNo($2);
	$$.IncludeLineNo($7);
      }
            | type_id  func_arg_prototype func_qualifier  /* This catches constructors, the typename is the class type. */
      { MethodC amethod($1.Name(), DataTypeC(STR(void)),ObjectListC($2),$3); 
        amethod.IncludeLineNo($1);
        amethod.IncludeLineNo($2);
	amethod.IncludeLineNo($3);
        amethod.SetConstructor(true);
        $$ = amethod;
	ObjectC subScope = $1.GetScope();
	if(subScope.IsValid()) {
	  ObjectListC ol(subScope);
	  DListC<ObjectC> tmp = ol.List().Copy();
	  //cerr << "Got constructor:  SubScope '" << subScope.Name() << "' Path:" << PathName(tmp) << " \n";
	  tmp.DelLast();
	  if(!tmp.IsEmpty()) {
	    //cerr << "Got constructor:  SetScope to Path:" << PathName(tmp) << " \n";
	    ObjectListC oln(STR(ConstructorScopePath),tmp);
	    $$.SetScope(oln);
	  }
	}
      }
            | type_id CPOPERATOR operator_types func_arg_templ_qual func_arg_prototype func_qualifier 
      { $$ = MethodC(STR(operator) + $3.Name(), DataTypeC($1),ObjectListC($5),$6); 
        $$.IncludeLineNo($1);
        $$.IncludeLineNo($2);
        $$.IncludeLineNo($6);
      }
      
            | type_id scope_id CLCL CPOPERATOR operator_types func_arg_templ_qual  func_arg_prototype func_qualifier  
       { $$ = MethodC(STR(operator) + $5.Name(), DataTypeC($1),ObjectListC($7),$8); 
         $$.SetScope($2);
         $$.IncludeLineNo($1);
         $$.IncludeLineNo($2);
         $$.IncludeLineNo($8);
       }

            | CPOPERATOR type_id func_arg_prototype func_qualifier 
      { $$ = MethodC(STR(operator), DataTypeC($2),ObjectListC($3),$4,true);
        $$.IncludeLineNo($1);
        $$.IncludeLineNo($4);
      }
            | scope_resolved_id CLCL CPOPERATOR type_id func_arg_prototype func_qualifier 
      { $$ = MethodC(STR(operator), DataTypeC($4),ObjectListC($5),$6,true); 
        $$.SetScope($1);
        $$.IncludeLineNo($1);
        $$.IncludeLineNo($2);
        $$.IncludeLineNo($6);
      }
;

func_throw_spec:  CPTHROW '(' list_scoped_ids_opt ')'
;
list_scoped_ids_opt: /*empty */
   | list_scoped_ids
;
list_scoped_ids: scope_resolved_id
   | list_scoped_ids ',' scope_resolved_id
; 
func_arg_list_all: /*empty */ {  $$=ObjectListC(STR(FuncArgList)); }
           | func_arg_list {  $$=$1; }
;
func_arg_list: func_arg_def         { ObjectListC ol(STR(FuncArgList)); $$= ol; ol.Append($1); }
   | func_arg_list ',' func_arg_def { $$=$1; ObjectListC ol($1); ol.Append($3); }
   | func_arg_list ELLIPSIS         { $$=$1; ObjectListC ol($1); DataTypeC ell("..."); ol.Append(ell); }
;
func_arg_def: type_id      { $$=$1; }
   | type_id var_name_elem { $$=$1; DataTypeC dt($1); dt.SetAlias($2.Name()); }
   | function_ptr_def      { $$=$1; }
   | ELLIPSIS              { $$= DataTypeC("..."); }

;
function_ptr_def: type_id '(' '*' maybe_identifier ')' '(' func_arg_list_all ')' func_qualifier 
        { 
	  StringC name;
	  if($4.IsValid())
	    name = $4.Name();
	  else
	    name = StringC("anon?") + StringC(anonCount++);
	  MethodC meth(name,DataTypeC($1),ObjectListC($7),$9,false,true);
	  //$$=DataTypeC($1.Name() + StringC(" (*)(") + $7.Name() + strp_CloseBracket + $9.Name(),name); 
	  ObjectListC ol("(*)");
	  ol.Append(meth);
	  $$ = DataTypeC(name,"",ol);
	  $$.SetupLineNos($1,$8,$9);
	}
   | type_id '('  scope_resolved_id CLCL '*' IDENTIFIER ')' '(' func_arg_list_all ')'  func_qualifier
        {
	  MethodC meth($6.Name(),DataTypeC($1),ObjectListC($9),$11,false,true);
	  ObjectListC ol("(*)");
	  ol.Append(meth);	  
	  //$$=DataTypeC($1.Name() + StringC(" (*)(") + $9.Name() + strp_CloseBracket + $11.Name(),$6.Name());
	  $$ = DataTypeC($7.Name(),"",ol);
	  $$.SetupLineNos($1,$10,$11);
	}
;

func_qualifier: /*empty*/ { $$=ObjectC(""); }
    | func_throw_spec  { $$=$1; }
    | CV_QUALIFIER func_throw_spec  { $$=$1; }
    | CV_QUALIFIER { $$=$1; }
/*    | CV_QUALIFIER CV_QUALIFIER { $$=$1; $1.Name() += StringC(" ") + $2.Name(); } */
;
func_body:  '{' func_body_contents_list '}'  { $$=$2; $$.SetupLineNos($1,$3); }
;
func_body_opt_constr: func_body                        { $$=$1; }
      | ':' base_class_constructors_list func_body     { $$=$3; }
;
func_body_contents_list: /*empty*/                    
      |  func_body_contents_list func_body_contents   
;
func_body_contents:  '{' func_body_contents_list '}' 
   | IDENTIFIER | CONSTANT | SCSPEC
   | '=' | '+' | '-' | '~' | '&' | '/' | '*' | '%' | '|' | '^' | '!' | ':'
   | '(' | ')' | '[' | ']' | ';' | ',' | '<' | '>' | BINOP
   | CLCL  | PUBLIC | PROTECTED | PRIVATE | NAMESPACE | CV_QUALIFIER 
   | STRING | CPVIRTUAL | ENUM | CPTYPEDEF | TYPEQUAL | BUILTIN  
   | CPFRIEND | CPOPERATOR | TEMPLATE | CPTHROW | CPTRY | CPCATCH | TYPENAME_KEYWORD | USING 
   | EXTERN | ASM_KEYWORD | ELLIPSIS
;

%%

