#include "three.h"
char *function_name;

#define print3code 0

#define L_value 0
#define R_value 1
str_table *str_table_head;
symtabnode *SymTab_GL[2][256];
bool stnode_exist = false;
static int label_num = 0;

void enter_function(tnode *t, char *fun_name)
{
    symtabnode *stptr;
    int sc = Global;
    tnode *temp0;
    instr *t_instr;
    temp0 = t;
    stnode_exist = false;
    function_name = fun_name;
    stptr = SymTabLookup(fun_name, sc);
    if (print3code == 1)
        printSTNode(stptr);
    //create instruction
    t_instr = newinstr(Enter_op, NONE, NONE, SymtabPtr_operand);
    t_instr->dest.val.stptr = stptr;
    t_instr->next = NULL;
    //insert instructions
    insert_code(&(t->code), t_instr);
    t->place = stptr;
    //transverse_tree(t, 4, 0);
    code_gen_stmt(t);
    if (print3code == 1)
        print_instruction(temp0->code);
    generate_assm(temp0);
    //reset the str_table_head
    str_table_head = NULL;
    //free_malloc_t_code(t,0,0);
    return;
}
void code_gen_stmt(tnode *t)
{
    int sc;
    symtabnode *stptr;
    tnode *tntmp0;
    instr *t_instr;
    if (t == NULL)
    {
        //  printf("-null-\n");
        return;
    }
    switch (t->ntype)
    {
    case Error:
        printf("-error-\n");
        break;

    case ArraySubscript:
        codeGen_express(t, R_value);
        break;

    case FunCall:
        codeGen_express(t, R_value);
        // codegen_funcall(t);
        break;
    case Assg:
        code_gen_assg(t, L_value);
        break;

    case Return:
        return_inst(t); //the return instruction
        break;

    case For:
        code_gen_for(t);
        break;

    case While:
        code_gen_while(t);
        break;

    case If:
        code_gen_if_else(t);
        break;

    case STnodeList: /* list of syntax tree nodes */
        stnode_exist = true;
        /* iterate down the list, printing out each tree in the list in turn */
        for (tntmp0 = t; tntmp0 != NULL; tntmp0 = stList_Rest(tntmp0))
        {
            code_gen_stmt(stList_Head(tntmp0));
            if (stList_Head(tntmp0) != NULL)
                insert_code(&(t->code), stList_Head(tntmp0)->code);
        }

        break;
    default:
        fprintf(stderr, "Unknown syntax tree node type %d\n", t->ntype);
    }
    return;
}

void codeGen_express(tnode *t, int lr)
{
    symtabnode *stptr;
    tnode *tntmp0;

    if (t == NULL)
    {
        // t->code = NULL;
        // t->place = NULL;
        return;
    }
    switch (t->ntype)
    {
    case UnaryMinus:
        code_gen_unary(t, UnaryMinus_op, lr);
        break;
    case LogicalNot:
        code_gen_unary(t, LogicalNot_op, lr);
        break;
    case Intcon:
        Intcon_code_assign(t);
        break;
    case Charcon:
        Charcon_code_assign(t);
        break;
    case ArraySubscript:
        code_gen_array(t, lr);
        store_Global_Local(stArraySubscript_Array(t), stArraySubscript_Array(t)->scope);
        break;
    case Stringcon:
        string_code_assign(t);
        break;
    case Var:
        t->place = stVar(t);
        t->code = NULL;
        store_Global_Local(stVar(t), stVar(t)->scope);
        break;
    case Plus:
        code_gen_binary(t, Plus_op, lr);
        break;
    case BinaryMinus:
        code_gen_binary(t, BinaryMinus_op, lr);
        break;
    case Mult:
        // printf("Here in Multi\n");
        code_gen_binary(t, Mult_op, lr);
        break;
    case Div:
        code_gen_binary(t, Div_op, lr);
        break;
    case FunCall:
        codegen_funcall(t);
        break;
    case Equals:
        code_gen_binary(t, Equals_op, lr);
        break;
    case Neq:
        code_gen_binary(t, Neq_op, lr);
        break;
    case Leq:
        code_gen_binary(t, Leq_op, lr);
        break;
    case Lt:
        code_gen_binary(t, Lt_op, lr);
        break;
    case Geq:
        code_gen_binary(t, Geq_op, lr);
        break;
    case Gt:
        code_gen_binary(t, Gt_op, lr);
        break;
    case LogicalAnd:
        code_gen_binary(t, LogicalAnd_op, lr);
    case LogicalOr:
        code_gen_binary(t, LogicalOr_op, lr);
        break;
    case STnodeList:
        //this is for the arg list code
        for (tntmp0 = t; tntmp0 != NULL; tntmp0 = stList_Rest(tntmp0))
        {
            codeGen_express(stList_Head(tntmp0), R_value);
            if (stList_Head(tntmp0) != NULL)
                insert_code(&(t->code), stList_Head(tntmp0)->code);
        }
        break;
    default:
        fprintf(stderr, "Unknown Expression tree node type %d\n", t->ntype);
    }
    return;
}

