#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Node_p makeNode(int value) {
    Node_p res = malloc(sizeof(struct Node));

    if (res == NULL) {
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }

    res->value = value;
    res->parent = NULL;
    res->left_sibling = NULL;
    res->right_sibling = NULL;
    res->leftmost_child = NULL;
    res->rightmost_child = NULL;

    return res;
}