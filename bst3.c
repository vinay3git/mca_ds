#include <stdio.h>
#include <stdlib.h>

struct node {
        struct node *left, *right;
        int data;
};

struct node *root = NULL;

struct node* newNode(int value) {
        struct node *newnode = malloc(sizeof(struct node));

        newnode->data = value;
        newnode->left = newnode->right = NULL;
        return newnode;
}

struct node* insert(struct node* root, int value) {
        if (root == NULL) {
                return newNode(value);
        }
        else if (value > root->data) {
                root->right = insert(root->right, value);
        }
        else {
                root->left = insert(root->left, value);
        }
        return root;
}

void inorderTraversal(struct node* root) {
    if (root == NULL) return; // Check for NULL pointer
    inorderTraversal(root->left);
    printf("%d -> ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(struct node* root) {
    if (root == NULL) return; // Check for NULL pointer
    printf("%d -> ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
void postorderTraversal(struct node* root) {
    if (root == NULL) return; // Check for NULL pointer
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d -> ", root->data);
}

struct node* search(struct node* root, int key) {
        if (root == NULL) {
                printf("\n number not found\n");
                return NULL;
        }
        if (root->data == key) {
                printf("\n number found in tree!\n");
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
        }
        else if (key > root->data) {
                root->right = deleteNode(root->right, key);
        }
        else if (key == root->data) {
                if (root->left == NULL) {
                        struct node* temp = root->right;
                        free(root);
                        return temp;
                }
                else if (root->right == NULL) {
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

int main() {
        int ch, value, searchv, key;
        do {
                printf("\n1) Insert Node\n2) Search\n3) Inorder Traversal\n4) Preorder Traversal\n5)>
                scanf("%d", &ch);

                switch (ch) {
                case 1: printf("Enter a number: ");
                        scanf("%d", &value);
                        root = insert(root, value);
                        break;
                case 2: printf("Enter a number: ");
                        scanf("%d", &searchv);
                        search(root, searchv);
                        break;
                case 3: printf("Inorder Traversal:\n");
                        inorderTraversal(root);
                        printf("\n");
                        break;
                case 4: printf("Preorder Traversal:\n");
                        preorderTraversal(root);
                        printf("\n");
                        break;
                case 5: printf("Postorder Traversal:\n");
                        postorderTraversal(root);
                        printf("\n");
                        break;
                case 6: printf("Enter number to delete: ");
                        scanf("%d", &key);
                        root = deleteNode(root, key);
                        break;
                case 7: printf("Exitted\n");
                        break;

                default: printf("Invalid option!\n");
                }
        } while (ch != 7);
}