void code_gen_for(tnode *t)
{
    instr *L_top, *L_eval, *L_after, *t_instr;
    L_top = newlabel();
    L_after = newlabel();
    L_eval = newlabel();
    code_gen_stmt(stFor_Init(t));
    Code_gen_BOOL_MAIN(stFor_Test(t), L_top, L_after);
    code_gen_stmt(stFor_Body(t));
    code_gen_stmt(stFor_Update(t));
    if (stFor_Init(t) != NULL)
        insert_code(&(t->code), stFor_Init(t)->code);
    t_instr = newinstr(Goto_op, NONE, NONE, Intcon_operand);
    t_instr->dest.val.i_const = L_eval->dest.val.i_const;
    insert_code(&(t->code), t_instr);
    insert_code(&(t->code), L_top);
    if (stFor_Body(t) != NULL)
        insert_code(&(t->code), stFor_Body(t)->code);
    if (stFor_Update(t) != NULL)
        insert_code(&(t->code), stFor_Update(t)->code);
    insert_code(&(t->code), L_eval);
    if (stFor_Test(t) != NULL)
        insert_code(&(t->code), stFor_Test(t)->code);
    else
    {
        t_instr = newinstr(Goto_op, NONE, NONE, Intcon_operand);
        t_instr->dest.val.i_const = L_top->dest.val.i_const;
         insert_code(&(t->code), t_instr);
    }
    insert_code(&(t->code), L_after);
    return;
}

void code_gen_while(tnode *t)
{
    instr *L_top, *L_eval, *L_after, *t_instr;
    L_top = newlabel();
    L_eval = newlabel();
    L_after = newlabel();
    Code_gen_BOOL_MAIN(stWhile_Test(t), L_top, L_after);
    code_gen_stmt(stWhile_Body(t));
    t_instr = newinstr(Goto_op, NONE, NONE, Intcon_operand);
    t_instr->dest.val.i_const = L_eval->dest.val.i_const;
    insert_code(&(t->code), t_instr);
    insert_code(&(t->code), L_top);
    if (stWhile_Body(t) != NULL)
        insert_code(&(t->code), stWhile_Body(t)->code);
    insert_code(&(t->code), L_eval);
    if (stWhile_Test(t) != NULL)
        insert_code(&(t->code), stWhile_Test(t)->code);
    insert_code(&(t->code), L_after);
    return;
}
void code_gen_if_else(tnode *t)
{
    instr *L_then, *L_else, *L_after, *t_instr;
    L_then = newlabel();
    L_else = newlabel();
    L_after = newlabel();
    Code_gen_BOOL_MAIN(stIf_Test(t), L_then, L_else);
    code_gen_stmt(stIf_Then(t));
    code_gen_stmt(stIf_Else(t));
    if (stIf_Test(t) != NULL)
        insert_code(&(t->code), stIf_Test(t)->code);
    insert_code(&(t->code), L_then);
    if (stIf_Then(t) != NULL)
        insert_code(&(t->code), stIf_Then(t)->code);
    t_instr = newinstr(Goto_op, NONE, NONE, Intcon_operand);
    t_instr->dest.val.i_const = L_after->dest.val.i_const;
    insert_code(&(t->code), t_instr);
    insert_code(&(t->code), L_else);
    if (stIf_Else(t) != NULL)
        insert_code(&(t->code), stIf_Else(t)->code);
    insert_code(&(t->code), L_after);
    return;
}

void Code_gen_BOOL_MAIN(tnode *t, instr *L_then, instr *L_else)
{
    if (t == NULL)
    {
        return;
    }
    switch (t->ntype)
    {
    case Equals:
    case Neq:
    case Leq:
    case Lt:
    case Geq:
    case Gt:
        code_gen_BOOL_EX(t, L_then, L_else);
        break;
    case LogicalAnd:
        code_gen_BOOL_AND(t, L_then, L_else);
        break;
    case LogicalOr:
        code_gen_BOOL_OR(t, L_then, L_else);
        break;

    case LogicalNot:
        code_gen_BOOL_NOT(t, L_then, L_else);
        break;
    }
    return;
}

void code_gen_BOOL_EX(tnode *t, instr *L_then, instr *L_else)
{
    instr *t_instr;
    codeGen_express(stBinop_Op1(t), R_value);
    codeGen_express(stBinop_Op2(t), R_value);
    if (stBinop_Op1(t) != NULL)
        insert_code(&(t->code), stBinop_Op1(t)->code);
    if (stBinop_Op2(t) != NULL)
        insert_code(&(t->code), stBinop_Op2(t)->code);
    t_instr = newinstr(find_op(t), SymtabPtr_operand, SymtabPtr_operand, Intcon_operand);
    t_instr->dest.val.i_const = L_then->dest.val.i_const;
    t_instr->src1.val.stptr = stBinop_Op1(t)->place;
    t_instr->src2.val.stptr = stBinop_Op2(t)->place;
    insert_code(&(t->code), t_instr);
    t_instr = newinstr(Goto_op, NONE, NONE, Intcon_operand);
    t_instr->dest.val.i_const = L_else->dest.val.i_const;
    insert_code(&(t->code), t_instr);
    return;
}

void code_gen_BOOL_AND(tnode *t, instr *L_then, instr *L_else)
{
    instr *L1 = newlabel();
    Code_gen_BOOL_MAIN(stBinop_Op1(t), L1, L_else);
    Code_gen_BOOL_MAIN(stBinop_Op2(t), L_then, L_else);
    if (stBinop_Op1(t) != NULL)
        insert_code(&(t->code), stBinop_Op1(t)->code);
    insert_code(&(t->code), L1);
    if (stBinop_Op2(t) != NULL)
        insert_code(&(t->code), stBinop_Op2(t)->code);
    return;
}
void code_gen_BOOL_OR(tnode *t, instr *L_then, instr *L_else)
{
    instr *L1 = newlabel();
    Code_gen_BOOL_MAIN(stBinop_Op1(t), L_then, L1);
    Code_gen_BOOL_MAIN(stBinop_Op2(t), L_then, L_else);
    if (stBinop_Op1(t) != NULL)
        insert_code(&(t->code), stBinop_Op1(t)->code);
    insert_code(&(t->code), L1);
    if (stBinop_Op2(t) != NULL)
        insert_code(&(t->code), stBinop_Op2(t)->code);
    return;
}
void code_gen_BOOL_NOT(tnode *t, instr *L_then, instr *L_else)
{
    Code_gen_BOOL_MAIN(stUnop_Op(t), L_else, L_then);
    if (stUnop_Op(t) != NULL)
        insert_code(&(t->code), stUnop_Op(t)->code);
    return;
}

