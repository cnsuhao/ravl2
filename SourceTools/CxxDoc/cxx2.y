


/* This grammar is based on the GNU CC grammar.  */

/* Note: Bison automatically applies a default action of "$$ = $1" for
   all derivations; this is applied before the explicit action, if one
   is given.  Keep this in mind when reading the actions.  */

%{
/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

%}

%start program

/* All identifiers that are not reserved words
   and are not declared typedefs in the current block */
%token IDENTIFIER

/* All identifiers that are declared typedefs in the current block.
   In some contexts, they are treated just like IDENTIFIER,
   but they can also serve as typespecs in declarations.  */
%token TYPENAME
%token SELFNAME

/* A template function.  */
%token PFUNCNAME

/* Reserved words that specify storage class.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token SCSPEC

/* Reserved words that specify type.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token TYPESPEC

/* Reserved words that qualify type: "const" or "volatile".
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token CV_QUALIFIER

/* Character or numeric constants.
   yylval is the node for the constant.  */
%token CONSTANT

/* String constants in raw form.
   yylval is a STRING_CST node.  */
%token STRING

/* "...", used for functions with variable arglists.  */
%token ELLIPSIS

/* the reserved words */
/* SCO include files test "ASM", so use something else.  */
%token SIZEOF ENUM /* STRUCT UNION */ IF ELSE WHILE DO FOR SWITCH CASE DEFAULT
%token BREAK CONTINUE RETURN_KEYWORD GOTO ASM_KEYWORD TYPEOF ALIGNOF
%token SIGOF
%token ATTRIBUTE EXTENSION LABEL
%token REALPART IMAGPART

/* the reserved words... C++ extensions */
%token AGGR
%token VISSPEC
%token DELETE NEW THIS OPERATOR CXX_TRUE CXX_FALSE
%token NAMESPACE TYPENAME_KEYWORD USING
%token LEFT_RIGHT TEMPLATE
%token TYPEID DYNAMIC_CAST STATIC_CAST REINTERPRET_CAST CONST_CAST
%token <itype> SCOPE

/* Define the operator tokens and their precedences.
   The value is an integer because, if used, it is the tree code
   to use in the expression made from the operator.  */

%left EMPTY			/* used to resolve s/r with epsilon */

%left error

/* Add precedence rules to solve dangling else s/r conflict */
%nonassoc IF
%nonassoc ELSE

%left IDENTIFIER PFUNCNAME TYPENAME SELFNAME PTYPENAME SCSPEC TYPESPEC CV_QUALIFIER ENUM AGGR ELLIPSIS TYPEOF SIGOF OPERATOR NSNAME TYPENAME_KEYWORD

%left '{' ',' ';'

%nonassoc THROW
%right <code> ':'
%right <code> ASSIGN '='
%right <code> '?'
%left <code> OROR
%left <code> ANDAND
%left <code> '|'
%left <code> '^'
%left <code> '&'
%left <code> MIN_MAX
%left <code> EQCOMPARE
%left <code> ARITHCOMPARE '<' '>'
%left <code> LSHIFT RSHIFT
%left <code> '+' '-'
%left <code> '*' '/' '%'
%left <code> POINTSAT_STAR DOT_STAR
%right <code> UNARY PLUSPLUS MINUSMINUS '~'
%left HYPERUNARY
%left  PAREN_STAR_PAREN LEFT_RIGHT
%left <code> POINTSAT '.' '(' '['

%right SCOPE			/* C++ extension */
%nonassoc NEW DELETE TRY CATCH

/* C++ extensions */
%token  PTYPENAME
%token  PRE_PARSED_FUNCTION_DECL EXTERN_LANG_STRING ALL
%token  PRE_PARSED_CLASS_DECL DEFARG DEFARG_MARKER

%token NSNAME

/* Used in lex.c for parsing pragmas.  */
%token END_OF_LINE

/* lex.c and pt.c depend on this being the last token.  Define
   any new tokens before this one!  */
%token END_OF_SAVED_INPUT

%%
program:
	  /* empty */
	| extdefs
               { finish_translation_unit (); }
	;

/* the reason for the strange actions in this rule
 is so that notype_initdecls when reached via datadef
 can find a valid list of type and sc specs in $0.  */

extdefs:
	  lang_extdef
	| extdefs lang_extdef
	;

extdefs_opt:
	  extdefs
	| /* empty */
	;

.hush_warning:
	;
.warning_ok:
	;

extension:
	EXTENSION
	;

asm_keyword:
	  ASM_KEYWORD
	;

lang_extdef:
	  extdef
	;

extdef:
	  fndef 
	| datadef
	| template_def
	| asm_keyword '(' string ')' ';'
	| extern_lang_string '{' extdefs_opt '}'
	| extern_lang_string .hush_warning fndef .warning_ok eat_saved_input
	| extern_lang_string .hush_warning datadef .warning_ok
	| NAMESPACE identifier '{' extdefs_opt '}'
	| NAMESPACE '{' extdefs_opt '}'
	| namespace_alias
	| using_decl ';'
	| using_directive
	| extension extdef
	;

namespace_alias:
          NAMESPACE identifier '=' 
          any_id ';'
	;

using_decl:
	  USING qualified_id
	| USING global_scope qualified_id
	| USING global_scope unqualified_id
	;

namespace_using_decl:
	  USING namespace_qualifier identifier
	| USING global_scope identifier
	| USING global_scope namespace_qualifier identifier
	;

using_directive:
	  USING NAMESPACE
	  any_id ';'
	;

namespace_qualifier:
	  NSNAME SCOPE
	| namespace_qualifier NSNAME SCOPE

any_id:
	  unqualified_id
	| qualified_id
	| global_scope qualified_id
		{ $$ = $2; }
	| global_scope unqualified_id
		{ $$ = $2; }
	;

extern_lang_string:
	EXTERN_LANG_STRING
	| extern_lang_string EXTERN_LANG_STRING
	;

template_header:
	  TEMPLATE '<'
	  template_parm_list '>'
	| TEMPLATE '<' '>'
	;

template_parm_list:
	  template_parm
	| template_parm_list ',' template_parm
	;

maybe_identifier:
	  identifier
	  	{ $$ = $1; }
	|	/* empty */
		{ $$ = NULL_TREE; }

template_type_parm:
	  aggr maybe_identifier
	| TYPENAME_KEYWORD maybe_identifier
	;

template_template_parm:
	  template_header aggr maybe_identifier
	;

template_parm:
	/* The following rules introduce a new reduce/reduce
	   conflict on the ',' and '>' input tokens: they are valid
	   prefixes for a `structsp', which means they could match a
	   nameless parameter.  See 14.6, paragraph 3.
	   By putting them before the `parm' rule, we get
	   their match before considering them nameless parameter
	   declarations.  */
	  template_type_parm
	| template_type_parm '=' type_id
	| parm
	| parm '=' expr_no_commas  %prec ARITHCOMPARE
	| template_template_parm
	| template_template_parm '=' template_arg
	;

template_def:
	  template_header template_extdef
	| template_header error  %prec EMPTY
	;

template_extdef:
	  fndef eat_saved_input
	| template_datadef
	| template_def
	| extern_lang_string .hush_warning fndef .warning_ok eat_saved_input
	| extern_lang_string .hush_warning template_datadef .warning_ok
	| extension template_extdef
	;

template_datadef:
	  nomods_initdecls ';'
	| declmods notype_initdecls ';'
	| typed_declspecs initdecls ';'
	| structsp ';'
	;

datadef:
	  nomods_initdecls ';'
	| declmods notype_initdecls ';'
	| typed_declspecs initdecls ';'
        | declmods ';'
	| explicit_instantiation ';'
	| typed_declspecs ';'
	| error ';'
	| error '}'
	| ';'
	;

ctor_initializer_opt:
	  nodecls
	| base_init
	;

maybe_return_init:
	  /* empty */
	| return_init
	| return_init ';'
	;

eat_saved_input:
	  /* empty */
	| END_OF_SAVED_INPUT
	;

fndef:
	  fn.def1 maybe_return_init ctor_initializer_opt compstmt_or_error
	| fn.def1 maybe_return_init function_try_block
	| fn.def1 maybe_return_init error
	;

constructor_declarator:
	  nested_name_specifier SELFNAME '(' 
	  parmlist ')' cv_qualifiers exception_specification_opt
	| nested_name_specifier SELFNAME LEFT_RIGHT cv_qualifiers exception_specification_opt
	| global_scope nested_name_specifier SELFNAME '(' 
	| global_scope nested_name_specifier SELFNAME LEFT_RIGHT cv_qualifiers exception_specification_opt
	| nested_name_specifier self_template_type '(' 
	  parmlist ')' cv_qualifiers exception_specification_opt
	| nested_name_specifier self_template_type LEFT_RIGHT cv_qualifiers exception_specification_opt
	| global_scope nested_name_specifier self_template_type '(' 
	| global_scope nested_name_specifier self_template_type LEFT_RIGHT cv_qualifiers exception_specification_opt
	;

fn.def1:
	  typed_declspecs declarator
	| declmods notype_declarator
	| notype_declarator
	| declmods constructor_declarator
	| constructor_declarator
	;

component_constructor_declarator:
	  SELFNAME '(' parmlist ')' cv_qualifiers exception_specification_opt
	| SELFNAME LEFT_RIGHT cv_qualifiers exception_specification_opt
	| self_template_type '(' parmlist ')' cv_qualifiers exception_specification_opt
	| self_template_type LEFT_RIGHT cv_qualifiers exception_specification_opt
	;

/* more C++ complexity.  See component_decl for a comment on the
   reduce/reduce conflict introduced by these rules.  */
fn.def2:
	  declmods component_constructor_declarator
	| component_constructor_declarator
	| typed_declspecs declarator
	| declmods notype_declarator
	| notype_declarator
	| declmods constructor_declarator
	| constructor_declarator
	;

return_id:
	  RETURN_KEYWORD IDENTIFIER
	;

return_init:
	  return_id maybe_init
	| return_id '(' nonnull_exprlist ')'
	| return_id LEFT_RIGHT
	;

base_init:
	  ':' .set_base_init member_init_list
	;
.set_base_init:
	;

member_init_list:
	  /* empty */
	| member_init
	| member_init_list ',' member_init
	| member_init_list error
	;

member_init:
	  '(' nonnull_exprlist ')'
	| LEFT_RIGHT
	| notype_identifier '(' nonnull_exprlist ')'
	| notype_identifier LEFT_RIGHT
	| nonnested_type '(' nonnull_exprlist ')'
	| nonnested_type LEFT_RIGHT
	| typename_sub '(' nonnull_exprlist ')'
	| typename_sub LEFT_RIGHT
	;

identifier:
	  IDENTIFIER
	| TYPENAME
	| SELFNAME
	| PTYPENAME
	| NSNAME
	;

notype_identifier:
	  IDENTIFIER
	| PTYPENAME 
	| NSNAME  %prec EMPTY
	;

identifier_defn:
	  IDENTIFIER_DEFN
	| TYPENAME_DEFN
	| PTYPENAME_DEFN
	;

explicit_instantiation:
	  TEMPLATE begin_explicit_instantiation typespec ';'
          end_explicit_instantiation
	| TEMPLATE begin_explicit_instantiation typed_declspecs declarator
          end_explicit_instantiation
	| TEMPLATE begin_explicit_instantiation notype_declarator
          end_explicit_instantiation
	| TEMPLATE begin_explicit_instantiation constructor_declarator
          end_explicit_instantiation
	| SCSPEC TEMPLATE begin_explicit_instantiation typespec ';'
          end_explicit_instantiation
	| SCSPEC TEMPLATE begin_explicit_instantiation typed_declspecs 
          declarator
          end_explicit_instantiation
	| SCSPEC TEMPLATE begin_explicit_instantiation notype_declarator
          end_explicit_instantiation
	| SCSPEC TEMPLATE begin_explicit_instantiation constructor_declarator
          end_explicit_instantiation
	;

begin_explicit_instantiation: 
      {}

end_explicit_instantiation: 
      {}

/* The TYPENAME expansions are to deal with use of a template class name as
  a template within the class itself, where the template decl is hidden by
  a type decl.  Got all that?  */

template_type:
	  PTYPENAME '<' template_arg_list_opt '>'
	    .finish_template_type
	| TYPENAME  '<' template_arg_list_opt '>'
	    .finish_template_type
	| self_template_type
	;

apparent_template_type:
	  template_type
	| identifier '<' template_arg_list_opt '>'
		{ $$ = $5; }

self_template_type:
	  SELFNAME  '<' template_arg_list_opt '>'
                { $$ = $5; }
	;

template_arg_list_opt:
         /* empty */
                 { $$ = NULL_TREE; }
       | template_arg_list
       ;

template_arg_list:
        template_arg
		{ $$ = build_tree_list (NULL_TREE, $$); }
	| template_arg_list ',' template_arg
		{ $$ = chainon ($$, build_tree_list (NULL_TREE, $3)); }
	;

