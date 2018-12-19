#include "peep_opti.h"

int instruction_count = 0;

void remove_if(tnode *t)
{
    instr *t_instr = t->code;
    instr *prev = NULL;
    instr *prev_instr, *prev_if;
    int curr_label;
    bool is_it_continuous = false;
    //delete consecutive goto's
    while (t_instr != NULL)
    {
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
            is_it_continuous = true;
            prev_if = t_instr;
            break;
        case Label_op:
            if (is_it_continuous == true)
            {
                if (t_instr->dest.val.i_const == prev_if->dest.val.i_const)
                {
                    delete_instr(prev_instr, prev_if);
                    delete_instr(prev_instr, t_instr);
                    t_instr = prev_instr;
                }
            }
            prev_instr = t_instr;
            is_it_continuous = false;
            break;
        default:
            prev_instr = t_instr;
            is_it_continuous = false;
            break;
        }
        t_instr = t_instr->next;
    }
}
void machine_independent_optimization_if_goto_con(tnode *t)
{
    instr *t_instr = t->code;
    instr *prev = NULL;
    instr *prev_jump, *prev_if;
    int curr_label;
    bool is_it_continuous = false;
    //delete consecutive goto's
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Goto_op:
            if (is_it_continuous == true)
            {
                delete_instr(prev_jump, t_instr);
                t_instr = prev_jump;
            }
            is_it_continuous = true;
            prev_jump = t_instr;
            break;
        default:
            is_it_continuous = false;
            break;
        }
        t_instr = t_instr->next;
    }
    t_instr = t->code;
    is_it_continuous = false;
    while (t_instr != NULL)
    {
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
            is_it_continuous = true;
            prev_if = t_instr;
            break;
        case Goto_op:
            if (is_it_continuous == true)
            {
                is_it_continuous = false;
                //make sure that label after this has address of the next statement if its true than go ahead and delete that label also
                if (t_instr->next->op == Label_op)
                {
                    if (t_instr->next->dest.val.i_const != prev_if->dest.val.i_const)
                        break;
                }
                else
                    break;

                //change the if condition in the prev if statement to exact opposite
                if (prev_if->op == If_Equals_op)
                    prev_if->op = If_Neq_op;
                else if (prev_if->op == If_Neq_op)
                    prev_if->op = If_Equals_op;
                else if (prev_if->op == If_Leq_op)
                    prev_if->op = If_Gt_op;
                else if (prev_if->op == If_Lt_op)
                    prev_if->op = If_Geq_op;
                else if (prev_if->op == If_Geq_op)
                    prev_if->op = If_Lt_op;
                else if (prev_if->op == If_Gt_op)
                    prev_if->op = If_Leq_op;
                else if (prev_if->op == If_LogicalAnd_op)
                    prev_if->op = If_LogicalOr_op;
                else if (prev_if->op == If_LogicalOr_op)
                    prev_if->op = If_LogicalAnd_op;
                else
                {
                }
                prev_if->dest.val.i_const = t_instr->dest.val.i_const;
                //delete the goto instr
                t_instr = delete_instr(prev_if, t_instr);
                //you can delete the next label also..if required...
            }

            break;
        default:
            is_it_continuous = false;
            break;
        }
        t_instr = t_instr->next;
    }
    //delete unused label
    t_instr = t->code;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Label_op:
            if (check_label(t, t_instr->dest.val.i_const) == true)
                t_instr = delete_instr(prev, t_instr);
            prev = t_instr;
            break;
        default:
            prev = t_instr;
        }
        t_instr = t_instr->next;
    }
    return;
}

void machine_independent_optimization_Bin_Unary(tnode *t)
{
    instr *t_instr = t->code;
    //  instr *prev = NULL;
    instr *prev_op = NULL;
    bool is_it_continuous = false;
    char *name_prev;
    int value_prev;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case UnaryMinus_op:
        case LogicalNot_op:
            if (t_instr->dest.operand_type != SymtabPtr_operand)
                break;
            is_it_continuous = true;
            name_prev = t_instr->dest.val.stptr->name;
            prev_op = t_instr;
            break;
        case Plus_op:
        case Div_op:
        case Mult_op:
        case BinaryMinus_op:
            if (t_instr->dest.operand_type != SymtabPtr_operand)
                break;
            is_it_continuous = true;
            name_prev = t_instr->dest.val.stptr->name;
            prev_op = t_instr;
            break;
        case Assn_op:
            if (is_it_continuous == true)
            {
                if (t_instr->src1.operand_type == SymtabPtr_operand && t_instr->dest.operand_type == SymtabPtr_operand)
                {
                    if (strcmp(name_prev, t_instr->src1.val.stptr->name) == 0)
                    {
                        //error because its an global array check it...
                        // prev_op->dest.operand_type = t_instr->dest.operand_type;
                        prev_op->dest.val.stptr = t_instr->dest.val.stptr;
                        t_instr = delete_instr(prev_op, t_instr);
                        t_instr = prev_op;
                    }
                    is_it_continuous = false;
                    //    prev = t_instr;
                }
            }
            is_it_continuous = false;
            break;
        default:
            //   prev = t_instr;
            prev_op = NULL;
            is_it_continuous = false;
            name_prev = "garbage___";
            break;
        }
        t_instr = t_instr->next;
    }

    return;
}

