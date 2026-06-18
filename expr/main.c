#include "ast.h"
#include "parser.h"
#include "semantic.h"
#include "symbols.h"
#include <stdio.h>

static int write_ast(AstNode *root, const char *path)
{
    FILE *out = fopen(path, "w");
    if (!out) {
        perror(path);
        return 1;
    }

    ast_print_dot(root, out);
    fclose(out);
    return 0;
}

int main(int argc, char **argv)
{
    FILE *input = stdin;

    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            perror(argv[1]);
            return 1;
        }
    }

    AstNode *root = parse_file(input);
    if (input != stdin) {
        fclose(input);
    }
    if (!root) {
        return 1;
    }

    semantic_analyze(root);
    symbols_print(stdout);

    if (write_ast(root, "ast.dot")) {
        return 1;
    }

    printf("\nAST wurde nach ast.dot geschrieben.\n");
    return 0;
}