Optype find_op(tnode *t)
{
    switch (t->ntype)
    {
    case Equals:
        return If_Equals_op;
        break;
    case Neq:
        return If_Neq_op;
        break;
    case Leq:
        return If_Leq_op;
        break;
    case Lt:
        return If_Lt_op;
        break;
    case Geq:
        return If_Geq_op;
        break;
    case Gt:
        return If_Gt_op;
        break;
    case LogicalAnd:
        return If_LogicalAnd_op;
        break;
    case LogicalOr:
        return If_LogicalOr_op;
        break;
    default:
        printf("None of If else operatoe foind\n");
        return NONE_op;
    }
}

void code_gen_assg(tnode *t, int lr)
{
    instr *t_instr;
    codeGen_express(stAssg_Lhs(t), L_value);
    codeGen_express(stAssg_Rhs(t), R_value);
    if (stAssg_Lhs(t)->code != NULL)
        insert_code(&(t->code), stAssg_Lhs(t)->code);
    if (stAssg_Rhs(t)->code != NULL)
        insert_code(&(t->code), stAssg_Rhs(t)->code);

    if (stAssg_Lhs(t)->place != NULL)
    {
        t_instr = newinstr(Assn_op, SymtabPtr_operand, NONE, SymtabPtr_operand);
        t_instr->dest.val.stptr = stAssg_Lhs(t)->place;
    }
    else
    {
        t_instr = newinstr(Assn_op, SymtabPtr_operand, NONE, Deref_operand);
        t_instr->dest.val.stptr = stAssg_Lhs(t)->loc;
    }
    t_instr->src1.val.stptr = stAssg_Rhs(t)->place;
    insert_code(&(t->code), t_instr);
    return;
}

void code_gen_array(tnode *t, int lr)
{
    codeGen_express(stArraySubscript_Subscript(t), R_value);

    symtabnode *tmp1 = newtemp(t_Int);
    symtabnode *tmp2 = newtemp(t_Address);
    //e.code
    if (stArraySubscript_Subscript(t) != NULL)
        insert_code(&(t->code), stArraySubscript_Subscript(t)->code);
    instr *t_instr;
    //mult
    t_instr = newinstr(Mult_op, SymtabPtr_operand, Intcon_operand, SymtabPtr_operand);
    t_instr->src1.val.stptr = stArraySubscript_Subscript(t)->place;
    t_instr->src2.val.i_const = width(stArraySubscript_Array(t));
    t_instr->dest.val.stptr = tmp1;
    insert_code(&(t->code), t_instr);
    //plus
    t_instr = newinstr(Plus_op, idLoc_operand, SymtabPtr_operand, Address_operand);
    t_instr->src1.val.stptr = stArraySubscript_Array(t);
    t_instr->src2.val.stptr = tmp1;
    t_instr->dest.val.stptr = tmp2;
    insert_code(&(t->code), t_instr);
    if (lr == L_value)
    {
        t->loc = tmp2;
        t->loc->elt_type = stArraySubscript_Array(t)->elt_type;
        t->place = NULL;
    }
    else
    {
        t->place = newtemp(stArraySubscript_Array(t)->elt_type);
        //deref instruction
        t_instr = newinstr(Deref_op, Address_operand, NONE, SymtabPtr_operand);
        t_instr->src1.val.stptr = tmp2;
        t_instr->dest.val.stptr = t->place;
        insert_code(&(t->code), t_instr);
    }
}

symtabnode *newtemp(int type)
{
    //symtabnode *ntmp = malloc(sizeof(symtabnode));
    symtabnode *ntmp;
    sprintf(temp_var[sym_temp_ref], "tmp_%d", sym_temp_ref);
    ntmp = SymTabInsert(&temp_var[sym_temp_ref], Local);
    // ntmp->name = &temp_var[sym_temp_ref];
    ntmp->type = type;
    ntmp->elt_type = t_None;
    sym_temp_ref++;
    store_Global_Local(ntmp, ntmp->scope);
    return ntmp;
}

