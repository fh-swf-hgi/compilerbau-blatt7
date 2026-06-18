%{
#include <stdio.h>
#include "ast.h"
#include "parser.h"

int yylex(void);
extern FILE *yyin;

static AstNode *root_of_ast = NULL;

void yyerror(const char *message)
{
    fprintf(stderr, "Syntaxfehler: %s\n", message);
}
%}

%union
{
    int int_value;
    double double_value;
    Symbol *symbol;
    AstNode *node;
}

%left SYMPLUS SYMMINUS
%left SYMMULT

%token <double_value> FLT
%token <int_value> INT
%token <symbol> IDENT

%type <node> prog stmts stmt expr term var

%start prog
%%

prog:
    stmts { root_of_ast = $1; $$ = $1; }
    ;

stmts:
    stmts stmt { $$ = ast_new_binary(StmtNode, $1, $2); }
    | stmt { $$ = $1; }
    ;

stmt:
    var '=' expr { $$ = ast_new_binary(AssignNode, $1, $3); }
    | expr { $$ = ast_new_unary(ExprStmtNode, $1); }
    ;

expr:
    expr SYMPLUS expr { $$ = ast_new_binary(AddNode, $1, $3); }
    | expr SYMMINUS expr { $$ = ast_new_binary(SubNode, $1, $3); }
    | expr SYMMULT expr { $$ = ast_new_binary(MulNode, $1, $3); }
    | term { $$ = $1; }
    ;

term:
    '(' expr ')' { $$ = $2; }
    | FLT { $$ = ast_new_double($1); }
    | INT { $$ = ast_new_int($1); }
    | var { $$ = $1; }
    ;

var:
    IDENT { $$ = ast_new_ident($1); }
    ;

%%

AstNode *parse_file(FILE *input)
{
    yyin = input;
    root_of_ast = NULL;

    if (yyparse()) {
        return NULL;
    }
    return root_of_ast;
}
