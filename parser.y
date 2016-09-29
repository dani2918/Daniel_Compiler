//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"
 #include "symbolTable.h"


 #include "parser.tab.h"



 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;
 extern int lineno;

 //SymbolTable st;
 

 //Like the TreeNode from tiny.y
 static TreeNode * savedTree;
 int savedLineNo;

 ExpType storedType;
 bool isStatic = false;
 TreeNode * nullablePlaceholder;

// To track epsilon productions
 int firstTimeThrough = 0;

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

//SymbolTable passSymTab()
//{
//	return st;
//}

 %}


%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%token <tokenData> ID RECTYPE
%token <tokenData> BOOLCONST
%token <tokenData> NOT AND OR RECORD STATIC INT BOOL CHAR IF ELSE WHILE RETURN BREAK
%token <tokenData> RAND DOT
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

%union
{
	ExpType expType;
	int number; 
	TokenData * td;
	TreeNode * t;
	char * name;

}

%union
{
	char * c;
}


%type <treeNode> declarationList declaration
%type <treeNode> varDeclaration funDeclaration  recDeclaration varDeclList varDeclInitialize varDeclId simpleExpression
	%type <treeNode> params paramList paramTypeList paramIdList paramId
%type <treeNode> statement otherStatement selectIterStmt expressionStmt compoundStmt returnStmt breakStmt
	%type <treeNode> localDeclarations scopedVarDeclaration statementList
%type <treeNode> expression firstmatched matched unmatched
	%type <treeNode> andExpression unaryRelExpression relExpression sumExpression term unaryExpression
	%type <treeNode> factor immutable mutable
	%type <treeNode> argList args call constant
%type <treeNode>   scopedTypeSpecifier
%type <expType> typeSpecifier returnTypeSpecifier
%type <td> relop sumop mulop unaryop




%%
program					: declarationList
							{savedTree = $1;}
						;

declarationList			: declarationList declaration 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									//printf("t is NULL\n");
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;
									$$ = $1;
								}
								else 
								{
									//printf("t is not NULL\n");
									$$ = $2;
								}
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

// TODO: RECORD
recDeclaration 			: RECORD ID LCUR localDeclarations RCUR
							{
								$$ = newDeclNode(recDeclaration);
								$$ -> isRecord = true;
								$$ -> lineno = $1 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								st.insert($$ -> attr.name, (char *)"RECORD");
								//st.print(pointerPrintStr); 
								$$ -> child[0] = $4;
								$$ -> numChildren = 1;
								
							}
						;

varDeclaration			: typeSpecifier varDeclList SEMI 
							{
								TreeNode * t = $2;
								if (t != NULL)
								{
									do 
									{
										t -> type = $1;
										t = t -> sibling;
									} while (t != NULL);
									$$ = $2;
								}
								else 
								{
									$$ = NULL;
								}
 							}
						;

// TOOD: scopedVarDeclaration
scopedVarDeclaration 	: scopedTypeSpecifier varDeclList SEMI
							{
								TreeNode * t = $2;
								if (t != NULL)
								{
									do 
									{
										t -> type = $1 -> type;
										t -> isStatic = $1 -> isStatic;
										t = t -> sibling;
									} while (t != NULL);
									$$ = $2;
								}
								else 
								{
									$$ = NULL;
								}
							}
						;

varDeclList				: varDeclList COMMA varDeclInitialize
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									//printf("t is not NULL\n");
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									$$ = $1;
									
								}
								else 
								{
									//printf("t is NULL\n");
									$$ = $3;
									
								}
								
								
							}							


								 

						| varDeclInitialize
							{ 
								$$ = $1; 
							}
						;

varDeclInitialize 		: varDeclId
							{	
 								$$ = $1;
							}
						| varDeclId COL simpleExpression
							{
								$$ -> child[0] = $3;
								$$ -> numChildren = 1;
								$$ = $1;
							}
						;


varDeclId				: ID 
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ -> lineno = $1 -> lineno;
								//$$->type = storedType; 
								$$->isArray = false;
								//$$ -> isStatic = isStatic;
							}
						| ID LBRAC NUMCONST RBRAC
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								//$$->type = storedType; 
								$$ -> lineno = $1 -> lineno;
								$$->isArray = true; //printf("Array\n");
								//$$ -> isStatic = isStatic;
							}		
						;


scopedTypeSpecifier 	: STATIC typeSpecifier
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> isStatic = true;
								$$ -> type = $2;
							}
						| typeSpecifier
							{ 
								$$ = newDeclNode(varDeclaration);
								$$ -> type = $1;
							}
						;

typeSpecifier 			: returnTypeSpecifier 
							{
								$$ = $1;
							}

							//TODO: RECORD part
						| RECTYPE /*MAYBE rectype?*/
							{
								//$$ = newDeclNode(recDeclaration);
								$$  = record; //printf("type: %d \n", $$ -> type);
							}
						;

