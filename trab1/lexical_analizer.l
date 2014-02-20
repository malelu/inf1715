%{
#define FOO 100
#define BAR 101
#define STRING 200
#define ERROR 999999

int done = 0;

%}

%%

\"([^\n"\\]|\\["\\])*\" { return STRING; }

if { return IF; }
else { return ELSE; }
while { return WHILE; }
return { return RETURN; }
int { return INT; }
char { return CHAR; }
bool { return TRUE; }
true { return TRUE; }
false { return FALSE; }
 

"(" { return OPEN_PARENTHESIS; }
")" { return CLOSE_PARENTHESIS; }

([ \t\n]*) { }

. { return ERROR; }

%%

yywrap() {
done = 1;
}

int main() {
while (!done) {
printf("%d\n", yylex());
printf("%s\n", yytext);
}
return 0;
}