template_arg:
	  type_id
		{ $$ = groktypename ($1.t); }
	| PTYPENAME
		{ $$ = lastiddecl; }
	| expr_no_commas  %prec ARITHCOMPARE
	;

unop:
	  '-'
 		{ $$ = NEGATE_EXPR; }
	| '+'
		{ $$ = CONVERT_EXPR; }
	| PLUSPLUS
		{ $$ = PREINCREMENT_EXPR; }
	| MINUSMINUS
		{ $$ = PREDECREMENT_EXPR; }
	| '!'
		{ $$ = TRUTH_NOT_EXPR; }
	;

expr:
	  nontrivial_exprlist
		{ $$ = build_x_compound_expr ($$); }
	| expr_no_commas
	;

paren_expr_or_null:
	LEFT_RIGHT
		{ error ("ANSI C++ forbids an empty condition for `%s'",
			 cond_stmt_keyword);
		  $$ = integer_zero_node; }
	| '(' expr ')'
                { $$ = $2; }
	;

paren_cond_or_null:
	LEFT_RIGHT
		{ error ("ANSI C++ forbids an empty condition for `%s'",
			 cond_stmt_keyword);
		  $$ = integer_zero_node; }
	| '(' condition ')'
                { $$ = $2; }
	;

xcond:
	  /* empty */
		{ $$ = NULL_TREE; }
	| condition
	| error
		{ $$ = NULL_TREE; }
	;

condition:
	  type_specifier_seq declarator maybeasm maybe_attribute '='
		{ {
		  tree d;
		  for (d = getdecls (); d; d = TREE_CHAIN (d))
		    if (TREE_CODE (d) == TYPE_DECL) {
		      tree s = TREE_TYPE (d);
		      if (TREE_CODE (s) == RECORD_TYPE)
			cp_error ("definition of class `%T' in condition", s);
		      else if (TREE_CODE (s) == ENUMERAL_TYPE)
			cp_error ("definition of enum `%T' in condition", s);
		    }
		  }
		  current_declspecs = $1.t;
		  $<itype>5 = suspend_momentary ();
		  $$ = start_decl ($2, current_declspecs, 1,
					  $4, /*prefix_attributes*/ NULL_TREE);
		}
	  init
		{ 
		  cp_finish_decl ($6, $7, $4, 1, LOOKUP_ONLYCONVERTING);
		  resume_momentary ($<itype>5);
		  $$ = convert_from_reference ($6); 
		  if (TREE_CODE (TREE_TYPE ($$)) == ARRAY_TYPE)
		    cp_error ("definition of array `%#D' in condition", $$); 
		}
	| expr
	;

compstmtend:
	  '}'
	| maybe_label_decls stmts '}'
	| maybe_label_decls stmts error '}'
	| maybe_label_decls error '}'
	;

already_scoped_stmt:
	  '{'
                { $$ = begin_compound_stmt (1); }
	  compstmtend
                { finish_compound_stmt (1, $2); }
	| simple_stmt
	;


nontrivial_exprlist:
	  expr_no_commas ',' expr_no_commas
		{ $$ = expr_tree_cons (NULL_TREE, $$, 
		                  build_expr_list (NULL_TREE, $3)); }
	| expr_no_commas ',' error
		{ $$ = expr_tree_cons (NULL_TREE, $$, 
		                  build_expr_list (NULL_TREE, error_mark_node)); }
	| nontrivial_exprlist ',' expr_no_commas
		{ chainon ($$, build_expr_list (NULL_TREE, $3)); }
	| nontrivial_exprlist ',' error
		{ chainon ($$, build_expr_list (NULL_TREE, error_mark_node)); }
	;

nonnull_exprlist:
	  expr_no_commas
		{ $$ = build_expr_list (NULL_TREE, $$); }
	| nontrivial_exprlist
	;

unary_expr:
	  primary  %prec UNARY
		{ $$ = $1; }
	/* __extension__ turns off -pedantic for following primary.  */
	| extension cast_expr  	  %prec UNARY
		{ $$ = $2;
		  pedantic = $<itype>1; }
	| '*' cast_expr   %prec UNARY
		{ $$ = build_x_indirect_ref ($2, "unary *"); }
	| '&' cast_expr   %prec UNARY
		{ $$ = build_x_unary_op (ADDR_EXPR, $2); }
	| '~' cast_expr
		{ $$ = build_x_unary_op (BIT_NOT_EXPR, $2); }
	| unop cast_expr  %prec UNARY
                { $$ = finish_unary_op_expr ($1, $2); }
	/* Refer to the address of a label as a pointer.  */
	| ANDAND identifier
		{ if (pedantic)
		    pedwarn ("ANSI C++ forbids `&&'");
  		  $$ = finish_label_address_expr ($2); }
	| SIZEOF unary_expr  %prec UNARY
		{ $$ = expr_sizeof ($2); }
	| SIZEOF '(' type_id ')'  %prec HYPERUNARY
		{ $$ = c_sizeof (groktypename ($3.t));
		  check_for_new_type ("sizeof", $3); }
	| ALIGNOF unary_expr  %prec UNARY
		{ $$ = grok_alignof ($2); }
	| ALIGNOF '(' type_id ')'  %prec HYPERUNARY
		{ $$ = c_alignof (groktypename ($3.t)); 
		  check_for_new_type ("alignof", $3); }

	/* The %prec EMPTY's here are required by the = init initializer
	   syntax extension; see below.  */
	| new new_type_id  %prec EMPTY
		{ $$ = build_new (NULL_TREE, $2.t, NULL_TREE, $1); 
		  check_for_new_type ("new", $2); }
	| new new_type_id new_initializer
		{ $$ = build_new (NULL_TREE, $2.t, $3, $1); 
		  check_for_new_type ("new", $2); }
	| new new_placement new_type_id  %prec EMPTY
		{ $$ = build_new ($2, $3.t, NULL_TREE, $1); 
		  check_for_new_type ("new", $3); }
	| new new_placement new_type_id new_initializer
		{ $$ = build_new ($2, $3.t, $4, $1); 
		  check_for_new_type ("new", $3); }
        /* The .begin_new_placement in the following rules is
	   necessary to avoid shift/reduce conflicts that lead to
	   mis-parsing some expressions.  Of course, these constructs
	   are not really new-placement and it is bogus to call
	   begin_new_placement.  But, the parser cannot always tell at this
	   point whether the next thing is an expression or a type-id,
	   so there is nothing we can do.  Fortunately,
	   begin_new_placement does nothing harmful.  When we rewrite
	   the parser, this lossage should be removed, of course.  */
	| new '(' .begin_new_placement type_id .finish_new_placement
            %prec EMPTY
		{ $$ = build_new (NULL_TREE, groktypename($4.t),
				  NULL_TREE, $1); 
		  check_for_new_type ("new", $4); }
	| new '(' .begin_new_placement type_id .finish_new_placement
            new_initializer
		{ $$ = build_new (NULL_TREE, groktypename($4.t), $6, $1); 
		  check_for_new_type ("new", $4); }
	| new new_placement '(' .begin_new_placement type_id
	    .finish_new_placement   %prec EMPTY
		{ $$ = build_new ($2, groktypename($5.t), NULL_TREE, $1); 
		  check_for_new_type ("new", $5); }
	| new new_placement '(' .begin_new_placement type_id
	    .finish_new_placement  new_initializer
		{ $$ = build_new ($2, groktypename($5.t), $7, $1); 
		  check_for_new_type ("new", $5); }

	| delete cast_expr  %prec UNARY
		{ $$ = delete_sanity ($2, NULL_TREE, 0, $1); }
	| delete '[' ']' cast_expr  %prec UNARY
		{ $$ = delete_sanity ($4, NULL_TREE, 1, $1);
		  if (yychar == YYEMPTY)
		    yychar = YYLEX; }
	| delete '[' expr ']' cast_expr  %prec UNARY
		{ $$ = delete_sanity ($5, $3, 2, $1);
		  if (yychar == YYEMPTY)
		    yychar = YYLEX; }
	| REALPART cast_expr %prec UNARY
		{ $$ = build_x_unary_op (REALPART_EXPR, $2); }
	| IMAGPART cast_expr %prec UNARY
		{ $$ = build_x_unary_op (IMAGPART_EXPR, $2); }
	;

        /* Note this rule is not suitable for use in new_placement
	   since it uses NULL_TREE as the argument to
	   finish_new_placement.  This rule serves only to avoid
	   reduce/reduce conflicts in unary_expr.  See the comments
	   there on the use of begin/finish_new_placement.  */
.finish_new_placement:
	  ')'
                { finish_new_placement (NULL_TREE, $<itype>-1); }

.begin_new_placement:
                { $$ = begin_new_placement (); }

new_placement:
	  '(' .begin_new_placement nonnull_exprlist ')'
                { $$ = finish_new_placement ($3, $2); }
	| '{' .begin_new_placement nonnull_exprlist '}'
                { cp_pedwarn ("old style placement syntax, use () instead");
		  $$ = finish_new_placement ($3, $2); }
	;

