#define OFF 0
#define ON 1
#include <stdio.h>

struct state_machine
{
    int state;
    void (*function)(struct state_machine *sm, int event);
};

void input_event(struct state_machine *sm, int e)
{
    switch (sm->state)
    {
        case OFF: if(e == 1) sm->state = ON; break;
        case ON: if(e == 0) sm->state = OFF; break;
    }
}

int main()
{
    struct state_machine sm1;
    sm1.state = OFF;
    sm1.function = input_event;

    foo(&sm1);

    printf("Initial State: %d\n", sm1.state);
    sm1.function(&sm1, 1); // Turn ON
    printf("State: %d\n", sm1.state);
    sm1.function(&sm1, 0); // Turn OFF
    printf("State: %d\n", sm1.state);
    sm1.function(&sm1, 1); // Turn ON
    printf("State: %d\n", sm1.state);
    sm1.function(&sm1, 1); // Turn ON
    printf("State: %d\n", sm1.state);

    return 0;
}
