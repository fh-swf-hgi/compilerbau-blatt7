%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "y.tab.h"
inline void yyerror(const char *s) { printf("%s", s); }
extern int yylex();
extern FILE *yyin;

int num_entries = 0;
struct symtabentry symtab[MAXSYMS];

%}

%union
{
    int i;
    float f;
    struct symtabentry *n;
}

%left SYMPLUS SYMMINUS
%left SYMMULT

%token <f> FLT
%token <i> INT
%token <n> IDENT

%type <f> prog stmts stmt expr term

%start prog
%%

prog: stmts { printf(" = %f\n", $1); }
	;

stmts: stmts stmt { $$ = $2; }
	| stmt
	;

stmt: IDENT '=' expr { ($1->v).f = $3; }
	| expr { $$ = $1; }
	;

expr: expr SYMPLUS expr { $$ = $1 + $3; }
		| expr SYMMINUS expr { $$ = $1 - $3; }
		| expr SYMMULT expr { $$ = $1 * $3; }
		| term { $$ = $1; }
		;

term: '(' expr ')' { $$ = $2; }
	| FLT { $$ = $1; }
	| INT { $$ = $1; }
	| IDENT { $$ = $1->v.f; }
	;

%%

//int main() { yyparse(); }


struct symtabentry * access_symtab(char *s) {
	char *p;
	struct symtabentry *sp;
	sp = symtab;
	int i;
	for(i=0; i<MAXSYMS; i++) {
		/* Ist das Symbol schon in der Tabelle? */
		if(sp->name && !strcmp(sp->name, s))
			return sp;
		/* Ist die Stelle in der Tabelle frei? */
		if(!sp->name) {
			sp->name = strdup(s);
			printf("Insert Symbol %s\n", s);
			return sp;
		}
		sp++; //Naechstes Symbol
	}
	yyerror("Symboltabelle zu klein");
	exit(1); /* Fehler */
}


int main(int argc, char **argv) {
	if(argc > 1) {
		if(!(yyin = fopen(argv[1], "r"))) {
		 	perror(argv[1]);
		 	return 1;
		}
	}
	yyparse();
	return 0;
}



