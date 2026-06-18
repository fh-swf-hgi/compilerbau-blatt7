#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stdio.h>
#include "types.h"

#define MAX_SYMBOLS 32

/* Ein Symboltabelleneintrag speichert den Namen und den bisher bekannten Typ. */
typedef struct Symbol {
    char *name;
    DataType type;
} Symbol;

/* Scanner nutzt diese Funktion, sobald ein Bezeichner gelesen wird. */
Symbol *symbol_get_or_create(const char *name);
void symbols_print(FILE *out);

#endif
