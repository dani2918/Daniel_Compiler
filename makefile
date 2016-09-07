BIN  = parser
CC   = g++
SRCS = $(BIN).y $(BIN).l scanType.h
OBJS = lex.yy.o $(BIN).tab.o
LIBS = -lm 


$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o c-

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y 

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l #-d debug


all: 
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~ *.output 

tar:
	tar -cvf $(BIN).tar $(SRCS) makefile 

