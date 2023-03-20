build: calc.l calc.y
	bison calc.y -y -o calc.tab.o
	flex calc.l
	cc calc.tab.c lex.yy.c
    
