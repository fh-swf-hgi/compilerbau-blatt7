%{
#include <stdlib.h>
#include "ast.h"
#include "symbols.h"
#include "y.tab.h"
%}

%option noinput nounput

%%

[a-zA-Z][a-zA-Z0-9]* { yylval.symbol = symbol_get_or_create(yytext); return IDENT; }
[0-9]*\.[0-9]+       { yylval.double_value = atof(yytext); return FLT; }
[0-9]+               { yylval.int_value = atoi(yytext); return INT; }
\+                   { return SYMPLUS; }
-                    { return SYMMINUS; }
\*                   { return SYMMULT; }
\/\*([^*]|\*+[^*/])*\*+\/ ;
[ \t\n]              ;
.                    { return yytext[0]; }

%%

int yywrap(void)
{
    return 1;
}
