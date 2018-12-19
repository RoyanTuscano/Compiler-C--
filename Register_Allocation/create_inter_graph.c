#include "create_inter_graph.h"

static int iteration_count;
static Block *block_list[50];
static int block_list_count = 0;

void reg_alloc_cal_live_range(tnode *t)
{
    graph_size = 0;
    create_graph_node_live_range(t);
    if (print_graph == 1)
        print_the_graph(&g_head, &graph_size);
    create_interference_graph(t);
    calculate_cost(t);
    return;
}

void create_graph_node_live_range(tnode *t)
{
    instr *t_instr = t->code;
    symtabnode *dest, *src1, *src2;
    while (t_instr != NULL)
    {
        dest = NULL;
        src1 = NULL;
        src2 = NULL;
        switch (t_instr->op)
        {
        case Enter_op:
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
            dest = t_instr->dest.val.stptr;
            src1 = t_instr->src1.val.stptr;
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
            //  if (t_instr->dest.operand_type != Address_operand)
            dest = t_instr->dest.val.stptr;
            if (t_instr->src2.operand_type != Intcon_operand)
                src2 = t_instr->src2.val.stptr;
            //   if (t_instr->src1.operand_type != idLoc_operand)
            src1 = t_instr->src1.val.stptr;
            //if below is needed to go to the gen_kill_block.c
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
            if (t_instr->dest.operand_type == Deref_operand)
                src2 = t_instr->dest.val.stptr;
            else
                dest = t_instr->dest.val.stptr;
            if (t_instr->src1.operand_type != Intcon_operand && t_instr->src1.operand_type != Stringcon_operand && t_instr->src1.operand_type != Charcon_operand)
                src1 = t_instr->src1.val.stptr;
            break;
        default:
            break;
        }
        if (dest != NULL && dest->type != t_Array)
            add_graph_vertex(dest, &g_head, &graph_size);
        if (src1 != NULL && src1->type != t_Array)
            add_graph_vertex(src1, &g_head, &graph_size);
        if (src2 != NULL && src2->type != t_Array)
            add_graph_vertex(src2, &g_head, &graph_size);
        t_instr = t_instr->next;
    }
    return;
}
void create_interference_graph(tnode *t)
{
    Block *t_block = block_head;
    iteration_count = 1;
    while (t_block != NULL) //make all the iterations zero for transversal
    {
        t_block->iteration_num = 0;
        t_block = t_block->next;
    }
    //add edge between the function args
    symtabnode *t_stptr = t->code->dest.val.stptr;
    t_stptr = t_stptr->formals;
    while (t_stptr != NULL)
    {
        symtabnode *temp_stptr = t->code->dest.val.stptr->formals;
        while (temp_stptr != NULL)
        {
            if (temp_stptr != t_stptr)
            {
                if (check_vertex_exist(temp_stptr, &g_head) == true && check_vertex_exist(t_stptr, &g_head) == true)
                {
                    graph_node *t_g = g_head;
                    symtabnode *t1, *t2;
                    while (t_g != NULL)
                    {
                        if (strcmp(t_g->g_node->name, temp_stptr->name) == 0)
                            t1 = t_g->g_node;
                        if (strcmp(t_g->g_node->name, t_stptr->name) == 0)
                            t2 = t_g->g_node;
                        t_g = t_g->next_node;
                    }
                    add_graph_edge(t1, t2, &g_head);
                    //add_graph_edge(temp_stptr, t_stptr, &g_head);
                }
            }
            temp_stptr = temp_stptr->next;
        }

        t_stptr = t_stptr->next;
    }

    /**********head Block***********************/
    t_block = block_head;
    transverse_the_blocks_backwards(t_block, t);        /*************go to the other blocks***********/
    free_symnode_struct(&head_live_now);                //empty the empty now mempry
    copy_symnode_struct(&t_block->out, &head_live_now); //copy Liveout to LiveNow
                                                        // trans_instr_backwards(t_block->head_gk_set, t_block); //interate in the block
    transverse_instruction_backwards(t_block, t_block->head);
    /***edge between live****/
    symtabnode *temp_stptr = t->code->dest.val.stptr->formals;
    while (temp_stptr != NULL)
    {
        struct symtabnode_struct *t_n = head_live_now;
        while (t_n != NULL)
        {
            if (t_n->kill_gen_in_out->type != t_Func)
            {
                if (check_vertex_exist(t_n->kill_gen_in_out, &g_head) == true && check_vertex_exist(temp_stptr, &g_head) == true)
                {
                    graph_node *t_g = g_head;
                    symtabnode *t1;
                    while (t_g != NULL)
                    {
                        if (strcmp(t_g->g_node->name, temp_stptr->name) == 0)
                            t1 = t_g->g_node;
                        t_g = t_g->next_node;
                    }
                    add_graph_edge(t_n->kill_gen_in_out, t1, &g_head);
                }
            }
            t_n = t_n->next;
        }
        temp_stptr = temp_stptr->next;
    }
    /*********************************************/
    if (print_graph == 1)
    {
        printf("********print the live range of the interfernce graph********\n");
        print_the_graph(&g_head, &graph_size);
    }
    return;
}

