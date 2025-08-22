#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct ll_node {
    int data;
    struct ll_node *next;
};


void add_to_head(struct ll_node **head, int x) {

    struct ll_node *p = (struct ll_node*)malloc(sizeof(struct ll_node));
    // p point to location of new ll_node
    // head point to first ll_node (or null if there is no first ll_node yet)
    p->data = x;
    // data  in ll_node that p point to is set to be x (new added data)
    p->next = *head;    // *head = value that head point to (which in this case should be global head)
    // now next in ll_node point to the same location of head which is old first ll_node (or null if there is no first ll_node yet)
    // making old first ll_node be new second ll_node 
    *head = p;  // *head = value that head point to (which in this case should be global head)
    // update new head which is p where it's pointing to new first ll_node
}

void add_to_tail(struct ll_node **head, int x) {

    struct ll_node *tail = *head;
    if (tail != NULL) { // check if its empty linked list or not
        while (tail->next != NULL) {    // find the last ll_node to add tail
            tail = tail->next;
        }

        struct ll_node *p = (struct ll_node*)malloc(sizeof(struct ll_node));
        tail->next = p;
        p->data = x;
        p->next = NULL;
        
    } else {    // if its empty, just add the new ll_node to head
        add_to_head(head, x);
    }
}

struct ll_node *ptr_to_pos(struct ll_node **head, int pos) {
    int n = 0;
    struct ll_node *p = *head;
    while (n != pos) {
        p = p->next;
        n += 1;
    }
    return p;
}

void add_to_position(struct ll_node **head, int x, int pos){
    if (pos == 0) {
        add_to_head(head, x);
        return;
        }
    int len = 0;
    struct ll_node *counter = *head;
    while (counter->next != NULL) {
        counter = counter->next;
        len += 1;
    }
    if (pos == len+1) {
        add_to_tail(head, x);
        return;
    }
    if (pos > len) {
        printf("out of index \n");
        return;
    }
    if (pos > 0){
        if (pos == len) {
            add_to_tail(head, x);
        } else {
            int n = 0;
            struct ll_node *p = (struct ll_node*)malloc(sizeof(struct ll_node));
            p->data = x;
            struct ll_node *old_pos = ptr_to_pos(head, pos);
            struct ll_node *before = ptr_to_pos(head, pos-1);
            p->next = old_pos;
            before->next = p;
        }

    } else{
        if (pos == -1) {
            add_to_tail(head, x);
        } else {
            printf("under construct ... \n");
        }
    }
}

void remove_from_head(struct ll_node **head) {
    if (*head == NULL) {
        printf("it's already empty \n");
        return;
    }
    if ((*head)->next == NULL) { 
        free(*head); *head = NULL; 
        return; 
    } // handle single ll_node

    struct ll_node *p = *head;
    *head = p->next;
    free(p); // prevent memory leak??

}

void remove_from_tail(struct ll_node **head)    {
    if (*head == NULL) {
        printf("it's already empty \n");
        return;
    }
    if ((*head)->next == NULL) { 
        free(*head); *head = NULL; 
        return; 
    } // handle single ll_node

    struct ll_node *tail = *head;
    int len = 0;
    while (tail->next != NULL) {    // find the last ll_node to add tail
        tail = tail->next;
        len += 1;
    }
    struct ll_node *before = ptr_to_pos(head, len-1);
    before->next = NULL;

    free(tail);
}

void remove_from_position(struct ll_node **head, int pos)   {
    if (*head == NULL) {
        printf("it's already empty \n");
        return;
    }
    if ((*head)->next == NULL) { 
        free(*head); *head = NULL; 
        return; 
    } // handle single ll_node

    if (pos == 0) {
        remove_from_head(head);
        return;
    }

    if (pos > 0){
        int len = 0;
        struct ll_node *counter = *head;
        while (counter->next != NULL) {
            counter = counter->next;
            len += 1;
        }
        if (pos > len) {
            printf("out of index \n");
            return;
        }
        if (pos == len) {
            remove_from_tail(head);
        } else {
            int n = 0;
            struct ll_node *p = ptr_to_pos(head, pos);
            struct ll_node *after = ptr_to_pos(head, pos+1);
            struct ll_node *before = ptr_to_pos(head, pos-1);
            before->next = after;
            free(p);
        }

    } else {
        if (pos == -1) {
            remove_from_head(head);
        } else {
            printf("under construct ... \n");
        }
    }
}

