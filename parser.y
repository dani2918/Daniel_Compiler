//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"


 #include "parser.tab.h"



 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;
 extern int lineno;

 //Like the TreeNode from tiny.y
 static TreeNode * savedTree;

//#define YYERROR_VERBOSE 1
void yyerror(const char *errMsg)
{
 	printf("ERROR(%d): %s\n", lineno, errMsg);
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
%error-verbose





%union
{
	TokenData *tokenData;
}

%union
{
	TreeNode *treeNode;
}


%type <treeNode> declarationList declaration
%type <treeNode> varDeclaration funDeclaration recDeclaration

%%
program					: declarationList
							{savedTree = $1;}
						;

declarationList			: declarationList declaration 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;
									$$ = $1;
								}
								else $$ = $2;
								
							}

						| declaration 
							{ $$ = $1;}
						;


declaration 			: varDeclaration
							{$$ = $1; }	
						| funDeclaration 
							{$$ = $1; }
						| recDeclaration 
							{$$ = $1; }
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

funDeclaration			: typeSpecifier ID LPAREN params RPAREN statement
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


statement 				: selectIterStmt
						| otherStatement
						;

otherStatement 			: expressionStmt /* TODO: look at grabbing sel/iter as match, unmatched*/
						| compoundStmt
						/*| iterationStmt */
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

selectIterStmt 			: firstmatched  
						| unmatched
						; 

firstmatched			: IF LPAREN simpleExpression RPAREN matched ELSE matched 
						| WHILE LPAREN simpleExpression RPAREN matched
						;

matched					: IF LPAREN simpleExpression RPAREN matched ELSE matched 
						| WHILE LPAREN simpleExpression RPAREN matched
						| otherStatement
						;

unmatched				: IF LPAREN simpleExpression RPAREN matched	
						| IF LPAREN simpleExpression RPAREN unmatched						
						| IF LPAREN simpleExpression RPAREN ELSE unmatched
						| WHILE LPAREN simpleExpression RPAREN unmatched						
						| WHILE LPAREN simpleExpression RPAREN ELSE unmatched
						;



/*iterationStmt			: WHILE LPAREN simpleExpression RPAREN statement
						;

*/

returnStmt				: RETURN SEMI
						| RETURN expression SEMI
						;

breakStmt 				: BREAK SEMI
						;

expression 				: mutable ASS expression 
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
						| mutable LBRAC expression RBRAC 
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

constant	 			: NUMCONST 	
						| CHARCONST 
						| BOOLCONST 
						;

%%

int main(int argc, char *argv[])
{

	extern int yydebug;
	int optCount = 1;

	// for options
	int opt; 

	while ((opt = getopt(argc, argv, "d::")) != -1)
	{
		switch (opt)
		{
			case 'd':
				yydebug = 1;
				break;
		}
		optCount++;
	}
	FILE *infile = fopen(argv[optCount], "r");
	yyin = infile;
	yyparse();
	fclose(yyin);

	printTree(savedTree);

	return 0;
}
