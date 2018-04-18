#pragma once

struct Node;

typedef struct Node* Node_p;

struct Node {
    int value; // numer wierzchołka
    Node_p parent;
    Node_p left_sibling, right_sibling;
    Node_p leftmost_child, rightmost_child;
};

Node_p makeNode(int value);