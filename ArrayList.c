#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // 리스트 최대 크기

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size;
} ArrayList;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//리스트 초기화
void init(ArrayList* L) {
    L->size = 0;
}

//리스트가 비어 있으면 1을 반환, 그렇지 않으면 0 반환
int is_empty(ArrayList* L) {
    return L->size == 0;
}

//리스트가 가득 차 있으면 1 반환
int is_full(ArrayList *L) {
    return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayList* L, int pos) {
    if (pos < 0 || pos >= L->size) {
        error("잘못된 pos(위치)입니다.");
    }

    return L->array[pos];
}

//리스트 출력
void print_list(ArrayList* L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d->", L->array[i]);
    }
    printf("\n");
}

//리스트 마지막 item(항목) 삽입
void insert_last(ArrayList *L, element item) {
    if (is_full(L)) {
        error("리스트에 빈 공간이 없습니다.");
    }

    L->array[L->size++] = item;
}

//특정한 위치에 item 삽입
void insert(ArrayList* L, int pos, element item) {
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        for (int i = (L->size - 1); i >= pos; i--) {
            L->array[i + 1] = L->array[i];
        }

        L->array[pos] = item;
        L->size++;
    }
}

//특정한 위치의 item 삭제
element delete(ArrayList* L, int pos) {
    if (pos < 0 || pos >= L->size) {
        error("잘못된 pos(위치)입니다.");
    }

    element item;
    item = L->array[pos];
    for (int i = pos; i < (L->size - 1); i++) {
        L->array[i] = L->array[i + 1]; // 필요시 삭제 후 한칸씩 앞으로 이동
    }

    L->size--;
    return item;
}

int main(void) {

    ArrayList list;
    init(&list);

    insert(&list, 0, 10); print_list(&list); //0번째 위치에 10 추가
    insert(&list, 0, 20); print_list(&list); //0번째 위치에 20 추가
    insert(&list, 0, 30); print_list(&list); //0번째 위치에 30 추가
    insert_last(&list, 40); print_list(&list); //리스트 마지막 항목 40 추가
    delete(&list, 0); print_list(&list); //0번째 항목 삭제

    return 0;
}