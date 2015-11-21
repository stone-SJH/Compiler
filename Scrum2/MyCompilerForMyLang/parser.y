%define api.pure
%parse-param	{ struct pcdata* pp }
%output  "parser.cpp"
%defines "parser.h"

%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%union {
	struct ast* a;
	struct symlist* sl;

	char* name;
	int type;
	double d;
	int i;
	char c;

	int fn;
}
%{
	#include "defination.h"
	#include "lexer.h"
	#define YYLEX_PARAM	 pp->scaninfo
%}

%token EOL END
%token <c> CHAR 
%token <i> INT
%token <d> DOUBLE
%token <type> TYPE
%token <name> NAME
%token <fn> FUNC

%token VAR AS ARRAY OF
%token IF THEN ELSE ENDIF
%token WHILE ENDWHILE
%token FOR	FROM TO STEP ENDFOR	
%token FOREACH	IN ENDFOREACH
%token LET	ENDFUNC DEFINE RETURN
%token CLASS EXTENDS ENDCLASS GET

%right	'='
%left	'|'
%left	'&'
%nonassoc <fn> CMP
%left	'+'	'-'
%left	'*'		'/'		'%'
%left GET
%right	'~'
%nonassoc	UMINUS	'['	']' '(' ')'

%type <a> prog	stmtlist	stmt	basedec	arrdec	asgnstmt	ifstmt	whilestmt	forstmt	foreachstmt	funcdefinestmt	funccallstmt	explist	exp 
%type <a> infunclist infunc returnstmt
%type <a> classdec classdefinestmt	classsucceed
%type <sl> symlist
%start prog
%%

prog:	
		END	{ pp->ast=NULL; YYACCEPT; }
		|	stmtlist		{ pp->ast=$1; YYACCEPT; }
		;
stmtlist:	stmt 	{ $$=$1; }
		|	stmt		stmtlist	{ $$=newast(pp,'L',$1,$2); }
		;
stmt:		basedec	{ $$=$1; }
		|	arrdec		{ $$=$1; }
		|	classdec	{$$=$1;}
		|	asgnstmt	{ $$=$1; }
		|	ifstmt		{ $$=$1; }
		|	forstmt		{ $$=$1; }
		|	whilestmt	{ $$=$1; }
		|	foreachstmt	{ $$=$1; }
		|	funcdefinestmt	{ $$=$1; }
		|	funccallstmt { $$=$1; }
		|   classdefinestmt {$$=$1;}
		|	classsucceed {$$=$1;}
		;
infunclist:	infunc 	{ $$=$1; }
		|	infunc	infunclist	{ $$=newast(pp,'L',$1,$2); }
		;
infunc:		basedec	{ $$=$1; }
		|	arrdec		{ $$=$1; }
		|	asgnstmt	{ $$=$1; }
		|	classdec	{ $$=$1; }
		|	ifstmt		{ $$=$1; }
		|	forstmt		{ $$=$1; }
		|	whilestmt	{ $$=$1; }
		|	foreachstmt	{ $$=$1; }
		|	funccallstmt { $$=$1; }
		|	returnstmt {$$=$1;}
		;
basedec:	VAR NAME AS TYPE ';'	{ $$=newvar(pp,$2,$4); }
		;
arrdec:	VAR NAME AS	ARRAY	'['	INT	']'	OF	TYPE	 ';' {$$=newarr(pp,$2,$9,$6); }
		;
classdec: VAR NAME AS NAME ';' {$$=newclass(pp,$2,$4); }
		;	
classdefinestmt: CLASS NAME  stmtlist ENDCLASS {$$=newclassdef(pp,$2,NULL,$3);}
		;
classsucceed:	CLASS NAME  EXTENDS NAME   stmtlist ENDCLASS { $$=newclassdef(pp,$2,$4,$5);}
		;
