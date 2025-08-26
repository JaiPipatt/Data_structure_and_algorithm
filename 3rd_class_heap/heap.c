#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 15

// int list[LENGTH] = {9,5,1,8,0,2,4,3,7,6};
int list[LENGTH] = {1,4,8,4,5,9,21,12,5,3,2,642,43,3,0};

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heaping(int i, int* arr, int length) {
    int parent = (i-1)/2;
    if (arr[i]<=arr[parent]) {
        return;
    }
    swap(&arr[i], &arr[parent]);
    heaping(parent, arr, length);
}

int* heapify(int* arr, int length) {
    for (int i=0; i<length; i++) {
        heaping(i, arr, length);
    }
    return arr;
}

int* heapsort(int* arr, int length) {
    int* heaped = heapify(arr, length);
    int* ans = malloc(length * sizeof(int));
    for (int l=length; l>1; l--) {
        swap(&arr[0], &arr[length-1]);
        ans[l-1]=arr[length-1];
        arr[length-1]=0;
        heaped = heapify(arr, length);
    }
    ans[0] = arr[0];
    return ans;

}

static void print_heap_tree(const int* arr, int n) {
    int level = 0;
    int i = 0;
    int nodes_in_level = 1;
    while (i < n) {
        printf("Level %d: ", level);
        for (int j = 0; j < nodes_in_level && i < n; j++, i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        level++;
        nodes_in_level <<= 1; // next level has twice the nodes
    }
}

int main(void) {
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int* sorted = heapsort(list, LENGTH);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    return 0;
}

// void heapsort(){

// }
