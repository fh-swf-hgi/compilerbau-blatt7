CC = gcc
CFLAGS = -Wall -std=gnu11
LDLIBS = -ll -ly

PARSER = parser
SOURCES = main.c ast.c semantic.c symbols.c types.c y.tab.c lex.yy.c

.PHONY: all run test ast clean

all: $(PARSER)

run: $(PARSER)
	./$(PARSER) testfile
	dot ast.dot -Tpng > ast.png

test: $(PARSER)
	@echo "== ok-simple =="
	@./$(PARSER) tests/ok-simple.expr
	@echo
	@echo "== ok-mixed =="
	@./$(PARSER) tests/ok-mixed.expr
	@echo
	@echo "== error-reassign =="
	@./$(PARSER) tests/error-reassign.expr || true
	@echo
	@echo "== error-unknown =="
	@./$(PARSER) tests/error-unknown.expr || true

ast: run

$(PARSER): y.tab.c lex.yy.c main.c ast.c ast.h semantic.c semantic.h symbols.c symbols.h types.c types.h parser.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(PARSER) $(LDLIBS)

y.tab.h y.tab.c: parser.y ast.h symbols.h parser.h
	bison -y -d parser.y

lex.yy.c: parser.l y.tab.h ast.h symbols.h
	flex parser.l

clean:
	rm -f y.tab.h y.tab.c lex.yy.c $(PARSER) ast.dot ast.png