new_initializer:
	  '(' nonnull_exprlist ')'
		{ $$ = $2; }
	| LEFT_RIGHT
		{ $$ = NULL_TREE; }
	| '(' typespec ')'
		{
		  cp_error ("`%T' is not a valid expression", $2.t);
		  $$ = error_mark_node;
		}
	/* GNU extension so people can use initializer lists.  Note that
	   this alters the meaning of `new int = 1', which was previously
	   syntactically valid but semantically invalid.  */
	| '=' init
		{
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids initialization of new expression with `='");
		  if (TREE_CODE ($2) != TREE_LIST
		      && TREE_CODE ($2) != CONSTRUCTOR)
		    $$ = build_expr_list (NULL_TREE, $2);
		  else
		    $$ = $2;
		}
	;

/* This is necessary to postpone reduction of `int ((int)(int)(int))'.  */
regcast_or_absdcl:
	  '(' type_id ')'  %prec EMPTY
		{ $2.t = finish_parmlist (build_tree_list (NULL_TREE, $2.t), 0);
		  $$ = make_call_declarator (NULL_TREE, $2.t, NULL_TREE, NULL_TREE);
		  check_for_new_type ("cast", $2); }
	| regcast_or_absdcl '(' type_id ')'  %prec EMPTY
		{ $3.t = finish_parmlist (build_tree_list (NULL_TREE, $3.t), 0); 
		  $$ = make_call_declarator ($$, $3.t, NULL_TREE, NULL_TREE);
		  check_for_new_type ("cast", $3); }
	;

cast_expr:
	  unary_expr
	| regcast_or_absdcl unary_expr  %prec UNARY
		{ $$ = reparse_absdcl_as_casts ($$, $2); }
	| regcast_or_absdcl '{' initlist maybecomma '}'  %prec UNARY
		{ 
		  tree init = build_nt (CONSTRUCTOR, NULL_TREE,
					nreverse ($3)); 
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids constructor-expressions");
		  /* Indicate that this was a GNU C constructor expression.  */
		  TREE_HAS_CONSTRUCTOR (init) = 1;

		  $$ = reparse_absdcl_as_casts ($$, init);
		}
	;

expr_no_commas:
	  cast_expr
	/* Handle general members.  */
	| expr_no_commas POINTSAT_STAR expr_no_commas
		{ $$ = build_x_binary_op (MEMBER_REF, $$, $3); }
	| expr_no_commas DOT_STAR expr_no_commas
		{ $$ = build_m_component_ref ($$, $3); }
	| expr_no_commas '+' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '-' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '*' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '/' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '%' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas LSHIFT expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas RSHIFT expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas ARITHCOMPARE expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '<' expr_no_commas
		{ $$ = build_x_binary_op (LT_EXPR, $$, $3); }
	| expr_no_commas '>' expr_no_commas
		{ $$ = build_x_binary_op (GT_EXPR, $$, $3); }
	| expr_no_commas EQCOMPARE expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas MIN_MAX expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '&' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '|' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas '^' expr_no_commas
		{ $$ = build_x_binary_op ($2, $$, $3); }
	| expr_no_commas ANDAND expr_no_commas
		{ $$ = build_x_binary_op (TRUTH_ANDIF_EXPR, $$, $3); }
	| expr_no_commas OROR expr_no_commas
		{ $$ = build_x_binary_op (TRUTH_ORIF_EXPR, $$, $3); }
	| expr_no_commas '?' xexpr ':' expr_no_commas
		{ $$ = build_x_conditional_expr ($$, $3, $5); }
	| expr_no_commas '=' expr_no_commas
		{ $$ = build_x_modify_expr ($$, NOP_EXPR, $3);
		  if ($$ != error_mark_node)
                    C_SET_EXP_ORIGINAL_CODE ($$, MODIFY_EXPR); }
	| expr_no_commas ASSIGN expr_no_commas
		{ $$ = build_x_modify_expr ($$, $2, $3); }
	| THROW
		{ $$ = build_throw (NULL_TREE); }
	| THROW expr_no_commas
		{ $$ = build_throw ($2); }
/* These extensions are not defined.  The second arg to build_m_component_ref
   is old, build_m_component_ref now does an implicit
   build_indirect_ref (x, NULL_PTR) on the second argument.
	| object '&' expr_no_commas  %prec UNARY
		{ $$ = build_m_component_ref ($$, build_x_unary_op (ADDR_EXPR, $3)); }
	| object unop expr_no_commas  %prec UNARY
		{ $$ = build_m_component_ref ($$, build_x_unary_op ($2, $3)); }
	| object '(' type_id ')' expr_no_commas  %prec UNARY
		{ tree type = groktypename ($3.t);
		  $$ = build_m_component_ref ($$, build_c_cast (type, $5)); }
	| object primary_no_id  %prec UNARY
		{ $$ = build_m_component_ref ($$, $2); }
*/
	;

notype_unqualified_id:
	  '~' see_typename identifier
		{ $$ = build_parse_node (BIT_NOT_EXPR, $3); }
	| '~' see_typename template_type
		{ $$ = build_parse_node (BIT_NOT_EXPR, $3); }
        | template_id
	| operator_name
	| IDENTIFIER
	| PTYPENAME
	| NSNAME  %prec EMPTY
	;

do_id:
		{
		  /* If lastiddecl is a TREE_LIST, it's a baselink, which
		     means that we're in an expression like S::f<int>, so
		     don't do_identifier; we only do that for unqualified
		     identifiers.  */
		  if (lastiddecl && TREE_CODE (lastiddecl) != TREE_LIST)
		    $$ = do_identifier ($-1, 1, NULL_TREE);
		  else
		    $$ = $-1;
		}

template_id:
          PFUNCNAME '<' do_id template_arg_list_opt '>'
                { $$ = lookup_template_function ($3, $4); }
        | operator_name '<' do_id template_arg_list_opt  '>'
                { $$ = lookup_template_function ($3, $4); }
	;

object_template_id:
        TEMPLATE identifier '<' template_arg_list_opt '>' 
        | TEMPLATE PFUNCNAME '<' template_arg_list_opt '>'
        | TEMPLATE operator_name '<' template_arg_list_opt '>'
        ;

unqualified_id:
	  notype_unqualified_id
	| TYPENAME
	| SELFNAME
	;

expr_or_declarator_intern:
	  expr_or_declarator
	| attributes expr_or_declarator
	;

expr_or_declarator:
	  notype_unqualified_id
	| '*' expr_or_declarator_intern  %prec UNARY
	| '&' expr_or_declarator_intern  %prec UNARY
	| '(' expr_or_declarator_intern ')'
	;

notype_template_declarator:
	  IDENTIFIER '<' template_arg_list_opt '>'
                { $$ = lookup_template_function ($1, $3); }
	| NSNAME '<' template_arg_list '>'
                { $$ = lookup_template_function ($1, $3); }
	;
		
direct_notype_declarator:
	  complex_direct_notype_declarator
	/* This precedence declaration is to prefer this reduce
	   to the Koenig lookup shift in primary, below.  I hate yacc.  */
	| notype_unqualified_id %prec '('
	| notype_template_declarator
	| '(' expr_or_declarator_intern ')'
	;

primary:
	  notype_unqualified_id
	| CONSTANT
	| boolean.literal
	| string
	| '(' expr ')'
	| '(' expr_or_declarator_intern ')'
	| '(' error ')'
	| '(' compstmt ')'
        /* Koenig lookup support
           We could store lastiddecl in $1 to avoid another lookup,
           but that would result in many additional reduce/reduce conflicts. */
        | notype_unqualified_id '(' nonnull_exprlist ')'
        | notype_unqualified_id LEFT_RIGHT
	| primary '(' nonnull_exprlist ')'
	| primary LEFT_RIGHT
	| primary '[' expr ']'
	| primary PLUSPLUS
	| primary MINUSMINUS
	/* C++ extensions */
	| THIS
	| CV_QUALIFIER '(' nonnull_exprlist ')'
	| functional_cast
	| DYNAMIC_CAST '<' type_id '>' '(' expr ')'
	| STATIC_CAST '<' type_id '>' '(' expr ')'
	| REINTERPRET_CAST '<' type_id '>' '(' expr ')'
	| CONST_CAST '<' type_id '>' '(' expr ')'
	| TYPEID '(' expr ')'
	| TYPEID '(' type_id ')'
	| global_scope IDENTIFIER
	| global_scope template_id
	| global_scope operator_name
	| overqualified_id  %prec HYPERUNARY
	| overqualified_id '(' nonnull_exprlist ')'
	| overqualified_id LEFT_RIGHT
        | object object_template_id %prec UNARY
                { 
		  $$ = build_x_component_ref ($$, $2, NULL_TREE, 1); 
		}
        | object object_template_id '(' nonnull_exprlist ')'
                { $$ = finish_object_call_expr ($2, $1, $4); }
	| object object_template_id LEFT_RIGHT
                { $$ = finish_object_call_expr ($2, $1, NULL_TREE); }
	| object unqualified_id  %prec UNARY
		{ $$ = build_x_component_ref ($$, $2, NULL_TREE, 1); }
	| object overqualified_id  %prec UNARY
		{ if (processing_template_decl)
		    $$ = build_min_nt (COMPONENT_REF, $1, copy_to_permanent ($2));
		  else
		    $$ = build_object_ref ($$, OP0 ($2), OP1 ($2)); }
	| object unqualified_id '(' nonnull_exprlist ')'
                { $$ = finish_object_call_expr ($2, $1, $4); }
	| object unqualified_id LEFT_RIGHT
                { $$ = finish_object_call_expr ($2, $1, NULL_TREE); }
	| object overqualified_id '(' nonnull_exprlist ')'
                { $$ = finish_qualified_object_call_expr ($2, $1, $4); }
	| object overqualified_id LEFT_RIGHT
                { $$ = finish_qualified_object_call_expr ($2, $1, NULL_TREE); }
	/* p->int::~int() is valid -- 12.4 */
	| object '~' TYPESPEC LEFT_RIGHT
		{ $$ = finish_pseudo_destructor_call_expr ($1, NULL_TREE, $3); }
	| object TYPESPEC SCOPE '~' TYPESPEC LEFT_RIGHT
		{ $$ = finish_pseudo_destructor_call_expr ($1, $2, $5); }
	| object error
		{
		  $$ = error_mark_node;
		}
	;

new:
	  NEW
		{ $$ = 0; }
	| global_scope NEW
		{ got_scope = NULL_TREE; $$ = 1; }
	;

delete:
	  DELETE
		{ $$ = 0; }
	| global_scope delete
		{ got_scope = NULL_TREE; $$ = 1; }
	;

boolean.literal:
	  CXX_TRUE
		{ $$ = boolean_true_node; }
	| CXX_FALSE
		{ $$ = boolean_false_node; }
	;

/* Produces a STRING_CST with perhaps more STRING_CSTs chained onto it.  */
string:
	  STRING
	| string STRING
		{ $$ = chainon ($$, $2); }
	;

nodecls:
	  /* empty */
		{
		  if (! current_function_parms_stored)
		    store_parm_decls ();
		  setup_vtbl_ptr ();
		  /* Always keep the BLOCK node associated with the outermost
		     pair of curley braces of a function.  These are needed
		     for correct operation of dwarfout.c.  */
		  keep_next_level ();
		}
	;

object:
	  primary '.'
		{ got_object = TREE_TYPE ($$); }
	| primary POINTSAT
		{
		  $$ = build_x_arrow ($$); 
		  got_object = TREE_TYPE ($$);
		}
	;

decl:
	  typespec initdecls ';'
		{
		  resume_momentary ($2);
		  if ($1.t && IS_AGGR_TYPE_CODE (TREE_CODE ($1.t)))
		    note_got_semicolon ($1.t);
		}
	| typed_declspecs initdecls ';'
		{
		  resume_momentary ($2);
		  note_list_got_semicolon ($1.t);
		}
	| declmods notype_initdecls ';'
		{ resume_momentary ($2); }
	| typed_declspecs ';'
		{
		  shadow_tag ($1.t);
		  note_list_got_semicolon ($1.t);
		}
	| declmods ';'
		{ warning ("empty declaration"); }
	| extension decl
		{ pedantic = $<itype>1; }
	;

/* Any kind of declarator (thus, all declarators allowed
   after an explicit typespec).  */

declarator:
	  after_type_declarator  %prec EMPTY
	| notype_declarator  %prec EMPTY
	;

/* This is necessary to postpone reduction of `int()()()()'.  */
fcast_or_absdcl:
	  LEFT_RIGHT  %prec EMPTY
		{ $$ = make_call_declarator (NULL_TREE, empty_parms (),
					     NULL_TREE, NULL_TREE); }
	| fcast_or_absdcl LEFT_RIGHT  %prec EMPTY
		{ $$ = make_call_declarator ($$, empty_parms (), NULL_TREE,
					     NULL_TREE); }
	;

/* ANSI type-id (8.1) */
type_id:
	  typed_typespecs absdcl
		{ $$.t = build_decl_list ($1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| nonempty_cv_qualifiers absdcl
		{ $$.t = build_decl_list ($1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| typespec absdcl
		{ $$.t = build_decl_list (build_decl_list (NULL_TREE, $1.t),
					  $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| typed_typespecs  %prec EMPTY
		{ $$.t = build_decl_list ($1.t, NULL_TREE);
		  $$.new_type_flag = $1.new_type_flag;  }
	| nonempty_cv_qualifiers  %prec EMPTY
		{ $$.t = build_decl_list ($1.t, NULL_TREE); 
		  $$.new_type_flag = $1.new_type_flag; }
	;

/* Declspecs which contain at least one type specifier or typedef name.
   (Just `const' or `volatile' is not enough.)
   A typedef'd name following these is taken as a name to be declared.
   In the result, declspecs have a non-NULL TREE_VALUE, attributes do not.  */

typed_declspecs:
	  typed_typespecs  %prec EMPTY
	| typed_declspecs1
	;

typed_declspecs1:
	  declmods typespec
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t, $1); 
		  $$.new_type_flag = $2.new_type_flag; }
	| typespec reserved_declspecs  %prec HYPERUNARY
		{ $$.t = decl_tree_cons (NULL_TREE, $1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| typespec reserved_typespecquals reserved_declspecs
		{ $$.t = decl_tree_cons (NULL_TREE, $1.t, chainon ($2, $3)); 
		  $$.new_type_flag = $1.new_type_flag; }
	| declmods typespec reserved_declspecs
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t, chainon ($3, $1)); 
		  $$.new_type_flag = $2.new_type_flag; }
	| declmods typespec reserved_typespecquals
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t, chainon ($3, $1)); 
		  $$.new_type_flag = $2.new_type_flag; }
	| declmods typespec reserved_typespecquals reserved_declspecs
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t,
					 chainon ($3, chainon ($4, $1))); 
		  $$.new_type_flag = $2.new_type_flag; }
	;

reserved_declspecs:
	  SCSPEC
		{ if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ($$));
		  $$ = build_decl_list (NULL_TREE, $$); }
	| reserved_declspecs typespecqual_reserved
		{ $$ = decl_tree_cons (NULL_TREE, $2.t, $$); }
	| reserved_declspecs SCSPEC
		{ if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ($2));
		  $$ = decl_tree_cons (NULL_TREE, $2, $$); }
	| reserved_declspecs attributes
		{ $$ = decl_tree_cons ($2, NULL_TREE, $1); }
	| attributes
		{ $$ = decl_tree_cons ($1, NULL_TREE, NULL_TREE); }
	;

/* List of just storage classes and type modifiers.
   A declaration can start with just this, but then it cannot be used
   to redeclare a typedef-name.
   In the result, declspecs have a non-NULL TREE_VALUE, attributes do not.  */

/* We use hash_tree_cons for lists of typeless declspecs so that they end
   up on a persistent obstack.  Otherwise, they could appear at the
   beginning of something like

      static const struct { int foo () { } } b;

   and would be discarded after we finish compiling foo.  We don't need to
   worry once we see a type.  */

declmods:
	  nonempty_cv_qualifiers  %prec EMPTY
		{ $$ = $1.t; TREE_STATIC ($$) = 1; }
	| SCSPEC
		{ $$ = hash_tree_cons (NULL_TREE, $$, NULL_TREE); }
	| declmods CV_QUALIFIER
		{ $$ = hash_tree_cons (NULL_TREE, $2, $$);
		  TREE_STATIC ($$) = 1; }
	| declmods SCSPEC
		{ if (extra_warnings && TREE_STATIC ($$))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ($2));
		  $$ = hash_tree_cons (NULL_TREE, $2, $$);
		  TREE_STATIC ($$) = TREE_STATIC ($1); }
	| declmods attributes
		{ $$ = hash_tree_cons ($2, NULL_TREE, $1); }
	| attributes  %prec EMPTY
		{ $$ = hash_tree_cons ($1, NULL_TREE, NULL_TREE); }
	;

