#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "ast.h"

AstNode *parse_file(FILE *input);
void yyerror(const char *message);

#endif
