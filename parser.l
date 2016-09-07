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
				if(yytext[2] == 'n' || yytext[2] == '0')
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
ID 			{letter}|{letdig}*
NUMCONST	{digit}+
CHARCONST 	\'\\?.\'

comment		"//".* 
%%
{whitespace}	;
{comment}		;
\n 				{lineno++;}

"not"			{return setTokenData(NOT, "NOT");}
"and"			{return setTokenData(AND, "AND");}
"or"			{return setTokenData(OR, "OR");}
"record"		{return setTokenData(RECORD, "RECORD");}
"static"		{return setTokenData(STATIC, "STATIC");}
"int"			{return setTokenData(INT, "INT");}
"bool"			{return setTokenData(BOOL, "BOOL");}
"char"			{return setTokenData(CHAR, "CHAR");}

"==" 			{return setTokenData(EQ, "EQ");}	
"!="			{return setTokenData(NOTEQ, "NOTEQ");}
"<="			{return setTokenData(LESSEQ, "LESSEQ");}
"<"				{return setTokenData(LT, "LT");}
">="			{return setTokenData(GRTEQ, "GRTEQ");}
">"				{return setTokenData(GT, "GT");}

"+="			{return setTokenData(ADDASS, "ADDASS");}
"-="			{return setTokenData(SUBASS, "SUBASS");}
"*="			{return setTokenData(MULASS, "MULASS");}
"/="			{return setTokenData(DIVASS, "DIVASS");}
"--"			{return setTokenData(DEC, "DEC");}
"++"			{return setTokenData(INC, "INC");}


"*"				{return setTokenData(PTR);}
"?"				{return setTokenData(PTR);}



"="				{return setTokenData(ASS, "ASS");}

"+"				{return setTokenData(ADD, "ADD");}
"-"				{return setTokenData(SUB, "SUB");}
"/"				{return setTokenData(DIV, "DIV");}
"%"				{return setTokenData(MOD, "MOD");}

{NUMCONST}		{return setTokenData(NUMCONST);}
{ID}			{return setTokenData(ID);}
{CHARCONST}		{return setTokenData(CHARCONST);}

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