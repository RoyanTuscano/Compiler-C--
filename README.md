XXXXXXXXXXXXXXXXXXXXXXXXX---------CONTENT Provided by Professor Saumya Debray-----------------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
course website : http://www2.cs.arizona.edu/classes/cs553/fall18/

This directory contains files to create a front end for a
C-- compiler using flex and yacc.

FILES:
=====
These are the files present initially:

  README	this file

  Makefile	builds the front end; this results in an executable
		called "parse".
		
		Defining the symbol DEBUG in the variable CFLAGS will
		cause the syntax tree to be printed out after processing
		each function.

  main.c	The driver program that calls the parser.

  error.h	Defines various types of errors for special handling.

  error.c	Routines for reporting error messages.

  parser.y	Yacc specification for the parser.

  print.c       Code for printing stuff out.  Right now it contains code
                for printing out syntax trees.

  protos.h      Prototypes.  Right now it contains prototypes for 
  	        syntax tree accessor functions.

  scanner.l	Flex specification for the scanner.

  symbol-table.h  Typedefs etc. for symbol tables.

  symbol-table.c  Code for maintaining and accessing the symbol table.

  syntax-tree.h  Typedefs etc. for syntax trees.

  syntax-tree.c  Code for constructing the syntax tree.

  util.h        Declarations and prototypes for utility routines.

  util.c        Assorted utilities.

Additionally, the following files are created during the build process:

  y.tab.h, 
  y.tab.c, 
  y.output	Created by yacc.

  lex.yy.c	Created by flex.

GLOBAL VARIABLES:
================

  char *id_name		When the scanner recognizes an identifier, this
			variable points to (a copy of) the lexeme.  This is
			what needs to be accessed when you subsequently
			want to get at the identifier's name, since by
			that time yytext may have been long since overwritten.

			Defined by the function id_or_keywd() in file
						scanner.l.

  int ival              When a scanner recognizes an integer or character
                        constant, this variable is assigned the value of
                        that constant.  Defined in scanner.l.

  int linenum		Contains the line number currently being processed.
			Typically used in error messages.  Defined in scanner.l.

  int errstate		Indicates what kind of an error has occurred.  The
			parser treats a few kinds of errors specially: the
			nature of such special errors is communicated to yyerror()
			via the variable errstate.  For the values this can
			take on, see errmrgs.h --- the value ORDINARY refers
			to errors that don't get any special handling.


SYMBOL TABLES
=============
Declarations pertaining to symbol tables are in the file symbol-table.h.



SYNTAX TREES
============
Declarations pertaining to syntax trees are in the file syntax-tree.h.
Components of syntax tree nodes can be accessed via the accessor functions
whose prototypes are given in protos.h.



BUILDING THE SYSTEM
===================
Type "make", this will create an executable named "compile".



INVOKING THE PROGRAM
====================
This program reads from stdin and writes error messages to stderr.  If
compiled with the flag -DDEBUG, syntax trees are printed to stdout.  Other
than this, syntactically correct input files are accepted silently.

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxXXX

XXXXXXXXXXXXXXXXXXXXXXXXXXXXX---------------CONTENT Written by me---------------------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
1. Code_Generation

    Edited 
    symbol-table.c and symbol-table.h, syntax-tree.c and syntax-tree.h
    written by me
    three.c , three.h ------used to write three address linked list , using the syntax tree and symbol table
    assemcode.c, assemcode.h -----used to print the assembly code this call the functions in printasm.c that are used to print assembly code
    printasm.c, printasm.h ----- Used to print the machine level code from 3 address code

    project requirements:
    This assignment involves generating code for C--. You will write code to traverse the syntax tree for each function in a program and generate three-address statements, then translate these into MIPS assembly code and output the assembly code generated. Your code generator should reuse temporaries as far as possible.
    For intermediate code generation, you can use the three-address instruction set given here; a translation from this instruction set to MIPS assembly code is given here. You are not required to adhere to this particular three-address instruction set, and are free to deviate from it if you want; however, if you do you will have to work out the mapping to MIPS assembly code yourself.

    Note : Even though the intermediate code plays a relatively small role in this assignment, future assignments will involve dataflow analysis and machine-independent optimization using the intermediate code you will be generating in this assignment.

    running the generated MIPS code
    I will run the MIPS assembly code generated by your compiler using a version of SPIM that provides statistics on different kinds of instructions executed by a program. The source code for this version of SPIM is available here and also in /home/cs553/fall18/spim-7.2.1-keepstats; the executable for this version of SPIM is in
    /home/cs553/fall18/bin/spim
    To run SPIM on a file foo.s containing MIPS assembly code, use:
    spim -file foo.s
    To get execution count statistics, use:
    spim -keepstats -file foo.s


