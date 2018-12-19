#include "printasm.h"

extern bool print_int_asm;
extern bool print_string_asm;
extern int stack_len;
extern str_table *str_table_head;
global_var global_vars[100];
int no_of_globs = 0;
bool param_switch = false;
int sign_extension = 0;
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
        int reg_d_1 = 0;
        if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
        {
            printf("        move $v0, $%d\n", reg_d_1);
            fprintf(asm_File, "          move $v0, $%d\n", reg_d_1);
        }
        else
        {
            printf("            lw $v0, ");
            fprintf(asm_File, "         lw $v0,");
            stack_or_global(t_instr->dest, t_stack);
        }
    }
    if (strcmp("main", t->code->dest.val.stptr->name) != 0 && register_allocation == 1) //load save all the registers on the stack
    {
        graph_node *t_g = g_head;
        printf("                     # store all the register to global \n");
        fprintf(asm_File, "                     # store all the register to global\n");
        while (t_g != NULL)
        {
            if (t_g->g_node->scope == Global)
            {

                if (t_g->reg_used != -1)
                {
                    int reg_d_1 = 0;
                    check_register(t_g->g_node, &reg_d_1);
                    printf("        sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                    fprintf(asm_File, "         sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                }
            }
            t_g = t_g->next_node;
        }
        printf("                     # done storing globals\n");
        fprintf(asm_File, "                     # done storing globals\n");

        if (num_of_reg > 0) //expand stack and save on it
        {
            printf("                     # return back all the registers\n");
            fprintf(asm_File, "                     # return back all the registers\n");
            int j = 0;
            for (int i = 0; i < 20; i++)
                if (check_reg_num_used[i] == true)
                {
                    printf("        lw $%d, %d($fp)\n", reg_stack[j].reg_name, reg_stack[j].fp_offset);
                    fprintf(asm_File, "          lw $%d, %d($fp)\n", reg_stack[j].reg_name, reg_stack[j].fp_offset);
                    j++;
                }
            printf("                     # Done returning registers\n");
            fprintf(asm_File, "                     #  Done returning registers\n");
        }
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

    graph_node *t_g = g_head;
    int value_int = strcmp(t_instr->src1.val.stptr->name, "print_int");
    int value_string = strcmp(t_instr->src1.val.stptr->name, "print_string");
    if (strcmp(t_instr->src1.val.stptr->name, "print_int") != 0 && strcmp(t_instr->src1.val.stptr->name, "print_string") != 0)
    {
        printf("                     # store all the register to global \n");
        fprintf(asm_File, "                     # store all the register to global\n");
        while (t_g != NULL)
        {
            if (t_g->g_node->scope == Global)
            {

                if (t_g->reg_used != -1)
                {
                    int reg_d_1 = 0;
                    check_register(t_g->g_node, &reg_d_1);
                    printf("        sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                    fprintf(asm_File, "         sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                }
            }
            t_g = t_g->next_node;
        }
        printf("                     # done storing globals\n");
        fprintf(asm_File, "                     # done storing globals\n");
    }

    printf("        jal _%s\n", t_instr->src1.val.stptr->name);
    int k = t_instr->src2.val.i_const * 4;
    printf("        la $sp, %d($sp)\n", k);
    fprintf(asm_File, "         jal _%s\n", t_instr->src1.val.stptr->name);
    fprintf(asm_File, "         la $sp, %d($sp)\n", k);

    t_g = g_head;
    if (strcmp(t_instr->src1.val.stptr->name, "print_int") != 0 && strcmp(t_instr->src1.val.stptr->name, "print_string") != 0)
    {
        printf("                     # store all the global to registers \n");
        fprintf(asm_File, "                     # store all the global to registers\n");
        while (t_g != NULL)
        {
            if (t_g->g_node->scope == Global)
            {

                if (t_g->reg_used != -1)
                {
                    int reg_d_1 = 0;
                    check_register(t_g->g_node, &reg_d_1);
                    printf("        lw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                    fprintf(asm_File, "         lw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                }
            }
            t_g = t_g->next_node;
        }
        printf("                     # done storing globals\n");
        fprintf(asm_File, "                     # done storing globals\n");
    }
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
    /*
    graph_node *t_g = g_head;
    printf("                     # store all the register to global \n");
    fprintf(asm_File, "                     # store all the register to global\n");
    while (t_g != NULL)
    {
        if (t_g->g_node->scope == Global)
        {

            if (t_g->reg_used != -1)
            {
                int reg_d_1 = 0;
                check_register(t_g->g_node, &reg_d_1);
                printf("        sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                fprintf(asm_File, "         sw $%d, _%s\n", reg_d_1, t_g->g_node->name);
            }
        }
        t_g = t_g->next_node;
    }
    printf("                     # done storing globals\n");
    fprintf(asm_File, "                     # done storing globals\n");
*/

    int offset = find_local_var(t_stack, t_instr->src1.val.stptr->name);
    param_switch = true;
    int reg_s_1 = 0;
    int reg_d_1 = 0;
    bool char_src1_found = false;
    if (check_register(t_instr->src1.val.stptr, &reg_s_1) == true && register_allocation == 1)
    {
        if (t_instr->src1.val.stptr->type == t_Char)
        {
            printf("        sb $%d, ", reg_s_1);
            fprintf(asm_File, "        sb $%d, ", reg_s_1);
            stack_or_global(t_instr->src1, t_stack);
            printf("        lb $%d, ", reg_s_1);
            fprintf(asm_File, "         lb $%d, ", reg_s_1);
            stack_or_global(t_instr->src1, t_stack);
        }
    }
    else
    {
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        reg_s_1 = reg_src1;
    }
    param_switch = false;
    printf("        la $sp, -4($sp)\n");
    fprintf(asm_File, "         la $sp, -4($sp)\n");
    char *b = "w";
    printf("        s%s $%d, 0($sp)\n", b, reg_s_1);
    fprintf(asm_File, "         s%s $%d, 0($sp)\n", b, reg_s_1);
    if (char_src1_found == true)
    {
        printf("        andi $%d, $%d, 255\n", reg_s_1, reg_s_1);
        fprintf(asm_File, "          andi $%d, $%d, 255\n", reg_s_1, reg_s_1);
    }
    return;
}

void output_retrieve(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1)
{
    int offset = find_local_var(t_stack, t_instr->dest.val.stptr->name);
    char *b = "w";
    if (t_instr->dest.val.stptr->type == t_Char)
        b = "b";
    int reg_d_1 = 0;
    if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
    {
        printf("        move $%d, $v0\n", reg_d_1);
        fprintf(asm_File, "          move $%d, $v0\n", reg_d_1);
        if (t_instr->dest.val.stptr->type == t_Char)
        {
            printf("        andi $%d, $%d, 255\n", reg_d_1, reg_d_1);
            fprintf(asm_File, "          andi $%d, $%d, 255\n", reg_d_1, reg_d_1);
        }
    }
    else
    {
        printf("            s%s $v0, %d($fp)\n", b, t_stack[offset].fp_offset);
        fprintf(asm_File, "         s%s $v0, %d($fp)\n", b, t_stack[offset].fp_offset);
    }

    return;
}
void output_enter(tnode *t, temp_stack *t_stack)
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

    if (strcmp("main", t->code->dest.val.stptr->name) != 0 && register_allocation == 1) //load save all the registers on the stack
    {

        if (num_of_reg > 0) //expand stack and save on it
        {
            printf("                     # store all the registers to stack\n");
            fprintf(asm_File, "                     # store all the registers to stack\n");
            int j = 0;
            for (int i = 0; i < 20; i++)
                if (check_reg_num_used[i] == true)
                {
                    printf("        sw $%d, %d($fp)\n", reg_stack[j].reg_name, reg_stack[j].fp_offset);
                    fprintf(asm_File, "          sw $%d, %d($fp)\n", reg_stack[j].reg_name, reg_stack[j].fp_offset);
                    j++;
                }
            printf("                     # Done storing register\n");
            fprintf(asm_File, "                     # Done storing register\n");
        }
        graph_node *t_g = g_head;
        printf("                     # store all the global to registers \n");
        fprintf(asm_File, "                     # store all the global to registers\n");
        while (t_g != NULL)
        {
            if (t_g->g_node->scope == Global)
            {

                if (t_g->reg_used != -1)
                {
                    int reg_d_1 = 0;
                    check_register(t_g->g_node, &reg_d_1);
                    printf("        lw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                    fprintf(asm_File, "         lw $%d, _%s\n", reg_d_1, t_g->g_node->name);
                }
            }
            t_g = t_g->next_node;
        }
        printf("                     # done storing globals\n");
        fprintf(asm_File, "                     # done storing globals\n");
    }
    //check if any node is global if yes than store its value in the assigned register

    print_formals_register(t->code->dest.val.stptr, t_stack);
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
        int reg_1 = 0;
        if (check_register(t_instr->dest.val.stptr, &reg_1) == true && register_allocation == 1)
        {

            if (t_instr->dest.operand_type == Deref_operand)
            {
                printf("        li $%d, %d\n", reg_src1, t_instr->src1.val.i_const);
                fprintf(asm_File, "        li $%d, %d\n", reg_src1, t_instr->src1.val.i_const);
                if (t_instr->dest.val.stptr->elt_type == t_Char)
                {
                    printf("        sb $%d, ($%d)\n", reg_src1, reg_1);
                    fprintf(asm_File, "          sb $%d, ($%d)\n", reg_src1, reg_1);
                }
                else
                {
                    printf("        sw $%d, ($%d)\n", reg_src1, reg_1);
                    fprintf(asm_File, "          sw $%d, ($%d)\n", reg_src1, reg_1);
                }
            }
            else
            {
                //find the dest name and the register allocated to i
                printf("        li $%d, %d\n", reg_1, t_instr->src1.val.i_const);
                fprintf(asm_File, "        li $%d, %d\n", reg_1, t_instr->src1.val.i_const);
            }
        }
        else
        {
            load_reg_LG(t_instr->src1, t_stack, reg_src1);
            store_reg_LG(t_instr->dest, t_stack, reg_src1, t_Int);
        }
    }
    else if (check_temp_stack(t_instr->src1.val.stptr->name, t_stack) == 0 && t_instr->src1.operand_type == Stringcon_operand) //in this case its neighther in the temp also the value is there in string
    {
        int reg_d_1 = 0;
        if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
        {
            printf("        la $%d, _%s\n", reg_d_1, t_instr->dest.val.stptr->name);
            fprintf(asm_File, "          la $%d, _%s\n", reg_d_1, t_instr->dest.val.stptr->name);
        }
        else
        {
            printf("        la $%d, _%s\n", reg_src1, t_instr->dest.val.stptr->name);
            fprintf(asm_File, "          la $%d, _%s\n", reg_src1, t_instr->dest.val.stptr->name);
            store_reg_LG(t_instr->dest, t_stack, reg_src1, t_instr->src1.val.stptr->type);
        }
    }
    else
    {
        int reg_s_1 = 0;
        int reg_d_1 = 0;
        if (check_register(t_instr->src1.val.stptr, &reg_s_1) == true && register_allocation == 1)
        {
        }
        else
        {
            load_reg_LG(t_instr->src1, t_stack, reg_src1);
            reg_s_1 = reg_src1;
        }
        if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
        {
            if (t_instr->dest.operand_type == Deref_operand)
            {
                if (t_instr->dest.val.stptr->elt_type != t_Char)
                {
                    printf("        sw $%d, ($%d)\n", reg_s_1, reg_d_1);
                    fprintf(asm_File, "          sw $%d, ($%d)\n", reg_s_1, reg_d_1);
                }
                else
                {
                    printf("        sb $%d, ($%d)\n", reg_s_1, reg_d_1);
                    fprintf(asm_File, "          sb $%d, ($%d)\n", reg_s_1, reg_d_1);
                }
            }
            else
            {
                if (t_instr->dest.val.stptr->type == t_Char)
                {
                    printf("        andi $%d, $%d, 255\n", reg_d_1, reg_s_1);
                    fprintf(asm_File, "          andi $%d, $%d, 255\n", reg_d_1, reg_s_1);
                }
                else
                {
                    if (reg_d_1 != reg_s_1)
                    {
                        printf("        move $%d, $%d\n", reg_d_1, reg_s_1);
                        fprintf(asm_File, "          move $%d, $%d\n", reg_d_1, reg_s_1);
                    }
                }
            }
        }
        else
        {
            store_reg_LG(t_instr->dest, t_stack, reg_s_1, t_instr->src1.val.stptr->type);
        }
    }
    return;
}
void output_Binary_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{
    int reg_s_1 = 0;
    int reg_s_2 = 0;
    int reg_d_1 = 0;
    bool no_store = false;
    bool char_src1_found = false;
    bool char_src2_found = false;
    if (check_register(t_instr->src1.val.stptr, &reg_s_1) == true && register_allocation == 1)
    {
        if (t_instr->src1.operand_type == idLoc_operand)
        {
            if (t_instr->src1.val.stptr->scope == Global)
            {
                printf("        la $%d, _%s\n", reg_s_1, t_instr->src1.val.stptr->name);
                fprintf(asm_File, "          la $%d, _%s\n", reg_s_1, t_instr->src1.val.stptr->name);
            }
            else
            {
                load_reg_LG(t_instr->src1, t_stack, reg_src1);
                reg_s_1 = reg_src1;
            }
        }
        if (t_instr->src1.val.stptr->type == t_Char)
        {
            char_src1_found = true;
            printf("        sb $%d, ", reg_s_1);
            fprintf(asm_File, "        sb $%d, ", reg_s_1);
            stack_or_global(t_instr->src1, t_stack);
            printf("        lb $%d, ", reg_s_1);
            fprintf(asm_File, "         lb $%d, ", reg_s_1);
            stack_or_global(t_instr->src1, t_stack);
        }
    }
    else
    {
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        reg_s_1 = reg_src1;
    }
    //temperory is used here *****************
    if (t_instr->src2.operand_type == Intcon)
    {
        load_reg_LG(t_instr->src2, t_stack, reg_src2);
        reg_s_2 = reg_src2;
    }
    else if (check_register(t_instr->src2.val.stptr, &reg_s_2) == true && register_allocation == 1)
    {
        if (t_instr->src2.val.stptr->type == t_Char)
        {
            printf("        sb $%d, ", reg_s_2);
            fprintf(asm_File, "        sb $%d, ", reg_s_2);
            stack_or_global(t_instr->src2, t_stack);
            printf("        lb $%d, ", reg_s_2);
            fprintf(asm_File, "         lb $%d, ", reg_s_2);
            stack_or_global(t_instr->src2, t_stack);
            char_src2_found = true;
        }
    }
    else
    {
        load_reg_LG(t_instr->src2, t_stack, reg_src2);
        reg_s_2 = reg_src2;
    }
    if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
    {
        no_store = true;
    }
    else
    {
        reg_d_1 = reg_dest;
    }

    printf("        %s $%d, $%d, $%d \n", comp_operation(t_instr), reg_d_1, reg_s_1, reg_s_2);
    fprintf(asm_File, "          %s $%d, $%d, $%d \n", comp_operation(t_instr), reg_d_1, reg_s_1, reg_s_2);
    if (no_store == false)
        store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->src1.val.stptr->type);
    return;
}
void output_unary_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_dest)
{
    char *op;
    int reg_s_1 = 0;
    int reg_d_1 = 0;
    bool no_store = false;
    if (check_register(t_instr->src1.val.stptr, &reg_s_1) == true && register_allocation == 1)
    {
    }
    else
    {
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        reg_s_1 = reg_src1;
    }
    if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
    {
        no_store = true;
    }
    else
    {
        reg_d_1 = reg_dest;
    }
    printf("        %s $%d, $%d \n", comp_operation(t_instr), reg_d_1, reg_s_1);
    fprintf(asm_File, "          %s $%d, $%d\n", comp_operation(t_instr), reg_d_1, reg_s_1);
    if (no_store == false)
        store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->src1.val.stptr->type);
    return;
}

void output_deref_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{
    char *w_b = "w";
    int s1_offset = find_local_var(t_stack, t_instr->src1.val.stptr->name);
    int reg_s_1 = 0;
    int reg_d_1 = 0;
    bool no_store = false;
    if (check_register(t_instr->src1.val.stptr, &reg_s_1) == true && register_allocation == 1)
    {
    }
    else
    {
        printf("        lw $%d, %d($fp)\n", reg_src1, t_stack[s1_offset].fp_offset);
        fprintf(asm_File, "         lw $%d, %d($fp)\n", reg_src1, t_stack[s1_offset].fp_offset);
        reg_s_1 = reg_src1;
    }
    if (check_register(t_instr->dest.val.stptr, &reg_d_1) == true && register_allocation == 1)
    {
        no_store = true;
    }
    else
    {
        reg_d_1 = reg_dest;
    }
    if (t_instr->dest.val.stptr->type == t_Char)
        w_b = "b";
    printf("        l%s $%d, ($%d)\n", w_b, reg_d_1, reg_s_1);
    fprintf(asm_File, "         l%s $%d, ($%d)\n", w_b, reg_d_1, reg_s_1);
    if (no_store == false)
        store_reg_LG(t_instr->dest, t_stack, reg_dest, t_instr->dest.val.stptr->type);
    return;
}