instr *newinstr(Optype opType, Operandtype src1, Operandtype src2, Operandtype dest)
{
    instr *ninstr = malloc(sizeof(instr));
    ninstr->op = opType;
    ninstr->src1.operand_type = src1;
    ninstr->src2.operand_type = src2;
    ninstr->dest.operand_type = dest;
    ninstr->next = NULL;
    return ninstr;
}

instr *newlabel()
{
    instr *t_instr;
    t_instr = newinstr(Label_op, NONE, NONE, Intcon_operand);
    t_instr->dest.val.i_const = label_num++;
    return t_instr;
}
void insert_code(struct instruction **t_instr1, struct instruction *insert)
{
    instr *temp;
    if (insert == NULL)
    {
        return;
    }
    if ((*t_instr1) == NULL)
    {
        *t_instr1 = insert;
        //  (*t_instr1)->next=NULL;
        return;
    }
    else
    {
        temp = *t_instr1;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = insert;
        //temp->next->next=NULL;
    }

    return;
}
int width(symtabnode *str)
{
    switch (str->elt_type)
    {
    case t_Char:
        return 1;
    case t_Int:
        return 4;
    }
    return 0;
}

void codegen_funcall(tnode *t)
{
    symtabnode *stptr;
    stptr = stFunCall_Fun(t);
    tnode *tntmp0;
    codeGen_express(stFunCall_Args(t), R_value);
    instr *t_instr;
    int arg_num = 0;
    if (stFunCall_Args(t) != NULL)
        insert_code(&(t->code), stFunCall_Args(t)->code);
    add_param(t, stFunCall_Args(t), &arg_num);
    t_instr = newinstr(Call_op, SymtabPtr_operand, Intcon_operand, NONE);
    t_instr->src1.val.stptr = stptr;
    t_instr->src2.val.i_const = arg_num;
    insert_code(&(t->code), t_instr);
    if (stptr->ret_type != t_None)
    {
        t_instr = newinstr(Retrieve_op, NONE, NONE, SymtabPtr_operand);
        t->place = newtemp(stptr->ret_type);
        t_instr->dest.val.stptr = t->place;
        insert_code(&(t->code), t_instr);
    }
    return;
}

void add_param(tnode *t, tnode *tntmp0, int *arg_num)
{
    if (tntmp0 == NULL)
    {
        return;
    }
    add_param(t, stList_Rest(tntmp0), arg_num);
    stList_Head(tntmp0);
    instr *t_instr;
    t_instr = newinstr(Param_op, SymtabPtr_operand, NONE, NONE);
    t_instr->src1.val.stptr = stList_Head(tntmp0)->place;
    insert_code(&(t->code), t_instr);
    *arg_num = *arg_num + 1;
    return;
}

void code_gen_binary(tnode *t, Optype OP, int lr)
{
    instr *t_instr;
    if (lr == L_value)
    {
        printf("Error lvalue called\n");
    }
    else
    {

        codeGen_express(stBinop_Op1(t), R_value);
        codeGen_express(stBinop_Op2(t), R_value);
        t->place = newtemp(t->etype);
        if (stBinop_Op1(t) != NULL)
            insert_code(&(t->code), stBinop_Op1(t)->code);
        if (stBinop_Op2(t) != NULL)
            insert_code(&(t->code), stBinop_Op2(t)->code);

        t_instr = newinstr(OP, SymtabPtr_operand, SymtabPtr_operand, SymtabPtr_operand);
        t_instr->src1.val.stptr = stBinop_Op1(t)->place;
        t_instr->src2.val.stptr = stBinop_Op2(t)->place;
        t_instr->dest.val.stptr = t->place;
        insert_code(&(t->code), t_instr);
    }
    return;
}

void code_gen_unary(tnode *t, Optype OP, int lr)
{
    instr *t_instr;
    if (lr == L_value)
    {
        printf("Error lvalue called\n");
    }
    else
    {

        codeGen_express(stUnop_Op(t), R_value);
        t->place = newtemp(t->etype);
        if (stUnop_Op(t) != NULL)
            insert_code(&(t->code), stUnop_Op(t)->code);
        t_instr = newinstr(OP, SymtabPtr_operand, NONE, SymtabPtr_operand);
        t_instr->src1.val.stptr = stUnop_Op(t)->place;
        t_instr->dest.val.stptr = t->place;
        insert_code(&(t->code), t_instr);
    }
    return;
}