2. Machine_Independent_Optmization
    Edited 

    symbol-table.c and symbol-table.h, syntax-tree.c and syntax-tree.h

    written by me
    three.c , three.h ------used to write three address linked list , using the syntax tree and symbol table
    assemcode.c, assemcode.h -----used to print the assembly code this call the functions in printasm.c that are used to print assembly code
    printasm.c, printasm.h ----- Used to print the machine level code from 3 address code
    block_design.c, block_design.h -------Used to generate the basic blocks from the C code
    gen_kill_block.c, gen_kill_block.h --------Used for generate and Kill analysis of the defination and uses in the basic block that will be used in Live Varaible analysis
    liveness.c, liveness.h ----------Used to find out the variables that are live
    remove_dead.c, remove_dead.h ------Used to remove dead code from the liveliness analysis
    intra_cp_prop.c, intra_cp_prop.h -------Used to find the intra block copy of the variable
    peep_opti.c, peep_opti.h ------Used in Simple machine independent peephole optimization, used to remove unwanted jumps and optmize them

    Assignment Requirements :

    This assignment involves the implementation of dataflow analysis and machine-independent optimizations. These optimizations are to be carried out if your program is invoked with the command-line option –O1.
    You are to test the effectiveness of your optimizations by testing programs compiled with and without the –O1 option and report the results in a README file.

    1.1. Optimizations Independent of Flow Information
    You should implement the following optimizations:
    Collapsing jump chains: chains of jump instructions should be collapsed so that each jump branches directly to its final destination.
    Simple machine-independent peephole optimizations. E.g., transform the sequence (where R is a relational operator)
    if x R y goto L1
    goto L2
    label L1
    to the following (where, S is the complement operator of R):

    if x S y goto L2
    label L1
    Examine the code generated by your compiler on several programs of reasonable size, of your choosing, to determine what patterns to use for your peephole optimizations.

    Intra-block copy propagation: given a copy instruction d: x := y and a subsequent use u of x within a basic block, if it can be guaranteed that x is not redefined between d and u, then the reference to x at u can be replaced by a reference to y, as illustrated by the following:
    Before	     	After
    t1 := z	 	t1 := z
    u := t1+1	 	u := z+1

    Intra-Procedural Liveness Analysis and Dead Code Elimination
    You should carry out liveness analysis at the intra-procedural level. For this, you may assume that global variables are always live. To simplify the problem, you may also assume that all elements of an array are live if any of its elements is (i.e., treat the array as a single variable).
    Copy propagation can cause some instructions to become dead. You are to use the information obtained from your liveness analysis to eliminate dead code, i.e., code whose results are never used.

    Note that the elimination of some dead code can cause additional instructions to become dead. A naive approach would be to repeat the liveness analysis all over again, eliminate some more dead code, and so on. Such an approach would be hopelessly inefficient, and should not be used. Instead, during liveness analysis, you should propagate information about what instructions are dead, and use this to improve the liveness analysis. The idea is as follows:

    An instruction is marked "dead" if it defines a variable that is dead.
    Uses of variables in an instruction that is marked "dead" can be ignored.
    At the end of the analysis all instructions that are marked "dead" represent dead code and can be eliminated.



3. Register_Allocation

    Edited:

    symbol-table.c and symbol-table.h, syntax-tree.c and syntax-tree.h

    written by me
    three.c , three.h ------used to write three address linked list , using the syntax tree and symbol table
    assemcode.c, assemcode.h -----used to print the assembly code this call the functions in printasm.c that are used to print assembly code
    printasm.c, printasm.h ----- Used to print the machine level code from 3 address code
    block_design.c, block_design.h -------Used to generate the basic blocks from the C code
    gen_kill_block.c, gen_kill_block.h --------Used for generate and Kill analysis of the defination and uses in the basic block that will be used in Live Varaible analysis
    liveness.c, liveness.h ----------Used to find out the variables that are live
    remove_dead.c, remove_dead.h ------Used to remove dead code from the liveliness analysis
    intra_cp_prop.c, intra_cp_prop.h -------Used to find the intra block copy of the variable
    peep_opti.c, peep_opti.h ------Used in Simple machine independent peephole optimization, used to remove unwanted jumps and optmize them   
    cal_live_range.c, cal_live_range.h -------Used to calculate live range of each variable and store them in linked list.
    create_inter_graph.c, create_inter_graph.h --------Used to create inter procedure graph for each variable depending on live range
    graph_coloring.c, graph_coloring.h --------Used to color graph and spill the variables from graph if the colors or registers are less
    insert_reg.c, insert_reg.h -------Used to allocate register depending on the graph coloring

    Assignment requirements:
    This assignment involves the improvement of the final code generated by your compiler via register allocation. This optimization is to be carried out if your program is invoked with the –O2 option. You are to test the effectiveness of your optimizations by testing programs compiled with and without the –O2 option, both by itself and in conjunction with previously implemented optimizations. You should report the results of these experiments in a README file.
    Note: The actions taken for the –O2 option should be independent of those for the –O1 option used for the previous assignment. In other words, it should be possible to carry out register allocation with or without also performing machine-independent optimization: if both are desired, the compiler will be invoked with both –O1 and –O2 (the order of these arguments should not matter).

    Intra-Procedural Register Allocation
    You are to use the information obtained from your liveness analysis and/or reaching definitions to carry out register allocation within procedures.
    I would like you to implement, if possible, global register allocation based on graph coloring. This requires the identification of live ranges, but for the purposes of this assignment it is acceptable to consider all of the occurrences of each variable to constitute a single live range.

    If, for some reason, it is not feasible for you to implement global register allocation, you may implement local register allocation (i.e., intra-basic-block). However, this will not get full credit for this assignment.

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX