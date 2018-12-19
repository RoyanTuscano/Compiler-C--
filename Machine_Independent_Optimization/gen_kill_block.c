#include "gen_kill_block.h"

#define print_gk 0
#define allow_print_gen_kill 0

void find_gen_kill(tnode *t)
{
    Block *t_block = block_head;
    while (t_block != NULL)
    {
        t_block->head_gk_set = NULL;
        t_block->instr_gen_kill_set = NULL;
        transverse_backwards(t_block, t_block->head);
        complete_gen_kill(t_block);
        t_block = t_block->next;
    }
    //Now print the gen and kill blocks
    t_block = block_head;
    if (print_gk == 1)
    {
        int block_no = 0;
        while (t_block != NULL)
        {
            //  printf("Block No : %i \n", ++block_no);
              printf("Gen : ");
            print_gen_kill(&t_block->gen);
              printf("Kill : ");
            print_gen_kill(&t_block->kill);
            t_block = t_block->next;
        }
    }

    return;
}

void transverse_backwards(Block *t_block, instr *t_instr)
{
    if (t_instr != t_block->tail)
    {
        gen_kill_instruction(t_block, t_instr);
        transverse_backwards(t_block, t_instr->next);
    }
    else
    {
        gen_kill_instruction(t_block, t_instr);
    }

    /*
    if (t_instr != t_block->tail)
    {
        transverse_backwards(t_block, t_instr->next);
    }
    gen_kill_instruction(t_block, t_instr);

    /*
    printf("Gen : ");
    print_gen_kill(&t_block->gen);
    printf("Kill : ");
    print_gen_kill(&t_block->kill);
    */
    return;
}

void gen_kill_instruction(Block *t_block, instr *t_instr)
{
    symtabnode *dest, *src1, *src2;
    dest = NULL;
    src1 = NULL;
    src2 = NULL;
    switch (t_instr->op)
    {
    case Enter_op:
        // t_block->instr_gen_kill_set = NULL;
        break;
    case If_Equals_op:
    case If_Neq_op:
    case If_Leq_op:
    case If_Lt_op:
    case If_Geq_op:
    case If_Gt_op:
    case If_LogicalAnd_op:
    case If_LogicalOr_op:
        src1 = t_instr->src1.val.stptr;
        src2 = t_instr->src2.val.stptr;
        break;
    case Deref_op:
        //  dest = t_instr->dest.val.stptr;
        //  src1 = t_instr->src1.val.stptr;
        //  dest
        break;
    case UnaryMinus_op:
    case LogicalNot_op:
        dest = t_instr->dest.val.stptr;
        src1 = t_instr->src1.val.stptr;
        break;
    case Plus_op:
    case Div_op:
    case Mult_op:
    case BinaryMinus_op:
        if (t_instr->dest.operand_type != Address_operand)
            dest = t_instr->dest.val.stptr;
        if (t_instr->src2.operand_type != Intcon_operand)
            src2 = t_instr->src2.val.stptr;
        if (t_instr->src1.operand_type != idLoc_operand)
            src1 = t_instr->src1.val.stptr;
        else
        {
            instr *temp_instr = t_instr->next;
            while (temp_instr != NULL)
            {
                if (temp_instr->dest.operand_type == Deref_operand && temp_instr->op == Assn_op && t_instr->dest.val.stptr == temp_instr->dest.val.stptr)
                {
                    dest = t_instr->src1.val.stptr;
                    break;
                }
                else if (temp_instr->op == Deref_op && t_instr->dest.val.stptr == temp_instr->src1.val.stptr)
                {
                    src1 = t_instr->src1.val.stptr;
                    break;
                }
                temp_instr = temp_instr->next;
            }
            /*
            //if its deref than I am generating and if pointer
            if (t_instr->next->dest.operand_type == Deref_operand && t_instr->next->op == Assn_op)
            {
                dest = t_instr->src1.val.stptr;
            }
            //if its is
            else if (t_instr->next->op == Deref_op)
            {
                src1 = t_instr->src1.val.stptr;
            }
            */
        }
        break;
    case Param_op:
        src1 = t_instr->src1.val.stptr;
        break;
    case Return_op:
        if (t_instr->dest.operand_type != NONE)
            src1 = t_instr->dest.val.stptr;
        break;
    case Retrieve_op:
        dest = t_instr->dest.val.stptr;
        break;
    case Assn_op:
        //   if (t_instr->dest.operand_type != Deref_operand)
        dest = t_instr->dest.val.stptr;
        if (t_instr->src1.operand_type != Intcon_operand && t_instr->src1.operand_type != Stringcon_operand && t_instr->src1.operand_type != Charcon_operand)
            src1 = t_instr->src1.val.stptr;
        break;
    default:
        break;
    }
    /*
    if (dest != NULL)
        printf("%s, ", dest->name);
    if (src1 != NULL)
        printf("%s, ", src1->name);
    if (src2 != NULL)
        printf("%s, ", src2->name);
    printf("\n");
*/
    if (t_block->instr_gen_kill_set != NULL)
    {
        //  struct symtabnode_set *t_instr_kg = t_block->instr_gen_kill_set;
        t_block->instr_gen_kill_set = malloc(sizeof(struct symtabnode_set));
        t_block->tail_gk_set->next = t_block->instr_gen_kill_set;
        t_block->tail_gk_set = t_block->tail_gk_set->next;

        t_block->tail_gk_set->next = NULL;

        /*
        struct symtabnode_set *t_instr_kg = t_block->instr_gen_kill_set;
        t_block->instr_gen_kill_set = malloc(sizeof(struct symtabnode_set));
        t_block->instr_gen_kill_set->next = t_instr_kg;
        t_block->head_gk_set = t_block->instr_gen_kill_set;
        */
    }
    else
    {
        t_block->instr_gen_kill_set = malloc(sizeof(struct symtabnode_set));
        t_block->instr_gen_kill_set->next = NULL;
        t_block->tail_gk_set = t_block->instr_gen_kill_set;
        t_block->head_gk_set = t_block->instr_gen_kill_set;
        t_block->head_gk_set->next = NULL;
    }
    t_block->instr_gen_kill_set->kill_dest_i = dest;
    t_block->instr_gen_kill_set->gen_src1_i = src1;
    t_block->instr_gen_kill_set->gen_src2_i = src2;

    return;
}

