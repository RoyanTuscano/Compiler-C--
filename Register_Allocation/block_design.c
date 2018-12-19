#include "block_design.h"

leader_set *leader_head;
int instr_num = 0;
static int print_block = 0;
void begin_live_analysis(tnode *t)
{

    create_block(t);
    instr_num = 0;
    print_all_Blocks(print_block);
    instr_num = 0;
    return;
}

void create_block(tnode *t)
{
    instr *t_instr = t->code;
    instr *prev_instr, *goto_instr, *if_next_instr;
    Block *t_block, *t_rchild, *t_lchild, *prev_block;
    //identify the leaders and create blocks for all the leaders
    leader_set *t_leader = malloc(sizeof(leader_set));
    identify_all_leaders(t_leader, t);
    leader_set *tmp_leader;
    if (allow_print_all_Blocks == 1)
    {
        printf("******************PRINT LEADER*************************\n");
        //transverse the leader
        tmp_leader = leader_head;
        while (tmp_leader != NULL)
        {
            print_instruction_block(tmp_leader->curr);
            tmp_leader = tmp_leader->next;
        }
    }
    // printf("******************PRINT BLOCK *************************\n\n");
    leader_set *temp_lead, *t1_lead, *t2_lead;
    while (t_instr != NULL)
    {
        temp_lead = check_if_leader(t_leader, t_instr);
        if (temp_lead != NULL)
        {
            if (t_instr->op == Enter_op)
            {

                block_head = temp_lead->curr_block;
                t_block = block_head;
                t_block->above_head = NULL;
                t_block->head = t_instr;
                t_block->next = NULL;
                //  t_block->gen.kill_gen_in_out=NULL;
                t_block->gen = NULL;
                prev_block = t_block;
                prev_instr = t_instr;
            }
            else if (prev_instr->op == Goto_op)
            {
                /*****this is to enter information about the tail end of the block that has been eneded by this leader instr****/
                t_block->tail = prev_instr;
                t_block->b_type = No_Branch;
                t_block->iteration_num = 0;
                //find the child block
                goto_instr = find_the_child(prev_instr->dest.val.i_const, t);
                //find the block no of child
                t1_lead = check_if_leader(t_leader, goto_instr);
                child(t_block) = t1_lead->curr_block;
                /**********this is to enter information about the new leader that has been created**************************/
                t_block = temp_lead->curr_block;
                t_block->head = t_instr;
                t_block->above_head = prev_instr;
                //  t_block->gen.kill_gen_in_out=NULL;
                t_block->gen = NULL;
                prev_block->next = t_block;
                prev_block = t_block;
            }
            else if ((prev_instr->op == If_Equals_op || prev_instr->op == If_Neq_op || prev_instr->op == If_Leq_op || prev_instr->op == If_Lt_op) || (prev_instr->op == If_Geq_op || prev_instr->op == If_Gt_op || prev_instr->op == If_LogicalAnd_op || prev_instr->op == If_LogicalOr_op))
            {
                /*****this is to enter information about the tail end of the block that has been eneded by this leader instr****/
                t_block->tail = prev_instr;
                t_block->b_type = Branch;
                t_block->iteration_num = 0;
                //find the child blocks 1.right and 2 left
                goto_instr = find_the_child(prev_instr->dest.val.i_const, t);
                t1_lead = check_if_leader(t_leader, goto_instr);
                t2_lead = check_if_leader(t_leader, t_instr);
                r_child(t_block) = t1_lead->curr_block;
                l_child(t_block) = t2_lead->curr_block;
                /**********this is to enter information about the new leader that has been created**************************/
                t_block = temp_lead->curr_block;
                t_block->head = t_instr;
                t_block->above_head = prev_instr;
                //     t_block->gen.kill_gen_in_out=NULL;
                t_block->gen = NULL;
                prev_block->next = t_block;
                prev_block = t_block;
            }
            else if (prev_instr->op == Return_op)
            {
                t_block->tail = prev_instr;
                t_block->b_type = Finish;
                t_block->iteration_num = 0;
                child(t_block) = NULL;
                /**********this is to enter information about the new leader that has been created**************************/
                t_block = temp_lead->curr_block;
                t_block->head = t_instr;
                t_block->above_head = prev_instr;
                //     t_block->gen.kill_gen_in_out=NULL;
                t_block->gen = NULL;
                prev_block->next = t_block;
                prev_block = t_block;
            }
            else
            {
                /*****this is to enter information about the tail end of the block that has been eneded by this leader instr****/
                t_block->tail = prev_instr;
                t_block->b_type = No_Branch;
                t_block->iteration_num = 0;
                //find the child block
                child(t_block) = temp_lead->curr_block;
                /**********this is to enter information about the new leader that has been created**************************/
                t_block = temp_lead->curr_block;
                t_block->head = t_instr;
                t_block->above_head = prev_instr;
                // t_block->gen.kill_gen_in_out=NULL;
                t_block->gen = NULL;
                prev_block->next = t_block;
                prev_block = t_block;
            }
            //   print_instruction_block(t_instr);
        }
        prev_instr = t_instr;
        t_instr = t_instr->next;
        if (t_instr == NULL)
        {
            /****means we are in return****/
            t_block->tail = prev_instr;
            t_block->b_type = Finish;
            t_block->iteration_num = 0;
            child(t_block) = NULL;
            block_tail = t_block;
            prev_block->next = NULL;
        }
    }

    return;
}

