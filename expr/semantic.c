#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>

static void semantic_error(const char *message, const char *name,
                           DataType expected, DataType actual)
{
    fprintf(stderr, "Semantikfehler: %s", message);
    if (name) {
        fprintf(stderr, " '%s'", name);
    }
    if (expected != UnknownType || actual != UnknownType) {
        fprintf(stderr, " (%s statt %s)", type_name(actual), type_name(expected));
    }
    fprintf(stderr, "\n");
    exit(1);
}

static DataType analyze_node(AstNode *node)
{
    DataType left_type = UnknownType;
    DataType right_type = UnknownType;

    if (!node) {
        return UnknownType;
    }

    /*
     * Postorder-Traversierung: Erst werden die Kinder analysiert, danach wird
     * der Typ des aktuellen Knotens gesetzt.
     */
    switch (node->kind) {
    case IntNode:
        /* Literale haben ihren Typ direkt aus der Syntax. */
        node->type = IntType;
        return node->type;

    case DoubleNode:
        /* Literale haben ihren Typ direkt aus der Syntax. */
        node->type = DoubleType;
        return node->type;

    case IdentNode:
        /* Beim Lesen eines Bezeichners muss sein Typ bereits bekannt sein. */
        node->type = node->value.symbol->type;
        if (node->type == UnknownType) {
            semantic_error("Variable wurde vor der ersten Zuweisung gelesen",
                           node->value.symbol->name, UnknownType, UnknownType);
        }
        return node->type;

    case AssignNode:
        /* Zuweisung: rechter Ausdruck bestimmt den Typ der linken Variable. */
        right_type = analyze_node(node->right);
        node->type = right_type;

        if (!node->left || node->left->kind != IdentNode) {
            semantic_error("Linke Seite einer Zuweisung ist kein Bezeichner",
                           NULL, UnknownType, UnknownType);
        }

        node->left->type = right_type;
        if (node->left->value.symbol->type == UnknownType) {
            /* Erste Zuweisung: Typ in die Symboltabelle eintragen. */
            node->left->value.symbol->type = right_type;
        } else {
            /*
             * TYPE WIDENING:
             * Fuegen Sie hier Code ein, der den vorhandenen Variablentyp
             * und right_type zum allgemeineren Typ zusammenfasst.
             * Wenn diese Erweiterung implementiert ist, soll diese Stelle
             * vor der folgenden Fehlerbehandlung mit return verlassen werden.
             */
            if (node->left->value.symbol->type != right_type) {
                /* Aktuelle Regel: Spaetere Zuweisungen muessen typgleich sein. */
                semantic_error("Variable hat bereits einen anderen Typ",
                               node->left->value.symbol->name,
                               node->left->value.symbol->type, right_type);
            }
        }
        return node->type;

    case AddNode:
    case SubNode:
    case MulNode:
        /* Ausdruckstyp aus den Operandentypen berechnen. */
        left_type = analyze_node(node->left);
        right_type = analyze_node(node->right);
        node->type = common_type(left_type, right_type);
        return node->type;

    case ExprStmtNode:
        node->type = analyze_node(node->left);
        return node->type;

    case StmtNode:
        analyze_node(node->left);
        node->type = analyze_node(node->right);
        return node->type;
    }

    return UnknownType;
}

DataType semantic_analyze(AstNode *tree)
{
    return analyze_node(tree);
}
