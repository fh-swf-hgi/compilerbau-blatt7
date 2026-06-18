#include "ast.h"
#include <stdlib.h>

static int next_node_id = 0;

static AstNode *ast_new_node(NodeType kind)
{
    AstNode *node = malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Kein Speicher fuer AST-Knoten\n");
        exit(1);
    }

    node->kind = kind;
    node->id = next_node_id++;
    node->type = UnknownType;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AstNode *ast_new_int(int value)
{
    AstNode *node = ast_new_node(IntNode);
    node->type = IntType;
    node->value.int_value = value;
    return node;
}

AstNode *ast_new_double(double value)
{
    AstNode *node = ast_new_node(DoubleNode);
    node->type = DoubleType;
    node->value.double_value = value;
    return node;
}

AstNode *ast_new_ident(Symbol *symbol)
{
    AstNode *node = ast_new_node(IdentNode);
    node->value.symbol = symbol;
    return node;
}

AstNode *ast_new_unary(NodeType kind, AstNode *child)
{
    AstNode *node = ast_new_node(kind);
    node->left = child;
    return node;
}

AstNode *ast_new_binary(NodeType kind, AstNode *left, AstNode *right)
{
    AstNode *node = ast_new_node(kind);
    node->left = left;
    node->right = right;
    return node;
}

static void ast_print_label(AstNode *node, FILE *out)
{
    char type = type_short_name(node->type);

    switch (node->kind) {
    case StmtNode:
        fprintf(out, "Stmt (%c)", type);
        break;
    case AssignNode:
        fprintf(out, "= (%c)", type);
        break;
    case ExprStmtNode:
        fprintf(out, "Expr (%c)", type);
        break;
    case AddNode:
        fprintf(out, "Add (%c)", type);
        break;
    case SubNode:
        fprintf(out, "Sub (%c)", type);
        break;
    case MulNode:
        fprintf(out, "Mul (%c)", type);
        break;
    case IdentNode:
        fprintf(out, "%s (%c)", node->value.symbol->name, type);
        break;
    case IntNode:
        fprintf(out, "%d (%c)", node->value.int_value, type);
        break;
    case DoubleNode:
        fprintf(out, "%.2f (%c)", node->value.double_value, type);
        break;
    }
}

static void ast_print_node(AstNode *node, FILE *out)
{
    fprintf(out, "    %d [label=\"", node->id);
    ast_print_label(node, out);
    fprintf(out, "\"];\n");
}

static void ast_print_edges(AstNode *node, FILE *out)
{
    ast_print_node(node, out);

    if (node->left) {
        fprintf(out, "    %d -> %d;\n", node->id, node->left->id);
        ast_print_edges(node->left, out);
    }
    if (node->right) {
        fprintf(out, "    %d -> %d;\n", node->id, node->right->id);
        ast_print_edges(node->right, out);
    }
}

void ast_print_dot(AstNode *tree, FILE *out)
{
    fprintf(out, "digraph AST {\n");
    fprintf(out, "    node [fontname=\"Arial\"];\n");

    if (tree) {
        ast_print_edges(tree, out);
    }

    fprintf(out, "}\n");
}
