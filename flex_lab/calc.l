%{
  /* This code will be inserted at the top of lex.yy.c
     You do not need to change any of this*/
  #include <stdio.h>
  #include <stdlib.h>

%}

%option noyywrap

digit [0-9]

%%
  /* Comments in this region must be indented */
"+"  {return yytext[0]; }
"-"  {return yytext[0]; }
"/"  {return yytext[0]; }
"*"  {return yytext[0]; }
"("  {return yytext[0]; }
")"  {return yytext[0]; }

  /* Fill in code for the remaining simple tokens:
     -, *, /, (, )
  */

  /* Fill in code for the float literal here
     Follow a similar process to what we did for integers in the slides */
{digit}+(.{digit}*)?([eE][+\-]?{digit}+)?f? {  yylval.fltval = strtof(yytext, NULL); return FLOAT_LIT;  }


  /* These are generally nice to have: */
[ \t] {}
. {fprintf(stderr, "ERROR: Unrecognized character %s\n", yytext);}
%%


/* This code will be inserted at the bottom of lex.yy.c
   You do not need to change any of this */
int main() {
  int tok;

  while((tok = yylex())) {
    printf("Read token %d", tok);
    if(tok == FLOAT_LIT) {
      printf(" with value %0.3f\n", yylval.fltval);
    } else {
      printf("\n");
    }
  }
}
