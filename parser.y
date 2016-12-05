//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"
 #include "symbolTable.h"
 #include "printtree.h"
 #include "semantic.h"
 #include "yyerror.h"
 #include "codegen.h"

 #include "parser.tab.h"

 using namespace std;

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

 char * infileName;
 //char * tmFileName;

 ExpType storedType;
 bool isStatic = false;
 TreeNode * nullablePlaceholder;

// To track epsilon productions
 int firstTimeThrough = 0;



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
%type <treeNode> statement otherstmt  expressionStmt compoundStmt returnStmt breakStmt
	%type <treeNode> localDeclarations scopedVarDeclaration statementList
%type <treeNode> expression  matched unmatched
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
							{$$ = NULL;}
						;

recDeclaration 			: RECORD ID LCUR localDeclarations RCUR
							{

								$$ = newDeclNode(recDeclaration);
								$$ -> isRecord = true;
								$$ -> lineno = $1 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								//symTab.insert($$ -> attr.name, (char *)"RECORD");
								//st.print(pointerPrintStr); 
								$$ -> child[0] = $4;
								$$ -> numChildren = 1;
								$$ -> lineno = $2 -> lineno;
							}
						;

varDeclaration			: typeSpecifier varDeclList SEMI 
							{
								yyerrok;
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
						| error varDeclList SEMI {$$ = NULL;}
						| typeSpecifier error SEMI
							{yyerrok; $$ = NULL;}
						;

scopedVarDeclaration 	: scopedTypeSpecifier varDeclList SEMI
							{
								yyerrok;
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
						| error varDeclList SEMI 
							{yyerrok; $$ = NULL;}
						| scopedTypeSpecifier error SEMI 
							{yyerrok; $$ = NULL;}
						;

varDeclList				: varDeclList COMMA varDeclInitialize
							{
								yyerrok;
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
						| varDeclList COMMA error
							{$$ = NULL;}								 

						| varDeclInitialize
							{ 
								$$ = $1; 
							}
						| error
							{$$ = NULL;}
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
							{yyerrok; $$ = NULL;}
						| varDeclId COL error
							{$$ = NULL;}
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
								$$->arrLen = $3 -> numVal;
								//$$ -> isStatic = isStatic;
							}	
						| ID LBRAC error 
							{$$ = NULL;}
						| error RBRAC
							{yyerrok; $$ = NULL;}	
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
							{$$ = NULL;}
						| typeSpecifier ID LPAREN error
							{$$ = NULL;}
					 	| typeSpecifier ID LPAREN params LPAREN error
					 		{$$ = NULL;}

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
							{$$ = NULL;}
						| ID LPAREN params RPAREN error	
							{ $$ = NULL;}
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
								yyerrok;
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
						| paramList SEMI error

						| paramTypeList
							{ 
								$$ = $1; 
							}
						| error
							{$$ = NULL;}
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
							{$$ = NULL;}
						;

paramIdList				: paramIdList COMMA paramId 
							{
								yyerrok;
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

						| paramIdList COMMA error
							{$$ = NULL;}

						| paramId
							{ 
								$$ = $1; 
							}

						| error
							{$$ = NULL;}
						;

paramId 				: ID 
							{
								$$ = newDeclNode(paramDeclaration); 
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->isArray = false;
								$$->isParam = true;
								$$ -> lineno = $1 -> lineno;
							}
						| ID LBRAC RBRAC
							{
								$$ = newDeclNode(paramDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->isArray = true;
								$$->isParam = true;
								$$ -> lineno = $1 -> lineno;
							}	
						| error RBRAC
							{yyerrok; $$ = NULL;}	
						;


statement 				: matched
							{$$ = $1;}
						| unmatched
							{$$ = $1;}
						;
					
otherstmt				: expressionStmt 
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
								yyerrok;
								$$ = newStmtNode(compoundStmt); 
								$$ -> lineno = $1 -> lineno;
								$$ -> numChildren = 2;
								$$ -> child[0] = $2;
								$$ -> child[1] = $3; 

								//TODO: Remove this, enter new scope for compoundStmt
								$$ -> attr.name = $1 -> tokenString; 
								$$ -> type = Void;

								
							}
						| LCUR error statementList RCUR
							{yyerrok; $$ = NULL;}
						| LCUR localDeclarations error RCUR
							{yyerrok; $$ = NULL;}
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
								yyerrok;
								$$ = $1;

							}

						| SEMI
							{
								yyerrok;
								$$ = NULL;
								
							}

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
							{ $$ = NULL;}
						| IF error RPAREN matched ELSE matched
							{yyerrok; $$ = NULL;}


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
							{yyerrok; $$ = NULL;}
						| WHILE LPAREN error RPAREN matched
							{yyerrok; $$ = NULL;}
						| WHILE error
							{$$ = NULL;}

						| otherstmt
							{
								$$ = $1;
							}
						| error
							{$$ = NULL;}
						;

unmatched				: IF LPAREN simpleExpression RPAREN statement	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> numChildren = 2;
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;
							}		

						| IF error
							{$$ = NULL;}
						| IF error RPAREN statement
							{yyerrok; $$ = NULL;}
						| IF error RPAREN matched ELSE unmatched
							{yyerrok; $$ = NULL;}


						| WHILE LPAREN simpleExpression RPAREN statement	
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
							{yyerrok; $$ = NULL;}
						| WHILE LPAREN error RPAREN unmatched
							{yyerrok; $$ = NULL;}	

						;


returnStmt				: RETURN SEMI
							{   
								yyerrok;
								$$ = newStmtNode(returnStmt); 
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
								$$ -> type = Void;

								
							}
						| RETURN expression SEMI
							{ 	
								yyerrok;
								$$ = newStmtNode(returnStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> lineno = $1 -> lineno;
								$$ -> child[0] = $2;
								$$ -> numChildren = 1;
								$$ -> type = Void;
								
							}
						;

breakStmt 				: BREAK SEMI
							{	
								yyerrok;
								$$ = newStmtNode(breakStmt);
								$$ -> attr.name = $1 -> tokenString;
								$$ -> type = Void;
								
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
							{$$ = NULL;}

						| mutable ADDASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}

						| error ADDASS error 
							{$$ = NULL;}
	
						| mutable SUBASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}

						| error SUBASS error 
							{$$ = NULL;}

						| mutable MULASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}

						| error MULASS error 
							{$$ = NULL;}	

						| mutable DIVASS expression
							{
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
							}

						| error DIVASS error 
							{$$ = NULL;}	

						| mutable INC 
							{	
								yyerrok;
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
								
							}

						| error INC
							{yyerrok; $$ = NULL;}

						| mutable DEC 
							{
								yyerrok;
								$$ = newExpNode(AssK);
								$$ -> child[0] = $1;
								$$ -> numChildren = 2;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> lineno = $2 -> lineno;
								
							}

						| error DEC
							{yyerrok; $$ = NULL;}

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
								$$ -> lineno = $2 -> lineno;
							}
						| simpleExpression OR error
							{$$ = NULL;}
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
								$$ -> lineno = $2 -> lineno;
						}
						| andExpression AND error
							{$$ = NULL;}
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
							{$$ = NULL;}
							
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
							{$$ = NULL;}
						| error relop sumExpression
							{yyerrok; $$ = NULL;}	
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
							{yyerrok; $$ = NULL;}	
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
							{$$ = NULL;}
							
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
							{$$ = NULL;}
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
								$$ -> lineno = $1 -> lineno;
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
								$$ -> lineno = $3 -> lineno;
							}
						;						

