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

struct btree_node *dfs(struct btree_node *root, int value) {
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

int main() {

}