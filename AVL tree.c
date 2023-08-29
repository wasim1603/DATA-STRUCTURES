#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};
int getHeight(struct Node* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        return root;
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1 && data < root->left->data) {
        return rightRotate(root);
    }
    if (balance < -1 && data > root->right->data) {
        return leftRotate(root);
    }
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node* temp = findMinNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL) {
        return root;
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1 && getHeight(root->left->left) >= getHeight(root->left->right)) {
        return rightRotate(root);
    }
    if (balance < -1 && getHeight(root->right->right) >= getHeight(root->right->left)) {
        return leftRotate(root);
    }
    if (balance > 1 && getHeight(root->left->left) < getHeight(root->left->right)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getHeight(root->right->right) < getHeight(root->right->left)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}
void displaySearchResult(struct Node* result, int key) {
    if (result != NULL) {
        printf("Key element %d found in the AVL tree.\n", key);
    } else {
        printf("Key element %d not found in the AVL tree.\n", key);
    }
}
void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}
int main() {
    struct Node* root = NULL;
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
    printf("In-order traversal of the AVL tree after insertion: ");
    inOrderTraversal(root);
    printf("\n");
    int key1 = 6;
    struct Node* result1 = search(root, key1);
    displaySearchResult(result1, key1);
    int key2 = 8;
    struct Node* result2 = search(root, key2);
    displaySearchResult(result2, key2);
    int keyToDelete = 10;
    root = deleteNode(root, keyToDelete);
    printf("In-order traversal of the AVL tree after deletion: ");
    inOrderTraversal(root);
    printf("\n");
    return 0;
}

