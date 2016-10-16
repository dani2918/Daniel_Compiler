BIN  = parser
CC   = g++
SRCS = $(BIN).y $(BIN).l syntaxTree.cpp symbolTable.cpp printtree.cpp semantic.cpp
OBJS = lex.yy.o $(BIN).tab.o syntaxTree.o symbolTable.o printtree.o semantic.o
LIBS = -lm 


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

semantic.o: semantic.cpp semantic.h globals.h
	$(CC) $(CCFLAGS) -c semantic.cpp

all: 
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) syntaxTree.o lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~ *.output 

tar:
	tar -cvf $(BIN).tar $(SRCS) globals.h scanType.h syntaxTree.h symbolTable.h printtree.h semantic.h makefile 

