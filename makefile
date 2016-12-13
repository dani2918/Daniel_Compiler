BIN  = parser
CC   = g++
SRCS = $(BIN).y $(BIN).l syntaxTree.cpp symbolTable.cpp printtree.cpp typeCheck.cpp semantic.cpp yyerror.cpp emitcode.cpp codegen.cpp tm.c
OBJS = lex.yy.o $(BIN).tab.o syntaxTree.o symbolTable.o printtree.o typeCheck.o semantic.o yyerror.o emitcode.o codegen.o 
LIBS = -lm 
CCFLAGS = -g 


$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o c-

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d  $(BIN).y 

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l #-d debug

symbolTable.o: symbolTable.cpp symbolTable.h
	$(CC) $(CCFLAGS) -c symbolTable.cpp

syntaxTree.o: syntaxTree.cpp syntaxTree.h globals.h 
	$(CC) $(CCFLAGS) -c syntaxTree.cpp

printtree.o: printtree.cpp printtree.h globals.h
	$(CC) $(CCFLAGS) -c printtree.cpp

typeCheck.o: typeCheck.cpp typeCheck.h globals.h
	$(CC) $(CCFLAGS) -c typeCheck.cpp

semantic.o: semantic.cpp semantic.h globals.h
	$(CC) $(CCFLAGS) -c semantic.cpp

yyerror.o: yyerror.cpp yyerror.h globals.h
	$(CC) $(CCFLAGS) -c yyerror.cpp

emitcode.o: emitcode.cpp emitcode.h globals.h
	$(CC) $(CCFLAGS) -c emitcode.cpp

codegen.o: codegen.cpp codegen.h globals.h
	$(CC) $(CCFLAGS) -c codegen.cpp




all: 
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) syntaxTree.o lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~ *.output 

tar:
	make
	tar -cvf $(BIN).tar $(SRCS) globals.h scanType.h syntaxTree.h symbolTable.h printtree.h semantic.h typeCheck.h yyerror.h emitcode.h codegen.h makefile 

submit: 
	curl -F student=daniel -F assignment="CS445 F16 Assignment 7" -F "submittedfile=@parser.tar" "http://ec2-52-89-93-46.us-west-2.compute.amazonaws.com/cgi-bin/fileCapture.py"



