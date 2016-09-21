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
void yyerror(const char *errMsg)
{
 	printf("ERROR(): %s\n", errMsg);
}

void printToken(int lineno, char* tokenString)
{
	printf("Line %d Token: %s\n", lineno, tokenString);
}

void printErrToken(int lineno, char* tokenString)
{
	printf("ERROR(%d): Invalid or misplaced input character: \"%s\"\n", lineno, tokenString);
}

 %}


%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%token <tokenData> ID
%token <tokenData> BOOLCONST
%token <tokenData> NOT AND OR RECORD STATIC INT BOOL CHAR IF ELSE WHILE RETURN BREAK
%token <tokenData> OPT DOT
%token <tokenData> ADDASS SUBASS MULASS DIVASS DEC INC
%token <tokenData> EQ NOTEQ LESSEQ LT GRTEQ GT
%token <tokenData> ASS MUL ADD SUB DIV MOD
%token <tokenData> LPAREN RPAREN LBRAC RBRAC LCUR RCUR COMMA COL SEMI
%token <tokenData> ERR

%union
{
	TokenData *tokenData;
}

%%
program					: declarationList
						;

declarationList			: declarationList declaration 
						| declaration
						;



declaration 			: varDeclaration	
						;


varDeclaration			: varDeclList SEMI
						;



varDeclList				: varDeclList COMMA varDeclInitialize
						| varDeclInitialize
						;

varDeclInitialize 		: simpleExpression
						;



simpleExpression		: andExpression
						;

	
andExpression			: unaryRelExpression
						;

unaryRelExpression		: relExpression
						;



relExpression			: sumExpression
						;	

sumExpression			: term
						;

term					: unaryExpression
						;

unaryExpression			: factor
						;

factor					: immutable
						;

immutable				: constant
						;

constant	 			: NUMCONST 	{printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", $1->lineno, $1->numVal,  $1->tokenString);}
				
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
