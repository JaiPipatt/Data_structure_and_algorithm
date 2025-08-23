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
    if(root==NULL) {
        return NULL;
    }
    if(root->data == value) {
        return root;
    }
    struct btree_node *found_l = root->left;
    struct btree_node *found_r = root->right;
    if (found_l->data == value) {
        return found_l;
    }
    else if (found_r->data == value) {
        return found_r;
    }
    else {
        found_l = bfs(found_l, value);
        found_r = bfs(found_r, value);
    }
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

int main() {
    struct btree_node *root = malloc(sizeof(struct btree_node));
    root->data = 1;
    root->left = malloc(sizeof(struct btree_node));
    root->left->data = 2;
    root->right = malloc(sizeof(struct btree_node));
    root->right->data = 3;

    // Initialize missing pointers
    root->parent = NULL;
    root->left->left = root->left->right = NULL;
    root->left->parent = root;
    root->right->left = root->right->right = NULL;
    root->right->parent = root;

    print_btree(root);

    struct btree_node *root2 = malloc(sizeof(struct btree_node));
    root2->data = 1;
    root2->left = malloc(sizeof(struct btree_node));
    root2->left->data = 2;
    root2->right = malloc(sizeof(struct btree_node));
    root2->right->data = 3;

    // Initialize missing pointers
    root2->parent = NULL;
    root2->left->left = root2->left->right = NULL;
    root2->left->parent = root2;
    root2->right->left = root2->right->right = NULL;
    root2->right->parent = root2;

    print_btree(root2);

    struct btree_node *merged = merge_btree(root, root2, 0);
    print_btree(merged);
    struct btree_node *merged2 = merge_btree(merged, merged, 0);
    print_btree(merged2);
    return 0;
}