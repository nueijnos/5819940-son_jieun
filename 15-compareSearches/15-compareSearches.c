#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int compareCount;
int totalCompare;

void generateRandomArray(int array[]) { //랜덤 데이터 생성 함수
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;
	}
}

void printArray(int* array) { //정렬 데이터 출력 함수
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++) //배열을 처음부터 20번째 출력한 다음
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++) //뒤에서 20번째에서 마지막을 출력함
		printf("%3d ", array[i]);
	printf("\n");

}

//++++
double getAverageLinearSearchCompareCount(int array[]) { //순차 탐색 함수
	int key;
	totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		key = array[rand() % SIZE]; //데이터 탐색 시 이렇게 타겟값을 잡는다.
		
		compareCount = 0; //비교횟수 초기화

		for (int j = 0; j < SIZE; j++) {
			compareCount++;
			if (array[j] == key) break; //타겟값을 찾으면 종료
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100; 
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
			compareCount++;
		} while (low <= right && array[low] < pivot);

		do { //피벗값보다 큰 값을 찾을 때까지 high 감소(비교횟수, 이동횟수도 증가)
			high--;
			compareCount++;
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

void getQuickSortCompareCount(int array[]) { //배열 전체에 대해 퀵정렬을 수행하고 비교횟수를 기록하는 함수
	compareCount = 0;
	QuickSort(array, 0, SIZE - 1);
}

//++++
double getAverageBinarySearchCompareCount(int array[]) { //이진 탐색 함수
	int key;
	totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		key = array[rand() % SIZE]; //데이터 탐색 시 타겟값을 잡는다.
		
		int middle;
		int low = 0;
		int high = SIZE - 1;
	    compareCount = 0; //비교횟수 초기화

		while (low <= high) { //아직 숫자들이 남아 있으면
			middle = (low + high) / 2; //중간값 계산
			compareCount++;
			if (array[middle] == key) break; //타겟값을 찾으면 종료
			else if (key > array[middle]) low = middle + 1; //타겟값이 중간값보다 크면 왼쪽 부분배열 탐색
			else high = middle - 1; //타겟값이 중간값보다 작으면 오른쪽 부분배열 탐색
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	//평균값을 반환받기 위한 조치, 순차탐색을 100번 수행 후 평균 비교횟수 출력(평균 비교횟수 A)
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));

	//compareCount가 global variable이므로, 다음과 같이 구현
	//array에 대해서 직접 정렬하면 된다.
	getQuickSortCompareCount(array); //퀵 정렬 수행 후 배열 정렬한 뒤 비교횟수 출력(비교횟수 B)
	printf("Quick Sort Compare Count: %d\n", compareCount);

	//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력(평균 비교횟수 C)
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array)); 
	printArray(array);
	return 0;
}