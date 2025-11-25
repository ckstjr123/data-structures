#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

//스택을 이용한 트리 순회(스택에 자식 노드들을 저장하고 꺼내면서 순회, 재귀 호출과 유사)
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];


void push(TreeNode *p) {
    if (top < SIZE - 1) {
        stack[++top] = p;
    }
}

TreeNode* pop() {
    TreeNode* p = NULL;
    if (top >= 0) {
        p = stack[top--];
    }
    
    return p;
}


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

//중위 순회(LVR)
void inorder_iter(TreeNode* root) {
    while (1) {
        for (; root; root = root->left) {
            push(root);
        }
        
        root = pop();
        if (!root) {
            break;
        }
        printf("[%d] ", root->data);
        
        root = root->right;
    }

}

int main(void) {
    printf("중위 순회: ");
    inorder_iter(root);
    printf("\n");

    return 0;
}