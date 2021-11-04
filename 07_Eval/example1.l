%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
[0-9]+ return NUMBER;
"+" return ADD;
"-" return SUB;
"*" return MUL;
"/" return DIV;
"(" return LP;
" return RP;
\n /* ignore end of line */;
[ \t]+ /* ignore whitespace */
%%
void main()
{
    yylex(); /* start the analysis*/
}
int yywrap()
{
    return 1;
}