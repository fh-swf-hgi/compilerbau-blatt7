CC = gcc
CFLAGS = -Wall -std=gnu11
LDLIBS = -ll -ly

PARSER = parser
SOURCES = main.c ast.c semantic.c symbols.c types.c y.tab.c lex.yy.c

.PHONY: all run test test-widening ast clean

all: $(PARSER)

run: $(PARSER)
	./$(PARSER) testfile
	dot ast.dot -Tpng > ast.png

test: $(PARSER)
	@echo "== ok-simple =="
	@cat tests/ok-simple.expr
	@./$(PARSER) tests/ok-simple.expr
	@echo
	@echo "== ok-mixed =="
	@cat tests/ok-mixed.expr
	@./$(PARSER) tests/ok-mixed.expr
	@echo
	@echo "== error-reassign =="
	@cat tests/error-reassign.expr
	@./$(PARSER) tests/error-reassign.expr || true
	@echo
	@echo "== error-unknown =="
	@cat tests/error-unknown.expr 
	@./$(PARSER) tests/error-unknown.expr || true

test-widening: $(PARSER)
	@echo "== widening =="
	@echo "Dieser Test soll nach der Erweiterung der Zuweisungsregel erfolgreich sein."
	@./$(PARSER) tests/widening.expr

ast: run

$(PARSER): y.tab.c lex.yy.c main.c ast.c ast.h semantic.c semantic.h symbols.c symbols.h types.c types.h parser.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(PARSER) $(LDLIBS)

y.tab.h y.tab.c: parser.y ast.h symbols.h parser.h
	bison -y -d parser.y

lex.yy.c: parser.l y.tab.h ast.h symbols.h
	flex parser.l

clean:
	rm -f y.tab.h y.tab.c lex.yy.c $(PARSER) ast.dot ast.png
