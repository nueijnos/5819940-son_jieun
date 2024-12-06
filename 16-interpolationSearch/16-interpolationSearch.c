#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount;

void generateRandomArray(int array[]) { //���� ������ ���� �Լ�
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

void printArray(int* array) { //���� ������ ��� �Լ�
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) //�迭�� ó����°~20��° ���
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) //�迭�� �ڿ��� 20��°~��������° ���
        printf("%4d ", array[i]);
    printf("\n\n");
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
        } while (low <= right && array[low] < pivot);

        do { //�ǹ������� ū ���� ã�� ������ high ����(��Ƚ��, �̵�Ƚ���� ����)
            high--;
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

//++++
int BinarySearch(int array[], int key) { //���� Ž�� �� ��Ƚ�� ��ȯ �Լ�
    int middle;
    int low = 0;
    int high = SIZE - 1; //�迭�� ���� �ε���
    compareCount = 0; //�迭�� ������ �ε���

    while (low <= high) { //���� ���� ���������� �߰��� ���
        middle = (low + high) / 2;
        //compareCount++;
        if (array[middle] == key) { 
            compareCount++;
            break;
        }
        else if (key > array[middle]) { //Ÿ�ٰ��� �߰������� ũ�� ���� �κй迭 Ž��
            low = middle + 1;
            compareCount++;
        }
        else { //Ÿ�ٰ��� �߰������� ������ ������ �κй迭 Ž��
            high = middle - 1;
            compareCount++;
        }
    }
    return compareCount;
}

float getAverageBinarySearchCompareCount(int array[]) { //���� Ž�� �Լ�
    int key;
    float totalCompare = 0;
    for (int i = 0; i < SIZE; i++) {
        key = array[rand() % SIZE]; //������ Ž�� �� Ÿ�ٰ��� ��´�.
        totalCompare += BinarySearch(array, key);
    }
    return (float)totalCompare / SIZE;
}

//++++
int interpolSearch(int array[], int key) { //���� Ž�� �� ��Ƚ�� ��ȯ �Լ�
    int pos;
    int low = 0;
    int high = SIZE - 1; //�迭�� ���� �ε���
    compareCount = 0; //�迭�� ������ �ε���

    while ((low <= high) && (array[high] >= key) && (key >= array[low])) { //���� Ž�� ��ġ ���
        pos = ((float)(key - array[low]) / (array[high] - array[low]) * (high - low)) + low; //���� Ž��(pos�� Ž�� ��ġ)
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

float getAverageInterpolationSearchComparecount(int array[]) { //���� Ž�� �Լ�
    int key;
    float totalCompare = 0;

    for (int i = 0; i < SIZE; i++) {
        key = array[rand() % SIZE]; //������ Ž�� �� Ÿ�ٰ��� ��´�.
        totalCompare += interpolSearch(array, key);
    }
    return (float)totalCompare / SIZE;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array); //�������� �� ����

    QuickSort(array, 0, SIZE - 1); //�� ����
    printArray(array); //������ �迭 ���

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array)); //���� Ž�� ��� ��Ƚ�� ���

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array)); //���� Ž�� ��� ��Ƚ�� ���, 5~10 ���簣��

    return 0;
}

//<1.> 0���� 9999������ ������ ���� 1000���� ����� �迭A�� ����
//<2.> �迭A�� Quick Sort�� �̿��� ������ ��, �迭�� ó������ 20��°, �ڿ��� 20��°~�������� ���
//<3.> <2.> ���� ���ĵ� �迭A�� �̿��� Binary Search��1000�������ϰ�, ��� ��Ƚ���� ���
//<4.> <2.> ���� ���ĵ� �迭A�� �̿��� Interpolation Search�� 1000�������ϰ�, ��� ��Ƚ���� ���
//Interpolation Search�� Binary Search���� ���� ���ϴ� ������ ����
