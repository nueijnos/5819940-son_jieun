#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y)=(t) )

void generateRandomData(int list[]) { //���� ������ ���� �Լ�
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

void print_list(int list[], int n) { //��� �Լ�
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void doSelectionSort(int list[]) { //���� ���� �Լ�
    printf("Selection Sort: \n");
    int i, j, least, temp;
    int n = SIZE;

    for (i = 0; i < n - 1; i++) { //��ȸ�ϸ鼭 ����
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[least] > list[j]) least = j;

        SWAP(list[i], list[least], temp); //�ּڰ��� ���� ��ġ ���� ��ȯ
        if ((i + 1) % 20 == 10) { //10���� 20 �������� ���(10, 30, 50, 70, 90)
            printf("Step %d: ", i + 1);
            print_list(list, n);
            printf("\n");
        }
    }
    printf("Step %d: ", i); //99
    print_list(list, n); //������ ��° ������ ���
}

void doInsertionSort(int list[]) { //���� ����
    int i, j, key, compareCount;
    int n = SIZE;
    int total = 0; //�� ��Ƚ�� ����

    for (int try = 0; try < 20; try++) { //���� ����20ȸ �õ��ϰ�
        int randomData[SIZE];
        generateRandomData(randomData);
        compareCount = 0;
        for (i = 1; i < n; i++) { //���� ���� �˰���
            key = randomData[i];
            for (j = i - 1; j >= 0; j--) {
                compareCount++;
                if (randomData[j] > key) randomData[j + 1] = randomData[j];
                else break;
            }
            randomData[j + 1] = key; //������ ��ġ�� Ű �� ����
        }
        total += compareCount;
    }
    int avgCompare = total / 20; //��� ��Ƚ�� �Ի�
    printf("\n\nInsertion Sort Compare Average: %d\n", avgCompare);
    printf("Insertion Sort Result:\n");
    print_list(list, n); //���� ���� ��� ���
}

void doBubbleSort(int list[]) { //���� ����
    int i, j, temp, flag, moveCount;
    int n = SIZE;
    int total = 0; //�� ��Ƚ�� ����

    for (int try = 0; try < 20; try++) { //���� ����20ȸ �õ��ϰ�
        int randomData[SIZE];
        generateRandomData(randomData);
        moveCount = 0;
        for (i = n - 1; i > 0; i--) { //���� ���� �˰���
            flag = 0;
            for (j = 0; j < i; j++) {
                if (randomData[j] > randomData[j + 1]) {
                    SWAP(randomData[j], randomData[j + 1], temp); //�� ��ȯ
                    flag = 1;
                    moveCount += 3; //�� swap���� ���� �̵��� 3ȸ�� ����
                }
            }
            if (flag == 0) break;
        }
        total += moveCount;
    }
    int avgMove = total / 20; //��� �̵�Ƚ�� ���
    printf("\n\nBubble Sort Move Average: %d\n", avgMove);
    printf("Bubble Sort Result:\n");
    print_list(list, n); //���� ���� ��� ���
}

int main() {
    srand(time(NULL));
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}

//�� 0 - 999 ������ ���� ������ 100���� ��������, ��������, ���������� �����Ѵ�.
//1. ���� ���Ŀ��� ���� ������ 10���� 20������ ���, ������ ��° ���
//2. ���� ����20ȸ �õ��ϰ� ��� ��Ƚ���� ���İ�� ���
//3. ���� ����20ȸ �õ��ϰ� ��� �̵�Ƚ��(�� swap���� ���� �̵��� 3ȸ�� ����)�� ���İ�� ���
//- 20ȸ �ݺ��� ���, �Լ� ���ο��� generateRandomNumbers�Լ��� ��ȸ���� ȣ���� �Ź� �ٸ� random������ ������ �� ������ ����� ���� ���. (if�� ������ 20ȸ ����ÿ��� print�ȵǵ��� ����)