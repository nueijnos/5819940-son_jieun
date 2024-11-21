#include <stdio.h>
#include <stdlib.h>
//#define MAX_ELEMENT 100
//�̹� ������ heap ����ü�� ���ʿ��� �� ���� ���ܽ��׽��ϴ�.
/*
typedef struct HeapType{
    int heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    h->heap_size = 0;
    return h;
}
*/

//��ȯ �Լ�
void swap(int inputData[], int a, int b) {
    int temp = inputData[a];
    inputData[a] = inputData[b];
    inputData[b] = temp;
}

//�ִ� �� ���� �Լ�(i�� �������� �ִ��� ����)
void resortHeap(int inputData[], int n, int i) {
    int largest = i; //i(���� ���)
    int left = 2 * i + 1; //���� �ڽ� �ε���
    int right = 2 * i + 2; //������ �ڽ� �ε���

    if (left < n && inputData[left] > inputData[largest]) { //���� �ڽ��� �� ũ�ٸ�
        largest = left;
    }
    if (right < n && inputData[right] > inputData[largest]) { //������ �ڽ��� �� ũ�ٸ�
        largest = right;
    }
    if (largest != i) { //��Ʈ�� ���� ū ���� �ƴ� ���
        swap(inputData, i, largest); //��ȯ ��
        resortHeap(inputData, n, largest); //�ٽ� �� ����
    }
}

//�ִ� ������ ����� ���� �Լ�
void buildMaxHeap(int inputData[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i); //�� ��忡 �ִ� �� ����
    }
}

//�� ���� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        buildMaxHeap(inputData, i);
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // �ϳ��� ������ ��Ʈ(�ִ밪)�� �����ϰ� ����
    for (int i = n - 1; i > 0; i--) {
        swap(inputData, 0, i); //��Ʈ ���� ������ ��带 ��ȯ
        resortHeap(inputData, i, 0); 

        // �� ������ �� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main(void) {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    //�� ���� ����
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // ���ĵ� ��� ���(�������� ���ĵ� ���)
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
