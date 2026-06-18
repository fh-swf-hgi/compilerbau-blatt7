#ifndef TYPES_H
#define TYPES_H

typedef enum {
    UnknownType = 0,
    IntType = 1,
    DoubleType = 2
} DataType;

const char *type_name(DataType type);
char type_short_name(DataType type);

/* Typregel fuer binaere Ausdruecke: int+int -> int, sonst double. */
DataType common_type(DataType left, DataType right);

#endif