void transverse_the_blocks_backwards(Block *t_block, tnode *t)
{
    block_list[block_list_count++] = t_block;
    if (t_block->b_type == No_Branch)
    {
        if (child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_the_block_transversed(child(t_block)) == true)
            {
                return;
            }
            transverse_the_blocks_backwards(child(t_block), t);
            free_symnode_struct(&head_live_now);                //empty the empty now mempry
            copy_symnode_struct(&t_block->out, &head_live_now); //copy Liveout to LiveNow
                                                                //   trans_instr_backwards(t_block->head_gk_set, t_block); //interate in the block
            transverse_instruction_backwards(child(t_block), (child(t_block))->head);
        }
    }
    else if (t_block->b_type == Branch)
    {
        if (l_child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_the_block_transversed(l_child(t_block)) == true)
            {
                return;
            }
            transverse_the_blocks_backwards(l_child(t_block), t);
            free_symnode_struct(&head_live_now);                //empty the empty now mempry
            copy_symnode_struct(&t_block->out, &head_live_now); //copy Liveout to LiveNow
                                                                //   trans_instr_backwards(t_block->head_gk_set, t_block); //interate in the block
            transverse_instruction_backwards(l_child(t_block), l_child(t_block)->head);
        }
        if (r_child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_the_block_transversed(r_child(t_block)) == true)
            {
                return;
            }
            transverse_the_blocks_backwards(r_child(t_block), t);
            free_symnode_struct(&head_live_now);                //empty the empty now mempry
            copy_symnode_struct(&t_block->out, &head_live_now); //copy Liveout to LiveNow
                                                                //trans_instr_backwards(t_block->head_gk_set, t_block); //interate in the block
            transverse_instruction_backwards(r_child(t_block), r_child(t_block)->head);
        }
    }
    else if (t_block->b_type == Finish)
    {
    }
    return;
}

void transverse_instruction_backwards(Block *t_block, instr *t_instr)
{
    if (t_instr != t_block->tail)
    {
        transverse_instruction_backwards(t_block, t_instr->next);
        live_range_instruction(t_block, t_instr);
    }
    else
    {
        live_range_instruction(t_block, t_instr);
    }
    return;
}

void live_range_instruction(Block *t_block, instr *t_instr)
{
    symtabnode *dest, *src1, *src2;
    dest = NULL;
    src1 = NULL;
    src2 = NULL;
    switch (t_instr->op)
    {
    case Enter_op:
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
        dest = t_instr->dest.val.stptr;
        src1 = t_instr->src1.val.stptr;
        add_graph_vertex(src1, &g_head, &graph_size);
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
        //  if (t_instr->dest.operand_type != Address_operand)
        dest = t_instr->dest.val.stptr;
        if (t_instr->src2.operand_type != Intcon_operand)
            src2 = t_instr->src2.val.stptr;
        //   if (t_instr->src1.operand_type != idLoc_operand)
        src1 = t_instr->src1.val.stptr;
        //if below is needed to go to the gen_kill_block.c
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
        if (t_instr->dest.operand_type == Deref_operand)
            src2 = t_instr->dest.val.stptr;
        else
            dest = t_instr->dest.val.stptr;
        if (t_instr->src1.operand_type != Intcon_operand && t_instr->src1.operand_type != Stringcon_operand && t_instr->src1.operand_type != Charcon_operand)
            src1 = t_instr->src1.val.stptr;
        break;
    default:
        break;
    }
    if (print_graph == 1)
    {
        if (dest != NULL)
        {
            printf("k : %s ,", dest->name);
        }
        if (src1 != NULL)
        {
            printf("g : %s ,", src1->name);
        }
        if (src2 != NULL)
        {
            printf("g : %s ,", src2->name);
        }
        printf("\n");
    }

    struct symtabnode_struct *t_n = head_live_now;
    //add the edge between kill and the other live variables
    if (dest != NULL)
    {
        while (t_n != NULL)
        {
            if (t_n->kill_gen_in_out->type != t_Func)
            {
                if (check_vertex_exist(t_n->kill_gen_in_out, &g_head) == true)
                {
                    add_graph_edge(t_n->kill_gen_in_out, dest, &g_head);
                }
            }
            t_n = t_n->next;
        }
        //remove LRc from the live variable
        min_var_in_gkio(&head_live_now, dest);
    }
    //add LRa and LRb to livenow
    if (src1 != NULL)
    {
        add_var_in_gkio(&head_live_now, src1);
    }
    if (src2 != NULL)
    {
        add_var_in_gkio(&head_live_now, src2);
    }
    return;
}