void complete_gen_kill(Block *t_block)
{
    //added nowe
    t_block->gen = NULL;
    t_block->kill = NULL;
    if (t_block->head_gk_set == NULL)
        return;
    transverse_for_gen_kill(t_block, t_block->head_gk_set);
    generator(t_block, t_block->head_gk_set->kill_dest_i, t_block->head_gk_set->gen_src1_i, t_block->head_gk_set->gen_src2_i);
    killer(t_block, t_block->head_gk_set->kill_dest_i, t_block->head_gk_set->gen_src1_i, t_block->head_gk_set->gen_src2_i);
    return;
}

void transverse_for_gen_kill(Block *t_block, struct symtabnode_set *t_instr_kg)
{
    if (t_instr_kg->next != NULL)
    {
        transverse_for_gen_kill(t_block, t_instr_kg->next);
    }
    generator(t_block, t_instr_kg->kill_dest_i, t_instr_kg->gen_src1_i, t_instr_kg->gen_src2_i);
    killer(t_block, t_instr_kg->kill_dest_i, t_instr_kg->gen_src1_i, t_instr_kg->gen_src2_i);
    return;
}

void generator(Block *t_block, symtabnode *dest, symtabnode *src1, symtabnode *src2)
{
    if (dest != NULL)
        min_var_in_gkio(&t_block->gen, dest);
    if (src1 != NULL)
        add_var_in_gkio(&t_block->gen, src1);
    if (src2 != NULL)
        add_var_in_gkio(&t_block->gen, src2);
    return;
}

void killer(Block *t_block, symtabnode *dest, symtabnode *src1, symtabnode *src2)
{
    if (dest != NULL)
        add_var_in_gkio(&t_block->kill, dest);
    if (src1 != NULL && dest != src1)
        min_var_in_gkio(&t_block->kill, src1);
    if (src2 != NULL && dest != src2)
        min_var_in_gkio(&t_block->kill, src2);
    return;
}

void add_var_in_gkio(struct symtabnode_struct **gkio, symtabnode *var)
{
    //check the first element if it is filled, if not than put variable in it and exit

    if (*gkio == NULL)
    {
        //struct symtabnode_struct *t_gkio = *gkio;
        *gkio = malloc(sizeof(struct symtabnode_struct));
        struct symtabnode_struct *t_gkio = *gkio;
        t_gkio->kill_gen_in_out = var;
        // printf("Add variable: %s\n", var->name);
        t_gkio->next = NULL;
        return;
    }
    struct symtabnode_struct *t_gkio = *gkio;
    struct symtabnode_struct *prev_gkio;

    while (t_gkio != NULL)
    {
        if (t_gkio->kill_gen_in_out == var)
        {
            return;
        }
        prev_gkio = t_gkio;
        t_gkio = t_gkio->next;
    }
    //this means that the element was not found, hence add it now
    t_gkio = malloc(sizeof(struct symtabnode_struct));
    t_gkio->kill_gen_in_out = var;
    //  printf("Add variable: %s \n", var->name);
    t_gkio->next = NULL;
    prev_gkio->next = t_gkio;
    return;
}

void min_var_in_gkio(struct symtabnode_struct **gkio, symtabnode *var)
{
    //check the first element if it is filled, if not than exit nothing to delete here

    if (*gkio == NULL)
    {
        return;
    }
    //struct symtabnode_struct *t_gkio = gkio;
    struct symtabnode_struct *t_gkio = *gkio;
    struct symtabnode_struct *prev_gkio = NULL;
    struct symtabnode_struct *next_gkio = NULL;
    while (t_gkio != NULL)
    {
        if (t_gkio->kill_gen_in_out == var)
        {
            //  printf("delete variable: %s \n", var->name);
            //need to delete this element
            if (prev_gkio == NULL)
            {
                if (t_gkio->next != NULL)
                {
                    *gkio = t_gkio->next;
                    free(t_gkio);
                    return;
                }
                else
                {
                    free(t_gkio);
                    t_gkio = NULL;
                    *gkio = NULL;
                }
                return;
            }
            prev_gkio->next = t_gkio->next;
            free(t_gkio);
            t_gkio = NULL;
            return;
        }
        prev_gkio = t_gkio;
        t_gkio = t_gkio->next;
    }
    return;
}

void print_gen_kill(struct symtabnode_struct **gkio)
{
    if (allow_print_gen_kill == 0)
        return 0;

    if (*gkio == NULL)
    {
        printf("\n");
        return;
    }
    struct symtabnode_struct *t_gkio = *gkio;
    //struct symtabnode_struct *t_gkio = gkio;

    while (t_gkio != NULL)
    {
        printf("%s, ", t_gkio->kill_gen_in_out->name);
        t_gkio = t_gkio->next;
    }
    printf("\n");
    return;
}