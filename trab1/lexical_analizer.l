 /* declarations */
%{
#include "lexical_analizer.h"

int done = 0;

%}
/* regular expressions */
digit [0-9]
exp [eE][-+]?[0-9]+
hexa "0"[xX][0-9a-f-A-F]+
character [a-zA-Z]
numInt {digit}+|{hexa}
fraction ("."{digit}+|{digit}+".")
id (_|{character})+(_|{character}|{digit})*
numFloat (({digit}+{fraction}|{fraction})({exp})?|{digit}+{exp}) 
string \"([^\n"\\]|\\["\\])*\"
comment ("/*"([^*]|\n|"*"+[^*/])*"*"*"*/")
%%
 
 /* tokens */
char { return CHAR; }
int { return INT; }
float { return FLOAT; }
while { return WHILE; }
if { return IF; }
else { return ELSE; }
new { return NEW; }
return { return RETURN; }
void { return VOID; }
bool { return TRUE; }
true { return TRUE; }
false { return FALSE; }
">=" { return GREATER_EQUAL; } 
"<=" { return LESS_EQUAL; }
"==" { return EQUAL_EQUAL; }
"!=" { return NOT_EQUAL; }
"&&" { return AND; }
"||" { return OR; }
"(" { return OPEN_PARENTHESIS; }
")" { return CLOSE_PARENTHESIS; }
{string} {return STRING; }

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


