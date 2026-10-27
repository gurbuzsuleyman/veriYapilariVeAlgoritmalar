#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

int findHeight(struct Node* root) {
    if (root == NULL) {
        return -1; 
    }
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

struct Node* search(struct Node* root, int key, int step) {
    if (root == NULL) {
        printf("Adim %d: Dugum bulunamadi.\n", step);
        printf("Cunku yok!\n"); 
        return NULL;
    }
    
    printf("Adim %d: Ziyaret edilen dugum = %d\n", step, root->data); 
    
    if (root->data == key) {
        printf("Hazine bulundu!\n"); 
        return root;
    }
    
    if (key < root->data) {
        return search(root->left, key, step + 1);
    } else {
        return search(root->right, key, step + 1);
    }
}

int main() {
    struct Node* root = NULL;
    int arananSayi;
    
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    int height = findHeight(root);
    printf("Agacin yuksekligi: %d\n\n", height + 1);
    
    printf("Aramak istediginiz sayiyi girin: ");
    scanf("%d", &arananSayi);
    
    printf("\nArama basliyor...\n");
    search(root, arananSayi, 1);
    
    return 0;
}
