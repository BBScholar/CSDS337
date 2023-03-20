%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    FILE *in_file, *out_file;

    int lines = 0, words = 0, chars = 0;
    int multi = 0, single = 0;
    int n_for = 0, n_while = 0, n_do = 0;
    
    int lines_tot = 0, words_tot = 0, chars_tot= 0;
    int multi_tot = 0, single_tot = 0;
    int n_for_tot = 0, n_while_tot = 0, n_do_tot = 0;

    int files = 0;

    bool in_single = false;
    int multi_depth = 0;
%}

ws [ \t]
word [a-zA-Z0-9_]

%%

\n { lines++; chars++; in_single = false; output(yytext); }

for     { n_for++; update();  output(yytext); }
while   { n_while++; update();  output(yytext); }
do      { n_do++; update(); output(yytext); }

{word}+ { update(); output(yytext); } 

\/\/ { 
    if(!in_single && multi_depth == 0) {
        in_single = true;
        single++;
    }
    update();
    output(yytext);
}
\/\* { 
    if(multi_depth == 0) {
        multi++; 
    }
    multi_depth++;
    update(); output(yytext); 
}
\*\/ { 
    if(multi_depth > 0) multi_depth--;
    update();
    output(yytext);
}

{ws}+ { chars += yyleng; fprintf(out_file, " "); }
. {chars++; words++; output(yytext); }

%%

void output(char* text) {
   fprintf(out_file, "%s", text); 
}

void update() {
    words++;
    chars += yyleng;
}

int main(int argc, char** argv) {
    argc--;
    argv++;

    out_file = fopen("problem4output", "w");
    int i;

    if(argc < 1) {
        printf("1 or more input files required.\n");
        return 1;
    }

    for(i = 0; i < argc; ++i) {
        const char* current_fn = argv[i];
        in_file = fopen(current_fn, "r");

        if(!in_file) {
            perror(current_fn);
            continue;
        }

        files++;

        fprintf(out_file, "File: %s\n\n", current_fn);

        // lex file
        yyrestart(in_file);
        yylex();

        // close files
        fclose(in_file);

        // 
        fprintf(out_file, "\n\n");

        // write stats to overall output file
        fprintf(out_file, "Characters: %d\tWords: %d\tLines: %d\n", chars, words, lines);
        fprintf(out_file, "Single-line comments: %d\tMulti-line comments: %d\n", single, multi);
        fprintf(out_file, "For: %d\tDo: %d\tWhile: %d\n\n", n_for, n_do, n_while);

        
        // tally totally counters
        chars_tot += chars;
        words_tot += words;
        lines_tot += lines;
        single_tot += single;
        multi_tot += multi;
        n_for_tot += n_for;
        n_do_tot += n_do;
        n_while_tot += n_while;
        
        // reset counters
        chars = 0;
        words = 0;
        lines = 0;
        single = 0;
        multi = 0;
        n_for = 0;
        n_do = 0;
        n_while = 0;


    }

    fprintf(out_file, "\nTotal for all %d files:\n", files);
    fprintf(out_file, "Characters: %d\tWords: %d\tLines: %d\n", chars_tot, words_tot, lines_tot);
    fprintf(out_file, "Single-line comments: %d\tMulti-line comments: %d\n", single_tot, multi_tot);
    fprintf(out_file, "For: %d\tDo: %d\tWhile: %d\n", n_for_tot, n_do_tot, n_while_tot);

    fclose(out_file);

    return 0;
}
