pname=calc
fname=$(pname)$(VERSION)

.PHONY: clean

$(pname): clean y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -o $(pname) -ll -ly

y.tab.h y.tab.c: $(fname).y
	bison -y -d --graph $(fname).y

lex.yy.c: $(fname).l
	flex $(fname).l


clean:
	rm -f y.tab.h y.tab.c lex.yy.c $(pname)
