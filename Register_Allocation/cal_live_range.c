#include "cal_live_range.h"

void print_the_graph(graph_node **src_head, int *g_size)
{
    if (*g_size == 0)
        return;
    graph_node *t_g = *src_head;
    sym_node *t_addj;
    while (t_g != NULL)
    {
        printf("Vertex : %s, Edges :", t_g->g_node->name);
        t_addj = t_g->adj_head;
        while (t_addj != NULL)
        {
            printf(" %s,", t_addj->vertex->g_node->name);
            t_addj = t_addj->next;
        }
        printf("  Neighbours : %i", t_g->neighbours);
        printf("  frequency : %i\n", t_g->g_node->freq);
        t_g = t_g->next_node;
    }
}

bool add_graph_edge(symtabnode *src_node, symtabnode *dest_node, graph_node **src_head)
{
    //add it to all the nodes of the graph
    if (src_node == dest_node)
    {
        return;
    }
    graph_node *t_g = *src_head;
    graph_node *temp_g;
    //graph_node *t_addj, *prev_addj;
    sym_node *t_addj, *prev_addj;
    bool found;
    while (t_g != NULL)
    {
        if (t_g->g_node == dest_node)
        {
            t_addj = t_g->adj_head;
            prev_addj = NULL;
            found = false;
            while (t_addj != NULL)
            {
                if (t_addj->vertex->g_node == src_node)
                {
                    found = true;
                    break;
                }
                prev_addj = t_addj;
                t_addj = t_addj->next;
            }
            if (found == false)
            {

                temp_g = *src_head;
                while (temp_g != NULL)
                {
                    if (strcmp(temp_g->g_node->name, src_node->name) == 0)
                    {
                        break;
                    }
                    temp_g = temp_g->next_node;
                }
                //Not found now try to add to the graph
                if (prev_addj == NULL) //No edge is there on the vertex
                {
                    t_g->adj_head = malloc(sizeof(struct sym_node));
                    t_g->adj_head->vertex = temp_g;
                    t_g->adj_head->next = NULL;
                }
                else
                {
                    prev_addj->next = malloc(sizeof(struct sym_node));
                    prev_addj->next->vertex = temp_g;
                    prev_addj->next->next = NULL;
                }
                t_g->neighbours++;
            }
        }
        if (t_g->g_node == src_node)
        {
            t_addj = t_g->adj_head;
            prev_addj = NULL;
            found = false;
            while (t_addj != NULL)
            {
                if (t_addj->vertex->g_node == dest_node)
                {
                    found = true;
                    break;
                }
                prev_addj = t_addj;
                t_addj = t_addj->next;
            }
            if (found == false)
            {
                //Not found now try to add to the graph
                temp_g = *src_head;
                while (temp_g != NULL)
                {
                    if (strcmp(temp_g->g_node->name, dest_node->name) == 0)
                    {
                        break;
                    }
                    temp_g = temp_g->next_node;
                }
                if (prev_addj == NULL) //No edge is there on the vertex
                {
                    t_g->adj_head = malloc(sizeof(struct sym_node));
                    t_g->adj_head->vertex = temp_g;

                    t_g->adj_head->next = NULL;
                }
                else
                {
                    prev_addj->next = malloc(sizeof(struct sym_node));
                    prev_addj->next->vertex = temp_g;
                    prev_addj->next->next = NULL;
                }
                t_g->neighbours++;
            }
        }

        t_g = t_g->next_node;
    }
    return true;
}

bool check_vertex_exist(symtabnode *s_node, graph_node **src_head)
{
    graph_node *t_g = *src_head;
    while (t_g != NULL)
    {
        if (t_g->g_node == s_node)
        {
            return true;
        }
        if (strcmp(t_g->g_node->name, s_node->name) == 0)
        {
            return true;
        }
        t_g = t_g->next_node;
    }
    return false;
}
bool delete_graph_vertex(symtabnode *s_node, graph_node **src_head, int *g_size)
{
    if (*g_size == 0)
    {
        return false;
    }
    graph_node *t_g = *src_head;
    graph_node *prev_g = NULL;
    sym_node *t_addj, *prev_addj;
    //first delete all of its edges that may be present
    while (t_g != NULL)
    {
        t_addj = t_g->adj_head;
        prev_addj = NULL;
        while (t_addj != NULL)
        {
            if (t_addj->vertex->g_node == s_node)
            {
                //delete the node
                if (prev_addj == NULL)
                {
                    t_g->adj_head = t_g->adj_head->next;
                    free(t_addj);
                    t_addj = t_g->adj_head;
                }
                else
                {
                    prev_addj->next = t_addj->next;
                    free(t_addj);
                    t_addj = prev_addj->next;
                }
                t_g->neighbours--;
                break;
            }
            prev_addj = t_addj;
            t_addj = t_addj->next;
        }
        t_g = t_g->next_node;
    }
    t_g = *src_head;
    //transverse the graph till we get to the end
    prev_g = NULL;
    while (t_g != NULL)
    {
        if (t_g->g_node == s_node)
        {
            if (prev_g == NULL) //this means this is the head node
            {
                *src_head = t_g->next_node;
                free(t_g);
                *g_size = *g_size - 1;
                // graph_size--;
                return true;
            }
            else
            {
                prev_g->next_node = t_g->next_node;
                free(t_g);
                *g_size = *g_size - 1;
                //graph_size--;
                return false;
            }
        }
        prev_g = t_g;
        t_g = t_g->next_node;
    }
    return false;
}

