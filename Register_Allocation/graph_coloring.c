#include "graph_coloring.h"

register_alloc registers[20];
symtabnode **node_stack;
int node_stack_total;
bool success_found = false;
void start_graph_coloring(tnode *t)
{
    total_reg = 20;
    do
    {
        if (print_graph == 1)
            printf("*********In graph coloring***********\n");
        tmp_graph_size = copy_the_graph(&g_head, &tmp_g_head); //copy the graph into the new structure
        if (print_graph == 1)
            print_the_graph(&tmp_g_head, &tmp_graph_size);
        graph_coloring_algo();
        if (print_graph == 1)
            printf("\n*********original graph***********\n");
        if (print_graph == 1)
            print_the_graph(&g_head, &graph_size);
        if (print_graph == 1)
            print_reg_assigned(&g_head);
        success_found = assign_register();
        if (print_graph == 1)
            print_reg_assigned(&g_head);
        //spill the registers if the success is not found
        if (success_found == false)
        {
            symtabnode *t_stptr;
            t_stptr = spill_vertex();
            if (print_graph == 1)
            {
                printf("------------------VERTEX SPILL : %s -------------\n", t_stptr->name);
                print_the_graph(&g_head, &graph_size);
            }
        }
    } while (success_found == false);
}

bool assign_register()
{
    int preserved_used = 0;
    int not_preserved_used = 0;
    graph_node *temp_graph_node;
    sym_node *t_addj;
    int reg_used = -1;
    for (int i = 0; i < 20; i++)
        check_reg_num_used[i] = false;
    for (int i = 0; i < node_stack_total; i++)
    {
        //go through its neighbours and check if any of them has a register assigned if none than assign the preserved
        //find the graph node for that vertex
        bool reg_fill[20] = {false}; //to check the number of register that are filled and the values they are filled
        temp_graph_node = graph_node_vertex(node_stack[i], &g_head);
        t_addj = temp_graph_node->adj_head;
        //iterate through the neighbours and check the registers assigned to its neighbours
        while (t_addj != NULL)
        {
            reg_used = t_addj->vertex->reg_used;
            if (reg_used != -1)
            {
                reg_fill[reg_used] = true;
            }
            t_addj = t_addj->next;
        }
        //return the reg to allocated depending on the registers allocated
        temp_graph_node->reg_used = alloc_reg(reg_fill);
        if (temp_graph_node->reg_used == -1)
        {
            node_stack_total = 0;
            free(node_stack);
            node_stack = NULL;
            return false;
        }

        check_reg_num_used[temp_graph_node->reg_used] = true;
    }
    node_stack_total = 0;
    free(node_stack);
    node_stack = NULL;
    return true;
}

int alloc_reg(bool *reg_fill)
{
    int reg_value = -1;
    for (int i = 0; i < 20; i++)
    {
        if (reg_fill[i] == false)
        {
            return i;
        }
    }
    return reg_value;
}

void graph_coloring_algo()
{
    //find the node with the fewest neighbour or less than k
    //and delete that neighbour on the stack and than delete it
    int neighbour_count = 0;
    int curr_stack = 0;
    symtabnode *t_stptr;
    node_stack = malloc(tmp_graph_size * sizeof(struct stblnode));
    node_stack_total = tmp_graph_size;
    int no_of_vertices = tmp_graph_size - 1;
    for (; no_of_vertices >= 0; no_of_vertices--)
    {
        t_stptr = least_neighbours(&tmp_g_head, total_reg, &neighbour_count);
        node_stack[no_of_vertices] = t_stptr;
        if (print_graph == 1)
            printf("%s , ", t_stptr->name);
        delete_graph_vertex(t_stptr, &tmp_g_head, &tmp_graph_size);
        //printf("*********Print graph coloring***********\n");
        //print_the_graph(&tmp_g_head, &tmp_graph_size);
    }
    if (print_graph == 1)
    {
        printf("\n");
        for (int i = 0; i < node_stack_total; i++)
        {
            printf("%s , ", node_stack[i]->name);
        }
    }
    tmp_g_head = NULL;
}

symtabnode *spill_vertex()
{
    graph_node *t_g = g_head;
    float spill_cost = 9999999;
    symtabnode *node_to_delete = NULL;
    while (t_g != NULL)
    {
        if (t_g->neighbours == 0)
            t_g->spill_cost = t_g->g_node->freq; //determine the spill cost
        else
            t_g->spill_cost = (float)t_g->g_node->freq / t_g->neighbours;
        if (spill_cost >= t_g->spill_cost)
        {
            spill_cost = t_g->spill_cost;
            node_to_delete = t_g->g_node;
        }
        t_g = t_g->next_node;
    }
    if (node_to_delete == NULL)
    {
        printf("*****Houston You got a problem here*************\n");
    }
    delete_graph_vertex(node_to_delete, &g_head, &graph_size);
    return node_to_delete;
}