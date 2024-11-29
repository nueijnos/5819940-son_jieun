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

void generateRandomArray(int array[]) { //���� ������ ���� �Լ�
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; 
    }
}

void printArray(int array[], int n) { //���� ������ ��� �Լ�
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int array[], int left, int right) { //���� ������ �����ִ� partition �Լ�
    int pivot, temp; 
    int low, high;

    low = left;
    high = right + 1;
    pivot = array[left];  //�ǹ��� ù ��° ��ҷ� ����
    
    do {
        do { //�ǹ������� ū ���� ã�� ������ low ����(��Ƚ��, �̵�Ƚ���� ����)
            low++;
            comparisonCount++;
            moveCount++;
        } while (low <= high && array[low] < pivot); 

        do { //�ǹ������� ū ���� ã�� ������ high ����(��Ƚ��, �̵�Ƚ���� ����)
            high--;
            comparisonCount++;
            moveCount++;
        } while (high >= high && array[high] > pivot); 

        if (low < high) { //low�� high�� ���� ��ȯ
            SWAP(array[low], array[high], temp);
            comparisonCount++;
            moveCount += 3; 
        }
    } while (low < high);

    SWAP(array[left], array[high], temp); //������ ���� �� �ǹ����� high�� ��ȯ�Ͽ� �ǹ����� �ùٸ� ��ġ�� �̵�
    moveCount += 3;

    return high;
}

/*
void doQuickSort(int array[], int left, int right) { //�� ���� �Լ�(����� ���)
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

void doQuickSort(int array[], int left, int right) { //�� ���� �Լ�(�ݺ��� ���)
    //���� �ʱ�ȭ
    int stack[SIZE];
    int top = -1;
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) { //������ ��� ������ �ݺ�
        right = stack[top--];
        left = stack[top--];

        int p = partition(array, left, right); //���� ���� �� �ǹ����� ��ġ�� ��ȯ

        if (p - 1 > left) { //�ǹ����� �������� ���� �κ��� �����Ѵٸ� ���ÿ� �߰�
            stack[++top] = left;
            stack[++top] = p - 1;
        }

        if (p + 1 < right) { //�ǹ����� �������� ������ �κ��� �����Ѵٸ� ���ÿ� �߰�
            stack[++top] = p + 1;
            stack[++top] = right;
        }
        if (rounds % 10 == 0 && isFirst == 0) { 
            for (int i = 40; i < 60; i++) //40~60�� ��ġ�� �ִ� ���� �ѹ��� ���
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


//0 - 999 ������ ���� ������ 100���� �Ʒ� ������ �����ϸ� �������� ����(�ݺ��� ���)
//1. �����ϴ� ������ ���(��°�� ����) �̴� �ѹ��� ����ϸ�, 40~60 �� ��ġ�� �ִ� ���� ���
//2. �� Ƚ���� ���(20ȸ ���)
//3. �̵� Ƚ���� ���(20ȸ ���)
//=20ȸ ����� �� ȸ ���ο� ������� �����͸� ����
//->�̵��� ����temp�� ���� �ְų� temp�κ��� ���� �������� ��� ������ ����