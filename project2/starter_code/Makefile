parser: lexer.l parser.y
#bison --debug -d parser.y -o parser.tab.cc
	bison -d parser.y -o parser.tab.cc
# clang++ -Wall -fsanitize=address -fno-omit-frame-pointer -o parser.o -c parser.tab.cc
	clang++ -o parser.o -c parser.tab.cc
	flex -o lex.yy.cc lexer.l
# clang++ -Wall -fsanitize=address -fno-omit-frame-pointer -o lexer.o -c lex.yy.cc
# clang++ -Wall -fsanitize=address -fno-omit-frame-pointer -o $@ lexer.o parser.o
	clang++ -o lexer.o -c lex.yy.cc
	clang++ -o $@ lexer.o parser.o


clean:
	rm parser lex.yy.cc parser.tab.cc parser.tab.hh lexer.o parser.o
