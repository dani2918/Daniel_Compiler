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
						| funDeclaration
						| recDeclaration
						;

recDeclaration 			: RECORD ID LCUR localDeclarations RCUR
						;

varDeclaration			: typeSpecifier varDeclList SEMI 
						;

scopedVarDeclaration 	: scopedTypeSpecifier varDeclList SEMI
						;

varDeclList				: varDeclList COMMA varDeclInitialize
						| varDeclInitialize
						;

varDeclInitialize 		: varDeclId
						| varDeclId COL simpleExpression
						;


varDeclId				: ID 
						| ID LBRAC NUMCONST RBRAC		
						;

scopedTypeSpecifier 	: STATIC typeSpecifier
						| typeSpecifier
						;

typeSpecifier 			: returnTypeSpecifier 
						| RECORD /*MAYBE rectype?*/
						;

returnTypeSpecifier		: INT 
						| BOOL
						| CHAR
						;

funDeclaration			: returnTypeSpecifier ID LPAREN params RPAREN statement
						| ID LPAREN params RPAREN statement
						;

params					: paramList
						| /* empty */
						;

paramList				: paramList SEMI paramTypeList 
						| paramTypeList
						;

paramTypeList			: typeSpecifier paramIdList
						;

paramIdList				: paramIdList COMMA paramId 
						| paramId
						;

paramId 				: ID
						| ID LBRAC RBRAC
						;

statement 				: expressionStmt /* TODO: look at grabbing sel/iter as match, unmatched*/
						| compoundStmt
						| selectionStmt 
						| iterationStmt 
						| returnStmt
						| breakStmt
						;

compoundStmt			: LCUR localDeclarations statementList RCUR
						;

localDeclarations		: localDeclarations scopedVarDeclaration
						| /* empty */
						;

statementList			: statementList statement
						| /* empty */
						;

expressionStmt			: expression SEMI 
						| SEMI
						;


/* TODO: Fix if/while*/
selectionStmt			: IF LPAREN simpleExpression RPAREN statement 
						| IF LPAREN simpleExpression RPAREN statement ELSE
						;


iterationStmt			: WHILE LPAREN simpleExpression RPAREN statement
						;



returnStmt				: RETURN SEMI
						| RETURN expression
						;

breakStmt 				: BREAK SEMI
						;

expression 				: mutable EQ expression 
						| mutable ADDASS expression
						| mutable SUBASS expression
						| mutable MULASS expression
						| mutable DIVASS expression
						| mutable INC expression
						| mutable DEC expression
						| simpleExpression 
						;


simpleExpression		: simpleExpression OR andExpression
						| andExpression
						;

	
andExpression			: andExpression AND unaryRelExpression
						| unaryRelExpression
						;

unaryRelExpression		: NOT unaryRelExpression
						| relExpression
						;

relExpression			: sumExpression relop sumExpression
						| sumExpression
						;	


relop 					: LESSEQ 
						| LT
						| GT
						| GRTEQ
						| EQ
						| NOTEQ
						;

sumExpression			: sumExpression sumop term
						| term
						;

sumop 					: ADD
						| SUB
						;

term					: term mulop unaryExpression
						| unaryExpression
						;

mulop					: MUL
						| DIV
						| MOD
						;						

unaryExpression			: unaryop unaryExpression
						| factor
						;

unaryop 				: SUB
						| MUL
						| OPT
						;

factor					: immutable 
						| mutable
						;

mutable					: ID 
						| ID LBRAC expression RBRAC 
						| mutable DOT ID
						;						

immutable				: LPAREN expression RPAREN 
						| call
						| constant 
						; 

call					: ID LPAREN args RPAREN 
						;

args 					: argList
						| /* empty */
						;


argList					: argList COMMA expression 
						| expression
						;

constant	 			: NUMCONST 	{printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", $1->lineno, $1->numVal,  $1->tokenString);}
						| CHARCONST {printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", $1->lineno, $1->charVal, $1->tokenString);}
						| BOOLCONST {printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", $1->lineno, $1->bvalue, $1->tokenString);}
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
