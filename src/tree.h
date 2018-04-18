#pragma once

#include "node.h"
#define MAX_N_OF_NODES 500000

struct Tree {
    /* Node'y tworzące drzewo trzymamy w tablicy, 
	 * by mieć do nich stały dostęp */
    Node_p lookup[MAX_N_OF_NODES];
    int size;
    int current_node_number; // <numer ostatnio dodanego wierzchołka> + 1
};

typedef struct Tree* Tree_p;

Tree_p makeTree();

void freeTree(Tree_p t);

void addNode(Tree_p t, int k);

void deleteNode(Tree_p t, int k);

int rightmostChild(Tree_p t, int k);

void deleteSubtree(Tree_p t, int k);

void splitNode(Tree_p t, int k, int w);