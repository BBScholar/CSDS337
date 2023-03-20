%{
  #include <stdio.h>
  #include <stdlib.h>

  double root;

  extern int yylex();
  void yyerror(const char *);
%}

%token FLOAT_LIT

%start root

%union {
    double fltval;
}

%type <fltval> term factor primary FLOAT_LIT

%define parse.error verbose

%header

 /* fill in union, tokens, and types */

%%
root: term {root = $1;}

term: factor  | term '+' factor {
    $$ = $1 + $3;
} | term '-' factor {
    $$ = $1 + $3;
};


factor: primary | factor '*' primary {
    $$ = $1 * $3;
} | factor '/' primary {
    $$ = $1 / $3;
};

primary: FLOAT_LIT | '(' term ')' {
    $$ = $2;
};
    
%%

int main() {
  yyparse();
  printf("%0.5f\n", root);
}

void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