void output_comparison_operation(tnode *t, instr *t_instr, temp_stack *t_stack, int reg_src1, int reg_src2, int reg_dest)
{
    int reg_1 = 0;
    if (check_register(t_instr->src1.val.stptr, &reg_1) == true && register_allocation == 1)
    {
    }
    else
    {
        load_reg_LG(t_instr->src1, t_stack, reg_src1);
        reg_1 = reg_src1;
    }
    int reg_2 = 0;
    if (check_register(t_instr->src2.val.stptr, &reg_2) == true && register_allocation == 1)
    {
    }
    else
    {
        load_reg_LG(t_instr->src2, t_stack, reg_src2);
        reg_2 = reg_src2;
    }

    printf("        b%s $%d, $%d, _tdest%d\n", comp_operation(t_instr), reg_1, reg_2, t_instr->dest.val.i_const);
    fprintf(asm_File, "        b%s $%d, $%d, _tdest%d\n", comp_operation(t_instr), reg_1, reg_2, t_instr->dest.val.i_const);
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

void print_formals_register(symtabnode *head_sym_node, temp_stack *t_stack)
{
    if (register_allocation == 0)
        return;
    symtabnode *t_stptr = head_sym_node->formals;
    graph_node *t_g;
    symtabnode *t1;
    int reg_s_1 = 0;
    while (t_stptr != NULL)
    {
        //find the node and its corresponding symbol table entry
        if (check_vertex_exist(t_stptr, &g_head) == true)
        {
            t_g = g_head;
            while (t_g != NULL)
            {
                if (strcmp(t_g->g_node->name, t_stptr->name) == 0)
                {
                    t1 = t_g->g_node;
                    if (check_register(t1, &reg_s_1) == true)
                    {
                        printf("        lw $%d,", reg_s_1);
                        fprintf(asm_File, "         lw $%d,", reg_s_1);
                        int s_offset = find_local_var(t_stack, t1->name);
                        if (s_offset == -1)
                        {
                            printf("_%s\n", t1->name); //load global
                            fprintf(asm_File, "_%s\n", t1->name);
                        }
                        else
                        {
                            printf("%d($fp)\n", t_stack[s_offset].fp_offset); //load local
                            fprintf(asm_File, "%d($fp)\n", t_stack[s_offset].fp_offset);
                        }
                    }
                }
                t_g = t_g->next_node;
            }
        }
        t_stptr = t_stptr->next;
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