void identify_all_leaders(leader_set *t_leader, tnode *t)
{
    instr *t_instr = t->code;
    instr *tmp_instr, *prev_instr;
    leader_set *t_lead, *prev_lead;
    bool branch_continuous = false;
    t_leader->curr = NULL;
    t_leader->curr_block = NULL;
    t_leader->next = NULL;
    t_lead = t_leader;
    leader_head = NULL;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Enter_op:
            t_lead->curr = t_instr;
            t_lead->next = NULL;
            t_lead->curr_block = malloc(sizeof(Block));
            leader_head = t_lead;
            break;
        case If_Equals_op:
        case If_Neq_op:
        case If_Leq_op:
        case If_Lt_op:
        case If_Geq_op:
        case If_Gt_op:
        case If_LogicalAnd_op:
        case If_LogicalOr_op:
            //check if the leader already exist if yes than no need to create another one
            tmp_instr = find_the_child(t_instr->dest.val.i_const, t);
            if (check_if_leader(t_leader, tmp_instr) == NULL)
            {
                prev_lead = t_lead;
                t_lead = malloc(sizeof(leader_set));
                prev_lead->next = t_lead;
                //first destination
                t_lead->curr = tmp_instr;
                t_lead->next = NULL;
                t_lead->curr_block = malloc(sizeof(Block));
            }
            if (check_if_leader(t_leader, t_instr->next) == NULL)
            {
                prev_lead = t_lead;
                t_lead = malloc(sizeof(leader_set));
                prev_lead->next = t_lead;
                t_lead->curr = t_instr->next;
                t_lead->next = NULL;
                t_lead->curr_block = malloc(sizeof(Block));
            }

            break;
        case Goto_op:
            tmp_instr = find_the_child(t_instr->dest.val.i_const, t);
            if (check_if_leader(t_leader, tmp_instr) == NULL)
            {
                prev_lead = t_lead;
                t_lead = malloc(sizeof(leader_set));
                prev_lead->next = t_lead;
                //first destination
                t_lead->curr = tmp_instr;
                t_lead->next = NULL;
                t_lead->curr_block = malloc(sizeof(Block));
            }
            //I have to create in this case
            if (t_instr->next->op == Leave_op)
            {
                prev_lead = t_lead;
                t_lead = malloc(sizeof(leader_set));
                prev_lead->next = t_lead;
                //first destination
                t_lead->curr = t_instr->next;
                t_lead->next = NULL;
                t_lead->curr_block = malloc(sizeof(Block));
            }
            break;
        case Return_op:
            if (t_instr->next == NULL)
            {
                return;
            }

            if (t_instr->next->op != Label_op && t_instr->next->op != Goto_op)
            {

                prev_instr = t_instr;
                t_instr = t_instr->next;
                for (; t_instr != NULL;) // t_instr = t_instr->next)
                {
                    delete_instr(prev_instr, t_instr);
                    t_instr = prev_instr->next;
                    if (t_instr->op == Leave_op)
                    {
                        prev_instr->next = NULL;
                        return;
                    }
                }
                return;
            }
            //delete all those instruction

            break;
        default:
            break;
        }

        t_instr = t_instr->next;
    }
    return;
}

