#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int comparisonCount;
int moveCount;
int totalComparisons = 0;
int totalMoveCount = 0;
int isFirst = 0;
int rounds = 0;

void generateRandomArray(int array[]) { //랜덤 데이터 생성 함수
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; 
    }
}

void printArray(int array[], int n) { //정렬 데이터 출력 함수
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int array[], int left, int right) { //분할 과정을 보여주는 partition 함수
    int pivot, temp; 
    int low, high;

    low = left;
    high = right + 1;
    pivot = array[left];  //피벗을 첫 번째 요소로 설정
    
    do {
        do { //피벗값보다 큰 값을 찾을 때까지 low 증가(비교횟수, 이동횟수도 증가)
            low++;
            comparisonCount++;
            moveCount++;
        } while (low <= high && array[low] < pivot); 

        do { //피벗값보다 큰 값을 찾을 때까지 high 감소(비교횟수, 이동횟수도 증가)
            high--;
            comparisonCount++;
            moveCount++;
        } while (high >= high && array[high] > pivot); 

        if (low < high) { //low와 high의 값을 교환
            SWAP(array[low], array[high], temp);
            comparisonCount++;
            moveCount += 3; 
        }
    } while (low < high);

    SWAP(array[left], array[high], temp); //과정이 끝날 시 피벗값과 high를 교환하여 피벗값을 올바른 위치로 이동
    moveCount += 3;

    return high;
}

/*
void doQuickSort(int array[], int left, int right) { //퀵 정렬 함수(재귀적 방법)
    if (left < right) {
        int q = partition(array, left, right);
        doQuickSort(array, left, q - 1);
        doQuickSort(array, q + 1, right);
    }    
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 40; i < 60; i++)
            printf("%d ", array[i]);
        printf("\n\n");
    }
    rounds++;
    
}
*/

void doQuickSort(int array[], int left, int right) { //퀵 정렬 함수(반복적 방법)
    //스택 초기화
    int stack[SIZE];
    int top = -1;
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) { //스택이 비기 전까지 반복
        right = stack[top--];
        left = stack[top--];

        int p = partition(array, left, right); //분할 과정 후 피벗값의 위치를 반환

        if (p - 1 > left) { //피벗값을 기준으로 왼쪽 부분이 존재한다면 스택에 추가
            stack[++top] = left;
            stack[++top] = p - 1;
        }

        if (p + 1 < right) { //피벗값을 기준으로 오른쪽 부분이 존재한다면 스택에 추가
            stack[++top] = p + 1;
            stack[++top] = right;
        }
        if (rounds % 10 == 0 && isFirst == 0) { 
            for (int i = 40; i < 60; i++) //40~60의 위치에 있는 값을 한번만 출력
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;
    }
}


int main(int argc, char* argv[]) { 
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}


//0 - 999 사이의 랜덤 데이터 100개로 아래 조건을 만족하며 퀵정렬을 수행(반복적 방법)
//1. 정렬하는 과정을 출력(출력결과 참고) 이는 한번만 출력하며, 40~60 의 위치에 있는 값을 출력
//2. 비교 횟수를 출력(20회 평균)
//3. 이동 횟수를 출력(20회 평균)
//=20회 평균은 각 회 새로운 랜덤기반 데이터를 생성
//->이동은 값을temp에 값을 넣거나 temp로부터 값을 가져오는 모든 행위를 포함