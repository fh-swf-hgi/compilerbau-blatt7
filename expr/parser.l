%{
#include "y.tab.h"
#include "parser.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]* { yylval.n=access_symtab(yytext); return IDENT; }
[0-9]*\.[0-9]+ { yylval.f = atof(yytext); return FLT; }
[0-9]+ { yylval.i = atoi(yytext); return INT; }
\+ { return SYMPLUS; }
- { return SYMMINUS; }
\* { return SYMMULT; }
\/\*(.*\n)*.*\*\/  {};
[ \t\n] ; /* Ignoriere Leerzeichen und Tabs */
. return yytext[0];


%%
