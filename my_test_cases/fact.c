extern void print_int(int x);
extern void print_string(char str[]);
int b(int n);
/**use n as global***/
int n;
int main(void)
{
//all the varaibles in this case will be assigned variables 
    int c, fact;
    fact = 1;
    n = 6;
    /**using for loop**/
    for (c = 1; c <= n; c = c + 1)
        fact = fact * c;

    print_int(fact);

    /*using function*/
    /*Store the globals when you make the function calls */
    fact = b(n);

    print_int(fact);
    /***While loop***/
    fact = 1;
    c = 1;
    while (c <= n)
    {
        fact = fact * c;
        c = c + 1;
    }
    print_int(fact);
    return 0;
}
//store the registers that are going to be used on the stack and get them back when done with return*/
int b(int n)
{
    if (n == 0)
        return 1;
    else
        return (n * b(n - 1));
}