returnTypeSpecifier		: INT 
							{
								//$$ -> type = integer; printf("type: %d \n", $$ -> type);
								$$ = integer;	//printf("type: %d \n", $$);
							}
						| BOOL
							{
								//$$ -> type = boolean; printf("type: %d \n", $$ -> type);
								//storedType = boolean;
								$$ = boolean; //printf("type: %d \n", $$);
							}
						| CHAR
							{
								//$$ -> type = character; printf("type: %d \n", $$ -> type);
								//storedType = character;
								$$ = character;// printf("type: %d \n", $$);
							}
						;

funDeclaration			: typeSpecifier ID LPAREN params RPAREN statement
							{
								//printf("we have this one\n");
								//storedType = $1;
								//TreeNode * f;
								//f = newExpTypeNode();
								//f -> type = $1;
								//storedType = $1;
								$$ = newDeclNode(funDeclaration);
								$$ -> lineno = $2 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> numChildren = 2;
								$$ -> type = $1;
								$$ -> child[0] = $4;
								$$ -> child[1] = $6;
								
							}

						| ID LPAREN params RPAREN statement
							{
								$$ = newDeclNode(funDeclaration);
								$$ -> type = Void;
								$$ -> lineno = $1 -> lineno;
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5; 
							}
						;




params					: paramList
							{
								$$ = $1;
							}
						| /* empty */
							{
								$$ = NULL;
							}
						;

paramList				: paramList SEMI paramTypeList 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									$$ = $1;
									
								}
								else 
								{
									$$ = $3;
									
								}
								
							}

						| paramTypeList
							{ 
								$$ = $1; 
							}
						;


paramTypeList			: typeSpecifier paramIdList
							{
								TreeNode * t = $2;
								if (t != NULL)
								{
									do 
									{
										t -> type = $1;
										t = t -> sibling;
									} while (t != NULL);
									$$ = $2;
								}
								else 
								{
									$$ = NULL;
								}
							}
						;

paramIdList				: paramIdList COMMA paramId 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									$$ = $1;
								}
								else 
								{
									$$ = $3; 
									
								}
								
							}
							

						| paramId
							{ 
								$$ = $1; 
							}
						;

paramId 				: ID 
							{
								$$ = newDeclNode(paramDeclaration); 
								$$ -> attr.name = strdup($1 -> tokenString);
								//$$->type = storedType; 
								$$->isArray = false;
								$$->isParam = true;
							}
						| ID LBRAC RBRAC
							{
								$$ = newDeclNode(paramDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								//$$->type = storedType; 
								$$->isArray = true;
								$$->isParam = true;
							}		
						;


statement 				: selectIterStmt
							{$$ = $1;}
						| otherStatement
							{
								$$ = $1; //printf("line 360\n");
							}
						;

otherStatement 			: expressionStmt 
							{$$ = $1;}
						| compoundStmt
							{$$ = $1;}
						| returnStmt
							{$$ = $1;}
						| breakStmt
							{$$ = $1;}
						;
					

compoundStmt			: LCUR localDeclarations statementList RCUR
							{
								$$ = newStmtNode(compoundStmt); //printf("compoundStmt!\n\n");
								$$ -> lineno = $1 -> lineno;
								$$ -> numChildren = 2;
								$$ -> child[0] = $2;
								$$ -> child[1] = $3; //printf("Line 385\n");
							}
						;

localDeclarations		: localDeclarations scopedVarDeclaration
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t -> sibling != NULL)
									{
										t = t -> sibling;
									}
									t -> sibling = $2;
									$$ = $1;
								}
								else
								{
									$$ = $2;
								}
								
							}
							
						| /* empty */
							{
								//$$ = newStmtNode(expressionStmt);
								//firstTimeThrough = 1;
								$$ = NULL;
							}
						;

statementList			: statementList statement
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t -> sibling != NULL)
									{
										t = t -> sibling;
									}
									t -> sibling = $2;
									$$ = $1;
								}
								else
								{
									$$ = $2;
								}
								
							}

						| /* empty */
							{
								//printf("got here!\n\n\n");
							//	$$ = newStmtNode(expressionStmt);
								//firstTimeThrough = 1;
								$$ = NULL;
							}
						;

expressionStmt			: expression SEMI 
							{
								$$ = $1;
							}

						| SEMI
							{
								$$ = NULL;
							}
						;



selectIterStmt 			: firstmatched 
							{ $$ = $1;} 
						| unmatched
							{ $$ = $1;} 
						; 

firstmatched			: IF LPAREN simpleExpression RPAREN matched ELSE matched 
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> numChildren = 3;
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
								$$ -> lineno = $1 -> lineno;
							}
						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
							}
						;

matched					: IF LPAREN simpleExpression RPAREN matched ELSE matched 
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
								$$ -> numChildren = 3;
								$$ -> lineno = $1 -> lineno;
							}
						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> numChildren = 2;
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
							}
						| otherStatement
							{
								$$ = $1;
							}
						;

unmatched				: IF LPAREN simpleExpression RPAREN matched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
							}
						| IF LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
							}					
						| IF LPAREN simpleExpression RPAREN matched ELSE unmatched
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3;
								$$ -> child[2] = $5;
								$$ -> child[2] = $7;
								$$ -> numChildren = 3;
								$$ -> lineno = $1 -> lineno;

							}
						| WHILE LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> numChildren = 2;
								$$ -> lineno = $1 -> lineno;
							}					
	
						;