void live_range_block(struct symtabnode_set *t_gk)
{
    struct symtabnode_struct *t_n = head_live_now;
    //add the edge between kill and the other live variables
    if (t_gk->kill_dest_i != NULL)
    {
        while (t_n != NULL)
        {
            if (t_n->kill_gen_in_out->type != t_Func)
                add_graph_edge(t_n->kill_gen_in_out, t_gk->kill_dest_i, &g_head);
            t_n = t_n->next;
        }
        //remove LRc from the live variable
        min_var_in_gkio(&head_live_now, t_gk->kill_dest_i);
    }
    //add LRa and LRb to livenow
    if (t_gk->gen_src1_i != NULL)
    {
        add_var_in_gkio(&head_live_now, t_gk->gen_src1_i);
    }
    if (t_gk->gen_src2_i != NULL)
    {
        add_var_in_gkio(&head_live_now, t_gk->gen_src2_i);
    }
    return;
}

bool check_if_the_block_transversed(Block *t_block)
{
    for (int i = 0; i < block_list_count; i++)
    {
        if (block_list[i] == t_block)
        {
            return true;
        }
    }
    return false;
}

void calculate_cost(tnode *t)
{
    instr *t_instr = t->code;
    symtabnode *dest, *src1, *src2;
    while (t_instr != NULL)
    {
        dest = NULL;
        src1 = NULL;
        src2 = NULL;
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
            src1 = t_instr->src1.val.stptr;
            src2 = t_instr->src2.val.stptr;
            break;
        case Label_op:
            find_the_loop(t_instr);
            break;
        case Deref_op:
            dest = t_instr->dest.val.stptr;
            src1 = t_instr->src1.val.stptr;
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
            dest = t_instr->dest.val.stptr;
            if (t_instr->src2.operand_type != Intcon_operand)
                src2 = t_instr->src2.val.stptr;
            src1 = t_instr->src1.val.stptr;
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
            dest = t_instr->dest.val.stptr;
            if (t_instr->src1.operand_type != Intcon_operand && t_instr->src1.operand_type != Stringcon_operand && t_instr->src1.operand_type != Charcon_operand)
                src1 = t_instr->src1.val.stptr;
            break;
        default:
            break;
        }
        if (dest != NULL && dest->type != t_Array)
            dest->freq = dest->freq + 1;
        if (src1 != NULL && src1->type != t_Array)
            src1->freq = src1->freq + 1;
        if (src2 != NULL && src2->type != t_Array)
            src2->freq = src2->freq + 1;
        t_instr = t_instr->next;
    }
    return;
}

void find_the_loop(instr *temp_instr)
{
    //iterate till you find a goto statement that points to that label
    instr *t_instr = temp_instr;
    symtabnode *dest, *src1, *src2;
    int label_name = temp_instr->dest.val.i_const;
    while (t_instr != NULL)
    {
        dest = NULL;
        src1 = NULL;
        src2 = NULL;
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
            if (t_instr->dest.val.i_const == label_name)
            {
                assign_loop_value(temp_instr, t_instr);
                return;
            }
            break;
        case Goto_op:
            if (t_instr->dest.val.i_const == label_name)
            {
                assign_loop_value(temp_instr, t_instr);
                return;
            }
            break;
        default:
            break;
        }
        t_instr = t_instr->next;
    }
    return;
}

void assign_loop_value(instr *start, instr *end)
{
    instr *t_instr = start;
    symtabnode *dest, *src1, *src2;
    while (t_instr != end)
    {
        dest = NULL;
        src1 = NULL;
        src2 = NULL;
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
            src1 = t_instr->src1.val.stptr;
            src2 = t_instr->src2.val.stptr;
            break;
        case Label_op:
            break;
        case Goto_op:
            break;
        case Deref_op:
            dest = t_instr->dest.val.stptr;
            src1 = t_instr->src1.val.stptr;
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
            dest = t_instr->dest.val.stptr;
            if (t_instr->src2.operand_type != Intcon_operand)
                src2 = t_instr->src2.val.stptr;
            src1 = t_instr->src1.val.stptr;
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
            dest = t_instr->dest.val.stptr;
            if (t_instr->src1.operand_type != Intcon_operand && t_instr->src1.operand_type != Stringcon_operand && t_instr->src1.operand_type != Charcon_operand)
                src1 = t_instr->src1.val.stptr;
            break;
        default:
            break;
        }
        if (dest != NULL && dest->type != t_Array)
            dest->freq = dest->freq + 5;
        if (src1 != NULL && src1->type != t_Array)
            src1->freq = src1->freq + 5;
        if (src2 != NULL && src2->type != t_Array)
            src2->freq = src2->freq + 5;
        t_instr = t_instr->next;
    }
}