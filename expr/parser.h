#include "y.tab.h"

#define MAXSYMS 20 /* Maximale Anzahl von Symbolen */
struct symtabentry {
	char *name;
	int type; /* 0 = ?, 1 = int, 2 = double */
	YYSTYPE v;
	};

struct symtabentry * access_symtab(char * s);

typedef enum { UnknownType, IntType, DoubleType } DataType;

typedef enum { StmtNode, AsgmtNode, ExprNode, AddNode, SubNode,  MulNode, IdentNode, IntNode, DoubleNode } NodeType;

struct Node {
       NodeType kind;
	   int id;
       DataType type;
       struct Node *left, *right;
       union { 
           int intValue;
           double doubleValue;
           struct symtabentry * ident; 
       } content ;
};

	struct Node* newIntNode(int i);
	struct Node* newDoubleNode(double i); 
	struct Node* newIdentNode(struct symtabentry *i);
	struct Node* newExprNode(NodeType kind, struct Node* e);
	struct Node* newBinOpNode(NodeType kind, struct Node* left, struct Node* right);
	struct Node* newStmtNode(NodeType kind, struct Node* left, struct Node* right);
	struct Node* newAssignementNode(NodeType kind, struct Node* left, struct Node* right);

