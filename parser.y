//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include "scanType.h"
 #include "parser.tab.h"
 
 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;

#define YYERROR_VERBOSE
void yyerror(char *errMsg)
{
 	printf("ERROR(): %s\n", errMsg);
}

void printToken(int lineno, char* tokenString)
{
	printf("Line %d Token: %s\n", lineno, tokenString);
}

void printErrToken(int lineno, char* tokenString)
{
	printf("ERROR(%d) Invalid or misplaced input character: \"%s\"\n", lineno, tokenString);
}

 %}


%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%token <tokenData> ID
%token <tokenData> NOT AND OR 
%token <tokenData> ADDASS SUBASS MULASS DIVASS DEC INC
%token <tokenData> EQ NOTEQ LESSEQ LT GRTEQ GT
%token <tokenData> ASS MUL ADD SUB DIV MOD
%token <tokenData> ERR

%union
{
	TokenData *tokenData;
}

%%
tokenlist		: tokenlist token
				| token
				;

token 			: token
				| ID 		{printf("Line %d Token: ID Value: %s\n", $1->lineno, $1->idVal);}
				| NUMCONST 	{printf("Line %d Token: NUMCONST Value: '%d' Input: %s\n", $1->lineno, $1->numVal,  $1->tokenString);}
				| CHARCONST {printf("Line %d Token: CHARCONST Value: '%c' Input: %s\n", $1->lineno, $1->charVal, $1->tokenString);}
				| NOT 		{printToken($1->lineno, $1->tokenString);}
				| AND		{printToken($1->lineno, $1->tokenString);}
				| OR		{printToken($1->lineno, $1->tokenString);}
				| ADDASS	{printToken($1->lineno, $1->tokenString);}
				| SUBASS	{printToken($1->lineno, $1->tokenString);}
				| MULASS 	{printToken($1->lineno, $1->tokenString);}
				| DIVASS	{printToken($1->lineno, $1->tokenString);}
				| DEC		{printToken($1->lineno, $1->tokenString);}
				| INC 		{printToken($1->lineno, $1->tokenString);}
				| EQ		{printToken($1->lineno, $1->tokenString);}
				| NOTEQ		{printToken($1->lineno, $1->tokenString);}
				| LESSEQ	{printToken($1->lineno, $1->tokenString);}
				| LT		{printToken($1->lineno, $1->tokenString);}
				| GRTEQ		{printToken($1->lineno, $1->tokenString);}
				| GT		{printToken($1->lineno, $1->tokenString);}
				| ASS 		{printToken($1->lineno, $1->tokenString);}
				| MUL 		{printToken($1->lineno, $1->tokenString);}
				| ADD 		{printToken($1->lineno, $1->tokenString);}
				| SUB 		{printToken($1->lineno, $1->tokenString);}
				| DIV 		{printToken($1->lineno, $1->tokenString);}
				| MOD		{printToken($1->lineno, $1->tokenString);}
				| ERR		{printErrToken($1->lineno, $1->tokenString);}
				;

%%

int main(int argc, char *argv[])
{
	FILE *infile = fopen(argv[1], "r");
	yyin = infile;
	yyparse();
	fclose(yyin);

	return 0;
}
