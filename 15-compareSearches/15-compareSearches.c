#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int compareCount;
int totalCompare;

void generateRandomArray(int array[]) { //���� ������ ���� �Լ�
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;
	}
}

void printArray(int* array) { //���� ������ ��� �Լ�
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++) //�迭�� ó������ 20��° ����� ����
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++) //�ڿ��� 20��°���� �������� �����
		printf("%3d ", array[i]);
	printf("\n");

}

//++++
double getAverageLinearSearchCompareCount(int array[]) { //���� Ž�� �Լ�
	int key;
	totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		key = array[rand() % SIZE]; //������ Ž�� �� �̷��� Ÿ�ٰ��� ��´�.
		
		compareCount = 0; //��Ƚ�� �ʱ�ȭ

		for (int j = 0; j < SIZE; j++) {
			compareCount++;
			if (array[j] == key) break; //Ÿ�ٰ��� ã���� ����
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100; 
}

int partition(int array[], int left, int right) { //�����İ� �Բ� ����ϴ� ��Ƽ�� �Լ�
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = array[left];  //�ǹ��� ù ��° ��ҷ� ����

	do {
		do { //�ǹ������� ū ���� ã�� ������ low ����(��Ƚ��, �̵�Ƚ���� ����)
			low++;
			compareCount++;
		} while (low <= right && array[low] < pivot);

		do { //�ǹ������� ū ���� ã�� ������ high ����(��Ƚ��, �̵�Ƚ���� ����)
			high--;
			compareCount++;
		} while (high >= left && array[high] > pivot);

		if (low < high) { //low�� high�� ���� ��ȯ
			SWAP(array[low], array[high], temp);
		}
	} while (low < high);

	SWAP(array[left], array[high], temp); //������ ���� �� �ǹ����� high�� ��ȯ�Ͽ� �ǹ����� �ùٸ� ��ġ�� �̵�
	return high;
}

void QuickSort(int array[], int left, int right) { //������ ���� �Լ�
	if (left < right) {
		int q = partition(array, left, right);
		QuickSort(array, left, q - 1);
		QuickSort(array, q + 1, right);
	}
}

void getQuickSortCompareCount(int array[]) { //�迭 ��ü�� ���� �������� �����ϰ� ��Ƚ���� ����ϴ� �Լ�
	compareCount = 0;
	QuickSort(array, 0, SIZE - 1);
}

//++++
double getAverageBinarySearchCompareCount(int array[]) { //���� Ž�� �Լ�
	int key;
	totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		key = array[rand() % SIZE]; //������ Ž�� �� Ÿ�ٰ��� ��´�.
		
		int middle;
		int low = 0;
		int high = SIZE - 1;
	    compareCount = 0; //��Ƚ�� �ʱ�ȭ

		while (low <= high) { //���� ���ڵ��� ���� ������
			middle = (low + high) / 2; //�߰��� ���
			compareCount++;
			if (array[middle] == key) break; //Ÿ�ٰ��� ã���� ����
			else if (key > array[middle]) low = middle + 1; //Ÿ�ٰ��� �߰������� ũ�� ���� �κй迭 Ž��
			else high = middle - 1; //Ÿ�ٰ��� �߰������� ������ ������ �κй迭 Ž��
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	//��հ��� ��ȯ�ޱ� ���� ��ġ, ����Ž���� 100�� ���� �� ��� ��Ƚ�� ���(��� ��Ƚ�� A)
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));

	//compareCount�� global variable�̹Ƿ�, ������ ���� ����
	//array�� ���ؼ� ���� �����ϸ� �ȴ�.
	getQuickSortCompareCount(array); //�� ���� ���� �� �迭 ������ �� ��Ƚ�� ���(��Ƚ�� B)
	printf("Quick Sort Compare Count: %d\n", compareCount);

	//���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���(��� ��Ƚ�� C)
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array)); 
	printArray(array);
	return 0;
}