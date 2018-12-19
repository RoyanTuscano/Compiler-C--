#include "assemcode.h"
#include "printasm.h"
#include "insert_reg.h"

bool print_int_asm = false;
bool print_int_once = false;
bool print_string_asm = false;
bool file_open = false;
bool print_string_once = false;
extern char *function_name;
int stack_len;

void generate_assm(tnode *t)
{

    //create a stack array for the temperoraries

    temp_stack *t_stack;
    arg_number = local_arg();
    stack_len = 0;

    if (arg_number > 0)
    {
        //add the stack_len or arg_num for the registers that are used
        num_of_reg = 0;
        reg_start_stack = arg_number;
        if (strcmp(t->code->dest.val.stptr->name, "main") != 0 && register_allocation == 1)
        {
            for (int i = 0; i < 20; i++)
                if (check_reg_num_used[i] == true)
                {
                    num_of_reg++;
                }
            if (num_of_reg != 0)
            {
                reg_stack = malloc(num_of_reg * sizeof(stack_reg));
            }
        }
        t_stack = malloc(arg_number * sizeof(temp_stack));

        //Now add the
        //this will allocate values to the local that are not formals
       stack_len = fill_local_stack(t_stack, function_name);
        if (file_open == false)
        {
            asm_File = fopen("./asmfile.s", "w");
            assert(asm_File);
            printf("        .globl main\n");
            printf("main:\n        b _main\n");
            fprintf(asm_File, "        .globl main\n");
            fprintf(asm_File, "main:\n        b _main\n");
            file_open = true;
        }
        else
            asm_File = fopen("./asmfile.s", "a");
        fclose(asm_File);
        int reg_stack_offset = stack_len;
        int j = 0;
        if (strcmp(t->code->dest.val.stptr->name, "main") != 0 && register_allocation == 1)
        {
            for (int i = 0; i < 20; i++)
                if (check_reg_num_used[i] == true && register_allocation == 1)
                {
                    reg_stack[j].reg_name = i + 5;
                    reg_stack[j].fp_offset = reg_stack_offset - 4;
                    reg_stack_offset = reg_stack_offset - 4;
                    stack_len = stack_len - 4;
                    j++;
                }
        }
    }
    else
    {
        t_stack = NULL;
    }
    //assim the values to the stacj
    if (file_open == false)
    {
        asm_File = fopen("./asmfile.s", "w");
        assert(asm_File);
        printf("        .globl main\n");
        printf("main:\n        b _main\n");
        fprintf(asm_File, "        .globl main\n");
        fprintf(asm_File, "main:\n        b _main\n");
        file_open = true;
    }
    else
        asm_File = fopen("./asmfile.s", "a");

    //output string table and global vars  if any
    //fclose(asm_File);
    output_string_table();

    node_asm_code(t->code, t, t_stack);
    //node_asm_code
    // tran_tree(t, t_stack);
    if (print_int_asm == true && print_int_once == false)
    {
        //print on stdout anmd the file

        output_print_int("print_int", 1);
        print_int_once = true;
    }
    if (print_string_asm == true && print_string_once == false)
    {
        //print on stdout anmd the file
        output_print_int("print_string", 4);
        print_string_once = true;
    }
    if (t_stack != NULL)
        free(t_stack);
    if (reg_stack != NULL)
        free(reg_stack);
    assert(asm_File);
    fclose(asm_File);
    //free the temp stack array

    return;
    //iterate_inst(t,t_stack);
}

