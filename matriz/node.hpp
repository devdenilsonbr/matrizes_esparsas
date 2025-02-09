#ifndef NODE_HPP
#define NODE_HPP

struct Node
{
    Node *right;
    Node *down;
    unsigned row;
    unsigned column;
    double value;

    Node(Node *right = nullptr, Node *down = nullptr, int row = 0, int column = 0, double value = 0)
    {
        this->right = right;
        this->down = down;
        this->row = row;
        this->column = column;
        this->value = value;
    }

    ~Node() { }
};

#endif