CC = gcc
CFLAGS = -g -Wall -DDEBUG -std=gnu99
# CFLAGS = -g -Wall

DEST = compile

HFILES = error.h  global.h  protos.h symbol-table.h  syntax-tree.h three.h

CFILES = error.c \
	lex.yy.c \
	main.c\
	symbol-table.c\
        syntax-tree.c \
	util.c\
	y.tab.c\
	three.c\
	assemcode.c\
	printasm.c

OFILES = error.o \
	lex.yy.o \
	main.o \
	symbol-table.o \
        syntax-tree.o \
	util.o \
	y.tab.o\
	three.o\
	assemcode.o\
	printasm.o

.c.o :
	$(CC) $(CFLAGS) -c $<

DEST : $(OFILES)
	$(CC) -o $(DEST) $(OFILES) -ll

error.o : error.h global.h syntax-tree.h error.c y.tab.h

main.o : global.h main.c

symbol-table.o : global.h symbol-table.h three.h symbol-table.c

syntax-tree.o : global.h syntax-tree.h  three.h syntax-tree.c

util.o : global.h util.h util.c

lex.yy.o : global.h error.h syntax-tree.h symbol-table.h lex.yy.c

three.o :  global.h symbol-table.h syntax-tree.h three.h three.c

assemcode.o: global.h symbol-table.h syntax-tree.h three.h assemcode.h assemcode.c

printasm.o: global.h symbol-table.h syntax-tree.h three.h printasm.h printasm.c

y.tab.c : parser.y 
	yacc -d -v parser.y

lex.yy.c : y.tab.h scanner.l 
	flex scanner.l

y.tab.h : parser.y
	yacc -d -v parser.y

clean :
	/bin/rm -f *.o core *.BAK

realclean :
	/bin/rm -f *.o core *.BAK lex.yy.c y.tab.c y.tab.h
