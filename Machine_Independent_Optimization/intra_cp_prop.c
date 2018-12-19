#include "intra_cp_prop.h"

static int print_block = 0;

void intra_block_cp_prop(tnode *t)
{
    // printf("********before the propogation***************\n");
    // print_all_Blocks(print_block);
    start_cp_prop(t);
    //  printf("********After the propogation***************\n");
    print_all_Blocks(print_block);

    return;
}

void start_cp_prop(tnode *t)
{
    //transverse the block
    Block *t_block;
    t_block = block_head;
    while (t_block != NULL)
    {
        cp_prop_task(t_block);
        t_block = t_block->next;
    }
}

void cp_prop_task(Block *t_block)
{
    instr *t_instr = t_block->head;
    bool sema_phore = false;
    while (1)
    {
        sema_phore = t_instr == t_block->tail ? true : false;

        switch (t_instr->op)
        {
        case Assn_op:
            //also do constant propogation later
            if (t_instr->dest.operand_type != Deref_operand && t_instr != t_block->tail)
                if (t_instr->src1.operand_type == SymtabPtr_operand)
                    transverse_var(t_block, t_instr);
            break;
        default:
            break;
        }

        t_instr = t_instr->next;
        if (sema_phore == true)
            break;
    }

    return;
}

bool transverse_var(Block *t_block, instr *t_instr)
{
    bool sema_phore = false;
    //char string to check in the source...
    symtabnode *dest_var = t_instr->dest.val.stptr;

    symtabnode *src_var = t_instr->src1.val.stptr;
    int dest_type = src_var->type;
    t_instr = t_instr->next;
    while (1)
    {
        sema_phore = t_instr == t_block->tail ? true : false;

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
            if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                t_instr->src1.val.stptr = src_var;
            if (t_instr->src2.val.stptr == dest_var && dest_type == t_instr->src2.val.stptr->type)
                t_instr->src2.val.stptr = src_var;
            break;
        case Deref_op:
            //*********************check later for Deref condition**************//
            if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                t_instr->src1.val.stptr = src_var;
            if (t_instr->dest.val.stptr == dest_var)
                return true;
            break;
        case UnaryMinus_op:
        case LogicalNot_op:
            if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                t_instr->src1.val.stptr = src_var;
            //now check if the destination is same as
            if (t_instr->dest.val.stptr == dest_var || t_instr->dest.val.stptr == src_var)
                return true;
            break;
        case Plus_op:
        case Div_op:
        case Mult_op:
        case BinaryMinus_op:
            if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                t_instr->src1.val.stptr = src_var;
            if (t_instr->src2.val.stptr == dest_var && dest_type == t_instr->src2.val.stptr->type)
                t_instr->src2.val.stptr = src_var;
            if (t_instr->dest.val.stptr == dest_var || t_instr->dest.val.stptr == src_var)
                return true;
            break;
        case Param_op:
            if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                t_instr->src1.val.stptr = src_var;
            break;
        case Return_op:
            if (t_instr->dest.operand_type != NONE)
                if (t_instr->dest.val.stptr == dest_var && dest_type == t_instr->dest.val.stptr->type)
                    t_instr->dest.val.stptr = src_var;
            break;
        case Retrieve_op:
            if (t_instr->dest.val.stptr == dest_var || t_instr->dest.val.stptr == src_var)
                return true;
            break;
        case Assn_op:
            //also do constant propogation later
            if (t_instr->dest.operand_type != Deref_operand)
                if (t_instr->src1.val.stptr == dest_var && dest_type == t_instr->src1.val.stptr->type)
                    t_instr->src1.val.stptr = src_var;

            if (t_instr->dest.val.stptr == dest_var || t_instr->dest.val.stptr == src_var)
                return true;

            break;
        default:
            break;
        }
        t_instr = t_instr->next;
        if (sema_phore == true)
            break;
    }
    return;
}