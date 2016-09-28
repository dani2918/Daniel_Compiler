BIN  = parser
CC   = g++
SRCS = $(BIN).y $(BIN).l syntaxTree.cpp 
OBJS = lex.yy.o $(BIN).tab.o syntaxTree.o
LIBS = -lm 


$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o c-

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d  $(BIN).y 

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l #-d debug

syntaxTree.o: syntaxTree.cpp syntaxTree.h globals.h 
	$(CC) $(CCFLAGS) -c syntaxTree.cpp

all: 
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) syntaxTree.o lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~ *.output 

tar:
	tar -cvf $(BIN).tar $(SRCS) globals.h scanType.h syntaxTree.h makefile 