void node_asm_code(instr *t_instr, tnode *t, temp_stack *t_stack)
{
    int reg_src1 = 3;
    int reg_src2 = 4;
    int reg_dest = 5;
    //  asm_File = fopen("./asmfile.s", "a");
    print_instruction_to_file(t_instr);

    switch (t_instr->op)
    {
    case If_Equals_op:
    case If_Neq_op:
    case If_Leq_op:
    case If_Lt_op:
    case If_Geq_op:
    case If_Gt_op:
    case If_LogicalAnd_op:
    case If_LogicalOr_op:
        output_comparison_operation(t, t_instr, t_stack, reg_src1, reg_src2, reg_dest);
        break;
    case Label_op:
        printf("_tdest%d :\n", t_instr->dest.val.i_const);
        fprintf(asm_File, "     _tdest%d :\n", t_instr->dest.val.i_const);
        break;
    case Goto_op:
        printf("         j _tdest%d\n", t_instr->dest.val.i_const);
        fprintf(asm_File, "         j _tdest%d\n", t_instr->dest.val.i_const);
        break;

    case Deref_op:
        output_deref_operation(t, t_instr, t_stack, reg_src1, reg_src2, reg_dest);
        break;
    case UnaryMinus_op:
    case LogicalNot_op:
        output_unary_operation(t, t_instr, t_stack, reg_src1, reg_dest);
        break;
    case Plus_op:
    case Div_op:
    case Mult_op:
    case BinaryMinus_op:
        output_Binary_operation(t, t_instr, t_stack, reg_src1, reg_src2, reg_dest);
        break;
    case Enter_op:
        output_enter(t, t_stack);
        break;
    case Call_op:
        output_call(t, t_instr, t_stack, reg_src1);
        break;
    case Param_op:
        output_param(t, t_instr, t_stack, reg_src1);
        break;
    case Leave_op:

        break;
    case Return_op:
        output_return(t, t_instr, t_stack, reg_src1);
        break;
    case Retrieve_op:
        output_retrieve(t, t_instr, t_stack, reg_src1);
        break;
    case Assn_op:
        output_assn(t, t_instr, t_stack, reg_src1);
        break;
    default:
        printf("the instrcution not included yet %s \n", t->code->op);
    }
    //   fclose(asm_File);
    if (t_instr->next != NULL)
        node_asm_code(t_instr->next, t, t_stack);

    return;
}

int assign_temp_stack(char *name, temp_stack *t_stack)
{
    bool found = false;
    //check if it exist and if does than returnt the pointer offset else add it and than send the pointer
    for (int i = 0; i < local_arg(); i++)
    {
        if (t_stack[i].name == name)
        {
            found = true;
            return (i + 1) * 4;
        }

        if (t_stack[i].name == NULL)
        {
            t_stack[i].name = name;
            return (i + 1) * 4;
        }
    }
    //not found
    printf("The Value Not found in the stack\n");
    return 999999;
}

int check_int(char *c)
{
    int temp;
    for (int i = 0; c[i] != NULL; i++)
    {
        temp = c[i];
        if (isdigit(temp) == 0)
            return 0;
    }
    return 1;
}