/* Used instead of declspecs where storage classes are not allowed
   (that is, for typenames and structure components).

   C++ can takes storage classes for structure components.
   Don't accept a typedef-name if anything but a modifier precedes it.  */

typed_typespecs:
	  typespec  %prec EMPTY
		{ $$.t = build_decl_list (NULL_TREE, $1.t); 
		  $$.new_type_flag = $1.new_type_flag; }
	| nonempty_cv_qualifiers typespec
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t, $1.t); 
		  $$.new_type_flag = $2.new_type_flag; }
	| typespec reserved_typespecquals
		{ $$.t = decl_tree_cons (NULL_TREE, $1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| nonempty_cv_qualifiers typespec reserved_typespecquals
		{ $$.t = decl_tree_cons (NULL_TREE, $2.t, chainon ($3, $1.t)); 
		  $$.new_type_flag = $1.new_type_flag; }
	;

reserved_typespecquals:
	  typespecqual_reserved
		{ $$ = build_decl_list (NULL_TREE, $1.t); }
	| reserved_typespecquals typespecqual_reserved
		{ $$ = decl_tree_cons (NULL_TREE, $2.t, $1); }
	;

/* A typespec (but not a type qualifier).
   Once we have seen one of these in a declaration,
   if a typedef name appears then it is being redeclared.  */

typespec:
	  structsp
	| TYPESPEC  %prec EMPTY
		{ $$.t = $1; $$.new_type_flag = 0; }
	| complete_type_name
		{ $$.t = $1; $$.new_type_flag = 0; }
	| TYPEOF '(' expr ')'
		{ $$.t = finish_typeof ($3);
		  $$.new_type_flag = 0; }
	| TYPEOF '(' type_id ')'
		{ $$.t = groktypename ($3.t);
		  $$.new_type_flag = 0; }
	| SIGOF '(' expr ')'
		{ tree type = TREE_TYPE ($3);

                  $$.new_type_flag = 0;
		  if (IS_AGGR_TYPE (type))
		    {
		      sorry ("sigof type specifier");
		      $$.t = type;
		    }
		  else
		    {
		      error ("`sigof' applied to non-aggregate expression");
		      $$.t = error_mark_node;
		    }
		}
	| SIGOF '(' type_id ')'
		{ tree type = groktypename ($3.t);

                  $$.new_type_flag = 0;
		  if (IS_AGGR_TYPE (type))
		    {
		      sorry ("sigof type specifier");
		      $$.t = type;
		    }
		  else
		    {
		      error("`sigof' applied to non-aggregate type");
		      $$.t = error_mark_node;
		    }
		}
	;

/* A typespec that is a reserved word, or a type qualifier.  */

typespecqual_reserved:
	  TYPESPEC
		{ $$.t = $1; $$.new_type_flag = 0; }
	| CV_QUALIFIER
		{ $$.t = $1; $$.new_type_flag = 0; }
	| structsp
	;

initdecls:
	  initdcl0
	| initdecls ',' initdcl
            { check_multiple_declarators (); }
	;

notype_initdecls:
	  notype_initdcl0
	| notype_initdecls ',' initdcl
            { check_multiple_declarators (); }
	;

nomods_initdecls:
	  nomods_initdcl0
	| nomods_initdecls ',' initdcl
            { check_multiple_declarators (); }
	;

maybeasm:
	  /* empty */
		{ $$ = NULL_TREE; }
	| asm_keyword '(' string ')'
		{ if (TREE_CHAIN ($3)) $3 = combine_strings ($3); $$ = $3; }
	;

initdcl:
	  declarator maybeasm maybe_attribute '='
		{ $$ = start_decl ($1, current_declspecs, 1,
					  $3, prefix_attributes); }
	  init
/* Note how the declaration of the variable is in effect while its init is parsed! */
		{ cp_finish_decl ($5, $6, $2, 1, LOOKUP_ONLYCONVERTING); }
	| declarator maybeasm maybe_attribute
		{ $$ = start_decl ($1, current_declspecs, 0,
					  $3, prefix_attributes);
		  cp_finish_decl ($$, NULL_TREE, $2, 1, 0); }
	;

        /* This rule assumes a certain configuration of the parser stack.
	   In particular, $0, the element directly before the beginning of
	   this rule on the stack, must be a maybeasm.  $-1 must be a
	   declarator or notype_declarator.  And $-2 must be some declmods
	   or declspecs.  We can't move the maybeasm into this rule because
	   we need that reduce so we prefer fn.def1 when appropriate.  */
initdcl0_innards:
	  maybe_attribute '='
		{ $<itype>2 = parse_decl ($-1, $-2, 
					   $1, 1, &$$); }
          /* Note how the declaration of the variable is in effect
	     while its init is parsed! */ 
	  init
		{ cp_finish_decl ($3, $4, $0, 1,
				  LOOKUP_ONLYCONVERTING);
		  $$ = $<itype>2; }
	| maybe_attribute
		{ tree d;
		  $$ = parse_decl ($-1, $-2, $1, 0, &d);
		  cp_finish_decl (d, NULL_TREE, $0, 1, 0); }
  	;
  
initdcl0:
	  declarator maybeasm initdcl0_innards
            { $$ = $3; }
  
notype_initdcl0:
          notype_declarator maybeasm initdcl0_innards
            { $$ = $3; }
        ;
  
nomods_initdcl0:
          notype_declarator maybeasm
            { /* Set things up as initdcl0_innards expects.  */
	      $2 = $1; 
              $1 = NULL_TREE; }
          initdcl0_innards 
            {}
	| constructor_declarator maybeasm maybe_attribute
		{ tree d;
		  parse_decl($1, NULL_TREE, $3, 0, &d);
		  cp_finish_decl (d, NULL_TREE, $2, 1, 0); }
	;

/* the * rules are dummies to accept the Apollo extended syntax
   so that the header files compile.  */
maybe_attribute:
	  /* empty */
  		{ $$ = NULL_TREE; }
	| attributes
		{ $$ = $1; }
	;
 
attributes:
      attribute
		{ $$ = $1; }
	| attributes attribute
		{ $$ = chainon ($1, $2); }
	;

attribute:
      ATTRIBUTE '(' '(' attribute_list ')' ')'
		{ $$ = $4; }
	;

attribute_list:
      attrib
		{ $$ = $1; }
	| attribute_list ',' attrib
		{ $$ = chainon ($1, $3); }
	;
 
attrib:
	  /* empty */
		{ $$ = NULL_TREE; }
	| any_word
		{ $$ = build_tree_list ($1, NULL_TREE); }
	| any_word '(' IDENTIFIER ')'
		{ $$ = build_tree_list ($1, build_tree_list (NULL_TREE, $3)); }
	| any_word '(' IDENTIFIER ',' nonnull_exprlist ')'
		{ $$ = build_tree_list ($1, tree_cons (NULL_TREE, $3, $5)); }
	| any_word '(' nonnull_exprlist ')'
		{ $$ = build_tree_list ($1, $3); }
	;

/* This still leaves out most reserved keywords,
   shouldn't we include them?  */

any_word:
	  identifier
	| SCSPEC
	| TYPESPEC
	| CV_QUALIFIER
	;

/* A nonempty list of identifiers, including typenames.  */
identifiers_or_typenames:
	  identifier
		{ $$ = build_tree_list (NULL_TREE, $1); }
	| identifiers_or_typenames ',' identifier
		{ $$ = chainon ($1, build_tree_list (NULL_TREE, $3)); }
	;

maybe_init:
	  /* empty */  %prec EMPTY
		{ $$ = NULL_TREE; }
	| '=' init
		{ $$ = $2; }

/* If we are processing a template, we don't want to expand this
   initializer yet.  */

init:
	  expr_no_commas  %prec '='
	| '{' '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, NULL_TREE);
		  TREE_HAS_CONSTRUCTOR ($$) = 1; }
	| '{' initlist '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ($2));
		  TREE_HAS_CONSTRUCTOR ($$) = 1; }
	| '{' initlist ',' '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ($2));
		  TREE_HAS_CONSTRUCTOR ($$) = 1; }
	| error
		{ $$ = NULL_TREE; }
	;

/* This chain is built in reverse order,
   and put in forward order where initlist is used.  */
initlist:
	  init
		{ $$ = build_tree_list (NULL_TREE, $$); }
	| initlist ',' init
		{ $$ = expr_tree_cons (NULL_TREE, $3, $$); }
	/* These are for labeled elements.  */
	| '[' expr_no_commas ']' init
		{ $$ = build_expr_list ($2, $4); }
	| identifier ':' init
		{ $$ = build_expr_list ($$, $3); }
	| initlist ',' identifier ':' init
		{ $$ = expr_tree_cons ($3, $5, $$); }
	;

fn.defpen:
	PRE_PARSED_FUNCTION_DECL
		{ start_function (NULL_TREE, TREE_VALUE ($1),
				  NULL_TREE, 2);
		  reinit_parse_for_function (); }

pending_inline:
	  fn.defpen maybe_return_init ctor_initializer_opt compstmt_or_error
		{
		  int nested = (hack_decl_function_context
				(current_function_decl) != NULL_TREE);
		  finish_function (lineno, (int)$3 | 2, nested);
		  process_next_inline ($1);
		}
	| fn.defpen maybe_return_init function_try_block
		{ 
		  int nested = (hack_decl_function_context
				(current_function_decl) != NULL_TREE);
		  finish_function (lineno, (int)$3 | 2, nested); 
                  process_next_inline ($1);
		}
	| fn.defpen maybe_return_init error
		{ process_next_inline ($1); }
	;

pending_inlines:
	/* empty */
	| pending_inlines pending_inline eat_saved_input
	;

/* A regurgitated default argument.  The value of DEFARG_MARKER will be
   the TREE_LIST node for the parameter in question.  */
defarg_again:
	DEFARG_MARKER expr_no_commas END_OF_SAVED_INPUT
		{ replace_defarg ($1, $2); }
	| DEFARG_MARKER error END_OF_SAVED_INPUT
		{ replace_defarg ($1, error_mark_node); }

pending_defargs:
	  /* empty */ %prec EMPTY
	| pending_defargs defarg_again
		{ do_pending_defargs (); }
	| pending_defargs error
		{ do_pending_defargs (); }
	;

structsp:
	  ENUM identifier '{'
		{ $<itype>3 = suspend_momentary ();
		  $$ = current_enum_type;
		  current_enum_type = start_enum ($2); }
	  enumlist maybecomma_warn '}'
		{ TYPE_VALUES (current_enum_type) = $5;
		  $$.t = finish_enum (current_enum_type);
		  $$.new_type_flag = 1;
		  current_enum_type = $4;
		  resume_momentary ((int) $<itype>3);
		  check_for_missing_semicolon ($$.t); }
	| ENUM identifier '{' '}'
		{ $$.t = finish_enum (start_enum ($2));
		  $$.new_type_flag = 1;
		  check_for_missing_semicolon ($$.t); }
	| ENUM '{'
		{ $<itype>2 = suspend_momentary ();
		  $$ = current_enum_type;
		  current_enum_type = start_enum (make_anon_name ()); }
	  enumlist maybecomma_warn '}'
                { TYPE_VALUES (current_enum_type) = $4;
		  $$.t = finish_enum (current_enum_type);
		  $$.new_type_flag = 1;
		  current_enum_type = $3;
		  resume_momentary ((int) $<itype>1);
		  check_for_missing_semicolon ($$.t); }
	| ENUM '{' '}'
		{ $$.t = finish_enum (start_enum (make_anon_name()));
		  $$.new_type_flag = 1;
		  check_for_missing_semicolon ($$.t); }
	| ENUM identifier
		{ $$.t = xref_tag (enum_type_node, $2, 1); 
		  $$.new_type_flag = 0; }
	| ENUM complex_type_name
		{ $$.t = xref_tag (enum_type_node, $2, 1); 
		  $$.new_type_flag = 0; }
	| TYPENAME_KEYWORD typename_sub
		{ $$.t = $2;
		  $$.new_type_flag = 0; 
		  if (!processing_template_decl)
		    cp_pedwarn ("using `typename' outside of template"); }
	/* C++ extensions, merged with C to avoid shift/reduce conflicts */
	| class_head '{'
                { $1.t = begin_class_definition ($1.t); }
          opt.component_decl_list '}' maybe_attribute
		{ 
		  int semi;

		  if (yychar == YYEMPTY)
		    yychar = YYLEX;
		  semi = yychar == ';';

		  $$ = finish_class_definition ($1.t, $6, semi,
						       $1.new_type_flag); 
		}
	  pending_defargs
                {
		  begin_inline_definitions ();
		}
	  pending_inlines
                {
		  finish_inline_definitions ();
		  $$.t = $7;
		  $$.new_type_flag = 1; 
		}
	| class_head  %prec EMPTY
		{
		  if ($1.new_type_flag)
		    pop_scope (CP_DECL_CONTEXT (TYPE_MAIN_DECL ($1.t)));
		  $$.new_type_flag = 0;
		  if (TYPE_BINFO ($1.t) == NULL_TREE)
		    {
		      cp_error ("%T is not a class type", $1.t);
		      $$.t = error_mark_node;
		    } 
		  else
		    {
		      $$.t = $1.t;
		      /* struct B: public A; is not accepted by the WP grammar.  */
		      if (TYPE_BINFO_BASETYPES ($$.t) && !TYPE_SIZE ($$.t)
			  && ! TYPE_BEING_DEFINED ($$.t))
			cp_error ("base clause without member specification for `%#T'",
				  $$.t);
		    }
		}
	;