void print_list(struct ll_node *head) {
    struct ll_node *p = head;
    printf("[");
    while (p != NULL) {
        printf("%d", p->data);
        p = p->next;
        if (p != NULL) printf(" -> ");
    }
    printf("]\n");
}

int printer(struct ll_node *head, struct ll_node *extra)
{
    FILE *fp = fopen("img.dot","w");
    if(fp == NULL)
    {
        printf("Error: no permission to create files\n");
        return 1;
    }

    int node_cnt = 0;

    //Graphviz graph start
    fprintf(fp,"digraph LL{\n rankdir=\"LR\";\n");
    fprintf(fp,"node [shape=Mdiamond] head;");
    while(head != NULL)
    {
        // Show node label as its data
        fprintf(fp,"node [shape=\"rect\"] n%d [label=\"%d\"];\n", node_cnt, head->data);
        if(node_cnt == 0)
        {
            fprintf(fp,"head -> n0;\n");
        }
        else
        {   
            fprintf(fp,"n%d -> n%d;\n", node_cnt - 1, node_cnt);
        }
        
        //if we have provided an extra pointer
        if(extra == head)
        {
            fprintf(fp,"node [shape=Mdiamond] p;");
            fprintf(fp,"p -> n%d;", node_cnt);
        }
        node_cnt++;
        head = head->next;
    }
    //Graphviz graph end
    fprintf(fp,"}\n");
    fclose(fp);
    system("dot -Tpng img.dot > img.png");
    system("wezterm imgcat img.png");
    return 0;
}



int main() {
    struct ll_node *list1 = NULL;

    printf("=== Testing add_to_head ===\n");
    add_to_head(&list1, 10);
    printer(list1, NULL); // expected: 10
    add_to_head(&list1, 20);
    printer(list1, NULL); // expected: 20 -> 10
    add_to_head(&list1, 30);
    printer(list1, NULL); // expected: 30 -> 20 -> 10

    printf("\n=== Testing add_to_tail ===\n");
    add_to_tail(&list1, 40);
    printer(list1, NULL); // expected: 30 -> 20 -> 10 -> 40
    add_to_tail(&list1, 50);
    printer(list1, NULL); // expected: 30 -> 20 -> 10 -> 40 -> 50

    printf("\n=== Testing add_to_position ===\n");
    add_to_position(&list1, 99, 0); // head
    printer(list1, NULL); // expected: 99 -> 30 -> 20 -> 10 -> 40 -> 50
    add_to_position(&list1, 77, 3); // middle
    printer(list1, NULL); // expected: 99 -> 30 -> 20 -> 77 -> 10 -> 40 -> 50
    add_to_position(&list1, 88, 7); // tail
    printer(list1, NULL); // expected: 99 -> 30 -> 20 -> 77 -> 10 -> 40 -> 50 -> 88
    add_to_position(&list1, 123, 20); // invalid
    printer(list1, NULL); // unchanged

    printf("\n=== Testing remove_from_head ===\n");
    remove_from_head(&list1);
    printer(list1, NULL); // head removed
    remove_from_head(&list1);
    printer(list1, NULL);

    printf("\n=== Testing remove_from_tail ===\n");
    remove_from_tail(&list1);
    printer(list1, NULL);
    remove_from_tail(&list1);
    printer(list1, NULL);

    printf("\n=== Testing remove_from_position ===\n");
    add_to_tail(&list1, 11);
    add_to_tail(&list1, 22);
    add_to_tail(&list1, 33);
    add_to_tail(&list1, 44);
    printer(list1, NULL); // expected: 20 -> 77 -> 10 -> 11 -> 22 -> 33 -> 44
    remove_from_position(&list1, 0); // remove head
    printer(list1, NULL);
    remove_from_position(&list1, 2); // remove middle
    printer(list1, NULL);
    remove_from_position(&list1, 10); // invalid
    printer(list1, NULL);

    printf("\n=== Testing empty list edge cases ===\n");
    struct ll_node *emptyList = NULL;
    remove_from_head(&emptyList);
    remove_from_tail(&emptyList);
    remove_from_position(&emptyList, 0);
    printer(emptyList, NULL);

    return 0;
}
