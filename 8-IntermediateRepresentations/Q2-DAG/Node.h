#ifndef NODE_H_HEADER_
#define NODE_H_HEADER_
typedef struct node
{
    int isOp;
    char type;
    int id;
    char expression[100];
    struct node *left;
    struct node *right;
} node;

node *createNode(int id, int isOp, char type, char expression[100], node *left, node *right)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->id = id;
    newnode->isOp = isOp;
    newnode->type = type;
    strcpy(newnode->expression, expression);
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

// ...
#endif