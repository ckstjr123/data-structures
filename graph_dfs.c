#include <stdio.h>
#include <stdlib.h>

/* 인접 리스트를 이용한 그래프 표현 */

#define MAX_VERTICES 50 //그래프 정점 최대 개수
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct Graph {
    int n; //그래프에 존재하는 정점 개수
    GraphNode* adj_list[MAX_VERTICES]; //각 정점마다 연결 리스트를 통해 인접 노드를 표현하므로 정점 개수만큼의 포인터 배열 필요(정점 번호를 배열의 인덱스로 하여 각 정점의 인접 리스트에 접근 가능)
} Graph;

void init(Graph* g) {
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

int visited[MAX_VERTICES]; // 노드 방문 여부 기록
#define TRUE 1;
//인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(Graph* g, int v) {

    visited[v] = TRUE; // 해당 노드 방문 처리
    printf("정점 %d -> ", v); // 방문한 노드 출력

    GraphNode* w;
    //인접 노드 탐색
    for (w = g->adj_list[v]; w; w = w->link) {
        if(!visited[w->vertex]) {
            dfs_list(g, w->vertex); //재귀 호출을 통해 정점 w에서 DFS 새로 시작
        }
    }
}

int main() {
    Graph *g;
    g = (Graph*) malloc(sizeof(Graph));
    init(g);
    for (int i = 0; i < 5; i++) {
        insert_vertex(g, i); // 그래프 정점 삽입
    }

    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 3);
    // insert_edge(g, 3, 3); //자체 간선
    
    print_adj_list(g);

    printf("\n깊이 우선 탐색:\n");
    dfs_list(g, 0); //0번 노드부터 깊이 우선 탐색 시작

    free(g);
    return 0;
}