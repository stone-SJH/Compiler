%{
/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "parser.h"
#include "defination.h"
#include <string.h>
%}

%option warn noyywrap nodefault yylineno reentrant bison-bridge
%option header-file="lexer.h"
%option outfile="lexer.cpp"

EXP ([Ee][-+]?[0-9]+)

%%
%{
	struct pcdata* pp=(struct pcdata*)yyextra;
%}

"+"	|
"-"	|
"/"	|
"*"	|
"%"	|
"~"	|
"&"	|
"|"		|
"="	|
"|"	|
","		|
";"		|
"("	|
")"	|
"["	|
"]"	{	return yytext[0];	}

">" { yylval->fn=1; return CMP; }
"<" { yylval->fn=2; return CMP; }
"<>" { yylval->fn=3; return CMP; }
"==" { yylval->fn=4; return CMP; }
">=" { yylval->fn=5; return CMP; }
"<=" { yylval->fn=6; return CMP; }
"->"  { return GET; }

"if"	{ return IF; }
"then"	{ return THEN; }
"else"	{ return ELSE; }
"endif"	{ return ENDIF;}
"while"	{ return WHILE; }
"endwhile"	{ return ENDWHILE; }
"for"		{ return FOR; }
"from"	{ return FROM; }
"to"	{ return TO; }
"step"	{ return STEP; }
"endfor"	{ return ENDFOR; }
"foreach"	{ return FOREACH; }
"in"	{ return YYIN;}
"endforeach" { return ENDFOREACH; }
"let"	{ return LET; }
"define" { return DEFINE;}
"endfunc"	{ return ENDFUNC; }
"return"	{ return RETURN; }
"class"	{ return CLASS;}
"extends" { return EXTENDS;}
"endclass" { return ENDCLASS;}

"var"		{ return VAR;}
"as"		{ return AS;}
"of"		{ return OF;}
"char"	{ yylval->type=0; return TYPE;  }
"int"	{ yylval->type=1; return TYPE; }
"double"	{ yylval->type=2;return TYPE; }
"array"	{ return ARRAY; }

"sqrt"	{ yylval->fn=B_sqrt; return FUNC; }
"exp"	{ yylval->fn=B_exp; return FUNC; }
"log"		{ yylval->fn=B_log; return FUNC; }
"print" { yylval->fn=B_print; return FUNC; }

[\'|\"][^ \n\r][\'|\"]	{ yylval->c=yytext[1]; return TYPECHAR; }
[0-9]+{EXP}?		{ yylval->i=atoi(yytext);return TYPEINT; }
[0-9]+"."[0-9]*{EXP}? { yylval->d=atof(yytext); return TYPEDOUBLE; }

[_a-zA-Z][_a-zA-Z0-9]* { char* t=new char[strlen(yytext)+1];
									strcpy_s(t,strlen(yytext)+1,yytext) ;
									yylval->name=t;
									return NAME; }

"//".*
[ \t]
\\n	
"\n" 

.	{ yyerror(pp,"invalid character %s\n",yytext); }
<<EOF>>	{ return FILEEND; }
%%