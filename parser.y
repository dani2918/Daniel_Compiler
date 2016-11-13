//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"
 #include "symbolTable.h"
 #include "printtree.h"
 #include "semantic.h"
 #include "yyerror.h"

 #include "parser.tab.h"

#define YYERROR_VERBOSE 1

 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;
 extern int lineno;
 extern SymbolTable symTab;
 


 SymbolTable finalSymTab;
 

 //Like the TreeNode from tiny.y
 static TreeNode * savedTree;
 static TreeNode * setupTree;
 int savedLineNo;

 ExpType storedType;
 bool isStatic = false;
 TreeNode * nullablePlaceholder;

// To track epsilon productions
 int firstTimeThrough = 0;


//void yyerror(const char *errMsg)
//{
 //	printf("ERROR(%d): %s\n", lineno, errMsg);

//}

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
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;
									$$ = $1;
								}
								else 
								{
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
						| error
						;

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
								yyerrok;
 							}
						| error varDeclList SEMI
						| typeSpecifier error SEMI
							{yyerrok;}
						;

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
								yyerrok;
							}
						| error varDeclList SEMI 
							{yyerrok;}
						| scopedTypeSpecifier error SEMI 
							{yyerrok;}
						;

varDeclList				: varDeclList COMMA varDeclInitialize
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
								yyerrok;
							}							
						| varDeclList COMMA error								 

						| varDeclInitialize
							{ 
								$$ = $1; 
							}
						| error
						;

varDeclInitialize 		: varDeclId
							{	
 								$$ = $1;
							}
						| varDeclId COL simpleExpression
							{
								$$ = $1;
								$$ -> child[0] = $3;
								$$ -> numChildren = 1;
								
							}
						| error COL simpleExpression 
							{yyerrok;}
						| varDeclId COL error
						;


varDeclId				: ID 
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ -> lineno = $1 -> lineno;
								$$->isArray = false;
								//$$ -> isStatic = isStatic;
							}
						| ID LBRAC NUMCONST RBRAC
							{

								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ -> lineno = $1 -> lineno;
								$$->isArray = true; 
								//$$ -> isStatic = isStatic;
							}	
						| ID LBRAC error 
						| error RBRAC
							{yyerrok;}	
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

						| RECTYPE /*MAYBE rectype?*/
							{
								$$  = record; 
							}
						;

returnTypeSpecifier		: INT 
							{
								$$ = integer;	
							}
						| BOOL
							{
								$$ = boolean; 
							}
						| CHAR
							{
								$$ = character;
							}
						;

funDeclaration			: typeSpecifier ID LPAREN params RPAREN statement
							{
								$$ = newDeclNode(funDeclaration);
								$$ -> lineno = $2 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> numChildren = 2;
								$$ -> type = $1;
								$$ -> child[0] = $4;
								$$ -> child[1] = $6;
								
							}
						| typeSpecifier error
						| typeSpecifier ID LPAREN error
					 	| typeSpecifier ID LPAREN params LPAREN error

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
						| ID LPAREN error
						| ID LPAREN params RPAREN error	
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
								yyerrok;
							}
						| paramList SEMI error

						| paramTypeList
							{ 
								$$ = $1; 
							}
						| error
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
						| typeSpecifier error
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
								yyerrok;
							}

						| paramIdList COMMA error

						| paramId
							{ 
								$$ = $1; 
							}

						| error
						;

paramId 				: ID 
							{
								$$ = newDeclNode(paramDeclaration); 
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->isArray = false;
								$$->isParam = true;
							}
						| ID LBRAC RBRAC
							{
								$$ = newDeclNode(paramDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->isArray = true;
								$$->isParam = true;
							}	
						| error RBRAC
							{yyerrok;}	
						;


statement 				: selectIterStmt
							{$$ = $1;}
						| otherStatement
							{ $$ = $1; }
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
								$$ = newStmtNode(compoundStmt); 
								$$ -> lineno = $1 -> lineno;
								$$ -> numChildren = 2;
								$$ -> child[0] = $2;
								$$ -> child[1] = $3; 

								//TODO: Remove this, enter new scope for compoundStmt
								$$ -> attr.name = $1 -> tokenString; 
								$$ -> type = Void;

								yyerrok;
							}
						| LCUR error statementList RCUR
							{yyerrok;}
						| LCUR localDeclarations error RCUR
							{yyerrok;}
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
								$$ = NULL;
							}
						;

