#include <stdio.h>
/* 
  이진 탐색(binary search)
   - 이진 탐색을 적용하려면 탐색 데이터(배열 등)가 반드시 정렬되어 있어야 하므로
     데이터의 삽입이나 삭제가 빈번한 경우에는 적합하지 않고, 주로 고정된 데이터에 대한 탐색에 적합
*/

int list[15] = {2, 6, 11, 13, 18, 20, 22, 27, 29, 30, 34, 38, 41, 42, 45};

// 반복을 이용한 이진 탐색
int search_binary(int key, int low, int high) {
    int middle;

    while (low <= high) { // 아직 탐색할 수들이 남아 있으면
        middle = (low + high) / 2; // low와 high의 중간값
        printf("탐색 범위 중앙값: %d\n", list[middle]);
        if (key == list[middle]) {
            return middle;
        }
        else if (key > list[middle]) {
            low = middle + 1;
        }
        else {
            high = middle - 1;
        }
    }
    return -1; // 해당 값이 발견되지 않음
}

int main() {
    printf("\n탐색 항목 인덱스: %d", search_binary(45, 0, 15));
}