maybecomma:
	  /* empty */
	| ','
	;

maybecomma_warn:
	  /* empty */
	| ','
		{ if (pedantic && !in_system_header)
		    pedwarn ("comma at end of enumerator list"); }
	;

aggr:
	  AGGR
	| aggr SCSPEC
		{ error ("storage class specifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ($2)); }
	| aggr TYPESPEC
		{ error ("type specifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ($2)); }
	| aggr CV_QUALIFIER
		{ error ("type qualifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ($2)); }
	| aggr AGGR
		{ error ("no body nor ';' separates two class, struct or union declarations"); }
	| aggr attributes
		{ $$ = build_decl_list ($2, $1); }
	;

named_class_head_sans_basetype:
	  aggr identifier
		{ 
		  current_aggr = $1; 
		  $$ = $2; 
		}
	;

named_class_head_sans_basetype_defn:
	  aggr identifier_defn  %prec EMPTY
		{ current_aggr = $$; $$ = $2; }
	| named_class_head_sans_basetype '{'
		{ yyungetc ('{', 1); }
	| named_class_head_sans_basetype ':'
		{ yyungetc (':', 1); }
	;

named_complex_class_head_sans_basetype:
	  aggr nested_name_specifier identifier
		{
		  current_aggr = $1;
		  $$.t = handle_class_head ($1, $2, $3);
		  $$.new_type_flag = 1;
		}
	| aggr global_scope nested_name_specifier identifier
		{
		  current_aggr = $1;
		  $$.t = handle_class_head ($1, $3, $4);
		  $$.new_type_flag = 1;
		}
	| aggr global_scope identifier
		{
		  current_aggr = $1;
		  $$.t = handle_class_head ($1, NULL_TREE, $3);
		  $$.new_type_flag = 1;
		}
	| aggr apparent_template_type
		{ 
		  current_aggr = $1; 
		  $$.t = $2;
		  $$.new_type_flag = 0;
		}
	| aggr nested_name_specifier apparent_template_type
		{ 
		  current_aggr = $1; 
		  $$.t = $3;
		  if (CP_DECL_CONTEXT ($$.t))
		    push_scope (CP_DECL_CONTEXT ($$.t));
		  $$.new_type_flag = 1;
		}
	;

named_class_head:
	  named_class_head_sans_basetype  %prec EMPTY
		{ 
		  $$.t = xref_tag (current_aggr, $1, 1); 
		  $$.new_type_flag = 0;
		}
	| named_class_head_sans_basetype_defn 
                { $$ = xref_tag (current_aggr, $1, 0); }
          /* Class name is unqualified, so we look for base classes
             in the current scope.  */
          maybe_base_class_list  %prec EMPTY
		{ 
		  $$.t = $2;
		  $$.new_type_flag = 0;
		  if ($3)
                    xref_basetypes (current_aggr, $1, $2, $3); 
		}
	| named_complex_class_head_sans_basetype 
	  maybe_base_class_list
		{ 
		  if ($1.t != error_mark_node)
		    {
		      $$.t = TREE_TYPE ($1.t);
		      $$.new_type_flag = $1.new_type_flag;
		      if (current_aggr == union_type_node
			  && TREE_CODE ($$.t) != UNION_TYPE)
			cp_pedwarn ("`union' tag used in declaring `%#T'", 
				    $$.t);
		      else if (TREE_CODE ($$.t) == UNION_TYPE
			       && current_aggr != union_type_node)
			cp_pedwarn ("non-`union' tag used in declaring `%#T'", $$);
		      else if (TREE_CODE ($$.t) == RECORD_TYPE)
			/* We might be specializing a template with a different
			   class-key; deal.  */
			CLASSTYPE_DECLARED_CLASS ($$.t) 
			  = (current_aggr == class_type_node);
		      if ($2)
			{
			  maybe_process_partial_specialization ($$.t);
			  xref_basetypes (current_aggr, $1.t, $$.t, $2); 
			}
		    }
		}
	;

unnamed_class_head:
	  aggr '{'
		{ $$ = xref_tag ($$, make_anon_name (), 0);
		  yyungetc ('{', 1); }
	;

/* The tree output of this nonterminal a declarationf or the type
   named.  If NEW_TYPE_FLAG is set, then the name used in this
   class-head was explicitly qualified, e.g.:  `struct X::Y'.  We have
   already called push_scope for X.  */
class_head:
	  unnamed_class_head
                {
		  $$.t = $1;
		  $$.new_type_flag = 0;
		}
	| named_class_head
	;

maybe_base_class_list:
	  /* empty */  %prec EMPTY
		{ $$ = NULL_TREE; }
	| ':' see_typename  %prec EMPTY
		{ yyungetc(':', 1); $$ = NULL_TREE; }
	| ':' see_typename base_class_list  %prec EMPTY
		{ $$ = $3; }
	;

base_class_list:
	  base_class
	| base_class_list ',' see_typename base_class
		{ $$ = chainon ($$, $4); }
	;

base_class:
	  base_class.1
		{ $$ = finish_base_specifier (access_default_node, $1,
					      current_aggr 
					      == signature_type_node); }
	| base_class_access_list see_typename base_class.1
                { $$ = finish_base_specifier ($1, $3, 
					      current_aggr 
					      == signature_type_node); } 
	;

base_class.1:
	  typename_sub
		{ if ($$ != error_mark_node) $$ = TYPE_MAIN_DECL ($1); }
	| nonnested_type
	| SIGOF '(' expr ')'
		{
		  if (current_aggr == signature_type_node)
		    {
		      if (IS_AGGR_TYPE (TREE_TYPE ($3)))
			{
			  sorry ("`sigof' as base signature specifier");
			  $$ = TREE_TYPE ($3);
			}
		      else
			{
			  error ("`sigof' applied to non-aggregate expression");
			  $$ = error_mark_node;
			}
		    }
		  else
		    {
		      error ("`sigof' in struct or class declaration");
		      $$ = error_mark_node;
		    }
		}
	| SIGOF '(' type_id ')'
		{
		  if (current_aggr == signature_type_node)
		    {
		      if (IS_AGGR_TYPE (groktypename ($3.t)))
			{
			  sorry ("`sigof' as base signature specifier");
			  $$ = groktypename ($3.t);
			}
		      else
			{
			  error ("`sigof' applied to non-aggregate expression");
			  $$ = error_mark_node;
			}
		    }
		  else
		    {
		      error ("`sigof' in struct or class declaration");
		      $$ = error_mark_node;
		    }
		}
	;

base_class_access_list:
	  VISSPEC see_typename
	| SCSPEC see_typename
		{ if ($1 != ridpointers[(int)RID_VIRTUAL])
		    cp_error ("`%D' access", $1);
		  $$ = access_default_virtual_node; }
	| base_class_access_list VISSPEC see_typename
		{
		  if ($1 != access_default_virtual_node)
		    error ("multiple access specifiers");
		  else if ($2 == access_public_node)
		    $$ = access_public_virtual_node;
		  else if ($2 == access_protected_node)
		    $$ = access_protected_virtual_node;
		  else /* $2 == access_private_node */
		    $$ = access_private_virtual_node;
		}
	| base_class_access_list SCSPEC see_typename
		{ if ($2 != ridpointers[(int)RID_VIRTUAL])
		    cp_error ("`%D' access", $2);
		  else if ($$ == access_public_node)
		    $$ = access_public_virtual_node;
		  else if ($$ == access_protected_node)
		    $$ = access_protected_virtual_node;
		  else if ($$ == access_private_node)
		    $$ = access_private_virtual_node;
		  else
		    error ("multiple `virtual' specifiers");
		}
	;

opt.component_decl_list:
	| component_decl_list
	| opt.component_decl_list access_specifier component_decl_list
	| opt.component_decl_list access_specifier 
	;

access_specifier:
	  VISSPEC ':'
                {
		  if (current_aggr == signature_type_node)
		    {
		      error ("access specifier not allowed in signature");
		      $1 = access_public_node;
		    }

		  current_access_specifier = $1;
                }
	;

/* Note: we no longer warn about the semicolon after a component_decl_list.
   ARM $9.2 says that the semicolon is optional, and therefore allowed.  */
component_decl_list:
	  component_decl
	| component_decl_list component_decl
	;

component_decl:
	  component_decl_1 ';'
	| component_decl_1 '}'
	/* C++: handle constructors, destructors and inline functions */
	/* note that INLINE is like a TYPESPEC */
	| fn.def2 ':' /* base_init compstmt */
	| fn.def2 TRY /* base_init compstmt */
	| fn.def2 RETURN_KEYWORD /* base_init compstmt */
	| fn.def2 '{' /* nodecls compstmt */
	| ';'
	| extension component_decl
        | template_header component_decl
	| template_header typed_declspecs ';'
	;

component_decl_1:
	/* Do not add a "typed_declspecs declarator" rule here for
	   speed; we need to call grok_x_components for enums, so the
	   speedup would be insignificant.  */
	  typed_declspecs components
		{
		  /* Most of the productions for component_decl only
		     allow the creation of one new member, so we call
		     finish_member_declaration in component_decl_list.
		     For this rule and the next, however, there can be
		     more than one member, e.g.:

		       int i, j;

		     and we need the first member to be fully
		     registered before the second is processed.
		     Therefore, the rules for components take care of
		     this processing.  To avoid registering the
		     components more than once, we send NULL_TREE up
		     here; that lets finish_member_declaration know
		     that there is nothing to do.  */
		  if (!$2)
		    grok_x_components ($1.t);
		  $$ = NULL_TREE;
		}
	| declmods notype_components
		{ 
		  if (!$2)
		    grok_x_components ($1);
		  $$ = NULL_TREE; 
		}
	| notype_declarator maybeasm maybe_attribute maybe_init
		{ $$ = grokfield ($$, NULL_TREE, $4, $2,
				  build_tree_list ($3, NULL_TREE)); }
	| constructor_declarator maybeasm maybe_attribute maybe_init
		{ $$ = grokfield ($$, NULL_TREE, $4, $2,
				  build_tree_list ($3, NULL_TREE)); }
	| ':' expr_no_commas
		{ $$ = grokbitfield (NULL_TREE, NULL_TREE, $2); }
	| error
		{ $$ = NULL_TREE; }

	/* These rules introduce a reduce/reduce conflict; in
		typedef int foo, bar;
		class A {
		  foo (bar);
		};
	   should "A::foo" be declared as a function or "A::bar" as a data
	   member? In other words, is "bar" an after_type_declarator or a
	   parmlist? */
	| declmods component_constructor_declarator maybeasm maybe_attribute maybe_init
		{ tree specs, attrs;
		  split_specs_attrs ($1, &specs, &attrs);
		  $$ = grokfield ($2, specs, $5, $3,
				  build_tree_list ($4, attrs)); }
	| component_constructor_declarator maybeasm maybe_attribute maybe_init
		{ $$ = grokfield ($$, NULL_TREE, $4, $2,
				  build_tree_list ($3, NULL_TREE)); }
	| using_decl
		{ $$ = do_class_using_decl ($1); }

/* The case of exactly one component is handled directly by component_decl.  */
/* ??? Huh? ^^^ */
components:
	  /* empty: possibly anonymous */
                { $$ = 0; }
	| component_declarator0
                { 
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    $1 = finish_member_template_decl ($1);
		  finish_member_declaration ($1); 
		  $$ = 1;
		}
	| components ',' component_declarator
                { 
		  check_multiple_declarators ();
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    $3 = finish_member_template_decl ($3);
		  finish_member_declaration ($3);
		  $$ = 2;
		}
	;

notype_components:
	  /* empty: possibly anonymous */
                { $$ = 0; }
	| notype_component_declarator0
                { 
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    $1 = finish_member_template_decl ($1);
		  finish_member_declaration ($1);
		  $$ = 1;
		}
	| notype_components ',' notype_component_declarator
                { 
		  check_multiple_declarators ();
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    $3 = finish_member_template_decl ($3);
		  finish_member_declaration ($3); 
		  $$ = 2;
		}
	;

component_declarator0:
	  after_type_component_declarator0
	| notype_component_declarator0
	;

component_declarator:
	  after_type_component_declarator
	| notype_component_declarator
	;

after_type_component_declarator0:
	  after_type_declarator maybeasm maybe_attribute maybe_init
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokfield ($$, current_declspecs, $4, $2,
				  build_tree_list ($3, prefix_attributes)); }
	| TYPENAME ':' expr_no_commas maybe_attribute
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokbitfield ($$, current_declspecs, $3);
		  cplus_decl_attributes ($$, $4, prefix_attributes); }
	;

notype_component_declarator0:
	  notype_declarator maybeasm maybe_attribute maybe_init
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokfield ($$, current_declspecs, $4, $2,
				  build_tree_list ($3, prefix_attributes)); }
	| constructor_declarator maybeasm maybe_attribute maybe_init
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokfield ($$, current_declspecs, $4, $2,
				  build_tree_list ($3, prefix_attributes)); }
	| IDENTIFIER ':' expr_no_commas maybe_attribute
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokbitfield ($$, current_declspecs, $3);
		  cplus_decl_attributes ($$, $4, prefix_attributes); }
	| ':' expr_no_commas maybe_attribute
		{ split_specs_attrs ($0, &current_declspecs,
				     &prefix_attributes);
		  $0 = current_declspecs;
		  $$ = grokbitfield (NULL_TREE, current_declspecs, $2);
		  cplus_decl_attributes ($$, $3, prefix_attributes); }
	;

after_type_component_declarator:
	  after_type_declarator maybeasm maybe_attribute maybe_init
		{ $$ = grokfield ($$, current_declspecs, $4, $2,
				  build_tree_list ($3, prefix_attributes)); }
	| TYPENAME ':' expr_no_commas maybe_attribute
		{ $$ = grokbitfield ($$, current_declspecs, $3);
		  cplus_decl_attributes ($$, $4, prefix_attributes); }
	;

notype_component_declarator:
	  notype_declarator maybeasm maybe_attribute maybe_init
		{ $$ = grokfield ($$, current_declspecs, $4, $2,
				  build_tree_list ($3, prefix_attributes)); }
	| IDENTIFIER ':' expr_no_commas maybe_attribute
		{ $$ = grokbitfield ($$, current_declspecs, $3);
		  cplus_decl_attributes ($$, $4, prefix_attributes); }
	| ':' expr_no_commas maybe_attribute
		{ $$ = grokbitfield (NULL_TREE, current_declspecs, $2);
		  cplus_decl_attributes ($$, $3, prefix_attributes); }
	;

/* We chain the enumerators in reverse order.
   Because of the way enums are built, the order is
   insignificant.  Take advantage of this fact.  */

enumlist:
	  enumerator
	| enumlist ',' enumerator
		{ TREE_CHAIN ($3) = $$; $$ = $3; }
	;

enumerator:
	  identifier
		{ $$ = build_enumerator ($$, NULL_TREE, current_enum_type); }
	| identifier '=' expr_no_commas
		{ $$ = build_enumerator ($$, $3, current_enum_type); }
	;

/* ANSI new-type-id (5.3.4) */
new_type_id:
	  type_specifier_seq new_declarator
		{ $$.t = build_decl_list ($1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| type_specifier_seq  %prec EMPTY
		{ $$.t = build_decl_list ($1.t, NULL_TREE); 
		  $$.new_type_flag = $1.new_type_flag; }
	/* GNU extension to allow arrays of arbitrary types with
	   non-constant dimension.  For the use of begin_new_placement
	   here, see the comments in unary_expr above.  */
	| '(' .begin_new_placement type_id .finish_new_placement
	      '[' expr ']'
		{
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids array dimensions with parenthesized type in new");
		  $$.t = build_parse_node (ARRAY_REF, TREE_VALUE ($3.t), $6);
		  $$.t = build_decl_list (TREE_PURPOSE ($3.t), $$.t);
		  $$.new_type_flag = $3.new_type_flag;
		}
	;

cv_qualifiers:
	  /* empty */  %prec EMPTY
		{ $$ = NULL_TREE; }
	| cv_qualifiers CV_QUALIFIER
		{ $$ = decl_tree_cons (NULL_TREE, $2, $$); }
	;

nonempty_cv_qualifiers:
	  CV_QUALIFIER
		{ $$.t = hash_tree_cons (NULL_TREE, $1, NULL_TREE);
		  $$.new_type_flag = 0; }
	| nonempty_cv_qualifiers CV_QUALIFIER
		{ $$.t = hash_tree_cons (NULL_TREE, $2, $1.t); 
		  $$.new_type_flag = $1.new_type_flag; }
	;

/* These rules must follow the rules for function declarations
   and component declarations.  That way, longer rules are preferred.  */

suspend_mom:
	  /* empty */
		{ $<itype>$ = suspend_momentary (); } 

/* An expression which will not live on the momentary obstack.  */
nonmomentary_expr:
	  suspend_mom expr
		{ resume_momentary ((int) $<itype>1); $$ = $2; }
	;

/* An expression which will not live on the momentary obstack.  */
maybe_parmlist:
	  suspend_mom '(' nonnull_exprlist ')'
		{ resume_momentary ((int) $<itype>1); $$ = $3; }
	| suspend_mom '(' parmlist ')'
		{ resume_momentary ((int) $<itype>1); $$ = $3; }
	| suspend_mom LEFT_RIGHT
		{ resume_momentary ((int) $<itype>1); $$ = empty_parms (); }
	| suspend_mom '(' error ')'
		{ resume_momentary ((int) $<itype>1); $$ = NULL_TREE; }
	;

/* A declarator that is allowed only after an explicit typespec.  */

after_type_declarator_intern:
	  after_type_declarator
	| attributes after_type_declarator
                {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  $$ = decl_tree_cons ($1, $2, NULL_TREE);
		}
	;

/* may all be followed by prec '.' */
after_type_declarator:
	  '*' nonempty_cv_qualifiers after_type_declarator_intern  %prec UNARY
		{ $$ = make_pointer_declarator ($2.t, $3); }
	| '&' nonempty_cv_qualifiers after_type_declarator_intern  %prec UNARY
		{ $$ = make_reference_declarator ($2.t, $3); }
	| '*' after_type_declarator_intern  %prec UNARY
		{ $$ = make_pointer_declarator (NULL_TREE, $2); }
	| '&' after_type_declarator_intern  %prec UNARY
		{ $$ = make_reference_declarator (NULL_TREE, $2); }
	| ptr_to_mem cv_qualifiers after_type_declarator_intern
		{ tree arg = make_pointer_declarator ($2, $3);
		  $$ = build_parse_node (SCOPE_REF, $1, arg);
		}
	| direct_after_type_declarator
	;

direct_after_type_declarator:
	  direct_after_type_declarator maybe_parmlist cv_qualifiers exception_specification_opt  %prec '.'
		{ $$ = make_call_declarator ($$, $2, $3, $4); }
	| direct_after_type_declarator '[' nonmomentary_expr ']'
		{ $$ = build_parse_node (ARRAY_REF, $$, $3); }
	| direct_after_type_declarator '[' ']'
		{ $$ = build_parse_node (ARRAY_REF, $$, NULL_TREE); }
	| '(' after_type_declarator_intern ')'
		{ $$ = $2; }
	| nested_name_specifier type_name  %prec EMPTY
		{ push_nested_class ($1, 3);
		  $$ = build_parse_node (SCOPE_REF, $$, $2);
		  TREE_COMPLEXITY ($$) = current_class_depth; }
	| type_name  %prec EMPTY
	;

nonnested_type:
	  type_name  %prec EMPTY
		{
		  if (TREE_CODE ($1) == IDENTIFIER_NODE)
		    {
		      $$ = lookup_name ($1, 1);
		      maybe_note_name_used_in_class ($1, $$);
		    }
		  else
		    $$ = $1;
		}
	| global_scope type_name
		{
		  if (TREE_CODE ($2) == IDENTIFIER_NODE)
		    $$ = IDENTIFIER_GLOBAL_VALUE ($2);
		  else
		    $$ = $2;
		  got_scope = NULL_TREE;
		}
	;

complete_type_name:
	  nonnested_type
	| nested_type
	| global_scope nested_type
		{ $$ = $2; }
	;

nested_type:
	  nested_name_specifier type_name  %prec EMPTY
		{ $$ = get_type_decl ($2); }
	;

/* A declarator allowed whether or not there has been
   an explicit typespec.  These cannot redeclare a typedef-name.  */

notype_declarator_intern:
	  notype_declarator
	| attributes notype_declarator
                {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  $$ = decl_tree_cons ($1, $2, NULL_TREE);
		}
	;
	
notype_declarator:
	  '*' nonempty_cv_qualifiers notype_declarator_intern  %prec UNARY
		{ $$ = make_pointer_declarator ($2.t, $3); }
	| '&' nonempty_cv_qualifiers notype_declarator_intern  %prec UNARY
		{ $$ = make_reference_declarator ($2.t, $3); }
	| '*' notype_declarator_intern  %prec UNARY
		{ $$ = make_pointer_declarator (NULL_TREE, $2); }
	| '&' notype_declarator_intern  %prec UNARY
		{ $$ = make_reference_declarator (NULL_TREE, $2); }
	| ptr_to_mem cv_qualifiers notype_declarator_intern
		{ tree arg = make_pointer_declarator ($2, $3);
		  $$ = build_parse_node (SCOPE_REF, $1, arg);
		}
	| direct_notype_declarator
	;

complex_notype_declarator:
	  '*' nonempty_cv_qualifiers notype_declarator_intern  %prec UNARY
		{ $$ = make_pointer_declarator ($2.t, $3); }
	| '&' nonempty_cv_qualifiers notype_declarator_intern  %prec UNARY
		{ $$ = make_reference_declarator ($2.t, $3); }
	| '*' complex_notype_declarator  %prec UNARY
		{ $$ = make_pointer_declarator (NULL_TREE, $2); }
	| '&' complex_notype_declarator  %prec UNARY
		{ $$ = make_reference_declarator (NULL_TREE, $2); }
	| ptr_to_mem cv_qualifiers notype_declarator_intern
		{ tree arg = make_pointer_declarator ($2, $3);
		  $$ = build_parse_node (SCOPE_REF, $1, arg);
		}
	| complex_direct_notype_declarator
	;

complex_direct_notype_declarator:
	  direct_notype_declarator maybe_parmlist cv_qualifiers exception_specification_opt  %prec '.'
		{ $$ = make_call_declarator ($$, $2, $3, $4); }
	| '(' complex_notype_declarator ')'
		{ $$ = $2; }
	| direct_notype_declarator '[' nonmomentary_expr ']'
		{ $$ = build_parse_node (ARRAY_REF, $$, $3); }
	| direct_notype_declarator '[' ']'
		{ $$ = build_parse_node (ARRAY_REF, $$, NULL_TREE); }
	| notype_qualified_id
                { enter_scope_of ($1); }
        | nested_name_specifier notype_template_declarator
                { got_scope = NULL_TREE;
		  $$ = build_parse_node (SCOPE_REF, $1, $2);
		  enter_scope_of ($$);
		}
	;

qualified_id:
	  nested_name_specifier unqualified_id
		{ got_scope = NULL_TREE;
		  $$ = build_parse_node (SCOPE_REF, $$, $2); }
        | nested_name_specifier object_template_id
                { got_scope = NULL_TREE;
 		  $$ = build_parse_node (SCOPE_REF, $1, $2); }
	;

notype_qualified_id:
	  nested_name_specifier notype_unqualified_id
		{ got_scope = NULL_TREE;
		  $$ = build_parse_node (SCOPE_REF, $$, $2); }
        | nested_name_specifier object_template_id
                { got_scope = NULL_TREE;
		  $$ = build_parse_node (SCOPE_REF, $1, $2); }
	;

overqualified_id:
	  notype_qualified_id
	| global_scope notype_qualified_id
		{ $$ = $2; }
	;

functional_cast:
	  typespec '(' nonnull_exprlist ')'
		{ $$ = build_functional_cast ($1.t, $3); }
	| typespec '(' expr_or_declarator_intern ')'
		{ $$ = reparse_decl_as_expr ($1.t, $3); }
	| typespec fcast_or_absdcl  %prec EMPTY
		{ $$ = reparse_absdcl_as_expr ($1.t, $2); }
	;
type_name:
	  TYPENAME
	| SELFNAME
	| template_type  %prec EMPTY
	;

nested_name_specifier:
	  nested_name_specifier_1
	| nested_name_specifier nested_name_specifier_1
		{ $$ = $2; }
	| nested_name_specifier TEMPLATE explicit_template_type SCOPE
		{ got_scope = $$ = make_typename_type ($1, $3); }
	;

/* Why the @#$%^& do type_name and notype_identifier need to be expanded
   inline here?!?  (jason) */
nested_name_specifier_1:
	  TYPENAME SCOPE
		{
		  if (TREE_CODE ($1) == IDENTIFIER_NODE)
		    {
		      $$ = lastiddecl;
		      maybe_note_name_used_in_class ($1, $$);
		    }
		  got_scope = $$ =
		    complete_type (TYPE_MAIN_VARIANT (TREE_TYPE ($$)));
		}
	| SELFNAME SCOPE
		{
		  if (TREE_CODE ($1) == IDENTIFIER_NODE)
		    $$ = lastiddecl;
		  got_scope = $$ = TREE_TYPE ($$);
		}
	| NSNAME SCOPE
		{
		  if (TREE_CODE ($$) == IDENTIFIER_NODE)
		    $$ = lastiddecl;
		  got_scope = $$;
		}
	| template_type SCOPE
		{ got_scope = $$ = complete_type (TREE_TYPE ($1)); }
/* 	These break 'const i;'
	| IDENTIFIER SCOPE
		{
		 failed_scope:
		  cp_error ("`%D' is not an aggregate typedef", 
			    lastiddecl ? lastiddecl : $$);
		  $$ = error_mark_node;
		}
	| PTYPENAME SCOPE
		{ goto failed_scope; } */
	;

typename_sub:
	  typename_sub0
	| global_scope typename_sub0
		{ $$ = $2; }
	;

typename_sub0:
	  typename_sub1 identifier %prec EMPTY
	| typename_sub1 template_type %prec EMPTY
	| typename_sub1 explicit_template_type %prec EMPTY
	| typename_sub1 TEMPLATE explicit_template_type %prec EMPTY
	;

typename_sub1:
	  typename_sub2
		{
		  if (TREE_CODE ($1) == IDENTIFIER_NODE)
		    cp_error ("`%T' is not a class or namespace", $1);
		}
	| typename_sub1 typename_sub2
		{
		  if (TREE_CODE_CLASS (TREE_CODE ($1)) == 't')
		    $$ = make_typename_type ($1, $2);
		  else if (TREE_CODE ($2) == IDENTIFIER_NODE)
		    cp_error ("`%T' is not a class or namespace", $2);
		  else
		    {
		      $$ = $2;
		      if (TREE_CODE ($$) == TYPE_DECL)
			$$ = TREE_TYPE ($$);
		    }
		}
	| typename_sub1 explicit_template_type SCOPE
		{ got_scope = $$ = make_typename_type ($1, $2); }
	| typename_sub1 TEMPLATE explicit_template_type SCOPE
		{ got_scope = $$ = make_typename_type ($1, $3); }
	;

typename_sub2:
	  TYPENAME SCOPE
		{
		  if (TREE_CODE ($1) != IDENTIFIER_NODE)
		    $1 = lastiddecl;

		  /* Retrieve the type for the identifier, which might involve
		     some computation. */
		  got_scope = $$ = complete_type (IDENTIFIER_TYPE_VALUE ($1));

		  if ($$ == error_mark_node)
		    cp_error ("`%T' is not a class or namespace", $1);
		}
	| SELFNAME SCOPE
		{
		  if (TREE_CODE ($1) != IDENTIFIER_NODE)
		    $$ = lastiddecl;
		  got_scope = $$ = complete_type (TREE_TYPE ($$));
		}
	| template_type SCOPE
		{ got_scope = $$ = complete_type (TREE_TYPE ($$)); }
	| PTYPENAME SCOPE
	| IDENTIFIER SCOPE
	| NSNAME SCOPE
		{
		  if (TREE_CODE ($$) == IDENTIFIER_NODE)
		    $$ = lastiddecl;
		  got_scope = $$;
		}
	;

explicit_template_type:
	  identifier '<' template_arg_list_opt '>'
	;

complex_type_name:
	  global_scope type_name
	| nested_type
	| global_scope nested_type
		{ $$ = $2; }
	;

ptr_to_mem:
	  nested_name_specifier '*'
	| global_scope nested_name_specifier '*'
	;

/* All uses of explicit global scope must go through this nonterminal so
   that got_scope will be set before yylex is called to get the next token.  */
global_scope:
	  SCOPE
	;

/* ANSI new-declarator (5.3.4) */
new_declarator:
	  '*' cv_qualifiers new_declarator
	| '*' cv_qualifiers  %prec EMPTY
	| '&' cv_qualifiers new_declarator  %prec EMPTY
	| '&' cv_qualifiers  %prec EMPTY
	| ptr_to_mem cv_qualifiers  %prec EMPTY
	| ptr_to_mem cv_qualifiers new_declarator
	| direct_new_declarator  %prec EMPTY
	;

/* ANSI direct-new-declarator (5.3.4) */
direct_new_declarator:
	  '[' expr ']'
	| direct_new_declarator '[' nonmomentary_expr ']'
	;

absdcl_intern:
	  absdcl
	| attributes absdcl
	;
	
/* ANSI abstract-declarator (8.1) */
absdcl:
	  '*' nonempty_cv_qualifiers absdcl_intern
	| '*' absdcl_intern
	| '*' nonempty_cv_qualifiers  %prec EMPTY
	| '*'  %prec EMPTY
	| '&' nonempty_cv_qualifiers absdcl_intern
	| '&' absdcl_intern
	| '&' nonempty_cv_qualifiers  %prec EMPTY
	| '&'  %prec EMPTY
	| ptr_to_mem cv_qualifiers  %prec EMPTY
	| ptr_to_mem cv_qualifiers absdcl_intern
	| direct_abstract_declarator  %prec EMPTY
	;

/* ANSI direct-abstract-declarator (8.1) */
direct_abstract_declarator:
	  '(' absdcl_intern ')'
	  /* `(typedef)1' is `int'.  */
	| PAREN_STAR_PAREN
	| direct_abstract_declarator '(' parmlist ')' cv_qualifiers exception_specification_opt  %prec '.'
	| direct_abstract_declarator LEFT_RIGHT cv_qualifiers exception_specification_opt  %prec '.'
	| direct_abstract_declarator '[' nonmomentary_expr ']'  %prec '.'
	| direct_abstract_declarator '[' ']'  %prec '.'
	| '(' complex_parmlist ')' cv_qualifiers exception_specification_opt  %prec '.'
	| regcast_or_absdcl cv_qualifiers exception_specification_opt  %prec '.'
	| fcast_or_absdcl cv_qualifiers exception_specification_opt  %prec '.'
	| '[' nonmomentary_expr ']'  %prec '.'
	| '[' ']'  %prec '.'
	;

/* For C++, decls and stmts can be intermixed, so we don't need to
   have a special rule that won't start parsing the stmt section
   until we have a stmt that parses without errors.  */

stmts:
	  stmt
	| errstmt
	| stmts stmt
	| stmts errstmt
	;

errstmt:
	  error ';'
	;

/* Read zero or more forward-declarations for labels
   that nested functions can jump to.  */
maybe_label_decls:
	  /* empty */
	| label_decls
	;

label_decls:
	  label_decl
	| label_decls label_decl
	;

label_decl:
	  LABEL identifiers_or_typenames ';'
		{ tree link;
		  for (link = $2; link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
	;

/* This is the body of a function definition.
   It causes syntax errors to ignore to the next openbrace.  */
compstmt_or_error:
	  compstmt
		{}
	| error compstmt
	;

compstmt:
	  '{'
                { $$ = begin_compound_stmt (0); }
	  compstmtend 
                { $$ = finish_compound_stmt (0, $2); }
	;

simple_if:
	  IF
		{
		  $$ = begin_if_stmt ();
		  cond_stmt_keyword = "if";
		}
            paren_cond_or_null
                { finish_if_stmt_cond ($3, $2); }
	    implicitly_scoped_stmt
                { $$ = finish_then_clause ($2); }
	;

implicitly_scoped_stmt:
	  compstmt
	|       { $$ = begin_compound_stmt (0); }
	  simple_stmt 
                { $$ = finish_compound_stmt (0, $1); }
	;

stmt:
	  compstmt
                {}
	| simple_stmt
	;

simple_stmt:
	  decl
		{ finish_stmt (); }
	| expr ';'
                { finish_expr_stmt ($1); }
	| simple_if ELSE
                { begin_else_clause (); }
	  implicitly_scoped_stmt
                { 
		  finish_else_clause ($1); 
		  finish_if_stmt ();
		}
	| simple_if  %prec IF
                { finish_if_stmt (); }
	| WHILE
		{
		  $$ = begin_while_stmt ();
		  cond_stmt_keyword = "while";
		}
	  paren_cond_or_null
                { finish_while_stmt_cond ($3, $2); }
	  already_scoped_stmt
                { finish_while_stmt ($2); }
	| DO
                { $$ = begin_do_stmt (); }
	  implicitly_scoped_stmt WHILE
		{
		  finish_do_body ($2);
		  cond_stmt_keyword = "do";
		}
	  paren_expr_or_null ';'
                { finish_do_stmt ($6, $2); }
	| FOR
                { $$ = begin_for_stmt (); }
	  '(' for.init.statement
                { finish_for_init_stmt ($2); }
	  xcond ';'
                { finish_for_cond ($6, $2); }
	  xexpr ')'
                { finish_for_expr ($9, $2); }
	  already_scoped_stmt
                { finish_for_stmt ($9, $2); }
	| SWITCH 
                { begin_switch_stmt (); }
	    '(' condition ')'
                { $$ = finish_switch_cond ($4); }
	  implicitly_scoped_stmt
                { finish_switch_stmt ($4, $6); }
	| CASE expr_no_commas ':'
                { finish_case_label ($2, NULL_TREE); }
	  stmt
	| CASE expr_no_commas ELLIPSIS expr_no_commas ':'
                { finish_case_label ($2, $4); }
	  stmt
	| DEFAULT ':'
		{ finish_case_label (NULL_TREE, NULL_TREE); }
	  stmt
	| BREAK ';'
                { finish_break_stmt (); }
	| CONTINUE ';'
                { finish_continue_stmt (); }
	| RETURN_KEYWORD ';'
                { finish_return_stmt (NULL_TREE); }
	| RETURN_KEYWORD expr ';'
                { finish_return_stmt ($2); }
	| asm_keyword maybe_cv_qualifier '(' string ')' ';'
		{ 
		  finish_asm_stmt ($2, $4, NULL_TREE, NULL_TREE,
				   NULL_TREE); 
		}
	/* This is the case with just output operands.  */
	| asm_keyword maybe_cv_qualifier '(' string ':' asm_operands ')' ';'
		{ 
		  finish_asm_stmt ($2, $4, $6, NULL_TREE,
				   NULL_TREE); 
		}
	/* This is the case with input operands as well.  */
	| asm_keyword maybe_cv_qualifier '(' string ':' asm_operands ':' asm_operands ')' ';'
		{ finish_asm_stmt ($2, $4, $6, $8, NULL_TREE); }
	/* This is the case with clobbered registers as well.  */
	| asm_keyword maybe_cv_qualifier '(' string ':' asm_operands ':'
	  asm_operands ':' asm_clobbers ')' ';'
		{ finish_asm_stmt ($2, $4, $6, $8, $10); }
	| GOTO '*' expr ';'
                { 
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids computed gotos");
		  finish_goto_stmt ($3);
		}
	| GOTO identifier ';'
                { finish_goto_stmt ($2); }
	| label_colon stmt
		{ finish_stmt (); }
	| label_colon '}'
		{ error ("label must be followed by statement");
		  yyungetc ('}', 0);
		  finish_stmt (); }
	| ';'
		{ finish_stmt (); }
	| try_block
	| using_directive
	| namespace_using_decl
	        { do_local_using_decl ($1); }
	| namespace_alias
	;

function_try_block:
	  TRY
		{
		  if (! current_function_parms_stored)
		    store_parm_decls ();
		  expand_start_early_try_stmts ();
		}
	  ctor_initializer_opt compstmt
		{ 
		  end_protect_partials ();
                  expand_start_all_catch (); 
                }
	  handler_seq
		{
		  expand_end_all_catch ();
		  $$ = $3;
		}
	;

try_block:
	  TRY
                { $$ = begin_try_block (); }
	  compstmt
                { finish_try_block ($2); }
	  handler_seq
                { finish_handler_sequence ($2); }
	;

handler_seq:
	  handler
	| handler_seq handler
	;

handler:
	  CATCH
                { $$ = begin_handler(); }
          handler_args
                { finish_handler_parms ($2); }
	  compstmt
                { finish_handler ($2); }
	;

type_specifier_seq:
	  typed_typespecs  %prec EMPTY
	| nonempty_cv_qualifiers  %prec EMPTY
	;

handler_args:
	  '(' ELLIPSIS ')'
		{ expand_start_catch_block (NULL_TREE, NULL_TREE); }
	/* This doesn't allow reference parameters, the below does.
	| '(' type_specifier_seq absdcl ')'
		{ check_for_new_type ("inside exception declarations", $2);
		  expand_start_catch_block ($2.t, $3); }
	| '(' type_specifier_seq ')'
		{ check_for_new_type ("inside exception declarations", $2);
		  expand_start_catch_block ($2.t, NULL_TREE); }
	| '(' type_specifier_seq notype_declarator ')'
		{ check_for_new_type ("inside exception declarations", $2);
		  expand_start_catch_block ($2.t, $3); }
	| '(' typed_typespecs after_type_declarator ')'
		{ check_for_new_type ("inside exception declarations", $2);
		  expand_start_catch_block ($2.t, $3); }
	This allows reference parameters...  */
	| '(' parm ')'
		{ check_for_new_type ("inside exception declarations", $2);
		  expand_start_catch_block (TREE_PURPOSE ($2.t),
					    TREE_VALUE ($2.t)); }
	;

label_colon:
	  IDENTIFIER ':'
		{ tree label;
		do_label:
		  label = define_label (input_filename, lineno, $1);
		  if (label && ! minimal_parse_mode)
		    expand_label (label);
		}
	| PTYPENAME ':'
		{ goto do_label; }
	| TYPENAME ':'
		{ goto do_label; }
	| SELFNAME ':'
		{ goto do_label; }
	;

for.init.statement:
	  xexpr ';'
		{ if ($1) cplus_expand_expr_stmt ($1); }
	| decl
	| '{' compstmtend
		{ if (pedantic)
		    pedwarn ("ANSI C++ forbids compound statements inside for initializations");
		}
	;

/* Either a type-qualifier or nothing.  First thing in an `asm' statement.  */

maybe_cv_qualifier:
	  /* empty */
		{ emit_line_note (input_filename, lineno);
		  $$ = NULL_TREE; }
	| CV_QUALIFIER
		{ emit_line_note (input_filename, lineno); }
	;

xexpr:
	  /* empty */
		{ $$ = NULL_TREE; }
	| expr
	| error
		{ $$ = NULL_TREE; }
	;

/* These are the operands other than the first string and colon
   in  asm ("addextend %2,%1": "=dm" (x), "0" (y), "g" (*x))  */
asm_operands:
	  /* empty */
		{ $$ = NULL_TREE; }
	| nonnull_asm_operands
	;

nonnull_asm_operands:
	  asm_operand
	| nonnull_asm_operands ',' asm_operand
		{ $$ = chainon ($$, $3); }
	;

asm_operand:
	  STRING '(' expr ')'
		{ $$ = build_tree_list ($$, $3); }
	;

asm_clobbers:
	  STRING
		{ $$ = tree_cons (NULL_TREE, $$, NULL_TREE); }
	| asm_clobbers ',' STRING
		{ $$ = tree_cons (NULL_TREE, $3, $$); }
	;

/* This is what appears inside the parens in a function declarator.
   Its value is represented in the format that grokdeclarator expects.

   In C++, declaring a function with no parameters
   means that that function takes *no* parameters.  */

parmlist:
	  /* empty */
		{
		  $$ = empty_parms();
		}
	| complex_parmlist
	| type_id
		{ $$ = finish_parmlist (build_tree_list (NULL_TREE, $1.t), 0);
		  check_for_new_type ("inside parameter list", $1); }
	;

/* This nonterminal does not include the common sequence '(' type_id ')',
   as it is ambiguous and must be disambiguated elsewhere.  */
complex_parmlist:
	  parms
                { $$ = finish_parmlist ($$, 0); }
	| parms_comma ELLIPSIS
                { $$ = finish_parmlist ($1, 1); }
	/* C++ allows an ellipsis without a separating ',' */
	| parms ELLIPSIS
                { $$ = finish_parmlist ($1, 1); }
	| type_id ELLIPSIS
                { $$ = finish_parmlist (build_tree_list (NULL_TREE,
							 $1.t), 1); } 
	| ELLIPSIS
                { $$ = finish_parmlist (NULL_TREE, 1); }
	| parms ':'
		{
		  /* This helps us recover from really nasty
		     parse errors, for example, a missing right
		     parenthesis.  */
		  yyerror ("possibly missing ')'");
		  $$ = finish_parmlist ($1, 0);
		  yyungetc (':', 0);
		  yychar = ')';
		}
	| type_id ':'
		{
		  /* This helps us recover from really nasty
		     parse errors, for example, a missing right
		     parenthesis.  */
		  yyerror ("possibly missing ')'");
		  $$ = finish_parmlist (build_tree_list (NULL_TREE,
							 $1.t), 0); 
		  yyungetc (':', 0);
		  yychar = ')';
		}
	;

/* A default argument to a */
defarg:
	  '='
		{ maybe_snarf_defarg (); }
	  defarg1
		{ $$ = $3; }
	;

defarg1:
	  DEFARG
	| init
	;

/* A nonempty list of parameter declarations or type names.  */
parms:
	  named_parm
		{ check_for_new_type ("in a parameter list", $1);
		  $$ = build_tree_list (NULL_TREE, $1.t); }
	| parm defarg
		{ check_for_new_type ("in a parameter list", $1);
		  $$ = build_tree_list ($2, $1.t); }
	| parms_comma full_parm
		{ check_for_new_type ("in a parameter list", $2);
		  $$ = chainon ($$, $2.t); }
	| parms_comma bad_parm
		{ $$ = chainon ($$, build_tree_list (NULL_TREE, $2)); }
	| parms_comma bad_parm '=' init
		{ $$ = chainon ($$, build_tree_list ($4, $2)); }
	;

parms_comma:
	  parms ','
	| type_id ','
		{ check_for_new_type ("in a parameter list", $1);
		  $$ = build_tree_list (NULL_TREE, $1.t); }
	;

/* A single parameter declaration or parameter type name,
   as found in a parmlist.  */
named_parm:
	/* Here we expand typed_declspecs inline to avoid mis-parsing of
	   TYPESPEC IDENTIFIER.  */
	  typed_declspecs1 declarator
		{ tree specs = strip_attrs ($1.t);
		  $$.new_type_flag = $1.new_type_flag;
		  $$.t = build_tree_list (specs, $2); }
	| typed_typespecs declarator
		{ $$.t = build_tree_list ($1.t, $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| typespec declarator
		{ $$.t = build_tree_list (build_decl_list (NULL_TREE, $1.t),
					  $2); 
		  $$.new_type_flag = $1.new_type_flag; }
	| typed_declspecs1 absdcl
		{ tree specs = strip_attrs ($1.t);
		  $$.t = build_tree_list (specs, $2);
		  $$.new_type_flag = $1.new_type_flag; }
	| typed_declspecs1  %prec EMPTY
		{ tree specs = strip_attrs ($1.t);
		  $$.t = build_tree_list (specs, NULL_TREE); 
		  $$.new_type_flag = $1.new_type_flag; }
	| declmods notype_declarator
		{ tree specs = strip_attrs ($1);
		  $$.t = build_tree_list (specs, $2); 
		  $$.new_type_flag = 0; }
	;

full_parm:
	  parm
		{ $$.t = build_tree_list (NULL_TREE, $1.t);
		  $$.new_type_flag = $1.new_type_flag;  }
	| parm defarg
		{ $$.t = build_tree_list ($2, $1.t);
		  $$.new_type_flag = $1.new_type_flag;  }
	;

parm:
	  named_parm
	| type_id
	;

see_typename:
	  /* empty */  %prec EMPTY
		{ see_typename (); }
	;

bad_parm:
	  /* empty */ %prec EMPTY
		{
		  error ("type specifier omitted for parameter");
		  $$ = build_tree_list (integer_type_node, NULL_TREE);
		}
	| notype_declarator
		{
		  error ("type specifier omitted for parameter");
		  if (TREE_CODE ($$) == SCOPE_REF
		      && (TREE_CODE (TREE_OPERAND ($$, 0)) == TEMPLATE_TYPE_PARM
			  || TREE_CODE (TREE_OPERAND ($$, 0)) == TEMPLATE_TEMPLATE_PARM))
		    cp_error ("  perhaps you want `typename %E' to make it a type", $$);
		  $$ = build_tree_list (integer_type_node, $$);
		}
	;

exception_specification_opt:
	  /* empty */  %prec EMPTY
		{ $$ = NULL_TREE; }
	| THROW '(' ansi_raise_identifiers  ')'  %prec EMPTY
		{ $$ = $3; }
	| THROW LEFT_RIGHT  %prec EMPTY
		{ $$ = build_decl_list (NULL_TREE, NULL_TREE); }
	;

ansi_raise_identifier:
	  type_id
		{ $$ = build_decl_list (NULL_TREE, groktypename($1.t)); }
	;

ansi_raise_identifiers:
	  ansi_raise_identifier
	| ansi_raise_identifiers ',' ansi_raise_identifier
		{
		  TREE_CHAIN ($3) = $$;
		  $$ = $3;
		}
	;

conversion_declarator:
	  /* empty */  %prec EMPTY
		{ $$ = NULL_TREE; }
	| '*' cv_qualifiers conversion_declarator
		{ $$ = make_pointer_declarator ($2, $3); }
	| '&' cv_qualifiers conversion_declarator
		{ $$ = make_reference_declarator ($2, $3); }
	| ptr_to_mem cv_qualifiers conversion_declarator
		{ tree arg = make_pointer_declarator ($2, $3);
		  $$ = build_parse_node (SCOPE_REF, $1, arg);
		}
	;

operator:
	  OPERATOR
		{ got_scope = NULL_TREE; }
	;

operator_name:
	  operator '*'
		{ $$ = ansi_opname[MULT_EXPR]; }
	| operator '/'
		{ $$ = ansi_opname[TRUNC_DIV_EXPR]; }
	| operator '%'
		{ $$ = ansi_opname[TRUNC_MOD_EXPR]; }
	| operator '+'
		{ $$ = ansi_opname[PLUS_EXPR]; }
	| operator '-'
		{ $$ = ansi_opname[MINUS_EXPR]; }
	| operator '&'
		{ $$ = ansi_opname[BIT_AND_EXPR]; }
	| operator '|'
		{ $$ = ansi_opname[BIT_IOR_EXPR]; }
	| operator '^'
		{ $$ = ansi_opname[BIT_XOR_EXPR]; }
	| operator '~'
		{ $$ = ansi_opname[BIT_NOT_EXPR]; }
	| operator ','
		{ $$ = ansi_opname[COMPOUND_EXPR]; }
	| operator ARITHCOMPARE
		{ $$ = ansi_opname[$2]; }
	| operator '<'
		{ $$ = ansi_opname[LT_EXPR]; }
	| operator '>'
		{ $$ = ansi_opname[GT_EXPR]; }
	| operator EQCOMPARE
		{ $$ = ansi_opname[$2]; }
	| operator ASSIGN
		{ $$ = ansi_assopname[$2]; }
	| operator '='
		{ $$ = ansi_opname [MODIFY_EXPR]; }
	| operator LSHIFT
		{ $$ = ansi_opname[$2]; }
	| operator RSHIFT
		{ $$ = ansi_opname[$2]; }
	| operator PLUSPLUS
		{ $$ = ansi_opname[POSTINCREMENT_EXPR]; }
	| operator MINUSMINUS
		{ $$ = ansi_opname[PREDECREMENT_EXPR]; }
	| operator ANDAND
		{ $$ = ansi_opname[TRUTH_ANDIF_EXPR]; }
	| operator OROR
		{ $$ = ansi_opname[TRUTH_ORIF_EXPR]; }
	| operator '!'
		{ $$ = ansi_opname[TRUTH_NOT_EXPR]; }
	| operator '?' ':'
		{ $$ = ansi_opname[COND_EXPR]; }
	| operator MIN_MAX
		{ $$ = ansi_opname[$2]; }
	| operator POINTSAT  %prec EMPTY
		{ $$ = ansi_opname[COMPONENT_REF]; }
	| operator POINTSAT_STAR  %prec EMPTY
		{ $$ = ansi_opname[MEMBER_REF]; }
	| operator LEFT_RIGHT
		{ $$ = ansi_opname[CALL_EXPR]; }
	| operator '[' ']'
		{ $$ = ansi_opname[ARRAY_REF]; }
	| operator NEW  %prec EMPTY
		{ $$ = ansi_opname[NEW_EXPR]; }
	| operator DELETE  %prec EMPTY
		{ $$ = ansi_opname[DELETE_EXPR]; }
	| operator NEW '[' ']'
		{ $$ = ansi_opname[VEC_NEW_EXPR]; }
	| operator DELETE '[' ']'
	/* Names here should be looked up in class scope ALSO.  */
	| operator type_specifier_seq conversion_declarator
	| operator error
	;

%%