expressionStmt			: expression SEMI 
							{
								$$ = $1;
								yyerrok;
							}

						| SEMI
							{
								$$ = NULL;
								//printf("Got here\n");
								yyerrok;
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
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 3;
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}

						| IF error RPAREN matched ELSE matched
							{yyerrok;}


						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}
						| WHILE error RPAREN matched
							{yyerrok;}
						| WHILE LPAREN error RPAREN matched
							{yyerrok;}
						;

matched					: IF LPAREN simpleExpression RPAREN matched ELSE matched 
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
								$$ -> numChildren = 3;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}

						| IF LPAREN error
						| IF error RPAREN matched ELSE matched
							{yyerrok;}

						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 2;
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}

						| WHILE error RPAREN matched
							{yyerrok;}
						| WHILE LPAREN error RPAREN matched
							{yyerrok;}
						| WHILE error

						| otherStatement
							{
								$$ = $1;
							}
						| error
						;

unmatched				: IF LPAREN simpleExpression RPAREN matched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}
						| IF LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}					
						| IF LPAREN simpleExpression RPAREN matched ELSE unmatched
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> child[0] = $3;
								$$ -> child[2] = $5;
								$$ -> child[2] = $7;
								$$ -> numChildren = 3;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;

							}
						| IF error
							//{printf("got here\n");}
						| IF error RPAREN unmatched
							{yyerrok;}
						| IF error RPAREN matched ELSE unmatched
							{yyerrok;}



						| WHILE LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> numChildren = 2;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}					


						| WHILE error RPAREN unmatched
							{yyerrok;}
						| WHILE LPAREN error RPAREN unmatched
							{yyerrok;}
						;


returnStmt				: RETURN SEMI
							{
								$$ = newStmtNode(returnStmt); 
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;

								yyerrok;
							}
						| RETURN expression SEMI
							{
								$$ = newStmtNode(returnStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
								$$ -> type = Void;
								yyerrok;
							}
						;

breakStmt 				: BREAK SEMI
							{
								$$ = newStmtNode(breakStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> type = Void;
								yyerrok;
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

						| error ASS error 

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
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
								yyerrok;
							}

						| error INC
							{yyerrok;}

						| mutable DEC 
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
								yyerrok;
							}

						| error DEC
							{yyerrok;}

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

							}
						| simpleExpression OR error
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
						| andExpression AND error
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

						| NOT error 
							
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

						| sumExpression relop error
						| error relop sumExpression
							{yyerrok;}	
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
								$$ -> lineno = $2 -> lineno;
							}

						| sumExpression sumop error
							{yyerrok;}	
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

						| term mulop error
							
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
							{	
								$$ = newExpNode(OpK);
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
							}
						| unaryop error
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
								t ->isArray = false;
								$$ -> child[1] = t;
								$$ -> numChildren = 2;
							}
						;						

immutable				: LPAREN expression RPAREN
							{	
								$$ = $2;
								yyerrok;
							} 

						| LPAREN error
						| error RPAREN
							{yyerrok;}	

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
								$$ -> lineno = $1 -> lineno;

							}
						| error LPAREN
							{yyerrok;}
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
								yyerrok;
							}
						| argList COMMA error
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
	int printingTree = 0;
	numWarnings = 0;
	numErrors = 0;

	bool capP;


	
	
	// for options
	int opt; 

	while ((opt = getopt(argc, argv, "dpP::")) != -1)
	{
		switch (opt)
		{
			case 'd':
				yydebug = 1;
				break;
			case 'p':
				printingTree = 1;
				capP = false;
				break;
			case 'P':
				printingTree = 1;
				capP = true;
				break;
		}
		optCount++;
	}
	

	if(optCount < argc)
	{
		FILE *infile = fopen(argv[optCount], "r");
		if (infile == NULL)
		{
			printError(-1, 0, argv[optCount], 0, na, na, 0);
			exit(-1);
		}
		yyin = infile;
	}
	initErrorProcessing();
	yyparse();
	fclose(yyin);
	
	savedTree = setup(setupTree, savedTree);

	// print -p before errors
	if (printingTree == 1 && !capP) //1)
	{
		printTree(savedTree, capP);
	}

	scopeAndTypeR(savedTree);
	

	if(symTab.lookup("main") == NULL)
	{
		printError(-2, 0, NULL, 0, na, na, 0);
	}

	/* Symtab printing stuff 
	//symTab.print(pointerPrintStr);
	//finalSymTab = getSymTab();
	//finalSymTab.print(pointerPrintStr);
	*/

	// print -P w types after errors
	if (printingTree == 1 && capP) //1)
	{
		printTree(savedTree, capP);
	}

	printf("Number of warnings: %d\n", numWarnings);
	printf("Number of errors: %d\n", numErrors);
	//symTab.print(pointerPrintStr);

	return 0;
}
