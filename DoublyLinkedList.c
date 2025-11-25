#include <stdio.h>
#include <stdlib.h>
//단순, 원형 연결 리스트는 구조상 선행 노드를 쉽게 찾기 어려움.
//이중 연결 리스트는 하나의 노드가 선행 노드와 후속 노드에 대한 두개의 링크를 가지므로 양방향 탐색 가능

typedef int element;
// 이중 연결 노드 타입
typedef struct Node {
    element data;
    struct Node* prev; // 선행 노드
    struct Node* next; // 후속 노드
} Node;

//이중 연결 리스트 초기화: 헤드 노드의 링크 필드들이 자기 자신을 가리키도록 함
void init(Node* phead) {
    phead->prev = phead;
    phead->next = phead;
}

//이중 연결 리스트 노드 출력
void print_dlist(Node* phead) {
    Node* p;
    for (p = phead->next; p != phead; p = p->next) {
        printf("<-| |%d| |-> ", p->data);
    }
    printf("\n");
}

//before 노드 오른쪽에 새로운 데이터 삽입
void dinsert(Node* before, element data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = before;
    new_node->next = before->next;

    before->next->prev = new_node;
    before->next = new_node;
}

//노드 remove를 삭제
void ddelete(Node* head, Node* removed) {
    if (removed == head) {
        return;
    }
    
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    free(removed);
}

int main(void) {
    // 삽입 및 삭제를 용이하게 하기 위한 '헤드 노드' 추가(헤드 노드의 데이터 필드는 아무런 데이터도 담고 있지 않음)
    Node* head = (Node*) malloc(sizeof(Node));
    init(head);

    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        dinsert(head, i); // 헤드 노드 오른쪽에 삽입
        print_dlist(head);
    }

    printf("\n삭제 단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->next);
    }

    free(head);
    return 0;
}