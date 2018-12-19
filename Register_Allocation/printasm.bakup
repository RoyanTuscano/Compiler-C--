#include "printasm.h"

extern bool print_int_asm;
extern bool print_string_asm;
extern int stack_len;
extern str_table *str_table_head;
global_var global_vars[100];
int no_of_globs = 0;
bool param_switch = false;

void output_string_table()
{
    int temp_glob;
    printf(".data\n");
    fprintf(asm_File, "         .data\n");
    temp_glob = fill_the_globs(global_vars, no_of_globs);
    if (temp_glob > no_of_globs)
    {
        output_the_globs(global_vars, no_of_globs);
        no_of_globs = temp_glob;
    }
    if (str_table_head == NULL)
        return;
    //start printing
    str_table *t_str;
    for (t_str = str_table_head; t_str != NULL; t_str = t_str->next)
    {
        printf("_%s:    .asciiz \"%s\"\n", t_str->temp_name, t_str->str_name);
        fprintf(asm_File, "_%s:    .asciiz \"%s\"\n", t_str->temp_name, t_str->str_name);
    }
    return;
}

void output_the_globs(global_var *t_global, int num)
{
    for (int i = num; t_global[i].stptr != NULL && i < 50; i++)
    {
        if (t_global[i].stptr->type == t_Int)
        {
            printf("#int %s;\n            _%s: .space 4\n", t_global[i].name, t_global[i].name);
            fprintf(asm_File, "#int %s;\n            _%s: .space 4\n", t_global[i].name, t_global[i].name);
        }
        else if (t_global[i].stptr->type == t_Char)
        {
            printf("#char %s;\n            _%s: .space 1\n              .align 2\n", t_global[i].name, t_global[i].name);
            fprintf(asm_File, "#char %s;\n            _%s: .space 1\n              .align 2\n", t_global[i].name, t_global[i].name);
        }
        else if (t_global[i].stptr->type == t_Array)
        {
            if (t_global[i].stptr->elt_type == t_Int)
            {
                int mem = t_global[i].stptr->num_elts * 4;
                printf("#int %s[%d];\n            _%s: .space %d\n", t_global[i].name, t_global[i].stptr->num_elts, t_global[i].name, mem);
                fprintf(asm_File, "#int %s[%d];\n            _%s: .space %d\n", t_global[i].name, t_global[i].stptr->num_elts, t_global[i].name, mem);
            }
            else
            {
                printf("#char %s[%d];\n            _%s: .space %d\n              .align 2\n", t_global[i].name, t_global[i].stptr->num_elts, t_global[i].name, t_global[i].stptr->num_elts);
                fprintf(asm_File, "#char %s[%d];\n            _%s: .space %d\n              .align 2\n", t_global[i].name, t_global[i].stptr->num_elts, t_global[i].name, t_global[i].stptr->num_elts);
            }
        }
    }
    return;
}
void output_return(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    int offset;
    if (t_instr->dest.operand_type != NONE)
    {
        printf("            lw $v0, ");
        fprintf(asm_File, "         lw $v0,");
        stack_or_global(t_instr->dest, t_stack);
    }
    printf("        la $sp,0($fp)\n");
    printf("        lw $ra,0($sp)\n");
    printf("        lw $fp,4($sp)\n");
    printf("        la $sp,8($sp)\n");
    printf("        jr $ra\n");
    fprintf(asm_File, "         la $sp,0($fp)\n");
    fprintf(asm_File, "         lw $ra,0($sp)\n");
    fprintf(asm_File, "         lw $fp,4($sp)\n");
    fprintf(asm_File, "         la $sp,8($sp)\n");
    fprintf(asm_File, "         jr $ra\n");
}