void print_instruction_to_file(instr *in)
{
    //char *temp = in->op;
    switch (in->op)
    {
    case If_Equals_op:
    case If_Neq_op:
    case If_Leq_op:
    case If_Lt_op:
    case If_Geq_op:
    case If_Gt_op:
    case If_LogicalAnd_op:
    case If_LogicalOr_op:
        printf("                                #If %s %s  %s goto _tdest%d \n", in->src1.val.stptr->name, printBinary_op(in), in->src2.val.stptr->name, in->dest.val.i_const);
        fprintf(asm_File, "                                #If %s %s %s goto _tdest%d \n", in->src1.val.stptr->name, printBinary_op(in), in->src2.val.stptr->name, in->dest.val.i_const);
        break;
    case Label_op:
        printf("                    #_tdest%d:\n", in->dest.val.i_const);
        fprintf(asm_File, "                    #_tdest%d:\n", in->dest.val.i_const);
        break;
    case Goto_op:
        printf("                         #Goto _tdest%d\n", in->dest.val.i_const);
        fprintf(asm_File, "              #Goto _tdest%d\n", in->dest.val.i_const);
        break;

    case Deref_op:
        printf("                                #(%s) = Deref(%s)\n", in->dest.val.stptr->name, in->src1.val.stptr->name);
        fprintf(asm_File, "                                #(%s) = Deref(%s)\n", in->dest.val.stptr->name, in->src1.val.stptr->name);
    case UnaryMinus_op:
    case LogicalNot_op:
        fprintf(asm_File, "                                 #%s = %s %s\n", in->dest.val.stptr->name, printBinary_op(in), in->src1.val.stptr->name);
        printf("                                 #%s = %s %s\n", in->dest.val.stptr->name, printBinary_op(in), in->src1.val.stptr->name);
        break;
    case Plus_op:
    case Div_op:
    case Mult_op:
    case BinaryMinus_op:
        printf("                                    #%s = ", in->dest.val.stptr->name);
        if (in->src1.operand_type == idLoc_operand)
            printf("(addr)");
        printf(" %s %s", in->src1.val.stptr->name, printBinary_op(in));
        if (in->src2.operand_type == SymtabPtr_operand)
            printf("%s\n", in->src2.val.stptr->name);
        else if (in->src2.operand_type == Intcon_operand)
            printf("%d\n", in->src2.val.i_const);

        fprintf(asm_File, "                                    #%s = ", in->dest.val.stptr->name);
        if (in->src1.operand_type == idLoc_operand)
            fprintf(asm_File, "(addr)");
        fprintf(asm_File, " %s %s", in->src1.val.stptr->name, printBinary_op(in));
        if (in->src2.operand_type == SymtabPtr_operand)
            fprintf(asm_File, "%s\n", in->src2.val.stptr->name);
        else if (in->src2.operand_type == Intcon_operand)
            fprintf(asm_File, "%d\n", in->src2.val.i_const);
        break;
    case Enter_op:
        printf("                                    #enter %s\n", in->dest.val.stptr->name);
        fprintf(asm_File, "                                    #enter %s\n", in->dest.val.stptr->name);
        break;
    case Call_op:
        printf("                                    #call  %s %d\n", in->src1.val.stptr->name, in->src2.val.i_const);
        fprintf(asm_File, "                                    #call  %s %d\n", in->src1.val.stptr->name, in->src2.val.i_const);
        break;
    case Param_op:
        printf("                                    #param  %s\n", in->src1.val.stptr->name);
        fprintf(asm_File, "                                    #param  %s\n", in->src1.val.stptr->name);
        break;
    case Leave_op:
        printf("                                    #leave %s\n", in->dest.val.stptr->name);
        fprintf(asm_File, "                                    #leave %s\n", in->dest.val.stptr->name);
        break;
    case Return_op:
        printf("                                    #return ");
        if (in->dest.operand_type != NONE)
            printf("%s", in->dest.val.stptr->name);
        printf("\n");
        fprintf(asm_File, "                                    #return ");
        if (in->dest.operand_type != NONE)
            fprintf(asm_File, "%s", in->dest.val.stptr->name);
        fprintf(asm_File, "\n");
        break;
    case Retrieve_op:
        printf("                                    #retrieve  %s\n", in->dest.val.stptr->name);
        fprintf(asm_File, "                                    #retrieve  %s\n", in->dest.val.stptr->name);
        break;
    case Assn_op:
        //if()
        printf("                                #");
        if (in->dest.operand_type == Deref_operand)
            printf("Pointer");
        if (in->dest.operand_type == Address_operand)
            printf("Deref");
        printf(" %s =", in->dest.val.stptr->name);
        if (in->src1.operand_type == SymtabPtr_operand)
            printf("%s", in->src1.val.stptr->name);
        else if (in->src1.operand_type == Intcon_operand)
            printf("%d", in->src1.val.i_const);
        else if (in->src1.operand_type == Stringcon_operand)
            printf("%s", in->src1.val.str_const);
        printf("\n");
        fprintf(asm_File, "                                #");
        if (in->dest.operand_type == Deref_operand)
            fprintf(asm_File, "Pointer");
        if (in->dest.operand_type == Address_operand)
            fprintf(asm_File, "Deref");
        fprintf(asm_File, " %s =", in->dest.val.stptr->name);
        if (in->src1.operand_type == SymtabPtr_operand)
            fprintf(asm_File, "%s", in->src1.val.stptr->name);
        else if (in->src1.operand_type == Intcon_operand)
            fprintf(asm_File, "%d", in->src1.val.i_const);
        else if (in->src1.operand_type == Stringcon_operand)
            fprintf(asm_File, "%s", in->src1.val.str_const);
        fprintf(asm_File, "\n");
        break;
    default:
        printf("No operation found\n");
    }
    return;
}
void printBinary_opq(instr *t)
{

    switch (t->op)
    {
    case Plus_op:
        fprintf(asm_File, "+");
        break;
    case BinaryMinus_op:
        fprintf(asm_File, "-");
        break;
    case Mult_op:
        fprintf(asm_File, "*");
        break;
    case Div_op:
        fprintf(asm_File, "/");
        break;
    case LogicalNot_op:
        fprintf(asm_File, "!");
        break;
    case UnaryMinus_op:
        fprintf(asm_File, "-");
        break;
    }
    return;
}

/*
            graph_node *t_g = g_head;
            while (t_g != NULL)
            {
                if (t_g->reg_used != -1)
                {
                    arg_number++;
                    num_of_reg++;
                }
                t_g = t_g->next_node;
            }
            */
/*
        for (int i = reg_start_stack; i < arg_number; i++)
        {
            //printf("#Name: %s, Offset: %d, formal: %d \n", t_stack[i].name, t_stack[i].fp_offset, t_stack[i].stptr->formal);
            t_stack[i].fp_offset = reg_stack_offset - 4;
            t_stack[i].name = NULL;
            if (t_g->reg_used != -1)
            {
                if (t_g->reg_used >= 0 && t_g->reg_used <= 5)
                    t_stack[i].reg_name = t_g->reg_used + 17;
                else
                    t_stack[i].reg_name = t_g->reg_used;
            }
            t_g = t_g->next_node;
            reg_stack_offset = reg_stack_offset - 4;
        }*/