void machine_independent_optimization_const(tnode *t)
{
    instr *t_instr = t->code;
    instr *prev = NULL;
    instr *prev_assign = NULL;
    bool is_it_continuous = false;
    char *name_prev;
    int value_prev;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Assn_op:
            if (is_it_continuous == true)
            {
                if (t_instr->src1.operand_type == SymtabPtr_operand)
                {
                    // if(SymTabLookupAll()->type== SymTabLookupAll()->type)
                    if (strcmp(name_prev, t_instr->src1.val.stptr->name) == 0)
                    {
                        if (prev_assign->src1.operand_type == Intcon_operand)
                        {
                            t_instr->src1.operand_type = Intcon_operand;
                            t_instr->src1.val.i_const = value_prev;
                        }
                        else if (prev_assign->src1.operand_type == Charcon_operand)
                        {
                            t_instr->src1.operand_type = Charcon_operand;
                            t_instr->src1.val.char_const = value_prev;
                        }

                        delete_instr(prev, prev_assign);
                    }
                    is_it_continuous = false;
                    prev = t_instr;
                }
            }
            else if (t_instr->src1.operand_type == Intcon_operand)
            {
                is_it_continuous = true;
                name_prev = t_instr->dest.val.stptr->name;
                value_prev = t_instr->src1.val.i_const;
                prev_assign = t_instr;
            }
            else if (t_instr->src1.operand_type == Charcon_operand)
            {
                is_it_continuous = true;
                name_prev = t_instr->dest.val.stptr->name;
                value_prev = t_instr->src1.val.char_const;
                prev_assign = t_instr;
            }
            else
            {
                prev = t_instr;
                is_it_continuous = false;
            }
            break;
        default:
            prev = t_instr;
            is_it_continuous = false;
            name_prev = "garbage___";
            break;
        }
        t_instr = t_instr->next;
    }
    return;
}

void machine_independent_optimization_jump(tnode *t)
{
    instr *t_instr = t->code;
    instr *prev = NULL;
    instr *prev_jump;
    int curr_label;
    bool change = true;

    while (change == true)
    {
        t_instr = t->code;
        prev = NULL;
        prev_jump = NULL;
        change = false;
        while (t_instr != NULL)
        {
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
                //check because of the goto try to collapse if there are useless jumps
                //check the labels and pass the label and than iterate through it
                curr_label = -1;
                while (curr_label != t_instr->dest.val.i_const)
                {
                    curr_label = t_instr->dest.val.i_const;
                    t_instr->dest.val.i_const = identify_the_chains(t_instr->dest.val.i_const, t);
                    if (curr_label != t_instr->dest.val.i_const)
                        change = true;
                    else
                        break;
                }
                //delete the chain instructions
                prev = t_instr;
                prev_jump = NULL;
                break;
            case Label_op:
                if (prev_jump != NULL)
                {
                    if (prev_jump->dest.val.i_const == t_instr->dest.val.i_const)
                    {
                        delete_instr(prev, prev_jump);
                        change = true;
                    }
                }
                prev_jump = NULL;
                prev = t_instr;
                break;
            case Goto_op:
                curr_label = -1;
                while (curr_label != t_instr->dest.val.i_const)
                {
                    curr_label = t_instr->dest.val.i_const;
                    t_instr->dest.val.i_const = identify_the_chains(t_instr->dest.val.i_const, t);
                    if (curr_label != t_instr->dest.val.i_const)
                        change = true;
                    else
                        break;
                }
                prev_jump = t_instr;
                break;
            default:
                prev = t_instr;
                prev_jump = NULL;
            }
            t_instr = t_instr->next;
        }

        //delete unused labels
        t_instr = t->code;
        while (t_instr != NULL)
        {
            switch (t_instr->op)
            {
            case Label_op:
                if (check_label(t, t_instr->dest.val.i_const) == true)
                {
                    delete_instr(prev, t_instr);
                    t_instr = prev->next;
                    change = true;
                }
                break;
            default:
                break;
            }
            prev = t_instr;
            t_instr = t_instr->next;
        }
    }

    return;
}

int identify_the_chains(int label_name, tnode *t)
{
    instr *t_instr = t->code;
    instr *prev = NULL;
    instr *label_instr = NULL;
    int label_to_jump = label_name;
    bool is_it_continuous = false;
    while (t_instr != NULL)
    {
        switch (t_instr->op)
        {
        case Label_op:
            if (is_it_continuous == true)
            {
                label_to_jump = t_instr->dest.val.i_const;
                //    delete_instr(prev, label_instr);
                return label_to_jump;
            }
            if (t_instr->dest.val.i_const == label_to_jump)
            {
                is_it_continuous = true;
                label_instr = t_instr;
            }
            break;
        case Goto_op:
            if (is_it_continuous == true)
            {
                // label_to_jump = t_instr->dest.val.i_const;
                label_to_jump = t_instr->dest.val.i_const;
                //   delete_instr(prev, label_instr);
                //  t_instr = delete_instr(prev, t_instr);
                return label_to_jump;
                // label_to_jump = identify_the_chains(label_to_jump, t);
            }
            break;
        default:
            is_it_continuous = false;
            prev = t_instr;
        }
        t_instr = t_instr->next;
    }
    return label_to_jump;
}

bool check_label(tnode *t, int label_name)
{
    instr *t_instr = t->code;
    while (t_instr != NULL)
    {
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
            if (label_name == t_instr->dest.val.i_const)
            {
                return false;
            }
            break;
        case Goto_op:
            if (label_name == t_instr->dest.val.i_const)
            {
                return false;
            }
            break;
        }
        t_instr = t_instr->next;
    }
    return true;
}
instr *delete_instr(instr *prev, instr *t_instr)
{
    if (prev == NULL || t_instr->next == NULL)
        return t_instr;
    prev->next = t_instr->next;
    free(t_instr);
    return prev->next;
}