void output_call(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    printf("        jal _%s\n", t_instr->src1.val.stptr->name);
    int k = t_instr->src2.val.i_const * 4;
    printf("        la $sp, %d($sp)\n", k);
    fprintf(asm_File, "         jal _%s\n", t_instr->src1.val.stptr->name);
    fprintf(asm_File, "         la $sp, %d($sp)\n", k);
    if (strcmp(t_instr->src1.val.stptr->name, "print_int") == 0)
    {
        print_int_asm = true;
    }
    if (strcmp(t_instr->src1.val.stptr->name, "print_string") == 0)
    {
        print_string_asm = true;
    }
    return;
}

void output_param(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    int offset = find_local_var(t_stack, t_instr->src1.val.stptr->name);
    param_switch = true;
    load_reg_LG(t_instr->src1, t_stack, reg_src1);
    param_switch = false;
    printf("        la $sp, -4($sp)\n");
    fprintf(asm_File, "         la $sp, -4($sp)\n");
    char *b = "w";
    // if(t_instr->src1.val.stptr->type==t_Char)
    //  b="b";
    printf("        s%s $%d, 0($sp)\n", b, reg_src1);
    fprintf(asm_File, "         s%s $%d, 0($sp)\n", b, reg_src1);
    return;
}

void output_retrieve(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    int offset = find_local_var(t_stack, t_instr->dest.val.stptr->name);
    char *b = "w";
    if (t_instr->dest.val.stptr->type == t_Char)
        b = "b";
    printf("            s%s $v0, %d($fp)\n", b, t_stack[offset].fp_offset);
    fprintf(asm_File, "         s%s $v0, %d($fp)\n", b, t_stack[offset].fp_offset);
    return;
}
void output_enter(tnode *t)
{
    printf("        .text\n");
    printf("        .globl _%s\n", t->place->name);
    printf("_%s:\n", t->place->name);
    printf("        la $sp, -8($sp)\n");
    printf("        sw $fp, 4($sp)\n");
    printf("        sw $ra, 0($sp)\n");
    printf("        la $fp, 0($sp)\n");
    printf("        la $sp, %d($sp)\n", stack_len);
    fprintf(asm_File, "         .text\n");
    fprintf(asm_File, "         .globl _%s\n", t->place->name);
    fprintf(asm_File, "_%s:\n", t->place->name);
    fprintf(asm_File, "         la $sp, -8($sp)\n");
    fprintf(asm_File, "         sw $fp, 4($sp)\n");
    fprintf(asm_File, "         sw $ra, 0($sp)\n");
    fprintf(asm_File, "         la $fp, 0($sp)\n");
    fprintf(asm_File, "         la $sp, %d($sp)\n", stack_len);
    return;
}

void output_print_int(char *name, int vo)
{
    printf("        .text\n");
    printf("_%s:\n", name);
    printf("        li $v0, %d\n", vo);
    printf("        lw $a0, 0($sp)\n");
    printf("        syscall\n");
    printf("        jr $ra\n");
    fprintf(asm_File, "         .text\n");
    fprintf(asm_File, "_%s:\n", name);
    fprintf(asm_File, "         li $v0, %d\n", vo);
    fprintf(asm_File, "         lw $a0, 0($sp)\n");
    fprintf(asm_File, "         syscall\n");
    fprintf(asm_File, "         jr $ra\n");
    return;
}

