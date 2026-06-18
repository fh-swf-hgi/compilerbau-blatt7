#include "types.h"

const char *type_name(DataType type)
{
    switch (type) {
    case IntType:
        return "int";
    case DoubleType:
        return "double";
    default:
        return "unknown";
    }
}

char type_short_name(DataType type)
{
    switch (type) {
    case IntType:
        return 'i';
    case DoubleType:
        return 'd';
    default:
        return '?';
    }
}

DataType common_type(DataType left, DataType right)
{
    if (left == UnknownType || right == UnknownType) {
        return UnknownType;
    }
    if (left == DoubleType || right == DoubleType) {
        return DoubleType;
    }
    return IntType;
}
