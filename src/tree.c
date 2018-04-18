#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"

/* "Puste" drzewo ma - zgodnie ze specyfikacją - jeden wierzchołek
 * o numerze 0 */
Tree_p makeTree() {
    Tree_p res = malloc(sizeof(struct Tree));

    if (res == NULL) {
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }

    Node_p root = makeNode(0);
    res->lookup[0] = root;

    for (int i = 1; i < MAX_N_OF_NODES; i++) {
        res->lookup[i] = NULL;
    }

    res->size = 1;
    res->current_node_number = 1;

    return res;
}

void freeTree(Tree_p t) {
    for (int i = 0; i < MAX_N_OF_NODES; i++) {
        free(t->lookup[i]);
    }
    free(t);
}

void addNode(Tree_p t, int k) {
    int c = t->current_node_number;
    Node_p new_node = makeNode(c);
    Node_p parent = t->lookup[k];

    // jeżeli <k> nie ma dzieci
    if (parent->leftmost_child == NULL) {
        new_node->parent = parent;
        parent->leftmost_child = new_node;
        parent->rightmost_child = new_node;
    }
    // jeżeli <k> ma co najmniej jednego syna
    else {
        parent->rightmost_child->right_sibling = new_node;
        new_node->left_sibling = parent->rightmost_child;
        parent->rightmost_child = new_node;
        new_node->parent = parent;
    }

    t->lookup[c] = new_node;
    t->current_node_number++;
    t->size++;
}

void deleteNode(Tree_p t, int k) {
    // Node, który chcemy usunąć
    Node_p target = t->lookup[k];

    // jeżeli <k> jest jedynym synem, to pamięta swojego prawdziwego ojca
    if (target->left_sibling == NULL && target->right_sibling == NULL) {
        // jeżeli <k> nie ma dzieci
        if (target->leftmost_child == NULL) {
            target->parent->leftmost_child = NULL;
            target->parent->rightmost_child = NULL;
        }
        // jeżeli <k> ma co najmniej jednego syna
        else {
            target->parent->leftmost_child = target->leftmost_child;
            target->parent->rightmost_child = target->rightmost_child;
            target->leftmost_child->parent = target->parent;
            target->rightmost_child->parent = target->parent;
        }
    }
    // jeżeli <k> jest lewym synem, to pamięta swojego prawdziwego ojca
    else if (target->left_sibling == NULL) {
        // jeżeli <k> nie ma dzieci
        if (target->leftmost_child == NULL) {
            target->parent->leftmost_child = target->right_sibling;
            target->right_sibling->parent = target->parent;
            target->right_sibling->left_sibling = NULL;
        }
        // jeżeli <k> ma co najmniej jedno dziecko
        else {
            target->leftmost_child->left_sibling = NULL;
            target->leftmost_child->parent = target->parent;
            target->parent->leftmost_child = target->leftmost_child;
            target->rightmost_child->right_sibling = target->right_sibling;
            target->right_sibling->left_sibling = target->rightmost_child;
        }
    }
    // jeżeli <k> jest prawym synem to pamięta swojego prawdziwego ojca
    else if (target->right_sibling == NULL) {
        // jeżeli <k> nie ma dzieci
        if (target->leftmost_child == NULL) {
            target->parent->rightmost_child = target->left_sibling;
            target->left_sibling->parent = target->parent;
            target->left_sibling->right_sibling = NULL;
        }
        // jeżeli <k> ma co najmniej jedno dziecko
        else {
            target->rightmost_child->right_sibling = NULL;
            target->rightmost_child->parent = target->parent;
            target->parent->rightmost_child = target->rightmost_child;
            target->leftmost_child->left_sibling = target->left_sibling;
            target->left_sibling->right_sibling = target->leftmost_child;
        }
    }
    /* jeżeli <k> jest środkowym synem, to nie mamy gwarancji, że <k>
     * pamięta swojego prawdziwego ojca - nie musi;
     * wystarczy, że w przypadku gdy <k> jest drugim z prawej synem
     * i usuwamy jego prawego brata, zaktualizujemy jego wskaźnik na ojca;
     * podobnie z lewej strony */
    else {
        // jeżeli <k> nie ma dzieci
        if (target->leftmost_child == NULL && target->rightmost_child == NULL) {
            target->left_sibling->right_sibling = target->right_sibling;
            target->right_sibling->left_sibling = target->left_sibling;
        }
        // jeżeli <k> ma co najmniej jedno dziecko
        else {
            target->leftmost_child->left_sibling = target->left_sibling;
            target->left_sibling->right_sibling = target->leftmost_child;
            target->rightmost_child->right_sibling = target->right_sibling;
            target->right_sibling->left_sibling = target->rightmost_child;
        }
    }

    free(target);
    t->lookup[k] = NULL;
    t->size--;
}

int rightmostChild(Tree_p t, int k) {
    Node_p rmc = t->lookup[k]->rightmost_child;
    return rmc == NULL ? -1 : rmc->value;
}

/* Aby usunąć poddrzewo o korzeniu <k>, usuwamy sukcesywnie wszysktie
 * dzieci <k> za pomocą gotowej funkcji [deleteNode];
 * na końcu usuwamy korzeń */
void deleteSubtree(Tree_p t, int k) {
    Node_p target = t->lookup[k];
    int rmc;

    while (target->rightmost_child != NULL) {
        rmc = target->rightmost_child->value;
        deleteNode(t, rmc);
    }

    deleteNode(t, k);
}

void splitNode(Tree_p t, int k, int w) {
    Node_p target = t->lookup[w];
    Node_p parent = t->lookup[k];

   /* jeżeli <w> jest prawym synem, to splitNode(k, w) jest równoważny
    * dodaniu nowego wierzchołka do <k> */
    if (target->right_sibling == NULL) {
        addNode(t, k);
    }
    else {
        int c = t->current_node_number;
        Node_p new_node = makeNode(c);

        new_node->leftmost_child = target->right_sibling;
        new_node->rightmost_child = parent->rightmost_child;
        new_node->left_sibling = target;
        target->right_sibling = new_node;
        new_node->parent = parent;
        parent->rightmost_child = new_node;

        if (new_node->leftmost_child != NULL) {
            new_node->leftmost_child->parent = new_node;
            new_node->leftmost_child->left_sibling = NULL;
        }
        if (new_node->rightmost_child != NULL) {
            new_node->rightmost_child->parent = new_node;
            new_node->rightmost_child->right_sibling = NULL;
        }

        t->lookup[c] = new_node;
        t->current_node_number++;
        t->size++;
    }
}