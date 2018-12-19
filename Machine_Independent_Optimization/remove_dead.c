#include "remove_dead.h"
static int iteration_count;
static Block *block_list[50];
static int block_list_count = 0;

void identify_dead_code(tnode *t)
{
    //   printf("***************Dead code Analysis**************\n");
    Block *t_block = block_head;
    iteration_count = 1;
    while (t_block != NULL)
    {
        t_block->iteration_num = 0;
        t_block = t_block->next;
    }
    t_block = block_head;
    block_list[block_list_count++] = t_block;
    dead_code_transverse_back(t_block, t);
    in_out_analysis(t_block);
    dead_code_analysis(t_block);
    in_out_analysis(t_block);
    print_in_out_analysis(t_block);

    //free the memory
    t_block = block_head;
    while (t_block != NULL)
    {
        t_block->iteration_num = 0;
        free_symnode_struct(&t_block->in);
        free_symnode_struct(&t_block->out);
        free_symnode_struct(&t_block->gen);
        free_symnode_struct(&t_block->kill);
        t_block = t_block->next;
    }
    return;
}

void dead_code_transverse_back(Block *t_block, tnode *t)
{
    block_list[block_list_count++] = t_block;
    if (t_block->b_type == No_Branch)
    {
        if (child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_block_transversed(child(t_block)) == true)
            {

                return;
            }

            dead_code_transverse_back(child(t_block), t);
            in_out_analysis(child(t_block));
            dead_code_analysis(child(t_block));

            in_out_analysis(child(t_block));
            int num = child(t_block)->iteration_num;
            find_in_out(t);
            child(t_block)->iteration_num = num;
            print_in_out_analysis(child(t_block));
        }
    }
    else if (t_block->b_type == Branch)
    {
        if (l_child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_block_transversed(l_child(t_block)) == true)
            {
  
                return;
            }

            dead_code_transverse_back(l_child(t_block), t);
            in_out_analysis(l_child(t_block));
            dead_code_analysis(l_child(t_block));
            in_out_analysis(l_child(t_block));
            // in_out_analysis(child(t_block));
            int num = l_child(t_block)->iteration_num;
            find_in_out(t);
            l_child(t_block)->iteration_num = num;
            print_in_out_analysis(l_child(t_block));
        }
        if (r_child(t_block)->iteration_num != iteration_count)
        {
            if (check_if_block_transversed(r_child(t_block)) == true)
            {

                return;
            }

            dead_code_transverse_back(r_child(t_block), t);
            in_out_analysis(r_child(t_block));
            dead_code_analysis(r_child(t_block));
            in_out_analysis(r_child(t_block));
            //in_out_analysis(child(t_block));
            int num = r_child(t_block)->iteration_num;
            find_in_out(t);
            r_child(t_block)->iteration_num = num;
            print_in_out_analysis(r_child(t_block));
        }
    }
    else if (t_block->b_type == Finish)
    {
    }
    else
    {
        printf("*****XXXXXX***Branch Type Not found**XXXX*******\n");
    }
    return;
}
static bool check_if_block_transversed(Block *t_block)
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

