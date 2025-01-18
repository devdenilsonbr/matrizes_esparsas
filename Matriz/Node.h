#ifndef NODE_H
#define NODE_H

struct Node {
    Node *right;
    Node *down;
    int row;
    int colum;
    double value;

    Node() {};
};

#endif
