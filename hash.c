#include <stdio.h>
#include <stdlib.h>
/* 제산 해시 함수 
   - (h(k) = k mod M)
   - 나머지 연산자(mod)를 사용해서 키(k)를 해시 테이블의 크기(M)로 나눈 나머지를 해시 주소로 사용하는 방법
   - 0 ~ M - 1을 골고루 사용하기 위해 해시 테이블의 크기 M은 주로 소수(prime number)로 정함
*/
// int hash_function(int key) {
//     int hash_index = key % M;
//     if (hash_index < 0) {
//         hash_index += M; //k mod M이 음수라면 여기에 M을 더해서 결과 값이 항상 0 ~ M - 1이 되도록 함
//     }
    
//     return hash_index;
// }

//탐색 키가 문자열
int char_hash_function(char*  key) {
    int g = 31;
    int hash_index = 0;
    while (*key) {
        hash_index = g * hash_index + *key++; //오버플로우가 발생하면 해시코드 값이 음수가 될 수 있으므로 검사 필요
    }

    return hash_index; 
}

/*
  [해시 충돌 해결책]
    - 개방 주소법: 충돌이 일어난 항목을 해시 테이블의 다른 위치에 저장.
    - 체이닝(chaining): 해시 테이블 구조를 각 버킷에 하나 이상의 항목을 저장할 수 있도록 연결 리스트를 할당(해시 주소가 동일한 키만을 하나의 리스트로 묶어둠).
                       버킷 내에서 원하는 항목을 찾을 때는 연결 리스트를 순차 탐색.
                       키 중복을 허용한다면 새로운 항목을 연결 리스트 처음에다 삽입하고, 허용하지 않으면 차례대로 삽입하는 것이 효율적임.

*/
typedef struct {
    int key;
    //key와 관련된 value...
} element;

struct list {
    element item;
    struct list* link;
};

#define TABLE_SIZE 7 // 해시 테이블의 크기(소수)
struct list* hash_table[TABLE_SIZE];

//제산 해시 함수
int hash_function(int key) {
    int hash_index = key % TABLE_SIZE;
    if (hash_index < 0) {
        hash_index += TABLE_SIZE;
    }
    
    return hash_index;
}

//체인법을 이용하여 해시 테이블에 노드 삽입
void hash_chain_add(element item, struct list* ht[]) {

    int hash_value = hash_function(item.key); //해시 값

    struct list* node_before = NULL, *node = ht[hash_value];
    for (; node; node_before = node, node = node->link) {
        if (node->item.key == item.key) {
            fprintf(stderr, "중복 키를 허용하지 않음\n");
            return;
        }
    }

    struct list* ptr = (struct list*) malloc(sizeof(struct list));
    ptr->item = item;
    ptr->link = NULL;

    if (node_before) {
        node_before->link = ptr; // 버킷에 기존 연결 리스트가 있으면 연결 리스트 맨끝에 연결
    }
    else {
        ht[hash_value] = ptr;
    }
}


//체인법을 이용하여 해시 테이블에 저장된 해당 키와 관련된 값 탐색
void hash_chain_search(element item, struct list* ht[]) {

    int hash_value = hash_function(item.key);

    struct list* node;
    for (node = ht[hash_value]; node; node = node->link) {
        if (node->item.key == item.key) {
            printf("key(%d)와(과) 매핑된 value 탐색 성공\n", item.key);
            return;
        }
    }

    printf("탐색 키 %d 및 매핑된 value 존재하지 않음\n", item.key);
}

//해시 테이블 출력
void hash_chain_print(struct list* ht[]) {
    printf("\n=========================================\n");

    struct list* node;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("버킷[%d]->", i);
        for (node = ht[i]; node; node = node->link) {
            printf("%d->", node->item.key);
        }
        printf("\n");
    }

    printf("=========================================\n");
}

#define SIZE 5
int main(void) {
    int data[SIZE] = {8, 1, 9, 6, 13};
    element e;

    for (int i = 0; i < SIZE; i++) {
        e.key = data[i];
        hash_chain_add(e, hash_table);
        hash_chain_print(hash_table);
    }

    for (int i = 0; i < SIZE; i++) {
        e.key = data[i];
        hash_chain_search(e, hash_table);
    }

    return 0;
}

