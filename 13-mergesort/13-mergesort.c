#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

//비교 횟수, 이동 횟수를 저장하는 전역 변수
int comparisonCount; 
int moveCount;   
int isFirst = 0; //첫번째 실행에서 특정 결과를 출력하는 변수

void generateRandomArray(int array[]) { //랜덤 데이터 생성 함수
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void print_list(int array[], int n) { //정렬 데이터 출력 함수
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void Merge(int array[], int left, int mid, int right) { //합병 함수
    int i = left, j = mid + 1, k = left;
    int temp[SIZE]; //복사할 배열 생성(temp)

    while (i <= mid && j <= right) { //왼쪽, 오른쪽에 값이 남아있을 때까지 반복하는 루프
        comparisonCount++; //비교 횟수 증가
        if (array[i] <= array[j]) { //왼쪽 배열의 값이 더 작거나 같을때
            temp[k++] = array[i++]; //복사할 배열에 추가한 후 증가
            moveCount++; //이동 횟수 증가
        }
        else { //오른쪽 배열의 값이 더 작을 때는
            temp[k++] = array[j++]; //복사할 배열에 추가한 후 증가
            moveCount++; //이동 횟수 증가
        }
    }

     //여기서부턴 남은 값을 처리하면서 이동 횟수를 증가시키는 부분
    while (i <= mid) { //왼쪽 배열에 값이 남아있을 시
        temp[k++] = array[i++]; //복사할 배열에 추가
        moveCount++; //이동 횟수 증가
    }

    while (j <= right) { //오른쪽 배열에 값이 남아있을 시
        temp[k++] = array[j++]; //복사할 배열에 추가
        moveCount++; //이동 횟수 증가
    }

    for (k = left; k <= right; k++) { //복사한 배열의 내용을 원래 배열에 복사
        array[k] = temp[k];
        moveCount++; //이동 횟수 증가
    }
}

void doMergeSort(int array[], int left, int right) { //병합 정렬 함수(반복적 방법)
    int size, start, mid, end;
    int rounds = 0; 

    for (size = 1; size <= right - left; size *= 2) { //size를 1로 초기화한다음 각 반복마다 size를 2배로 증가시킴(병합할 배열 크기를 늘려가기 위해서)
        for (start = left; start <= right; start += 2 * size) { //시작 인덱스를 설정 후 중간 인덱스
            mid = start + size - 1; //mid 인덱스 계산
            end = start + 2 * size - 1; //end 인덱스 계산

            if (mid > right) mid = right;  //mid가 right보다 클 시 right로 설정
            if (end > right) end = right; //end가 right보다 클 시 right로 설정

            Merge(array, start, mid, end); //합병

            rounds++;

            if (rounds % 10 == 0 && isFirst == 0) { //10번에 한번만 출력
                for (int i = 0; i < 10; i++) //0 ~ 9값
                    printf("%3d ", array[i]);
                printf("| ");
                for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) //중앙-1 ~ 중앙+10
                    printf("%3d ", array[i]);
                printf("\n\n");
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int array[SIZE];
    int totalComparisons = 0;
    int totalMoves = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n", i);
            doMergeSort(array, 0, SIZE - 1);
        
            printf("Result\n");
            print_list(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}



//1. 정렬하는 과정을 출력(출력결과 참고)
//•이는 한번만 출력
//•분할과 결합의 모든 과정에서 10번에 한번씩 출력한다.
//•배열 처음부터 10번째까지, 중앙 - 1위치부터 중앙 + 10 위치까지 출력(출력 및 코드 참조)
//2. 비교 횟수를 출력(20회 평균)
//3. 이동 횟수를 출력(20회 평균)->이동은 값을temp에 값을 넣거나 temp로부터 값을 가져오는 모든 행위를 포함
//합병정렬을 재귀적 방법이 아닌 반복적 방법으로 구현(처음부터 반복적 방법으로 구현해 위의 세 단계를 수행)