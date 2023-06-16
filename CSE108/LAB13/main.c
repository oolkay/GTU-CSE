#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
}Node;

typedef struct BST
{
    struct node *root;
}BST;

int count_leaf(Node *node)
{
    if (node == NULL)
        return (0);
    if (node->left == NULL && node->right == NULL)
        return (1);
    else
        return (count_leaf(node->left) + count_leaf(node->right));
}

int countLeafNodes(BST *bst)
{
    return(count_leaf(bst->root));
}

Node *searchNode(BST *bst, int value)
{
	Node *temp = NULL;
	temp = bst->root;
	while (temp != NULL){
		if (value == temp->value)
			return temp;
		else if (value < temp->value)
			temp = temp->left;
		else if (value > temp->value)
			temp = temp->right;
	}
	return NULL;
}

int count_nodes(Node *node)
{
    if (node == NULL)
        return (0);
    return (count_nodes(node->left) + count_nodes(node->right) + 1);
}

int countNodes(BST *bst)
{
    return(count_nodes(bst->root));
}

int getDepth(Node *node)
{
    if (node == NULL)
        return (0);
    int left = getDepth(node->left);
    int right = getDepth(node->right);
    if (left > right)
        return (left + 1);
    else
        return (right + 1);
}

int getMaxDepth(BST *bst)
{
    return(getDepth(bst->root));
}

void printTree(Node *bst)
{
    if (bst == NULL)
        return ;
    printTree(bst->right);
    printf("%d ",bst->value);
    printTree(bst->left);
}

void addNode(BST *bst, int data)
{
    if (bst == NULL)
    {
        BST *new = (BST *)malloc(sizeof(bst));
        new->root->value = data;
        new->root->left = NULL;
        new->root->right = NULL;
        bst = new;
    }
    Node *temp = bst->root;
    while (1)
        {
            if (data < temp->value)
            {
                if (temp->left == NULL)
                {
                    temp->left = (Node *)malloc(sizeof(Node));
                    temp->left->value = data;
                    temp->left->left = NULL;
                    temp->left->right = NULL;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = (Node *)malloc(sizeof(Node));
                    temp->right->value = data;
                    temp->right->left = NULL;
                    temp->right->right = NULL;
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }

}

Node *traversal_add(Node *srcnode, Node *dstnode)
{
    BST *bst = (BST *)malloc(sizeof(BST));
    bst->root = dstnode;
    if (srcnode == NULL)
        return NULL;
    addNode(bst, srcnode->value);
    traversal_add(srcnode->right, dstnode);
    traversal_add(srcnode->left, dstnode);
    return (dstnode);
}

Node *delete_element(Node *node, int data)
{
    if (node == NULL)
        return (NULL);
    if (data == node->value)
    {
        //child yoksa
        if (node->right == NULL && node->left == NULL)
        {
            free(node);
            return (NULL);
        }
        //2 tane child varsa
        else if (node->right != NULL && node->left != NULL)
        {
            Node *tmp = node->left;
            Node *tmp2 = node;
            node = node->right;
            node = traversal_add(tmp, node);
            free(tmp);
            free(tmp2);
        }
        //1 tane child varsa (solda)
        else if (node->left != NULL && node->right == NULL)
        {
            Node *tmp = node;
            node = node->left;
            free(tmp);
        }
        //1 tane child varsa (sağda)
        else
        {
            Node *tmp = node;
            node = node->right;
            free(tmp);
        }
    }
    else if (data > node->value)
        node->right = delete_element(node->right, data);
    else
        node->left = delete_element(node->left, data);
    return (node);
}

void *removeNode(BST *bst, int data)
{
    bst->root = delete_element(bst->root, data);
}

//read from file and generate bst
struct BST *generateBST(const char *filename)
{
    struct BST *bst = (struct BST *)malloc(sizeof(struct BST));
    int value;

    bst->root = NULL;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &value);
    
    bst->root = (Node *)malloc(sizeof(Node));
    bst->root->value = value;
    bst->root->left = NULL;
    bst->root->right = NULL;
    while (fscanf(fp, "%d", &value) > 0)
    {
        Node *temp = bst->root;
        while (1)
        {
            if (value < temp->value)
            {
                if (temp->left == NULL)
                {
                    temp->left = (Node *)malloc(sizeof(Node));
                    temp->left->value = value;
                    temp->left->left = NULL;
                    temp->left->right = NULL;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = (Node *)malloc(sizeof(Node));
                    temp->right->value = value;
                    temp->right->left = NULL;
                    temp->right->right = NULL;
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
    fclose(fp);
    return bst;
}

void free_tree(Node *root)
{
	if (root != NULL)
    {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main()
{

    BST *bst = generateBST("input.txt");
    int i = 1;
    while (i <= 7 && i >= 1)
    {
        printf("1. Add a node\n");
        printf("2. Delete a node\n");
        printf("3. Search a node\n");
        printf("4. Count nodes\n");
        printf("5. Get max depth\n");
        printf("6. Count leaf nodes\n");
        printf("7. Print tree\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &i);
        printf("\n");
        switch (i)
        {
            case 1:
                printf("Enter the value to be added: ");
                int value;
                scanf("%d", &value);
                addNode(bst, value);
                break;
            case 2:
                printf("Enter the value to be deleted: ");
                int value2;
                scanf("%d", &value2);
                removeNode(bst, value2);
                break;
            case 3:
                printf("Enter the value to be searched: ");
                int value3;
                scanf("%d", &value3);
                if (searchNode(bst, value3) != NULL)
                    printf("Found\n\n");
                else
                    printf("Not found\n\n");
                break;
            case 4:
                printf("Number of nodes: %d\n\n", countNodes(bst));
                break;
            case 5:
                printf("Max depth: %d\n\n", getMaxDepth(bst));
                break;
            case 6:
                printf("Number of leaf nodes: %d\n\n", countLeafNodes(bst));
                break;
            case 7:
                printTree(bst->root);
                printf("\n\n");
                break;
        }
    }
    free_tree(bst->root);
    free(bst);
    return (0);
}