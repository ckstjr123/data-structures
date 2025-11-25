#include <stdio.h>
#include <stdlib.h>

// 단순 연결리스트 //

typedef int element;
//연결리스트 노드
typedef struct ListNode {
    element data;
    struct ListNode* link; // 다음 노드를 가리킴
} Node;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

Node* insert_first(Node* head, int value) {
    Node* p = (Node*) malloc(sizeof(Node));
    p->data = value;
    p->link = head; // 헤드 포인터 값을 복사
    head = p; // 헤드 포인터 변경
    return head; // 변경된 헤드 포인터 반환
}

//pre 노드 뒤에 새로운 노드 삽입
Node* insert(Node* head, Node* pre, element value) {
    Node* p = (Node*) malloc(sizeof(Node));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

Node* delete_first(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* removed = head;
    head = removed->link;
    free(removed);
    return head;
}

//pre가 가리키는 노드의 다음 노드를 삭제
Node* delete(Node* head, Node* pre) {
    Node* removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(Node* head) {
    for (Node* p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

int main(void) {
    Node* head = NULL;

    for (int i = 0; i < 5; i++) {
        head = insert_first(head, i); // insert_first()가 반환한 헤드 포인터를 head에 대입
        print_list(head);
    }

    insert(head, head, 100);
    print_list(head);

    delete(head, head);
    print_list(head);

    for (int i = 0; i < 5; i++) {
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}