asgnstmt:	NAME	'='	exp ';'	{  $$=newasgn(pp,$1,$3,NULL); }
		|	NAME	'['	exp ']'	'='	exp	';' { $$=newasgn(pp,$1,$6,$3); } 
		|	NAME	'='	asgnstmt 	{  $$=newasgn(pp,$1,$3,NULL); }
		|	NAME	'['	exp ']'	'='	asgnstmt	  { $$=newasgn(pp,$1,$6,$3); } 
		;
ifstmt:	IF '(' exp ')' THEN stmtlist ELSE stmtlist ENDIF { $$=newflow(pp,'I',$3,$6,$8); }
		|	IF '(' exp ')' THEN stmtlist  ENDIF	{$$=newflow(pp,'I',$3,$6,NULL);}
		;
whilestmt:		WHILE '(' exp ')' stmtlist ENDWHILE { $$=newflow(pp,'W',$3,$5,NULL); }
		;
forstmt:	FOR  '(' NAME FROM INT TO	INT STEP	INT ')'	 stmtlist	ENDFOR	{ $$=newfor(pp,$3,$5,$7,$9,$11); }
		;
foreachstmt:		FOREACH	'(' NAME	IN NAME	')' stmtlist ENDFOREACH	{ $$=newforeach(pp,$3,$5,$7); }
		;
funcdefinestmt:	LET NAME	'('	symlist	')'	infunclist	ENDFUNC	{ $$=dodef(pp,$2,$4,$6); }
		|	DEFINE NAME '(' symlist ')' ';'	{ $$=dodef(pp,$2,$4,NULL); }
		;
returnstmt: RETURN exp ';' { $$=newast(pp,'R',$2,NULL);}
		;
funccallstmt:		FUNC	'('	explist	')' ';'	{$$=newfunc(pp,$1,$3); }
		|	NAME	'('	explist	')'	 ';' { $$=newcall(pp,$1,$3); }
		;
symlist:	
		|	NAME	{ $$=newsymlist(pp,$1,NULL); }
		|	NAME ','  symlist	{ $$=newsymlist(pp,$1,$3); }
		;
explist:	
		|	exp
		|	exp ',' explist		{ $$=newast(pp,'L',$1,$3); }
		;
exp:	exp CMP exp	{ $$=newcmp(pp,$2,$1,$3); }
		|	exp	'+'	exp	{ $$=newast(pp,'+',$1,$3); }
		|	exp	'-'		exp	{ $$=newast(pp,'-',$1,$3); }
		|	exp	'*'		exp	{ $$=newast(pp,'*',$1,$3); }
		|	exp	'/'		exp	{ $$=newast(pp,'/',$1,$3); }
		|	exp	'%'	exp	{ $$=newast(pp,'%',$1,$3); }
		|	'~'	exp	{ $$=newast(pp,'~',$2,NULL);}
		|	exp	'&'	exp	{ $$=newast(pp,'&',$1,$3);}
		|	exp	'|'	exp	{ $$=newast(pp,'|',$1,$3); }
		|	'('	exp	')'	{ $$=$2; }
		|	'-'	exp	%prec	UMINUS	{ $$=newast(pp,'M',$2,NULL); }
		|	DOUBLE	{ $$=newdoub(pp,$1); }
		|	CHAR	{ $$=newchar(pp,$1); }
		|	INT	{ $$=newint(pp,$1); }
		|	NAME	{  $$=newref(pp,$1,NULL); }
		|	NAME	'['	exp	']'	{ $$=newref(pp,$1,$3); }      
		|	FUNC	'('	explist	')' 	{$$=newfunc(pp,$1,$3); }
		|	NAME	'('	explist	')'	  { $$=newcall(pp,$1,$3); }
		|	NAME	GET	NAME {$$=newcsget(pp,$1,$3,-1,NULL,NULL);}
		|	NAME	GET  FUNC	'('	explist	')'	{ $$=newcsget(pp,$1,NULL,$3,$5,NULL);}
		|	NAME	GET NAME	'('	explist	')'	 { $$=newcsget(pp,$1,$3,-1,$5,NULL); }
		|	NAME	GET	NAME	'['	exp	']'	{ $$=newcsget(pp,$1,$3,-1,NULL,$5); }      
		;
%%