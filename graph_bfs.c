#include <stdio.h>
#include <stdlib.h>

/* 큐 */
#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화
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


/* 인접 리스트를 이용한 그래프 표현 */
#define MAX_VERTICES 50 //그래프 정점 최대 개수
#define TRUE 1
#define FALSE 0
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct Graph {
    int n; //그래프에 존재하는 정점 개수
    GraphNode* adj_list[MAX_VERTICES]; //각 정점마다 연결 리스트를 통해 인접 노드를 표현하므로 정점 개수만큼의 포인터 배열 필요(정점 번호를 배열의 인덱스로 하여 각 정점의 인접 리스트에 접근 가능)
} Graph;

void init_graph(Graph* g) {
    g->n = 0;
    int v;
    for (v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

//정점(노드) 삽입
void insert_vertex(Graph* g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {  
        fprintf(stderr, "그래프 정점 최대 개수 제한 초과");
        return;
    }
    
    g->n++;
}

//간선(edge) 삽입(정점 u의 인접 리스트에 간선을 나타내는 노드 삽입)
void insert_edge(Graph* g, int u, int v) {
    if ((u >= g->n) || (v >= g->n)) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }

    GraphNode* node = (GraphNode*) malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u]; // 삽입을 쉽게 하기 위해 인접 리스트 맨 처음에 삽입
    g->adj_list[u] = node; // 간선 연결
}

//그래프 각 노드의 인접 노드 출력
void print_adj_list(Graph* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("정점 %d의 인접 리스트 ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link; //그다음 인접 노드
        }
        printf("\n");
    }
}

int visited[MAX_VERTICES]; //노드 방문 여부 기록
//그래프 너비 우선 탐색(거리가 0인 시작 노드를 방문하고, 거리가 1인 인접 노드, 거리가 2인 노드 등의 순서로 정점들을 방문)
void bfs_list(Graph* g, int v) {
    Queue q;
    init_queue(&q);

    visited[v] = TRUE;
    printf("%d 방문 -> ", v);
    enqueue(&q, v); //탐색 시작 정점(노드)을 먼저 큐에 삽입
    GraphNode* w;
    while (!is_empty(&q)) {
        v = dequeue(&q); //큐에서 정점을 꺼냄
        //v의 인접 노드 탐색 및 방문
        for (w = g->adj_list[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = TRUE; // 미방문 인접 노드 방문 처리
                printf("%d 방문 -> ", w->vertex);
                enqueue(&q, w->vertex); // 해당 정점을 큐에 삽입 
            }
        }
    }
}


int main() {
    Graph* g;
    g = (Graph*) malloc(sizeof(Graph));
    init_graph(g);
    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i); // 정점(노드) 삽입
    }

    insert_edge(g, 0, 4);
    insert_edge(g, 4, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 4, 5);
    insert_edge(g, 5, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 5, 1);
        
    print_adj_list(g);
    printf("\n너비 우선 탐색:\n");
    bfs_list(g, 0); //0번 노드부터 탐색 시작

    free(g);
    return 0;
}