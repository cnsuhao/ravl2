#ifndef BISON_CXX_TAB_H
# define BISON_CXX_TAB_H

# ifndef YYSTYPE
#  define YYSTYPE int
#  define YYSTYPE_IS_TRIVIAL 1
# endif
# define	IDENTIFIER	257
# define	CLCL	258
# define	PUBLIC	259
# define	PROTECTED	260
# define	PRIVATE	261
# define	NAMESPACE	262
# define	STRING	263
# define	CONSTANT	264
# define	CPVIRTUAL	265
# define	ENUM	266
# define	CPTYPEDEF	267
# define	CPFRIEND	268
# define	CPOPERATOR	269
# define	TEMPLATE	270
# define	CPTHROW	271
# define	CPTRY	272
# define	CPCATCH	273
# define	SCSPEC	274
# define	TYPENAME_KEYWORD	275
# define	USING	276
# define	EXTERN	277
# define	ELLIPSIS	278
# define	ASM_KEYWORD	279
# define	CV_QUALIFIER	280
# define	TYPEQUAL	281
# define	BINOP	282
# define	BUILTIN	283
# define	DOCSECTION	284


extern YYSTYPE yylval;

#endif /* not BISON_CXX_TAB_H */
