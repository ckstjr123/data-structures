#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

//     15
//  4     20
// 1    16  25
TreeNode n6 = {25, NULL, NULL};
TreeNode n5 = {16, NULL, NULL};
TreeNode n4 = {1, NULL, NULL};
TreeNode n3 = {20, &n5, &n6};
TreeNode n2 = {4, &n4, NULL};
TreeNode n1 = {15, &n2, &n3};
TreeNode* root = &n1;


//전위 순회(VLR)
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("[%d] ", root->data); // 노드 방문
        preorder(root->left); // 왼쪽 서브 트리 순회
        preorder(root->right); // 오른쪽 서브 트리 순회
    }
}

//중위 순회(LVR)
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left); // 왼쪽 서브 트리 순회
        printf("[%d] ", root->data); // 노드 방문
        inorder(root->right); // 오른쪽 서브 트리 순회
    }
}

//후위 순회(LRV)
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left); // 왼쪽 서브 트리 순회
        postorder(root->right); // 오른쪽 서브 트리 순회
        printf("[%d] ", root->data); // 노드 방문
    }
}


int main(void) {

    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n");

    return 0;
}