returnStmt				: RETURN SEMI
							{
								$$ = newStmtNode(returnStmt); // printf("line 521\n");
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;

							}
						| RETURN expression SEMI
							{
								$$ = newStmtNode(returnStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
							}
						;

breakStmt 				: BREAK SEMI
							{
								$$ = newStmtNode(breakStmt);
								$$ -> attr.name = $1 -> tokenString;
							}
						;
//_________________________________________________________________________________


expression 				: mutable ASS expression 
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable ADDASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable SUBASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable MULASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable DIVASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable INC 
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								//$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}
						| mutable DEC 
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								//$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
								//$$ -> attr.td = $2;
							}
						| simpleExpression 
							{
								$$ = $1;
							}
						;


simpleExpression		: simpleExpression OR andExpression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								//printf("TD string is: %s\n", $$->attr.name);
							}
						| andExpression
							{
								$$ = $1;
							}
						;

	
andExpression			: andExpression AND unaryRelExpression
						{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
						}
						| unaryRelExpression
							{
								$$ = $1;
							}
						;

unaryRelExpression		: NOT unaryRelExpression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
								$$ -> attr.name = strdup($1 -> tokenString);
							}
						| relExpression
							{
								$$ = $1;
							}
						;

relExpression			: sumExpression relop sumExpression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
							}

						| sumExpression
							{
								$$ = $1;
							}
						;	


relop 					: LESSEQ 
							{$$ = $1;}
						| LT
							{$$ = $1;}
						| GT
							{$$ = $1;}
						| GRTEQ
							{$$ = $1;}
						| EQ
							{$$ = $1;}
						| NOTEQ
							{$$ = $1;}
						;

sumExpression			: sumExpression sumop term
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = $2 -> tokenString;
							}
						| term
							{
								$$ = $1;
							}
						;

sumop 					: ADD
							{$$ = $1;}
						| SUB
							{$$ = $1;}
						;

term					: term mulop unaryExpression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = $2 -> tokenString;
								$$ -> lineno = $2 -> lineno;
							}
						| unaryExpression
							{$$ = $1;}
						;

mulop					: MUL
							{$$ = $1;}
						| DIV
							{$$ = $1;}
						| MOD
							{$$ = $1;}
						;						

unaryExpression			: unaryop unaryExpression
							{	//TODO: FIX THIS
								$$ = newExpNode(OpK);
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
								$$ -> attr.td = $1;
							}
						| factor
							{$$ = $1;}
						;

unaryop 				: SUB
							{$$ = $1;}
						| MUL
							{$$ = $1;}
						| RAND
							{$$ = $1;}
						;

factor					: immutable 
							{$$ = $1;}
						| mutable
							{$$ = $1;}
						;

mutable					: ID 
							{
								$$ = newExpNode(IdK);
								$$ -> attr.name = $1 -> tokenString;
							//	$$->type = storedType; 
							//	$$->isArray = false;
							}
						| mutable LBRAC expression RBRAC 
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
							}
						| mutable DOT ID
							{
								$$ = newExpNode(OpK);
								$$ -> attr.name = $2 -> tokenString;
								$$ -> child[0] = $1;
								
								TreeNode * t;
								t = newExpNode(IdK);
								t -> attr.name = strdup($3 -> tokenString);
								//$$->type = storedType; 
								t ->isArray = false;
								$$ -> child[1] = t;
								$$ -> numChildren = 2;
							}
						;						

immutable				: LPAREN expression RPAREN
							{	// MAY BE WRONG
								$$ = $2;
							} 
						| call
							{
								$$ = $1;
							}
						| constant 
							{
								$$ = $1;
							}
						; 

call					: ID LPAREN args RPAREN 
							{
								$$ = newExpNode(CallK);
								$$ -> child[0] = $3;
								$$ -> numChildren = 1;
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ ->isArray = false;

							}
						;

args 					: argList	
							{
								$$ = $1;
							}
						| /* empty */
							{
								$$ = NULL;
							}
						;


argList					: argList COMMA expression 
							{
								TreeNode *t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t->sibling;
									}
									t->sibling = $3;
									$$ = $1;
								}
								else 
								{
									$$ = $3;
								}
							}

						| expression
							{
								$$ = $1;
							}
						;

constant	 			: NUMCONST 
							{
								$$ = newExpNode(constK);
								$$ ->attr.value = $1->numVal;
								$$ -> type = integer;
							}	
						| CHARCONST 
							{
								$$ = newExpNode(constK);
								$$ ->attr.cvalue = $1->charVal;
								$$ -> type = character;
							}	
						| BOOLCONST 
							{
								$$ = newExpNode(constK);
								$$ -> attr.bvalue = $1->bvalue;
								$$ -> type = boolean;
							}
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

	printf("Number of warnings: %d\n", 0);
	printf("Number of errors: %d\n", 0);

	return 0;
}
