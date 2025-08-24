#include<stdio.h>
#include<stdlib.h>

struct btree_node {
    //any data you want
    int data;
    //end of data
    struct btree_node *left;
    struct btree_node *right;
    struct btree_node *parent;
};

struct ll_node {
    struct btree_node *tree_root;
    struct ll_node *next;
};

struct ll_node *ptr_to_pos(struct ll_node **head, int pos) {
    int n = 0;
    struct ll_node *p = *head;
    while (n != pos) {
        p = p->next;
        n += 1;
    }
    return p;
}


void add_to_head(struct ll_node **head, struct btree_node *root) {
    struct ll_node *p = (struct ll_node*)malloc(sizeof(struct ll_node));
    p->tree_root = root;
    p->next = *head;  
    *head = p; 
}

void remove_from_tail(struct ll_node **head) {
    if (*head == NULL) {
        printf("it's already empty \n");
        return;
    }
    if ((*head)->next == NULL) { 
        free(*head); *head = NULL; 
        return; 
    } 
    struct ll_node *tail = *head;
    int len = 0;
    while (tail->next != NULL) {  
        tail = tail->next;
        len += 1;
    }
    struct ll_node *before = ptr_to_pos(head, len-1);
    before->next = NULL;
    free(tail);
}

int sum_btree (struct btree_node *root) {
    if(root == NULL) {
        return 0;
    }
    return root->data + sum_btree(root->right) + sum_btree(root->left);
}

int num_btree(struct btree_node *root) {
    if(root == NULL) {
        return 0;
    }
    return 1 + num_btree(root->right) + num_btree(root->left);
}

int depth_btree (struct btree_node *root) {
    if (root == NULL) {
        return 0;
    }
    if (depth_btree(root->left)>depth_btree(root->right)) {
        return 1 + depth_btree(root->left);
    } else {
        return 1 + depth_btree(root->right);
    }
}

// A function dfs that return struct btree_node* type (pointer that point to struct btree_node)
struct btree_node* dfs(struct btree_node *root, int value) { 
    if(root==NULL) {
        return NULL;
    }
    if(root->data == value) {
        return root;
    }
    struct btree_node *found_l = dfs(root->left, value);
    if(found_l != NULL) {
        return found_l;
    }
    else {
        return dfs(root->right, value);
    }
}

struct btree_node* bfs(struct btree_node *root, int value) { 

    printf("BFS start: looking for %d\n", value);

    if (root->data == value) {
        printf("Found at root: %d\n", root->data);
        return root;
    }
    struct ll_node *head = NULL;
    add_to_head(&head, root);
    printf("add to head: %d\n", root->data);

    while (head != NULL) {

        struct ll_node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        printf("Visit: %d\n", current->tree_root->data);

        if (current->tree_root->data == value) {
            printf("Match: %d\n", current->tree_root->data);
            return current->tree_root;
        }
        if (current->tree_root->left!=NULL) {
            printf("  add to head left: %d\n", current->tree_root->left->data);
            add_to_head(&head, current->tree_root->left);
        }
        if (current->tree_root->right!=NULL) {
            printf("  add to head right: %d\n", current->tree_root->right->data);
            add_to_head(&head, current->tree_root->right);
        }

        printf("remove from tail: %d\n", current->tree_root->data);
        remove_from_tail(&head);
    
    }
    printf("not found \n");
    return NULL;
}

struct btree_node* merge_btree(struct btree_node *t1, struct btree_node *t2, int new_data) {
    struct btree_node* merged = malloc(sizeof(struct btree_node));
    merged->data = new_data;
    merged->left = t1;
    t1->parent = merged;
    merged->right = t2;
    t2->parent = merged;
    return merged;
}

static void print_btree_impl(struct btree_node *node, int depth) {
    if (node == NULL) {
        printf("%*s(null)\n", depth * 2, "");
        return;
    }
    print_btree_impl(node->left, depth + 1);
    printf("%*s%d\n", depth * 2, "", node->data);
    print_btree_impl(node->right, depth + 1);
}

void print_btree(struct btree_node *root) {
    print_btree_impl(root, 0);
}

// ...existing code...
int main(void) {
    // Asymmetric tree:
    //          10
    //        /     \
    //       5       20
    //      /       /  \
    //     2      15    30
    //    /            /  \
    //   1           25   35
    struct btree_node *n10 = malloc(sizeof(*n10));
    struct btree_node *n5  = malloc(sizeof(*n5));
    struct btree_node *n20 = malloc(sizeof(*n20));
    struct btree_node *n2  = malloc(sizeof(*n2));
    struct btree_node *n1  = malloc(sizeof(*n1));
    struct btree_node *n15 = malloc(sizeof(*n15));
    struct btree_node *n30 = malloc(sizeof(*n30));
    struct btree_node *n25 = malloc(sizeof(*n25));
    struct btree_node *n35 = malloc(sizeof(*n35));

    n10->data=10; n10->left=n10->right=NULL; n10->parent=NULL;
    n5->data=5;   n5->left=n5->right=NULL;   n5->parent=NULL;
    n20->data=20; n20->left=n20->right=NULL; n20->parent=NULL;
    n2->data=2;   n2->left=n2->right=NULL;   n2->parent=NULL;
    n1->data=1;   n1->left=n1->right=NULL;   n1->parent=NULL;
    n15->data=15; n15->left=n15->right=NULL; n15->parent=NULL;
    n30->data=30; n30->left=n30->right=NULL; n30->parent=NULL;
    n25->data=25; n25->left=n25->right=NULL; n25->parent=NULL;
    n35->data=35; n35->left=n35->right=NULL; n35->parent=NULL;

    // Wire up
    n10->left=n5;   n5->parent=n10;
    n10->right=n20; n20->parent=n10;

    n5->left=n2;  n2->parent=n5;
    n2->left=n1;  n1->parent=n2;

    n20->left=n15; n15->parent=n20;
    n20->right=n30; n30->parent=n20;

    n30->left=n25;  n25->parent=n30;
    n30->right=n35; n35->parent=n30;

    struct btree_node *root = n10;

    print_btree(root);

    struct btree_node *found;
    found = bfs(root, 10); if (found) printf("Found: %d\n", found->data);
    found = bfs(root, 1);  if (found) printf("Found: %d\n", found->data);
    found = bfs(root, 25); if (found) printf("Found: %d\n", found->data);
    found = bfs(root, 35); if (found) printf("Found: %d\n", found->data);
    found = bfs(root, 99); if (!found) printf("Not found: 99\n");

    return 0;
}