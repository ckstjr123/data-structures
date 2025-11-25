// 최댓값 우선순위 큐(Max Heap)

#include<stdio.h>
#include<stdlib.h>

#define MAX_ELEMENT 200
typedef struct {
    int key; //노드 키 값
} element;


typedef struct {
    element heap[MAX_ELEMENT]; // 힙은 '완전 이진트리'로서 배열로 구현할 수 있음
    int heap_size; //노드 개수
} Heap;

//힙 생성
Heap* create_heap() {
    return (Heap*) malloc(sizeof(Heap));
}

//힙 초기화
void init(Heap* h) {
    h->heap_size = 0;
}

//현재 노드의 개수가 heap_size만큼인 힙 h에 item 삽입
void insert_max_heap(Heap* h, element item) {
    int i = ++(h->heap_size); // 배열 1번 인덱스부터 삽입됨


    //트리를 거슬러 올라가면서 부모 노드와 키 값 비교, 부모 노드 키 값보다 크면 부모 노드를 끌어내림
    while ((i > 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2]; // 부모 노드 인덱스 = (자식 노드 인덱스) / 2
        i /= 2;
    }

    h->heap[i] = item; // 적합한 위치에 노드 삽입됨
}

// 최대 힙에서 최댓값 노드(루트 노드) 삭제 후 재구성
element delete_max_heap(Heap* h) {
    int parent, child;
    element max, temp;

    max = h->heap[1]; // 최대 힙이므로 최상위 노드인 루트 노드가 최댓값

    temp = h->heap[(h->heap_size)--]; // 완전 이진트리 마지막 노드를 이용해서 최대 힙의 성질을 만족하도록 재구성
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        //현재 노드의 자식 노드 중 더 큰 자식 노드를 찾음
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            // 오른쪽 자식 노드가 더 크면
            child++;
        }

        if (temp.key >= h->heap[child].key) {
            break;
        }

        h->heap[parent] = h->heap[child];
        //한단계 아래(하위 레벨)로 이동
        parent = child;
        child *= 2; //왼쪽 자식 노드 인덱스로 설정(왼쪽 자식 노드 인덱스 = (부모 인덱스 * 2), 오른쪽 자식 노드 인덱스 = (부모 인덱스 * 2 + 1))
    }
         
    h->heap[parent] = temp;
    return max;
}


int main(void) {
    Heap* heap;
    heap = create_heap(); // 힙 생성
    init(heap);

    //삽입
    element e1 = {10}, e2 = {5} , e3 = {30}; // 노드 키 값 세팅
    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    
    //삭제
    element e4, e5, e6;
    e4 = delete_max_heap(heap);
    printf("< %d > ", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %d > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d > ", e6.key);

    free(heap);
    return 0;
}