bool add_graph_vertex(symtabnode *s_node, graph_node **src_head, int *g_size)
{
    graph_node *t_g = *src_head;
    if (*g_size == 0)
    {
        //make a node and make it as head
        *src_head = malloc(sizeof(struct graph_node));
        t_g = *src_head;
        assert(t_g);
        t_g->g_node = s_node;
        t_g->neighbours = 0;
        t_g->adj_head = NULL;
        t_g->reg_used = -1;
        t_g->spill_cost = 0;
        t_g->next_node = NULL;
        *g_size = *g_size + 1;
        return true;
    }
    else
    {
        //graph_node *t_g = g_head;
        graph_node *prev_g = NULL;
        //transverse the graph till we get to the end
        while (t_g != NULL)
        {
            //if you find the vertex with same node than return
            if (t_g->g_node == s_node)
            {
                //   printf("vertex Already there\n");
                return true;
            }
            prev_g = t_g;
            t_g = t_g->next_node;
        }
        prev_g->next_node = malloc(sizeof(struct graph_node));
        assert(prev_g->next_node);
        prev_g->next_node->g_node = s_node;
        prev_g->next_node->neighbours = 0;
        prev_g->next_node->reg_used = -1;
        prev_g->next_node->spill_cost = 0;
        prev_g->next_node->adj_head = NULL;
        prev_g->next_node->next_node = NULL;
        *g_size = *g_size + 1;
        return true;
    }
    return false;
}

int copy_the_graph(graph_node **src_head, graph_node **dest_head)
{
    graph_node *t_g = *src_head;
    graph_node *temp_g = *src_head;
    graph_node *d_g = *dest_head;
    graph_node *prev_dg = NULL;
    sym_node *t_addj, *d_addj, *prev_d_addj;
    int count = 0;
    int inside_count;
    while (t_g != NULL)
    {
        //make the malloc vertex for the destinatin
        d_g = malloc(sizeof(struct graph_node));
        assert(d_g);
        if (count == 0)
            *dest_head = d_g;
        d_g->g_node = t_g->g_node;
        d_g->adj_head = NULL;
        d_g->neighbours = t_g->neighbours;
        d_g->next_node = NULL;
        if (prev_dg != NULL)
            prev_dg->next_node = d_g;
        prev_dg = d_g;
        t_g = t_g->next_node;
        count++;
    }
    //now add the nodes
    d_g = *dest_head;
    t_g = *src_head;
    while (d_g != NULL)
    {
        temp_g = *dest_head;
        inside_count = 0;
        t_addj = t_g->adj_head;
        prev_d_addj = NULL;
        while (t_addj != NULL)
        {
            d_addj = malloc(sizeof(struct sym_node));
            assert(d_addj);
            if (inside_count == 0)
                d_g->adj_head = d_addj;
            temp_g = *dest_head;
            while (temp_g != NULL)
            {
                if (temp_g->g_node == t_addj->vertex->g_node)
                {
                    break;
                }
                temp_g = temp_g->next_node;
            }
            d_addj->vertex = temp_g;
            d_addj->next = NULL;
            if (prev_d_addj != NULL)
                prev_d_addj->next = d_addj;
            prev_d_addj = d_addj;
            inside_count++;
            t_addj = t_addj->next;
        }
        d_g = d_g->next_node;
        t_g = t_g->next_node;
    }
    return count;
}

symtabnode *least_neighbours(graph_node **src_head, int reg_num, int *num_neighbours)
{
    graph_node *t_g = *src_head;
    symtabnode *node_with_least_neigh;
    int least_neighbours = 999999;
    while (t_g != NULL)
    {
        if (t_g->neighbours <= least_neighbours)
        {
            node_with_least_neigh = t_g->g_node;
            least_neighbours = t_g->neighbours;
            *num_neighbours = least_neighbours;
        }
        t_g = t_g->next_node;
    }
    return node_with_least_neigh;
}

int return_reg_allocated(symtabnode *t_stptr, graph_node **src_head)
{
    int return_value = -1;
    graph_node *t_g = *src_head;
    while (t_g != NULL)
    {
        if (t_g->g_node == t_stptr)
        {
            return_value = t_g->reg_used;
            break;
        }
        t_g = t_g->next_node;
    }
    return return_value;
}

graph_node *graph_node_vertex(symtabnode *t_stptr, graph_node **src_head)
{
    graph_node *t_g = *src_head;
    while (t_g != NULL)
    {
        if (t_g->g_node == t_stptr)
        {
            break;
        }
        t_g = t_g->next_node;
    }
    return t_g;
}
void print_reg_assigned(graph_node **src_head)
{
    graph_node *t_g = *src_head;
    printf("\n");
    while (t_g != NULL)
    {
        printf(" vertex %s, reg no : %i\n", t_g->g_node->name, t_g->reg_used);
        t_g = t_g->next_node;
    }
    return;
}

void add_live_now_vertices(struct symtabnode_struct **t_node_head)
{
    struct symtabnode_struct *t_n = *t_node_head;
    while (t_n != NULL)
    {
        add_graph_vertex(t_n->kill_gen_in_out, &g_head, &graph_size);
        t_n = t_n->next;
    }
    return;
}
