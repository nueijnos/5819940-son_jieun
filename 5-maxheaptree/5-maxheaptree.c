#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int key;
} element;

typedef struct TreeNode {
    int heap_size;
    element heap[MAX_SIZE];
} TreeNode;

TreeNode* create_heap() {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->heap_size = 0;
    return newNode;
}

void display_heap(TreeNode* h) {
    int i = 1;
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void free_heap(TreeNode* node) {
    if (node == NULL) return;
    free(node); 
}

void insertMaxHeapTree(TreeNode* h, element item) {
    if (h->heap_size >= MAX_SIZE - 1) {
        printf("���� ���� á���ϴ�!\n");
        return;
    }

    int i = ++h->heap_size; 
    h->heap[i] = item;
    int count = 0; 

    // Upheap
    while ((i != 1) && (h->heap[i / 2].key < h->heap[i].key)) {
        display_heap(h);
        element temp = h->heap[i / 2];
        h->heap[i / 2] = h->heap[i];
        h->heap[i] = temp;

        i /= 2; 
        count++; 
    }

    display_heap(h);

    if (count > 0) {
        printf("��尡 �̵��� Ƚ��: %d\n", count);
    }
}

element delete_heap(TreeNode* h) {
    if (h->heap_size == 0) {
        printf("���� ��� �ֽ��ϴ�!\n");
        return (element) { -1 };
    }

    element item = h->heap[1]; 
    element temp = h->heap[h->heap_size--]; 
    int parent = 1;
    int child = 2;
    int count = 1; 

    h->heap[parent] = temp; 
    display_heap(h); 

    // Downheap
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }

        if (temp.key >= h->heap[child].key) break; 

        element prev = h->heap[parent]; 
        h->heap[parent] = h->heap[child]; 
        h->heap[child] = prev; 

        display_heap(h); 

        parent = child; 
        child *= 2; 
        count++; 
    }

    h->heap[parent] = temp; 
    printf("��尡 �̵��� Ƚ��: %d\n", count); 
    return item;
}

void level_display(TreeNode* h) {
    if (h->heap_size == 0) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    int level = 1;
    int level_node_size = 1; 
    int index = 1; 

    while (index <= h->heap_size) {
        printf("[ %02d ] ", level);
        for (int i = 0; i < level_node_size && index <= h->heap_size; i++) {
            printf("%02d ", h->heap[index].key);
            index++;
        }
        printf("\n");
        level++;
        level_node_size *= 2; 
    }
}

TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* heap = create_heap();
    for (int i = 0; i < size; i++) {
        insertMaxHeapTree(heap, (element) { inputData[i] });
    }
    return heap; 
}

void runUserInterface(TreeNode* root) {
    char c = 0;
    int num = 0;

    for (;;) {
        printf("----------------------\n");
        printf("| i  : ��� �߰�     |\n");
        printf("| d  : ��� ����     |\n");
        printf("| p  : ������ ���   |\n");
        printf("| c  : ����          |\n");
        printf("----------------------\n");

        printf("�޴� �Է�: ");
        scanf(" %c", &c);

        switch (c) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &num);
            insertMaxHeapTree(root, (element) { num }); 
            break;
        case 'd':
            delete_heap(root);
            break;
        case 'p':
            level_display(root);
            break;
        case 'c':
            free(root); 
            exit(0);
            break;
        default:
            printf("�߸��� �Է��Դϴ�!\n");
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]); 

    TreeNode* root = generateMaxHeapTree(inputData, size);
    runUserInterface(root);

    free_heap(root); 

    return 0;
}
