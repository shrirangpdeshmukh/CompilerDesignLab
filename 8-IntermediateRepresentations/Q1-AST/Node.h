#ifndef NODE_H_HEADER_
#define NODE_H_HEADER_
typedef struct node
{
    int isOp;
    int value;
    struct node *left;
    struct node *right;
} node;

node *createNode(int isOp, int value, node *left, node *right)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->isOp = isOp;
    newnode->value = value;
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

void traversalUtil(node *x)
{
    if (x->isOp)
    {
        switch (x->value)
        {
        case 0:
            printf("+ ");
            break;
        case 1:
            printf("- ");
            break;
        case 2:
            printf("* ");
            break;
        case 3:
            printf("/ ");
            break;
        case 4:
            printf("%% ");
            break;
        default:
            printf("Invalid Character");
            break;
        }
    }
    else
    {
        printf("%d ", x->value);
    }
}

void preorder(node *x)
{

    if (x == NULL)
    {
        return;
    }
    traversalUtil(x);
    preorder(x->left);
    preorder(x->right);
}

void inorder(node *x)
{

    if (x == NULL)
    {
        return;
    }
    inorder(x->left);
    traversalUtil(x);
    inorder(x->right);
}

// ...
#endif