immutable				: LPAREN expression RPAREN
							{	
								$$ = $2;
								yyerrok;
							} 

						| LPAREN error
							{$$ = NULL;}
						| error RPAREN
							{yyerrok; $$ = NULL;}	

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
							{yyerrok; $$ = NULL;}
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
								yyerrok;
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
						| argList COMMA error
							{$$ = NULL;}
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
	bool syntaxErrors = false;

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
		

		//Gets filename, appends ".tm"
		infileName = argv[optCount];
	

		yyin = infile;
	}
	initErrorProcessing();
	yyparse();
	fclose(yyin);

	if (numErrors != 0)
	{
		syntaxErrors = true;
	}
	
	savedTree = setup(setupTree, savedTree);

	// print -p before errors
	if (printingTree == 1 && !capP) //1)
	{
		printTree(savedTree, capP);
	}


	if(!syntaxErrors)
	{
		scopeAndTypeR(savedTree);
	}
	

	if(symTab.lookup("main") == NULL && !syntaxErrors)
	{
		printError(-2, 0, NULL, 0, na, na, 0);
	}

	/* Symtab printing stuff 
	//symTab.print(pointerPrintStr);
	//finalSymTab = getSymTab();
	//finalSymTab.print(pointerPrintStr);
	*/

	// print -P w types after errors
	if (printingTree == 1 && capP && !syntaxErrors) //1)
	{
		printTree(savedTree, capP);
	}

	if(!syntaxErrors) printf("Offset for end of global space: %d\n", getGlobalOff());
	printf("Number of warnings: %d\n", numWarnings);
	printf("Number of errors: %d\n", numErrors);
	//symTab.print(pointerPrintStr);

	if (numErrors == 0)
	{

		generateCode(savedTree, infileName);
	}

	return 0;
}
