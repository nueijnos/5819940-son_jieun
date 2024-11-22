#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

//비교 횟수, 이동 횟수를 저장하는 전역 변수
int comparisonCount = 0;
int moveCount = 0;

void generateRandomNumbers(int array[]) { //랜덤 데이터 생성 함수
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void print_list(int array[]) { //정렬 데이터 출력 함수
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void print_gap_list(int array[]) { //정렬 데이터를 20개만 출력하는 함수
    for (int i = 0; i < 20; i++)
        printf("%d ", array[i]);
    printf("...\n"); //생략 문구
}

int inc_insertion_sort(int list[], int first, int last, int gap) { //gap만큼 떨어진 데이터를 삽입 정렬로 구현하는 함수
    int i, j, temp;

    for (i = first + gap; i <= last; i += gap) { //gap 간격으로 삽입 정렬
        temp = list[i]; //현재 값을 temp에 넣고
        moveCount++; //그 값을 넣는 이동 횟수 증가

        for (j = i - gap; j >= first; j -= gap) { //temp의 위치를 찾기 위해 비교
            comparisonCount++;  //비교 횟수 증가

            if (list[j] > temp) { //현재 값이 더 크면 값을 이동하고
                list[j + gap] = list[j];
                moveCount++; //이동 횟수 증가
            }
            else
                break;
            
        }
        list[j + gap] = temp; //temp값을 올바른 위치에 삽입
        moveCount++; //이동 횟수 증가
    }
}

void doShellSort(int array[], int gapType, int* avgComparison, int* avgMove) { //쉘 정렬 수행 함수
    int i, gap;
    comparisonCount = 0;
    moveCount = 0;

    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = array[i]; //원본 배열을 tempArray에 복사
    }

    //gapType에 따라 쉘 정렬 수행
    if (gapType == 2) {
        for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
            printf("Sorting with gap = %d\n", gap);
            print_gap_list(tempArray); //현재 배열 상태 출력
            printf("\n");

            for (i = 0; i < gap; i++) {
                inc_insertion_sort(tempArray, i, ARRAY_SIZE - 1, gap); //호출 시 배열 정렬을 한 뒤 비교 횟수, 이동 횟수 업데이트
            }
        }
    }
    else if (gapType == 3) {
        for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
            printf("Sorting with gap = %d\n", gap);
            print_gap_list(tempArray); //현재 배열 상태 출력
            printf("\n");

            for (i = 0; i < gap; i++) {
                inc_insertion_sort(tempArray, i, ARRAY_SIZE - 1, gap); //호출 시 배열 정렬을 한 뒤 비교 횟수, 이동 횟수 업데이트
            }
        }
    }
    else 
        return;

    //평균 비교 횟수, 평균 이동 횟수 저장
    *avgComparison = comparisonCount;
    *avgMove = moveCount;

    printf("Sorting shellArray (gap = %d):\n", gapType);
    print_list(tempArray); //최종 정렬된 배열 출력
    printf("\n");
}

void doInsertionSort(int array[], int* avgComparison, int* avgMove) { //삽입 정렬 함수
    int i, j, key;
    comparisonCount = 0;
    moveCount = 0;

    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        tempArray[i] = array[i]; //원본 배열을 tempArray에 복사
    }

    for (i = 1; i < ARRAY_SIZE; i++) { //삽입 정렬 수행
        key = tempArray[i];
        j = i - 1;

        while (j >= 0 && tempArray[j] > key) { //key 위치를 찾기 위해 비교
            tempArray[j + 1] = tempArray[j];
            j--;
            comparisonCount++;
            moveCount++;
        }
        tempArray[j + 1] = key; //temp값을 올바른 위치에 삽입
        moveCount++;
    }
    
    //평균 비교 횟수, 평균 이동 횟수 저장
    *avgComparison = comparisonCount;
    *avgMove = moveCount;

    printf("Sorted Insertion Array:\n");
    print_list(tempArray); //최종 정렬된 배열 출력
    printf("\n");
}

int main() {
    srand((unsigned int)time(NULL));
    int array[ARRAY_SIZE];
    int comparisonCount = 0, moveCount = 0;

    generateRandomNumbers(array);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort - 보너스
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
