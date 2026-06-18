#ifndef AST_H
#define AST_H

#include <stdio.h>
#include "symbols.h"
#include "types.h"

typedef enum {
    StmtNode,
    AssignNode,
    ExprStmtNode,
    AddNode,
    SubNode,
    MulNode,
    IdentNode,
    IntNode,
    DoubleNode
} NodeType;

/*
 * Einheitlicher AST-Knoten.
 *
 * kind legt fest, welche Felder sinnvoll belegt sind:
 * - IntNode: value.int_value
 * - DoubleNode: value.double_value
 * - IdentNode: value.symbol
 * - ExprStmtNode: left
 * - StmtNode, AssignNode, AddNode, SubNode, MulNode: left und right
 *
 * type ist ein Attribut der semantischen Analyse. Beim Parsen ist es oft noch
 * UnknownType und wird spaeter in semantic.c gesetzt.
 * id wird nur fuer die GraphViz-Ausgabe gebraucht.
 */
typedef struct AstNode {
    NodeType kind;
    int id;
    DataType type;
    struct AstNode *left;
    struct AstNode *right;
    union {
        int int_value;
        double double_value;
        Symbol *symbol;
    } value;
} AstNode;

AstNode *ast_new_int(int value);
AstNode *ast_new_double(double value);
AstNode *ast_new_ident(Symbol *symbol);
AstNode *ast_new_unary(NodeType kind, AstNode *child);
AstNode *ast_new_binary(NodeType kind, AstNode *left, AstNode *right);
void ast_print_dot(AstNode *tree, FILE *out);

#endif
