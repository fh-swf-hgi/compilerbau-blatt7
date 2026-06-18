#include "symbols.h"
#include <stdlib.h>
#include <string.h>

static Symbol symbols[MAX_SYMBOLS];

static char *copy_string(const char *text)
{
    size_t length = strlen(text) + 1;
    char *copy = malloc(length);
    if (!copy) {
        fprintf(stderr, "Kein Speicher fuer Symbolnamen\n");
        exit(1);
    }
    memcpy(copy, text, length);
    return copy;
}

Symbol *symbol_get_or_create(const char *name)
{
    for (int i = 0; i < MAX_SYMBOLS; ++i) {
        if (symbols[i].name && strcmp(symbols[i].name, name) == 0) {
            return &symbols[i];
        }
        if (!symbols[i].name) {
            symbols[i].name = copy_string(name);
            symbols[i].type = UnknownType;
            return &symbols[i];
        }
    }

    fprintf(stderr, "Symboltabelle ist voll\n");
    exit(1);
}

void symbols_print(FILE *out)
{
    fprintf(out, "\nSymboltabelle:\n");
    fprintf(out, "  Name  Typ\n");
    fprintf(out, "  ----  -------\n");

    for (int i = 0; i < MAX_SYMBOLS; ++i) {
        if (symbols[i].name) {
            fprintf(out, "  %-4s  %s\n", symbols[i].name, type_name(symbols[i].type));
        }
    }
}
