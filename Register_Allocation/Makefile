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
	printasm.c\
	peep_opti.c\
	block_design.c\
	intra_cp_prop.c\
	gen_kill_block.c\
	liveness_analysis.c\
	remove_dead.c\
	cal_live_range.c\
	create_inter_graph.c\
	graph_coloring.c\
	insert_reg.c

OFILES = error.o \
	lex.yy.o \
	main.o \
	symbol-table.o \
    syntax-tree.o \
	util.o \
	y.tab.o\
	three.o\
	assemcode.o\
	printasm.o\
	peep_opti.o\
	block_design.o\
	intra_cp_prop.o\
	gen_kill_block.o\
	liveness_analysis.o\
	remove_dead.o\
	cal_live_range.o\
	create_inter_graph.o\
	graph_coloring.o\
	insert_reg.o

.c.o :
	$(CC) $(CFLAGS) -c $<

DEST : $(OFILES)
	$(CC) -o $(DEST) $(OFILES) -ll

error.o : error.h global.h syntax-tree.h error.c y.tab.h

main.o : global.h main.c

symbol-table.o : global.h symbol-table.h three.h  cal_live_range.h symbol-table.c

syntax-tree.o : global.h syntax-tree.h  three.h syntax-tree.c

util.o : global.h util.h util.c

lex.yy.o : global.h error.h syntax-tree.h symbol-table.h lex.yy.c

three.o :  global.h symbol-table.h syntax-tree.h three.h three.c

assemcode.o: global.h symbol-table.h syntax-tree.h three.h insert_reg.h assemcode.h assemcode.c

printasm.o: global.h symbol-table.h syntax-tree.h three.h insert_reg.h printasm.h printasm.c

peep_opti.o: global.h symbol-table.h syntax-tree.h three.h peep_opti.h peep_opti.c

block_design.o: global.h symbol-table.h syntax-tree.h three.h block_design.h block_design.c

intra_cp_prop.o: global.h symbol-table.h syntax-tree.h three.h block_design.h intra_cp_prop.h intra_cp_prop.c

gen_kill_block.o: global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h gen_kill_block.c

liveness_analysis.o: global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h liveness_analysis.c

remove_dead.o: global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h peep_opti.h remove_dead.h

cal_live_range.o:global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h cal_live_range.h cal_live_range.c

create_inter_graph.o : global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h cal_live_range.h create_inter_graph.h create_inter_graph.c

graph_coloring.o: global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h cal_live_range.h create_inter_graph.h graph_coloring.h graph_coloring.c

insert_reg.o:global.h symbol-table.h syntax-tree.h three.h block_design.h gen_kill_block.h liveness_analysis.h cal_live_range.h create_inter_graph.h graph_coloring.h insert_reg.h insert_reg.c

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
