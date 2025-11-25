#include <stdio.h>
#include <stdlib.h>

// 원형 연결 리스트: 마지막 노드가 첫번째 노드를 가리키는 리스트 //

typedef int element;
typedef struct Node {
    element data;
    struct Node* link;
} Node;

Node* insert_first(Node* head, element data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;

    }
    
    return head;
}

Node* insert_last(Node* head, element data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;
        head = node; // head의 위치를 새로운 노드로 바꿔주면 새로운 노드가 마지막 노드가 됨
    } 
    
    return head;
}

void print_list(Node* head) {
    if (head == NULL) {
        return;
    }

    Node* p;
    p = head->link;
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head->link);
}


int main(void) {
    Node* head = NULL;

    // 40->20->30->10
    // head = insert_first(head, 20);
    // head = insert_last(head, 30);
    // head = insert_first(head, 40);
    // head = insert_last(head, 10);

    //10->20->30->40
    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);
    
    print_list(head);
    return 0;
}