void output_assn(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    int reg_src2 = 4;
    if (t_instr->src1.operand_type == Intcon_operand || t_instr->src1.operand_type == Charcon_operand) //in this case yes
    {
        //check if both the destination is in the temporary stack if not asssign in the stack with frame offset
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        store_reg_LG(t_instr->dest, t_stack, reg_src1, t_Int);
    }
    else if (check_temp_stack(t_instr->src1.val.stptr->name, t_stack) == 0 && t_instr->src1.operand_type == Stringcon_operand) //in this case its neighther in the temp also the value is there in string
    {
        printf("        la $%d, _%s\n", reg_src1, t_instr->dest.val.stptr->name);
        fprintf(asm_File, "          la $%d, _%s\n", reg_src1, t_instr->dest.val.stptr->name);
        store_reg_LG(t_instr->dest, t_stack, reg_src1, t_instr->src1.val.stptr->type);
    }
    else
    {
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        store_reg_LG(t_instr->dest, t_stack, reg_src1, t_instr->src1.val.stptr->type);
    }
    return;
}
void output_Binary_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{

    load_reg_LG(t_instr->src1, t_stack, reg_src1);
    load_reg_LG(t_instr->src2, t_stack, reg_src2);

    printf("        %s $%d, $%d, $%d \n", comp_operation(t_instr), reg_dest, reg_src1, reg_src2);
    fprintf(asm_File, "          %s $%d, $%d, $%d \n", comp_operation(t_instr), reg_dest, reg_src1, reg_src2);

    store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->src1.val.stptr->type);
    return;
}
void output_unary_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_dest)
{
    char *op;
    load_reg_LG(t_instr->src1, t_stack, reg_src1);

    printf("        %s $%d, $%d \n", comp_operation(t_instr), reg_dest, reg_src1);
    fprintf(asm_File, "          %s $%d, $%d\n", comp_operation(t_instr), reg_dest, reg_src1);

    store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->src1.val.stptr->type);
    return;
}

void output_deref_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{
    char *w_b = "w";
    int s1_offset = find_local_var(t_stack, t_instr->src1.val.stptr->name);
    printf("        lw $%d, %d($fp)\n", reg_src1, t_stack[s1_offset].fp_offset);
    fprintf(asm_File, "         lw $%d, %d($fp)\n", reg_src1, t_stack[s1_offset].fp_offset);
    if (t_instr->dest.val.stptr->type == t_Char)
        w_b = "b";
    printf("        l%s $%d, ($%d)\n", w_b, reg_dest, reg_src1);
    fprintf(asm_File, "         l%s $%d, ($%d)\n", w_b, reg_dest, reg_src1);

    store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->dest.val.stptr->type);
    return;
}

void output_comparison_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{
    load_reg_LG(t_instr->src1, t_stack, reg_src1);
    load_reg_LG(t_instr->src2, t_stack, reg_src2);
    printf("        b%s $%d, $%d, _tdest%d\n", comp_operation(t_instr), reg_src1, reg_src2, t_instr->dest.val.i_const);
    fprintf(asm_File, "        b%s $%d, $%d, _tdest%d\n", comp_operation(t_instr), reg_src1, reg_src2, t_instr->dest.val.i_const);
}

