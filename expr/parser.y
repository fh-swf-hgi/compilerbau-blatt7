%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "y.tab.h"
inline void yyerror(const char *s) { printf("%s", s); }
extern int yylex();
extern FILE *yyin;

extern struct Node* RootOfAst;
static int nodecnt = 0;

int num_entries = 0;
struct symtabentry symtab[MAXSYMS];

%}

%union
{
    int i;
    double f;
    struct symtabentry *n;
    struct Node *astNode;
}

%left SYMPLUS SYMMINUS
%left SYMMULT

%token <f> FLT
%token <i> INT
%token <n> IDENT

%type <astNode> prog stmts stmt expr term var

%start prog
%%

prog: stmts { RootOfAst = $1; }
	;

stmts: stmts stmt { $$ = newStmtNode(StmtNode, $1, $2); }
	| stmt { $$ = $1; }
	;

stmt: expr '=' expr { $$ = newAssignementNode(AsgmtNode, $1, $3); }
	| expr { $$ = newExprNode(ExprNode, $1); }
	;

expr: expr SYMPLUS expr { $$ = newBinOpNode(AddNode, $1, $3); }
		| expr SYMMINUS expr { $$ = newBinOpNode(SubNode, $1, $3); }
		| expr SYMMULT expr { $$ = newBinOpNode(MulNode, $1, $3); }
		| term { $$ = $1; }
		;

term: '(' expr ')' { $$ = $2; }
	| FLT { $$ = newDoubleNode($1); }
	| INT { $$ = newIntNode($1); }
	| var { $$ = $1; }
	;

var: IDENT { $$ = newIdentNode($1); }
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
			sp->type = UnknownType;
			printf("Insert Symbol %s\n", s);
			return sp;
		}
		sp++; //Naechstes Symbol
	}
	yyerror("Symboltabelle zu klein");
	exit(1); /* Fehler */
}

struct Node* RootOfAst;

struct Node* newIntNode(int i) {
	struct Node *erg = (struct Node*) malloc(sizeof(struct Node));
	erg-> id = nodecnt++;
	erg->content.intValue = i;
	erg->kind = IntNode;
	erg->type = IntType;
	erg->left = erg->right = 0;
	erg->type = IntType;
	return erg;
}
struct Node* newDoubleNode(double i) {
	struct Node *erg = (struct Node*) malloc(sizeof(struct Node));
	erg-> id = nodecnt++;
	erg->content.doubleValue = i;
	erg->kind = DoubleNode;
	erg->type = DoubleType;
	erg->left = erg->right = 0;
	erg->type = DoubleType;
	return erg;
}
struct Node* newIdentNode(struct symtabentry *i) {
	struct Node *erg = (struct Node*) malloc(sizeof(struct Node));
	erg-> id = nodecnt++;
	erg->content.ident = i;
	erg->kind = IdentNode;
	erg->type = UnknownType;
	erg->left = erg->right = 0;
	erg->type = UnknownType;
	return erg;
}
struct Node* newBinOpNode(NodeType kind, struct Node* left, struct Node* right) {
	struct Node *erg = (struct Node*) malloc(sizeof(struct Node));
	erg-> id = nodecnt++;
	erg->kind = kind;
	erg->left = left;
	erg->right = right;
	erg->type = UnknownType;
	return erg;
}

struct Node* newStmtNode(NodeType kind, struct Node* left, struct Node* right) {
	return newBinOpNode(kind, left, right);
}

struct Node* newAssignementNode(NodeType kind, struct Node* left, struct Node* right) {
	return newBinOpNode(kind, left, right);
}

struct Node* newExprNode(NodeType kind, struct Node* e) {
	return newBinOpNode(kind, e, 0);
}


struct Node* parse(FILE *fp) {
	yyin = fp;
    if (yyparse()) return 0;
    else return RootOfAst;
}




