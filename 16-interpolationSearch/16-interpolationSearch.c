#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount;

void generateRandomArray(int array[]) { //랜덤 데이터 생성 함수
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

void printArray(int* array) { //정렬 데이터 출력 함수
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) //배열의 처음번째~20번째 출력
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) //배열의 뒤에서 20번째~마지막번째 출력
        printf("%4d ", array[i]);
    printf("\n\n");
}

int partition(int array[], int left, int right) { //퀵정렬과 함께 사용하는 파티션 함수
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = array[left];  //피벗을 첫 번째 요소로 설정

    do {
        do { //피벗값보다 큰 값을 찾을 때까지 low 증가(비교횟수, 이동횟수도 증가)
            low++;
        } while (low <= right && array[low] < pivot);

        do { //피벗값보다 큰 값을 찾을 때까지 high 감소(비교횟수, 이동횟수도 증가)
            high--;
        } while (high >= left && array[high] > pivot);

        if (low < high) { //low와 high의 값을 교환
            SWAP(array[low], array[high], temp);
        }
    } while (low < high);

    SWAP(array[left], array[high], temp); //과정이 끝날 시 피벗값과 high를 교환하여 피벗값을 올바른 위치로 이동
    return high;
}

void QuickSort(int array[], int left, int right) { //퀵정렬 수행 함수
    if (left < right) {
        int q = partition(array, left, right);
        QuickSort(array, left, q - 1);
        QuickSort(array, q + 1, right);
    }
}

//++++
int BinarySearch(int array[], int key) { //이진 탐색 후 비교횟수 반환 함수
    int middle;
    int low = 0;
    int high = SIZE - 1; //배열의 시작 인덱스
    compareCount = 0; //배열의 마지막 인덱스

    while (low <= high) { //아직 값이 남아있으면 중간값 계산
        middle = (low + high) / 2;
        //compareCount++;
        if (array[middle] == key) { 
            compareCount++;
            break;
        }
        else if (key > array[middle]) { //타겟값이 중간값보다 크면 왼쪽 부분배열 탐색
            low = middle + 1;
            compareCount++;
        }
        else { //타겟값이 중간값보다 작으면 오른쪽 부분배열 탐색
            high = middle - 1;
            compareCount++;
        }
    }
    return compareCount;
}

float getAverageBinarySearchCompareCount(int array[]) { //이진 탐색 함수
    int key;
    float totalCompare = 0;
    for (int i = 0; i < SIZE; i++) {
        key = array[rand() % SIZE]; //데이터 탐색 시 타겟값을 잡는다.
        totalCompare += BinarySearch(array, key);
    }
    return (float)totalCompare / SIZE;
}

//++++
int interpolSearch(int array[], int key) { //보간 탐색 후 비교횟수 반환 함수
    int pos;
    int low = 0;
    int high = SIZE - 1; //배열의 시작 인덱스
    compareCount = 0; //배열의 마지막 인덱스

    while ((low <= high) && (array[high] >= key) && (key >= array[low])) { //보간 탐색 위치 계산
        pos = ((float)(key - array[low]) / (array[high] - array[low]) * (high - low)) + low; //보간 탐색(pos는 탐색 위치)
        //compareCount++;
        if (array[pos] == key) { 
            compareCount++;
            break;
        }
        else if (array[pos] < key) { 
            low = pos + 1;
            compareCount++;
        }
        else {
            high = pos - 1;
            compareCount++;
        }
    }

    return compareCount;
}

float getAverageInterpolationSearchComparecount(int array[]) { //보간 탐색 함수
    int key;
    float totalCompare = 0;

    for (int i = 0; i < SIZE; i++) {
        key = array[rand() % SIZE]; //데이터 탐색 시 타겟값을 잡는다.
        totalCompare += interpolSearch(array, key);
    }
    return (float)totalCompare / SIZE;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array); //무작위의 수 생성

    QuickSort(array, 0, SIZE - 1); //퀵 정렬
    printArray(array); //정렬한 배열 출력

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array)); //이진 탐색 평균 비교횟수 출력

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array)); //보간 탐색 평균 비교횟수 출력, 5~10 간당간당

    return 0;
}

//<1.> 0부터 9999사이의 임의의 숫자 1000개를 만들어 배열A에 저장
//<2.> 배열A를 Quick Sort를 이용해 정렬한 뒤, 배열의 처음부터 20번째, 뒤에서 20번째~마지막을 출력
//<3.> <2.> 에서 정렬된 배열A를 이용해 Binary Search를1000번수행하고, 평균 비교횟수를 출력
//<4.> <2.> 에서 정렬된 배열A를 이용해 Interpolation Search를 1000번수행하고, 평균 비교횟수를 출력
//Interpolation Search가 Binary Search보다 적게 비교하는 이유를 설명
