%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>	
#include "scanType.h"
#include "parser.tab.h"

static int lineno = 1;

int setTokenData(int tokenClass)
{
	yylval.tokenData = new TokenData;
	yylval.tokenData->tokenClass = tokenClass;
	yylval.tokenData->lineno = lineno;
	yylval.tokenData->tokenString = strdup(yytext);

	switch (tokenClass)
	{
		case ID:
			yylval.tokenData->idVal = strdup(yytext);
			break;
		case NUMCONST:
			yylval.tokenData->numVal = atoi(yytext);
			break;
		case CHARCONST:
			if(yytext[1] == '\\')
			{
				if(yytext[2] == 'n')
				{
					yylval.tokenData->charVal = '\n';
				}
				else if (yytext[2] == '0')
				{
					yylval.tokenData->charVal = '\0';
				}
				else
				{
					yylval.tokenData->charVal = yytext[2];
				}
			}
			else
			{
				yylval.tokenData->charVal = yytext[1];
			}
			break;
		case BOOLCONST:
			if(yytext[0] == 't')
			{
				yylval.tokenData->bvalue = true;
			}
			else
			{
				yylval.tokenData->bvalue = false;
			}

}

	return tokenClass;
}

int setTokenData(int tokenClass, char * tokenString)
{
	yylval.tokenData = new TokenData;
	yylval.tokenData->tokenClass = tokenClass;
	yylval.tokenData->lineno = lineno;
	yylval.tokenData->tokenString = strdup(tokenString);

	return tokenClass;
}


%}

%option noyywrap
%option yylineno

whitespace 	[ \t]+
letter 		[a-zA-Z]
digit 		[0-9]
letdig 		{digit}|{letter}
NUMCONST	{digit}+
ID 			{letter}{letdig}*
CHARCONST 	\'\\?.\'

comment		"//".* 
%%

{comment}		;
\n 				{lineno++;}

"true"			{return setTokenData(BOOLCONST);}
"false"			{return setTokenData(BOOLCONST);}

"not"			{return setTokenData(NOT, "NOT");}
"and"			{return setTokenData(AND, "AND");}
"or"			{return setTokenData(OR, "OR");}
"record"		{return setTokenData(RECORD, "RECORD");}
"static"		{return setTokenData(STATIC, "STATIC");}
"int"			{return setTokenData(INT, "INT");}
"bool"			{return setTokenData(BOOL, "BOOL");}
"char"			{return setTokenData(CHAR, "CHAR");}

"if"			{return setTokenData(IF, "IF");}
"else"			{return setTokenData(ELSE, "ELSE");}
"while"			{return setTokenData(WHILE, "WHILE");}
"return"		{return setTokenData(RETURN, "RETURN");}
"break"			{return setTokenData(BREAK, "BREAK");}

"==" 			{return setTokenData(EQ, "EQ");}	
"!="			{return setTokenData(NOTEQ, "NOTEQ");}
"<="			{return setTokenData(LESSEQ, "LESSEQ");}
"<"				{return setTokenData(LT);}
">="			{return setTokenData(GRTEQ, "GRTEQ");}
">"				{return setTokenData(GT);}

"+="			{return setTokenData(ADDASS, "ADDASS");}
"-="			{return setTokenData(SUBASS, "SUBASS");}
"*="			{return setTokenData(MULASS, "MULASS");}
"/="			{return setTokenData(DIVASS, "DIVASS");}
"--"			{return setTokenData(DEC, "DEC");}
"++"			{return setTokenData(INC, "INC");}


"*"				{return setTokenData(MUL);}
"?"				{return setTokenData(OPT);}
"."				{return setTokenData(DOT);}

"="				{return setTokenData(ASS);}

"+"				{return setTokenData(ADD);}
"-"				{return setTokenData(SUB);}
"/"				{return setTokenData(DIV);}
"%"				{return setTokenData(MOD);}

"("				{return setTokenData(LPAREN);}
")"				{return setTokenData(RPAREN);}
"["				{return setTokenData(RBRAC);}
"]"				{return setTokenData(LBRAC);}
"{"				{return setTokenData(LCUR);}
"}"				{return setTokenData(RCUR);}
","				{return setTokenData(COMMA);}
":"				{return setTokenData(COL);}
";"				{return setTokenData(SEMI);}


{NUMCONST}		{return setTokenData(NUMCONST);}
{ID}			{return setTokenData(ID);}
{CHARCONST}		{return setTokenData(CHARCONST);}

{whitespace}	;
.				{return setTokenData(ERR, yytext);}
%%


/*/////////////////

// Unary/binary op, will work when we institue grammar
"*"				{return setTokenData(MUL, "MUL");}


// int main()
// {
// 	yylex();	
// }


//////////*/