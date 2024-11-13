#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct node {
    struct node *left;
    struct node *right;
    int data;
};

// Function Prototypes
struct node* newNode(int value);
struct node* insert(struct node* root, int value);
void inorderTraversal(struct node* root);
void preorderTraversal(struct node* root);
void postorderTraversal(struct node* root);
struct node* search(struct node* root, int key);
struct node* deleteNode(struct node* root, int key);
struct node* minValueNode(struct node* node);

// Initialize root as a global pointer
struct node *root = NULL;

int main() {
    int opt;
    int value, searchv, key;
    do {
        printf("\n1) Create Root Node \n2) Insert Node\n3) Search\n4) Inorder Traversal\n5) Preorder Traversal\n6) Postorder Traversal\n7) Delete\n8) Quit\nChoose Option: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                if (root != NULL) {
                    printf("Root already exists.\n");
                } else {
                    printf("Enter a number: ");
                    scanf("%d", &value);
                    root = newNode(value);
                    if (root == NULL) {
                        printf("Failed to create root node\n");
                    }
                }
                break;
            case 2:
                printf("Enter a number: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 3:
                printf("Enter a number: ");
                scanf("%d", &searchv);
                search(root, searchv);
                break;
            case 4:
                printf("\nInorder Traversal:\n");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("\nPreorder Traversal:\n");
                preorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("\nPostorder Traversal:\n");
                postorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("Enter a number to be deleted: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (opt != 8);
    return 0;
}
struct node* newNode(int value) {
    struct node *newnode = malloc(sizeof(struct node));
    if (!newnode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return newNode(value);
    }
    if (value == root->data) {
        printf("Same data can't be stored\n");
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        root->left = insert(root->left, value);
    }
    return root;
}

void inorderTraversal(struct node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d -> ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(struct node* root) {
    if (root == NULL) return;
    printf("%d -> ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d -> ", root->data);
}

struct node* search(struct node* root, int key) {
    if (root == NULL) {
        printf("\nNot FOUND!\n");
        return NULL;
    }
    if (root->data == key) {
        printf("\nFOUND!\n");
        return root;
    }
    if (key > root->data) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
