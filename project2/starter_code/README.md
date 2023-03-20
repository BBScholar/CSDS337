# LLVM lab frontend

This repo will hold the code for the frontend until it has been fully integrated with the AST in the main project.

Built with flex 2.6.4 and bison 3.5.1, but it should work with other versions. These can be installed with `apt-get`. To draw parse trees, you will need graphviz, which can also be installed with `apt-get`.

To run, first run `make`, which will produce a binary `parser`. Run `./parser`, type in the input to be parsed, and end with Ctrl-D to send an EOF character. The program will print any errors, or, if there are none, it will generate `parsetree.dot`. You can then run `dot parsetree.dot -Tpng > graph.png` to draw the parse tree.