instr *find_the_child(int label_name, tnode *t)
{
    //find the label
    // printf("Label name %i",label_name);
    instr *t_instr = t->code;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Label_op:
            if (label_name == t_instr->dest.val.i_const)
            {
                //  printf("Label name %i",t_instr->dest.val.i_const);
                return t_instr;
            }
            break;
        default:
            break;
        }
        t_instr = t_instr->next;
    }
    return NULL;
}

leader_set *check_if_leader(leader_set *t_leader, instr *t_instr)
{
    leader_set *t_lead = t_leader;
    while (t_lead != NULL)
    {
        if (t_lead->curr == t_instr)
            return t_lead;
        t_lead = t_lead->next;
    }
    return NULL;
}

void print_all_Blocks(int print_block)
{
    if (allow_print_all_Blocks == 0)
        return;
    Block *t_block;
    if (print_block == 1)
    {
        printf("******************PRINT BLOCK ************************\n\n");
        //transverse the block
        t_block = block_head;
        while (t_block != NULL)
        {
            print_Block(t_block);
            t_block = t_block->next;
        }
    }
}

void print_Block(Block *t_block)
{
    if (allow_print_all_Blocks == 0)
        return;
    // printf("**In the Block***\n");
    instr *t_instr = t_block->head;
    bool sema_phore = false;
    while (1)
    {
        sema_phore = t_instr == t_block->tail ? true : false;
        printf("%i", instr_num++);
        print_instruction_block(t_instr);
        t_instr = t_instr->next;
        if (sema_phore == true)
            break;
    }
    return;
}

void print_instruction_block(instr *in)
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
        printf("    If %s %s  %s goto _tdest%d \n", in->src1.val.stptr->name, printBinary_op(in), in->src2.val.stptr->name, in->dest.val.i_const);
        break;
    case Label_op:
        printf("    _tdest%d:\n", in->dest.val.i_const);
        break;
    case Goto_op:
        printf("    Goto _tdest%d\n", in->dest.val.i_const);
        break;
    case Deref_op:
        printf("    (%s) = Deref(%s)\n", in->dest.val.stptr->name, in->src1.val.stptr->name);
        break;
    case UnaryMinus_op:
    case LogicalNot_op:
        printf("    %s = %s %s\n", in->dest.val.stptr->name, printBinary_op(in), in->src1.val.stptr->name);
        break;
    case Plus_op:
    case Div_op:
    case Mult_op:
    case BinaryMinus_op:
        printf("    %s = ", in->dest.val.stptr->name);
        if (in->src1.operand_type == idLoc_operand)
            printf("(addr)");
        printf(" %s %s", in->src1.val.stptr->name, printBinary_op(in));
        if (in->src2.operand_type == SymtabPtr_operand)
            printf("%s\n", in->src2.val.stptr->name);
        else if (in->src2.operand_type == Intcon_operand)
            printf("%d\n", in->src2.val.i_const);
        break;
    case Enter_op:
        printf("    enter %s\n", in->dest.val.stptr->name);
        break;
    case Call_op:
        printf("    call  %s %d\n", in->src1.val.stptr->name, in->src2.val.i_const);
        break;
    case Param_op:
        printf("    param  %s\n", in->src1.val.stptr->name);
        break;
    case Leave_op:
        printf("    leave %s\n", in->dest.val.stptr->name);
        break;
    case Return_op:
        printf("    return ");
        if (in->dest.operand_type != NONE)
            printf("%s", in->dest.val.stptr->name);
        printf("\n");
        break;
    case Retrieve_op:
        printf("    retrieve  %s\n", in->dest.val.stptr->name);
        break;
    case Assn_op:
        printf("    ");
        if (in->dest.operand_type == Address_operand)
            printf("Deref");
        printf(" %s =", in->dest.val.stptr->name);
        if (in->src1.operand_type == SymtabPtr_operand)
            printf("%s", in->src1.val.stptr->name);
        else if (in->src1.operand_type == Intcon_operand)
            printf("%d", in->src1.val.i_const);
        else if (in->src1.operand_type == Stringcon_operand)
            printf("%s", in->src1.val.str_const);
        else if (in->src1.operand_type == Charcon_operand)
            printf("%c", in->src1.val.char_const);
        printf("\n");
        break;
    default:
        printf("No operation found\n");
    }
    return;
}