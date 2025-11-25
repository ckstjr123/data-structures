#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}


void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

// 큐가 비어있는지 확인
int is_empty(Queue* q) {
    return (q->front == q-> rear);
}

// 큐가 꽉 차있는지 확인
int is_full(Queue* q) {
    // 공백, 포화 상태를 구분하기 위해 큐를 항상 하나 비워둠(count 변수를 추가하면 비워두지 않아도 됨)
    return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// 큐 출력
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

// 삽입
void enqueue(Queue* q, element item) {
    if (is_full(q)) {
        error("큐가 포화 상태입니다.");
    }
    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제
element dequeue(Queue* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(Queue* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
    Queue queue;
    int element;

    init_queue(&queue);
    srand(time(NULL));

    for (int i=0; i<100; i++) {
        if (rand() % 5 == 0) { // 5로 나누어 떨어지면
            enqueue(&queue, rand() % 100);
        }
        queue_print(&queue);
        if (rand() % 10 == 0) { // 10으로 나누어 떨어지면
            int data = dequeue(&queue);
        }
        queue_print(&queue);
    }

    return 0;
}