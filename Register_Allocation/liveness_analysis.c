#include "liveness_analysis.h"
static int iteration_count;
static int prinf_in_out = 0;
static Block *block_list[50];
static int block_list_count = 0;
symtabnode *global_variables[50];
int num_of_globals = 0;

void find_in_out(tnode *t)
{
    Block *t_block = block_head;
    num_of_globals = return_all_globes(global_variables, function_name);
    assign_gen_to_in();
    iteration_count = 1;
    t_block->out = NULL;
    while (t_block != NULL)
    {
        t_block->prev_in = NULL;
        t_block->prev_out = NULL;
        t_block = t_block->next;
    }
    t_block = block_head;
    do
    {
        block_list_count = 0;
        block_list[block_list_count++] = t_block;
        //    printf("***************Iteration  Start No : %i\n", iteration_count);
        transverse_blocks_backwards(t_block, t);
        in_out_analysis(t_block);
        print_in_out_analysis(t_block);
        //  printf("***************Iteration END No : %i\n", iteration_count);
        iteration_count++;

    } while (compare_blocks() == false);
    return;
}

void transverse_blocks_backwards(Block *t_block, tnode *t)
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
            transverse_blocks_backwards(child(t_block), t);
            in_out_analysis(child(t_block));
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
            //  printf("Analysis leader name %s");
            //  print_instruction_block(l_child(t_block)->head);
            transverse_blocks_backwards(l_child(t_block), t);

            in_out_analysis(l_child(t_block));
            print_in_out_analysis(l_child(t_block));
        }
        if (r_child(t_block)->iteration_num != iteration_count)
        {

            if (check_if_block_transversed(r_child(t_block)) == true)
            {
                return;
            }
            //printf("Analysis leader name %s");
            //print_instruction_block(r_child(t_block)->head);
            transverse_blocks_backwards(r_child(t_block), t);
            in_out_analysis(r_child(t_block));
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

bool check_if_block_transversed(Block *t_block)
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

void in_out_analysis(Block *t_block)
{
    t_block->iteration_num++;
    //********OUT OPERATION*************//
    //free all the variables of the out struct
    free_symnode_struct(&t_block->out);
    t_block->out = NULL;
    //Do out analysis 1st
    if (t_block->b_type == No_Branch)
    {
        //since only one child just copy its content like I did in assign
        copy_symnode_struct(&(t_block->val.child_node.child->in), &t_block->out);
    }
    else if (t_block->b_type == Branch)
    {
        //copy the lchild
        copy_symnode_struct(&(t_block->val.binary_node.l_child->in), &t_block->out);
        //iterate and add elements that dont exist for the rchild..since some elements can be common from both the blocks
        struct symtabnode_struct *t_in = t_block->val.binary_node.r_child->in;
        while (t_in != NULL)
        {
            add_var_in_gkio(&t_block->out, t_in->kill_gen_in_out);
            t_in = t_in->next;
        }
    }
    else if (t_block->b_type == Finish)
    {
        //write code for adding the the return variable and the globals
        instr *t_instr = t_block->head;
        for (; t_instr != NULL; t_instr = t_instr->next)
        {
            if (t_instr->op == Return_op)
            {
                if (t_instr->dest.operand_type != NONE)
                    add_var_in_gkio(&t_block->out, t_instr->dest.val.stptr);
            }
            //Now add all the globals
        }
        for (int i = 0; i < num_of_globals; i++)
        {
            add_var_in_gkio(&t_block->out, global_variables[i]);
        }
        //Now add all the params of the function...
    }
    //***********IN OPERATION*************//
    //free all the variables of the in struct
    free_symnode_struct(&t_block->in);
    //do the minus operation on the t_block->out out[B]-kill[B]
    struct symtabnode_struct *t_kill = t_block->kill;
    copy_symnode_struct(&t_block->out, &t_block->in); //this is copy out to in
    while (t_kill != NULL)
    {
        if (t_kill->kill_gen_in_out->formal != true && t_kill->kill_gen_in_out != Global)
            min_var_in_gkio(&t_block->in, t_kill->kill_gen_in_out);
        t_kill = t_kill->next;
    }
    //do the union operation between
    struct symtabnode_struct *t_gen = t_block->gen;
    while (t_gen != NULL)
    {
        add_var_in_gkio(&t_block->in, t_gen->kill_gen_in_out);
        t_gen = t_gen->next;
    }
    return;
}

void free_symnode_struct(struct symtabnode_struct **gkio)
{
    if (*gkio == NULL)
    {
        return;
    }
    struct symtabnode_struct *t_gkio = *gkio;
    //struct symtabnode_struct *t_gkio = gkio;

    while (t_gkio != NULL)
    {
        t_gkio = t_gkio->next;
        free(t_gkio);
    }
    *gkio = NULL;
    return;
}

void copy_symnode_struct(struct symtabnode_struct **src, struct symtabnode_struct **dest)
{
    bool in_head = true;
    struct symtabnode_struct *t_src = *src;
    struct symtabnode_struct *t_dest, *prev_dest;
    if (t_src == NULL)
    {
        *dest = NULL;
    }
    while (t_src != NULL)
    {
        t_dest = malloc(sizeof(struct symtabnode_struct));
        if (in_head == true)
        {
            in_head = false;
            *dest = t_dest;
        }
        else
        {
            prev_dest->next = t_dest;
        }
        prev_dest = t_dest;
        t_dest->kill_gen_in_out = t_src->kill_gen_in_out;
        prev_dest->next = NULL;
        t_src = t_src->next;
    }
    return;
}

bool compare_symnode_struct(struct symtabnode_struct **src, struct symtabnode_struct **dest)
{
    struct symtabnode_struct *t_src = *src;
    struct symtabnode_struct *t_dest = *dest;
    bool found;
    if (*src == NULL && *dest != NULL)
        return false;
    if (*src == NULL && *dest == NULL)
        return true;

    for (; t_src != NULL; t_src = t_src->next)
    {
        found = false;

        for (t_dest = *dest; t_dest != NULL; t_dest = t_dest->next)
        {
            if (t_dest->kill_gen_in_out == t_src->kill_gen_in_out)
            {
                found = true;
                break;
            }
        }
        if (found == false)
            return false;
    }

    return true;
}

bool compare_blocks()
{
    Block *t_block = block_head;
    bool compare = true;
    while (t_block != NULL)
    {
        if (compare_symnode_struct(&t_block->prev_in, &t_block->in) == false)
        {
            free_symnode_struct(&t_block->prev_in);
            copy_symnode_struct(&t_block->in, &t_block->prev_in);
            compare = false;
        }
        if (compare_symnode_struct(&t_block->prev_out, &t_block->out) == false)
        {
            free_symnode_struct(&t_block->prev_out);
            copy_symnode_struct(&t_block->out, &t_block->prev_out);
            compare = false;
        }
        t_block = t_block->next;
    }
    return compare;
}

void assign_gen_to_in()
{
    Block *t_block = block_head;
    //  printf("******The in during Initialization**************\n");
    int i = 0;

    while (t_block != NULL)
    {
        //  printf("Block %i in[%i]:    ", i++);
        copy_symnode_struct(&t_block->gen, &t_block->in);

        if (global_all_live == true)
        {
            for (i = 0; i < num_of_globals; i++)
            {
                add_var_in_gkio(&t_block->in, global_variables[i]);
            }
        }
        print_gen_kill(&t_block->in);
        t_block->out = NULL;
        t_block = t_block->next;
    }
    global_all_live = false;
    //  printf("******nitialization complete**************\n");
}

void print_in_out_analysis(Block *t_block)
{
    if (allow_print_all_Blocks == 0)
        return 0;
    printf("Leader :");
    if (t_block->head != NULL)
        print_instruction_block(t_block->head);
    if (1 == 1)
    {
        printf("in: ");
        print_gen_kill(&t_block->in);
        printf("out: ");
        print_gen_kill(&t_block->out);
    }
}