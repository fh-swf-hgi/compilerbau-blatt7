#include "y.tab.h"

#define MAXSYMS 20 /* Maximale Anzahl von Symbolen */
struct symtabentry {
	char *name;
	short type; /* 0 = float, 1 = int */
	YYSTYPE v;
	};

struct symtabentry * access_symtab(char * s);


