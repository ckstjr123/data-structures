#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;

// 덱(deque): double-ended queue 줄임말로서 전단(front)과 후단(rear)에서 모두 삽입, 삭제가 가능한 큐 
// 덱의 연산을 한쪽으로만 사용하면 스택으로 동작
// 삽입, 삭제를 각각 한쪽씩 사용하면 큐로 동작
// 원형큐를 확장하여 구현, 추가된 연산: delete_rear(), add_front(), get_rear()
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Deque;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화
void init_deque(Deque* q) {
    q->front = q->rear = 0;
}

// 큐가 비어있는지 확인
int is_empty(Deque* q) {
    return (q->front == q-> rear);
}

// 큐가 꽉 차있는지 확인
int is_full(Deque* q) {
    // 공백, 포화 상태를 구분하기 위해 큐를 항상 하나 비워둠(count 변수를 추가하면 비워두지 않아도 됨)
    return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// 큐 출력
void deque_print(Deque* q) {
    printf("DEQUE(front=%d, rear=%d) = ", q->front, q->rear);
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

// 삽입(enqueue와 동일)
void add_rear(Deque* q, element item) {
    if (is_full(q)) {
        error("큐가 포화 상태입니다.");
    }
    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제(dequeue와 동일)
element delete_front(Deque* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
//peek
element get_front(Deque* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

//-------- 추가된 연산 ---------//

void add_front(Deque* q, element val) {
    if (is_full(q)){
        error("큐가 포화 상태입니다.");
    }

    q->data[q->front] = val;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // 반대 방향으로 회전 필요(ex: [0] -> [4])
}

element delete_rear(Deque* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }
    
    int prev = q->rear;
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // 반대 방향 회전(ex: [4] -> [3])
    return q->data[prev];
}
element get_rear(Deque* q) {
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    return q->data[q->rear];
}



int main(void) {
    
    Deque queue;
    Deque* q = &queue;
    init_deque(&queue);

    for (int i = 0; i < 3; i++) {
        add_front(&queue, i);
        deque_print(&queue);
    }
    printf("%d\n", q->data[0]); // 0
    printf("%d\n", q->data[4]); // 1
    printf("%d\n", q->data[3]); // 2

    for (int i = 0; i < 3; i++) {
        delete_rear(&queue);
        deque_print(&queue);
        printf("q->rear=%d\n", q->rear); // 4 -> 3 -> 2
    }

    return 0;
}