void dead_code_analysis(Block *t_block)
{
    // t_block->iteration_num++;
    //I will also need to iterate the instructions they will be iterating too
    instr *t_instr = t_block->head;
    instr *prev_instr = t_block->above_head;
    instr *curr_instr, *prev_prev_instr;
    struct symtabnode_set *t_gk = t_block->head_gk_set;
    struct symtabnode_set *curr_gk, *prev_gk, *prev_prev_gk;
    instr *instr_to_delete;
    struct symtabnode_struct *t_out = t_block->out;
    symtabnode *src1, *src2, *dest, *dest_after;
    bool instr_live;
    prev_gk = NULL;
    bool start_again = false;
    bool remove_first_set = false;
    /*
    printf("Before Dead code Analysis \n");
    printf("Gen : ");
    print_gen_kill(&t_block->gen);
    printf("Kill : ");
    print_gen_kill(&t_block->kill);
    */
    while (t_gk != NULL || start_again == true)
    {
        if (start_again == true)
        {
            t_instr = t_block->head;
            t_gk = t_block->head_gk_set;
            if (t_gk == NULL)
                break;
            prev_instr = t_block->above_head;
            start_again = false;
            prev_gk = NULL;
        }
        instr_live = false;
        curr_gk = t_gk->next;
        curr_instr = t_instr;
        t_out = t_block->out;
        remove_first_set = false;
        dest = t_gk->kill_dest_i;
        while (curr_gk != NULL)
        {
            src1 = curr_gk->gen_src1_i;
            src2 = curr_gk->gen_src2_i;
            dest_after = curr_gk->kill_dest_i;
            //check if the kill element is used in generate or if not than in out element of the block
            if (dest == NULL)
            {
                instr_live = true;
                break;
            }
            if (src1 != NULL)
                if (src1 == dest)
                {
                    //check for the condition of the array
                    instr_live = true;

                    if (t_instr->src1.operand_type == idLoc_operand)
                    {
                        struct symtabnode_set *temp_gk = t_gk->next;
                        instr *tmp_instr = t_instr->next;
                        symtabnode *stptr = t_instr->dest.val.stptr;
                        while (temp_gk != NULL)
                        {
                            if (stptr == tmp_instr->dest.val.stptr)
                            {
                                instr_to_delete = tmp_instr;
                                if (instr_live == true)
                                    goto instr_live;
                                else
                                    break;
                            }
                            if (t_gk->kill_dest_i == temp_gk->gen_src1_i)
                            {
                                instr_live = false;
                            }
                            tmp_instr = tmp_instr->next;
                            temp_gk = temp_gk->next;
                        }
                    }

                    break;
                }

            if (src2 != NULL)
                if (src2 == dest)
                {
                    instr_live = true;
                    break;
                }
            if (dest_after != NULL)

                if (dest_after == dest && t_instr->src1.operand_type != idLoc_operand)
                {
                    instr_live = false;
                    goto delete_instruction;
                    break;
                }
            curr_gk = curr_gk->next;
        }
    instr_live:
        if (instr_live == false)
        {
            //check in the out also so that it is not used later
            while (t_out != NULL)
            {
                if (t_gk->kill_dest_i == t_out->kill_gen_in_out)
                {
                    instr_live = true;
                    break;
                }
                t_out = t_out->next;
            }
        }

        if (instr_live == false)
        {
            //kill that instructions
        delete_instruction:

            if ( t_instr->op != Call_op && t_instr->op != Param_op && t_instr->op != Return_op && t_instr->op != Leave_op &&
                (t_instr->op != If_Equals_op && t_instr->op != If_Neq_op && t_instr->op != If_Leq_op &&
                 t_instr->op != If_Lt_op) && t_instr->op != Label_op &&
                (t_instr->op != If_Geq_op && t_instr->op != If_Gt_op &&
                 t_instr->op != If_LogicalAnd_op && t_instr->op != If_LogicalOr_op) &&
                t_instr->op != Goto_op && t_instr->dest.operand_type != Deref_operand)
            //*&& t_instr->dest.val.stptr->scope != Global*/)
            {
                if (t_instr == t_block->head)
                {
                    t_block->head = t_instr->next;
                }
                if (t_instr->src1.operand_type == idLoc_operand)
                {
                    // check if there is x in generated again ignore
                    struct symtabnode_set *temp_gk = t_gk;
                    struct symtabnode_set *temp_curr_gk = t_gk;
                    instr *tmp_instr = t_instr;
                    bool array_live = false;
                    tmp_instr = tmp_instr->next;
                    temp_gk = temp_gk->next;
                    symtabnode *stptr = t_instr->dest.val.stptr;
                    /*
                    while (temp_gk != NULL)
                    {
                        if (t_gk->kill_dest_i == temp_gk->gen_src1_i) //&& tmp_instr->next->op!=Deref_op)
                        {
                            array_live = true;
                            break;
                        }
                        tmp_instr = tmp_instr->next;
                        temp_gk = temp_gk->next;
                    }*/
                    if (array_live == false)
                    {
                        delete_instr(prev_prev_instr, prev_instr);
                        prev_instr = prev_prev_instr;
                        delete_instr(prev_instr, t_instr);
                        t_instr = prev_instr->next;
                        instr *temp_instr = t_instr->next;

                        prev_prev_gk->next = prev_gk->next;
                        free(prev_gk);
                        prev_gk = prev_prev_gk;
                        prev_gk->next = t_gk->next;
                        free(t_gk);
                        t_gk = prev_gk->next;

                        while (1)
                        {
                            temp_instr = t_instr;
                            if (stptr == t_instr->dest.val.stptr) //t_instr->dest.operand_type == Deref_operand && t_instr->op == Assn_op)
                            {
                                delete_instr(prev_instr, t_instr);
                                t_instr = prev_instr;
                                prev_gk->next = t_gk->next;
                                free(t_gk);
                                t_gk = prev_gk;
                                break;
                            }
                            else
                            {
                                delete_instr(prev_instr, t_instr);
                                t_instr = prev_instr->next;
                                prev_gk->next = t_gk->next;
                                free(t_gk);
                                t_gk = prev_gk->next;
                            }
                            /*
                            if (temp_instr->dest.operand_type == Deref_operand && temp_instr->op == Assn_op)
                                break;
                            t_instr = t_instr->next;
                            t_gk = prev_gk->next;
                            */
                        }

                        start_again = true;

                        /*
                        delete_instr(prev_prev_instr, prev_instr);
                        prev_instr = prev_prev_instr;
                        delete_instr(prev_instr, t_instr);
                        t_instr = prev_instr->next;
                        delete_instr(prev_instr, t_instr);
                        t_instr = prev_instr;
                        //
                        t_gk->kill_dest_i = NULL;
                        t_gk->gen_src1_i = NULL;
                        t_gk->gen_src2_i = NULL;
                        prev_prev_gk->next = prev_gk->next;
                        free(prev_gk);
                        prev_gk = prev_prev_gk;
                        prev_gk->next = t_gk->next;
                        free(t_gk);
                        t_gk = prev_gk->next;
                        prev_gk->next = t_gk->next;
                        free(t_gk);
                        t_gk = prev_gk;
                        start_again = true;
                    */
                    }
                }
                else
                {
                    delete_instr(prev_instr, t_instr);
                    t_instr = prev_instr;
                    //kill the gen and kill set for that instruction
                    t_gk->kill_dest_i = NULL;
                    t_gk->gen_src1_i = NULL;
                    t_gk->gen_src2_i = NULL;
                    if (prev_gk == NULL)
                    {
                        prev_gk = t_gk;
                        t_gk = t_gk->next;
                        free(prev_gk);
                        t_block->head_gk_set = t_gk;
                        prev_gk = NULL;
                        remove_first_set = true;
                    }
                    else
                    {
                        prev_gk->next = t_gk->next;
                        free(t_gk);
                        t_gk = prev_gk;
                    }
                    start_again = true;
                }
            }
        }
        if (remove_first_set != true)
        {
            prev_prev_gk = prev_gk;
            prev_gk = t_gk;
            t_gk = t_gk->next;
        }
        prev_prev_instr = prev_instr;
        prev_instr = t_instr;
        t_instr = t_instr->next;
    }
    //modify the
    free_symnode_struct(&t_block->gen);
    t_block->gen = NULL;
    free_symnode_struct(&t_block->kill);
    t_block->kill = NULL;
    complete_gen_kill(t_block);
    /*
    printf("After Dead code Analysis \n");
    printf("Gen : ");
    print_gen_kill(&t_block->gen);
    printf("Kill : ");
    print_gen_kill(&t_block->kill);
*/
    return;
}
