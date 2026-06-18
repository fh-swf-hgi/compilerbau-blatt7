#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "types.h"

DataType semantic_analyze(AstNode *tree);

#endif
