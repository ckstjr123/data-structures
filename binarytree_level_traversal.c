#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// ============= 원형 큐 =============== //
#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//초기화
void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

//큐가 비어있는지 확인
int is_empty(Queue* q) {
    return (q->front == q-> rear);
}

//큐가 꽉 차있는지 확인
int is_full(Queue* q) {
    // 공백, 포화 상태를 구분하기 위해 큐를 항상 하나 비워둠(count 변수를 추가하면 비워두지 않아도 됨)
    return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

//큐 출력
void queue_print(Queue* q) {
    printf("QUEUE(front=%d, rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", q->data[i]);
            if (i == q->rear) {
                break;
            }
        } while (i != q->front);
    }
    printf("\n");
}

//삽입
void enqueue(Queue* q, element item) {
    if (is_full(q)) {
        error("큐가 포화 상태입니다.");
    }
    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

//삭제
element dequeue(Queue* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

//레벨 순회
void level_order(TreeNode* ptr) {
    Queue q;
    init_queue(&q);

    if (ptr == NULL) {
        return;
    }

    enqueue(&q, ptr);
    // 먼저 큐에 있는 노드(루트 노드부터)를 꺼내어 방문한 뒤 자식 노드들을 큐에 차례대로 삽입하는 것으로 한번의 반복을 끝냄, 큐가 빌 때까지 해당 작업을 반복.
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf(" [%d] ", ptr->data);
        if (ptr->left) {
            enqueue(&q, ptr->left);
        }
        if (ptr->right) {
            enqueue(&q, ptr->right);
        }
    }
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

int main(void) {
    printf("레벨 순회:");
    level_order(root);
    printf("\n");
    return 0;
}