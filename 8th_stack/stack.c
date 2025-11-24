#include <stdio.h>
#include <stdlib.h>

struct stack_node 
{
    int value;
    struct stack_node* down;
};

struct stack_node* tos = NULL; // topofstack, init NULL

//stack manipulation functions

void stack_push(int x)
{
    struct stack_node *tmp = (struct stack_node *)malloc(sizeof (struct stack_node));
    tmp->value = x;
    tmp->down = tos;
    tos = tmp;
}

int stack_pop(){
    int x = tos->value;
    struct stack_node *tmp = tos;

    if (tos == NULL) {
        printf("Error: trying to pop from empty stack\n");
        return -1;
    }
    tos = tos->down;
    free(tmp);
    return x;
}

//Helper function

// void h_read()
// {
//     int x;
//     scanf("%d", &x);
//     stack_push(x);
// }

// void h_write()
// {
//     int x = stack_pop();
//     printf("%d\n", x);
// }

// void h_add()
// {
//     int a, b;
//     a = stack_pop();
//     b = stack_pop();
//     stack_push(a+b);
// }

// void h_mul()
// {
//     int a, b;
//     a = stack_pop();
//     b = stack_pop();
//     stack_push(a*b);
// }

//test

// int main()
// {
//     h_read();
//     h_read();
//     h_read();
//     h_mul();
//     h_add();
//     h_write();
//     return 0;
// }

#define i_PUSH 0
#define i_ADD 1
#define i_WRITE 2
#define i_END 3
#define i_IF 4
#define i_ELSE 5
#define i_ENDIF 6
#define i_FOR 7
#define i_ENDFOR 8 // break

#define ADD {i_ADD, 0},
#define IF {i_IF, 0},
#define ELSE {i_ELSE, 0},
#define ENDIF {i_ENDIF, 0},
#define PUSH(x) {i_PUSH, (x)},
#define FOR(x) {i_FOR, (x)},
#define ENDFOR {i_ENDFOR, 0},
#define END {i_END, 0}

int code[][2] = 
    {
        PUSH(5)
        PUSH(2)
        ADD
        // PUSH(0)
        IF // top stack, 0 is false, not 0 is true
            PUSH(2)
            ADD
            // {i_WRITE, 0},
        ELSE
            PUSH(10)
            ADD
            // {i_WRITE, 0},
        ENDIF
        {i_WRITE, 0}, // if true, should print 9, else 17
        FOR(10)
            PUSH(1)
            PUSH(2)
            ADD
        ENDFOR
        END
    };

void interpret()
{
    int i = 0;
    int a, b;
    int cond;
    int iterations;
    while (code[i][0] != i_END)
    {
        printf("Executing instruction at %d: %d %d\n", i, code[i][0], code[i][1]);
        switch (code[i][0])
        {
            case i_PUSH:
                stack_push(code[i][1]);
                printf("Pushed %d onto stack\n", code[i][1]);
                break;
            case i_ADD:
                a = stack_pop();
                b = stack_pop();
                stack_push(a + b);
                printf("Added %d and %d, pushed %d\n", a, b, a + b);
                break;
            case i_WRITE:
                printf("%d\n", stack_pop());
                break;
            case i_IF:
                cond = tos->value;
                if (cond == 0) {
                    while (code[i][0] != i_ELSE && code[i][0] != i_ENDIF) {
                        i++;
                    }
                    printf("Condition false, Doing Else block\n");
                } 
                break;
            case i_ELSE:
                while (code[i][0] != i_ENDIF) {
                    i++;
                }
                printf("Skipping ELSE block\n");
                printf("End of IF block\n");
                break;
            case i_ENDIF:
                printf("End of IF block\n");
                break;
            case i_FOR:
                iterations = code[i][1];
                printf("Starting FOR loop with %d iterations\n", iterations);
                break;
            case i_ENDFOR:
                iterations--;
                if (iterations!=0)
                {
                    while (code[i][0] != i_FOR){
                        i--;
                    }
                    printf("Doing iteration %d \n", iterations);
                } else
                {
                    printf("END FOR \n");
                }
                
                break;
            default:
                break;
        }
        i++;
    }
}

int main()
{
    printf("Starting interpretation...\n");
    interpret();
    printf("Interpretation finished.\n");
    return 0;
}

