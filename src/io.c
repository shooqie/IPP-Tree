#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

char ADD_NODE[] = "ADD_NODE";
char RIGHTMOST_CHILD[] = "RIGHTMOST_CHILD";
char DELETE_NODE[] = "DELETE_NODE";
char DELETE_SUBTREE[] = "DELETE_SUBTREE";
char SPLIT_NODE[] = "SPLIT_NODE";
char OK[] = "OK\n";

int strEqual(char A[], char B[]) {
    return strcmp(A, B) == 0;
}

void runIO(bool display_nodes) {
    Tree_p tree = makeTree();
    
    char buf[255];
    int k, w;
    int scan_res;

    for (;;) {
        scan_res = scanf("%s", buf);
        if (scan_res != 1) {
            break;
        }
        if (strEqual(buf, ADD_NODE)) {
            scan_res = scanf("%d", &k);
            if (scan_res != 1) {
                break;
            }
            addNode(tree, k);
            printf("%s", OK);
        }
        else if (strEqual(buf, RIGHTMOST_CHILD)) {
            scan_res = scanf("%d", &k);
            if (scan_res != 1) {
                break;
            }
            printf("%d\n", rightmostChild(tree, k));
        }
        else if (strEqual(buf, DELETE_NODE)) {
            scan_res = scanf("%d", &k);
            if (scan_res != 1) {
                break;
            }
            deleteNode(tree, k);
            printf("%s", OK);
        }
        else if (strEqual(buf, DELETE_SUBTREE)) {
            scan_res = scanf("%d", &k);
            if (scan_res != 1) {
                break;
            }
            deleteSubtree(tree, k);
            printf("%s", OK);
        }
        else if (strEqual(buf, SPLIT_NODE)) {
            scan_res = scanf("%d %d", &k, &w);
            if (scan_res != 2) {
                break;
            }
            splitNode(tree, k, w);
            printf("%s", OK);
        }
        /* przerywamy wczytywanie danych gdy natrafimy na dane
         * niezgodne ze specyfikacją (lub ich brak) */
        else {
            break;
        }
        if (display_nodes) {
            fprintf(stderr, "NODES: %d\n", tree->size);
        }
    }
    freeTree(tree);
}