#include "parser.h"
#include <stdio.h>
#include <stdlib.h>


extern struct Node* parse();

void fprintNode(struct Node* n, FILE* fp) {
  
	char typeInfo;
	switch (n->type) {
		case DoubleType: typeInfo = 'd'; break;
		case IntType: typeInfo = 'i'; break;
		default: typeInfo = '?'; break;
	}
	switch (n->kind) {
		case StmtNode:  fprintf(fp, "Stmt (%c)", typeInfo); break;
		case AsgmtNode: fprintf(fp, "= (%c)", typeInfo); break;
		case ExprNode:  fprintf(fp, "Expr (%c)", typeInfo); break;
		case AddNode:   fprintf(fp, "Add (%c)", typeInfo); break;
		case SubNode:   fprintf(fp, "Sub (%c)", typeInfo); break;
		case MulNode:   fprintf(fp, "Mul (%c)", typeInfo); break;
		case IdentNode: fprintf(fp, "%s (%c)", n->content.ident->name, typeInfo); break;
		case IntNode:   fprintf(fp, "%d (%c)", n->content.intValue, typeInfo); break;
		case DoubleNode:fprintf(fp, "%.2f (%c)", n->content.doubleValue, typeInfo); break;
  	}
}


void _print_node(struct Node* node, FILE* fp){
	fprintf(fp, "    %d [label=\"", node->id);
	fprintNode(node, fp);
	fprintf(fp, "\"]\n");
}

void _print_tree(struct Node* node, FILE* fp)
{
	_print_node(node, fp);
    if (node->left)
    {
        fprintf(fp, "    %d -> %d;\n", node->id, node->left->id);
        _print_tree(node->left, fp);
    } 

    if (node->right)
    {
        fprintf(fp, "    %d -> %d;\n", node->id, node->right->id);
        _print_tree(node->right, fp);
    }
}

void print_tree(struct Node* tree, FILE* fp)
{
    fprintf(fp, "digraph BST {\n");
    fprintf(fp, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(fp, "\n");
    else if (!tree->right && !tree->left)
        _print_node(tree, fp);
    else
        _print_tree(tree, fp);

    fprintf(fp, "}\n");
}


DataType _walk_tree(struct Node* node)
{
	DataType tl=UnknownType, tr=UnknownType;
	switch (node->kind) {
    case IntNode:
		node->type = IntType;
		return IntType;
    case DoubleNode:
		node->type = DoubleType;
		return DoubleType;
    case IdentNode:
		node->type = node->content.ident->type;
		return node->type;
    default: 
		if (node->left)  tl = _walk_tree(node->left);
	    if (node->right) tr = _walk_tree(node->right); 
		node->type = (tl>tr) ? tl : tr;
		return node->type;
  }
}

void walk_tree(struct Node* tree)
{
    if (!tree)
        printf("Baum existiert nicht \n");
    else if (!tree->right && !tree->left)
        printf("Baum ist leer\n");
    else
        tree->type = _walk_tree(tree);
}


int main(int argc, char **argv) {
	FILE * ifile;
	if(argc > 1) {
		if(!(ifile = fopen(argv[1], "r"))) {
		 	perror(argv[1]);
		 	return 1;
		}
	}
	else ifile = stdin;
	printf("Parsing file\n");
	struct Node* root = parse(ifile);
	FILE *fp;
	fp = fopen("ast.dot", "w+");
	if (root) walk_tree(root);
	if (root) print_tree(root, fp);
	fclose(fp);
	return 0;
}