void load_reg_LG(Operand t_operand, temp_stack *t_stack, int reg_src)
{
    switch (t_operand.operand_type)
    {
    case Intcon_operand:
        printf("        li $%d, %d\n", reg_src, t_operand.val.i_const);
        fprintf(asm_File, "        li $%d, %d\n", reg_src, t_operand.val.i_const);
        break;
    case Address_operand:
    case idLoc_operand:
        printf(" ");
        int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
        if (s_offset != -1 && t_stack[s_offset].fp_offset < 0)
        {
            printf("        la $%d,", reg_src);
            fprintf(asm_File, "         la $%d,", reg_src);
            stack_or_global(t_operand, t_stack);
        }
        else if (s_offset == -1)
        {
            printf("        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
            fprintf(asm_File, "         la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
        }
        else
        {
            printf("        lw $%d,", reg_src);
            fprintf(asm_File, "         lw $%d,", reg_src);
            stack_or_global(t_operand, t_stack);
        }
        break;
    case Charcon_operand:
        printf("        li $%d, %d\n", reg_src, t_operand.val.char_const);
        fprintf(asm_File, "        li $%d, %d\n", reg_src, t_operand.val.char_const);
        break;
    case Stringcon_operand:
        printf("        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
        fprintf(asm_File, "        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
        break;
    case SymtabPtr_operand:
        switch (t_operand.val.stptr->type)
        {
        case t_String:
            printf("        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
            fprintf(asm_File, "        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
            break;
        case t_Array:
            printf(" ");
            int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
            if (/* s_offset!=-1 && t_stack[s_offset].fp_offset < 0*/ s_offset == -1)
            {
                printf("        la $%d,", reg_src);
                fprintf(asm_File, "         la $%d,", reg_src);
                stack_or_global(t_operand, t_stack);
            }
            else if (SymTabLookup(t_operand.val.stptr->name, Global) == NULL && param_switch == true && SymTabLookup(t_operand.val.stptr->name, Local)->elt_type == t_Int)
            {
                printf("        la $%d,", reg_src);
                fprintf(asm_File, "         la $%d,", reg_src);
                stack_or_global(t_operand, t_stack);
            }
            else
            {
                printf("        lw $%d,", reg_src);
                fprintf(asm_File, "         lw $%d,", reg_src);
                stack_or_global(t_operand, t_stack);
            }
            break;
        case t_Char:
            printf("        lb $%d, ", reg_src);
            fprintf(asm_File, "         lb $%d, ", reg_src);
            stack_or_global(t_operand, t_stack);
            break;
        default:
            printf("        lw $%d, ", reg_src);
            fprintf(asm_File, "         lw $%d, ", reg_src);
            stack_or_global(t_operand, t_stack);
            break;
        }
        break;
    default:
        printf("NONE FOUND !!!! DOUBLE CHECK!!!\n");
        fprintf(asm_File, "NONE FOUND !!!! DOUBLE CHECK!!!\n");
    }
    return;
}

void store_reg_LG(Operand t_operand, temp_stack *t_stack, int reg_dest, int src_type)
{
    int temp_reg = 8;
    if (t_operand.operand_type == Deref_operand)
    {
        printf("        lw $%d, ", temp_reg);
        fprintf(asm_File, "         lw $%d, ", temp_reg);
        stack_or_global(t_operand, t_stack);
        if (t_operand.val.stptr->elt_type == t_Char)
        {
            printf("            sb $%d, ($%d)\n", reg_dest, temp_reg);
            fprintf(asm_File, "          sb $%d, ($%d)\n", reg_dest, temp_reg);
        }
        else
        {
            printf("            sw $%d, ($%d)\n", reg_dest, temp_reg);
            fprintf(asm_File, "          sw $%d, ($%d)\n", reg_dest, temp_reg);
        }
    }
    else
    {
        if (/*src_type == t_Char ||*/ t_operand.val.stptr->type == t_Char) //change made here to also include destination type
        {
            printf("        sb $%d, ", reg_dest);
            fprintf(asm_File, "        sb $%d, ", reg_dest);
            stack_or_global(t_operand, t_stack);
        }
        else
        {
            printf("        sw $%d,", reg_dest);
            fprintf(asm_File, "        sw $%d,", reg_dest);
            stack_or_global(t_operand, t_stack);
        }
    }
}

void stack_or_global(Operand t_operand, temp_stack *t_stack)
{
    int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
    if (s_offset == -1)
    {
        printf("_%s\n", t_operand.val.stptr->name); //load global
        fprintf(asm_File, "_%s\n", t_operand.val.stptr->name);
    }
    else
    {
        printf("%d($fp)\n", t_stack[s_offset].fp_offset); //load local
        fprintf(asm_File, "%d($fp)\n", t_stack[s_offset].fp_offset);
    }
    return;
}

void load_reg(Operand t_operand, temp_stack *t_stack, int reg_src)
{
    if (t_operand.operand_type == Intcon_operand)
    {
        printf("        li $%d, %d\n", reg_src, t_operand.val.i_const);
        fprintf(asm_File, "        li $%d, %d\n", reg_src, t_operand.val.i_const);
    }
    else if (t_operand.operand_type == SymtabPtr_operand)
    {

        if (t_operand.val.stptr->type == t_String)
        {
            printf("        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
            fprintf(asm_File, "        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
        }
        else if (t_operand.val.stptr->type == t_Array)
        {
            int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
            if (t_stack[s_offset].fp_offset < 0)
            {
                printf("        la $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
                fprintf(asm_File, "         la $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
            }
            else
            {
                printf("        lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
                fprintf(asm_File, "         lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
            }
        }
        else
        {
            int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
            printf("        lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
            fprintf(asm_File, "         lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
        }
    }
    else if (t_operand.operand_type == Address_operand || t_operand.operand_type == idLoc_operand)
    {
        int s_offset = find_local_var(t_stack, t_operand.val.stptr->name);
        if (t_stack[s_offset].fp_offset < 0)
        {
            printf("        la $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
            fprintf(asm_File, "         la $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
        }
        else
        {
            printf("        lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
            fprintf(asm_File, "         lw $%d, %d($fp)\n", reg_src, t_stack[s_offset].fp_offset);
        }
    }
    else if (t_operand.operand_type == Charcon_operand)
    {
        printf("        li $%d, %d\n", reg_src, t_operand.val.char_const);
        fprintf(asm_File, "        li $%d, %d\n", reg_src, t_operand.val.char_const);
    }
    else if (t_operand.operand_type == Stringcon_operand)
    {
        printf("        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
        fprintf(asm_File, "        la $%d, _%s\n", reg_src, t_operand.val.stptr->name);
    }
}

void store_reg(Operand t_operand, temp_stack *t_stack, int reg_dest, int src_type)
{
    int temp_reg = 8;
    if (t_operand.operand_type == Deref_operand)
    {
        int d_offset = find_local_var(t_stack, t_operand.val.stptr->name);
        printf("            lw $%d, %d($fp)\n", temp_reg, t_stack[d_offset].fp_offset);
        fprintf(asm_File, "          lw $%d, %d($fp)\n", temp_reg, t_stack[d_offset].fp_offset);
        if (src_type == t_Char)
        {
            printf("            sb $%d, ($%d)\n", reg_dest, temp_reg);
            fprintf(asm_File, "          sb $%d, ($%d)\n", reg_dest, temp_reg);
        }
        else
        {
            printf("            sw $%d, ($%d)\n", reg_dest, temp_reg);
            fprintf(asm_File, "          sw $%d, ($%d)\n", reg_dest, temp_reg);
        }
    }
    else
    {
        int d_offset = find_local_var(t_stack, t_operand.val.stptr->name);
        if (src_type == t_Char)
        {
            printf("        sb $%d, %d($fp)\n", reg_dest, t_stack[d_offset].fp_offset);
            fprintf(asm_File, "        sb $%d, %d($fp)\n", reg_dest, t_stack[d_offset].fp_offset);
        }
        else
        {
            printf("        sw $%d, %d($fp)\n", reg_dest, t_stack[d_offset].fp_offset);
            fprintf(asm_File, "        sw $%d, %d($fp)\n", reg_dest, t_stack[d_offset].fp_offset);
        }
    }
}

char *comp_operation(instr *t)
{

    switch (t->op)
    {
    case Plus_op:
        return ("add");
        break;
    case BinaryMinus_op:
        return ("sub");
        break;
    case Mult_op:
        return ("mul");
        break;
    case Div_op:
        return ("div");
        break;
    case LogicalNot_op:
        return ("not");
        break;
    case UnaryMinus_op:
        return ("neg");
        break;
    case If_Equals_op:
        return ("eq");
        break;
    case If_Neq_op:
        return ("ne");
        break;
    case If_Leq_op:
        return ("le");
        break;
    case If_Lt_op:
        return ("lt");
        break;
    case If_Geq_op:
        return ("ge");
        break;
    case If_Gt_op:
        return ("gt");
        break;
    case If_LogicalAnd_op:
        return ("&&");
        break;
    case If_LogicalOr_op:
        return ("||");
        break;
    }
    return "";
}

int check_temp_stack(char *name, temp_stack *t_stack)
{
    bool found = false;
    for (int i = 0; i < local_arg(); i++)
    {
        if (t_stack[i].name == name)
        {
            return 1;
        }
    }
    return 0;
}