Operandtype give_operandtype(SyntaxNodeType ntype)
{
    if (ntype == Intcon)
        return Intcon_operand;
    else if (ntype == Stringcon_operand)
        return Stringcon;
    else if (ntype == Charcon)
        return Charcon_operand;
    else
        return SymtabPtr_operand;
}

void Charcon_code_assign(tnode *t)
{
    t->place = newtemp(t_Char);
    t->code = newinstr(Assn_op, Charcon_operand, NONE, SymtabPtr_operand);
    t->code->src1.val.char_const = stCharcon(t);
    t->code->dest.val.stptr = t->place;
}

void Intcon_code_assign(tnode *t)
{
    t->place = newtemp(t_Int);
    //create the instruction, now also assign the values where needed
    t->code = newinstr(Assn_op, Intcon_operand, NONE, SymtabPtr_operand);
    t->code->src1.val.i_const = stIntcon(t);
    t->code->dest.val.stptr = t->place;
}
void string_code_assign(tnode *t)

{
    t->place = newtemp(t_String);
    t->code = newinstr(Assn_op, Stringcon_operand, NONE, Stringcon_operand);
    t->code->src1.val.str_const = stStringcon(t);
    t->code->dest.val.stptr = t->place;
    insert_string(t->place->name, stStringcon(t));
}

void insert_string(char *temp, char *s_name)
{
    if (str_table_head == NULL)
    {
        str_table_head = malloc(sizeof(str_table));
        str_table_head->temp_name = temp;
        str_table_head->str_name = s_name;
        str_table_head->next = NULL;
        return;
    }

    str_table *temp2;
    temp2 = str_table_head;
    while (temp2->next != NULL)
    {
        temp2 = temp2->next;
    }
    temp2->next = malloc(sizeof(str_table));
    temp2->next->temp_name = temp;
    temp2->next->str_name = s_name;
    temp2->next->next = NULL;
    return;
}

void return_inst(tnode *t)
{
    int sc = Global;
    //the leave insturcion
    symtabnode *stptr;
    stptr = SymTabLookup(function_name, sc);
    instr *temp;
    instr *t_instr;
    //Leave
    t_instr = newinstr(Leave_op, NONE, NONE, SymtabPtr_operand);
    t_instr->dest.val.stptr = stptr;
    insert_code(&(t->code), t_instr);
    //Return
    if (stReturn(t) != NULL)
    {
        codeGen_express(stReturn(t), R_value);
        insert_code(&(t->code), stReturn(t)->code);
        t_instr = newinstr(Return_op, NONE, NONE, SymtabPtr_operand);
        t_instr->dest.val.stptr = stReturn(t)->place;
        insert_code(&(t->code), t_instr);
    }
    else
    {
        t_instr = newinstr(Return_op, NONE, NONE, NONE);
        insert_code(&(t->code), t_instr);
    }

    return;
}

int store_Global_Local(symtabnode *stptr, int sc)
{
    //check if it already exist if yes than return other wise add it
    for (int i = 0; i < 256; i++)
    {
        if (SymTab_GL[sc][i] == stptr)
        {
            return i;
        }
    }
    for (int i = 0; i < 256; i++)
    {
        if (SymTab_GL[sc] == NULL)
        {
            SymTab_GL[sc][i] = stptr;
            return i;
        }
    }
}

