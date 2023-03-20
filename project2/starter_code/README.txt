Name: Benjamin Scholar
CaseID: bbs27
email: scholar@case.edu

Changes:
Tokens containing a single character such as parens, brackets, and semicolons were 
accessed via their character symbol instead of defining new tokens for each one. Bison
starts custom tokens at a value of 256, leaving room for the 256 ascii character to be accessed  with their respective ascii values.
