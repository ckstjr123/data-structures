#include <stdio.h>
/* 
  색인 순차 탐색(indexed sequential search)
   - 인덱스 테이블을 사용하여 탐색의 효율을 높이는 방법.
     인덱스 테이블은 주 자료 테이블에서 일정 간격으로 발췌한 데이터들을 갖고 있음.
     인덱스 테이블에서 조건을 만족하는 항목으로부터 주 자료 테이블에서 순차 탐색을 수행함으로써
     주 자료 테이블에서의 탐색 시간을 대폭 줄일 수 있음(이때 주 자료 테이블과 인덱스 테이블은 모두 정렬되어 있어야 함).
*/

int list[9] = {3, 9, 15, 22, 31, 55, 67, 88, 91}; //주 자료 리스트

//기본 순차 탐색
int seq_search(int key, int low, int high) {
    printf("주 자료 리스트 내 순차 탐색 %d ~ %d\n", low, high);
    int i;
    for (i = low; i <= high; i++) {
        if (list[i] == key) {
            return i; // 탐색에 성공하면 키 값 인덱스 반환
        }
    }

    return -1;
}

#define INDEX_SIZE 3  //현재 인덱스 테이블 크기
typedef struct {
    int key; // 인덱스가 가리키는 곳의 키 값
    int index; // 리스트의 인덱스 값
} itable;

itable index_list[INDEX_SIZE];

//탐색이 성공하면 해당 키 값의 인덱스 반환(n은 전체 데이터 수)
int search_index(int key, int n) {
    //키 값이 리스트 범위 내의 값이 아니면 탐색 종료
    if (key < list[0] || key > list[n - 1]) {
        return -1;
    }

    int i, low, high;
    for (i = 0; i < INDEX_SIZE; i++) {
        //인덱스 테이블을 조사하여 해당 키의 구간 결정
        if ((index_list[i].key <= key) && (index_list[i + 1].key > key)) {
            break;
        }
    }

    if (i == INDEX_SIZE) { 
        //인덱스 테이블의 끝이면
        low = index_list[i - 1].index;
        high = n - 1;
    }
    else {
        low = index_list[i].index;
        high = index_list[i + 1].index;
    }


    //예상되는 범위만 순차 탐색
    return seq_search(key, low, high);
}

int main() {
    itable itable_list[3] = {{3, 0}, {22, 3}, {67, 6}}; // {키값, 키가 위치한 인덱스}
    for (int i = 0; i < 3; i++) {
        index_list[i] = itable_list[i];
    }

    int key = 31;
    int key_idx = search_index(key, sizeof(list) / sizeof(int));
    printf("주 자료 리스트 내 해당 키값 %d 위치한 인덱스: %d", key, key_idx);
}