char *printBinary_op(instr *t)
{

    switch (t->op)
    {
    case Plus_op:
        return ("+");
        break;
    case BinaryMinus_op:
        return ("-");
        break;
    case Mult_op:
        return ("*");
        break;
    case Div_op:
        return ("/");
        break;
    case LogicalNot_op:
        return ("!");
        break;
    case UnaryMinus_op:
        return ("-");
        break;
    case If_Equals_op:
    case Equals_op:
        return ("==");
        break;
    case If_Neq_op:
    case Neq_op:
        return ("!=");
        break;
    case If_Leq_op:
    case Leq_op:
        return ("<=");
        break;
    case If_Lt_op:
    case Lt_op:
        return ("<");
        break;
    case If_Geq_op:
    case Geq_op:
        return (">=");
        break;
    case If_Gt_op:
    case Gt_op:
        return (">");
        break;
    case If_LogicalAnd_op:
    case LogicalAnd_op:
        return ("&&");
        break;
    case If_LogicalOr_op:
    case LogicalOr_op:
        return ("||");
        break;
    }
    return "";
}

void free_malloc_t_code(tnode *t, int n, int depth)
{
}

void print_instruction(instr *in)
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
        printf("If %s %s", in->src1.val.stptr->name, printBinary_op(in));
        printf(" %s goto _tdest%d \n", in->src2.val.stptr->name, in->dest.val.i_const);
        break;
    case Label_op:
        printf("_tdest%d:\n", in->dest.val.i_const);
        break;
    case Goto_op:
        printf("Goto _tdest%d\n", in->dest.val.i_const);
        break;

    case Deref_op:
        printf(" (%s) = Deref(%s)\n", in->dest.val.stptr->name, in->src1.val.stptr->name);
        break;
    case UnaryMinus_op:
    case LogicalNot_op:
        printf("%s = %s %s\n", in->dest.val.stptr->name, printBinary_op(in), in->src1.val.stptr->name);
        break;
    case Plus_op:
    case Div_op:
    case Mult_op:
    case BinaryMinus_op:

        printf("%s = ", in->dest.val.stptr->name);
        if (in->src1.operand_type == idLoc_operand)
            printf("(addr)");
        printf(" %s %s", in->src1.val.stptr->name, printBinary_op(in));
        //   printf("%s\n", in->src2.val.stptr->name);
        if (in->src2.operand_type == SymtabPtr_operand)
            printf("%s\n", in->src2.val.stptr->name);
        else if (in->src2.operand_type == Intcon_operand)
            printf("%d\n", in->src2.val.i_const);
        break;
    case Enter_op:
        printf("enter %s\n", in->dest.val.stptr->name);
        break;
    case Call_op:
        printf("call  %s %d\n", in->src1.val.stptr->name, in->src2.val.i_const);
        break;
    case Param_op:
        printf("param  %s\n", in->src1.val.stptr->name);
        break;
    case Leave_op:
        printf("leave %s\n", in->dest.val.stptr->name);
        break;
    case Return_op:
        printf("return ");
        if (in->dest.operand_type != NONE)
            printf("%s", in->dest.val.stptr->name);
        printf("\n");
        break;
    case Retrieve_op:
        printf("retrieve  %s\n", in->dest.val.stptr->name);
        break;
    case Assn_op:
        find_operand(in->dest);
        printf(" = ");
        find_operand(in->src1);
        printf("\n");
        break;
    default:
        printf("No operation found\n");
    }

    if (in->next != NULL)
        print_instruction(in->next);

    return;
}

void find_operand(Operand t_oprnd)
{
    char str[50];

    switch (t_oprnd.operand_type)
    {
    case Deref_operand:
        printf("Deref %s", t_oprnd.val.stptr->name);
        break;

    case Intcon_operand:
        printf("Intcon(%d)", t_oprnd.val.i_const);
        break;
    case SymtabPtr_operand:
        printf("%s", t_oprnd.val.stptr->name);
        break;
    case Stringcon_operand:
        printf("%s", t_oprnd.val.str_const);
        break;
    case Charcon_operand:
        printf("charcon(%d)", t_oprnd.val.char_const);
        break;
    default:
        printf("None found\n");
    }
    return;
}

void indent(int n)
{
    if (n < 0)
        return;

    while (n-- > 0)
    {
        putc(' ', stdout);
    }
}