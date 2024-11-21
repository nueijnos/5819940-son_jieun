#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100 //��� �ִ� ũ�� ����

typedef struct Node { //�� �󵵼��� Ʈ�� ������ �����ϴ� ����ü
    int frequency;
    char character;
    struct Node* left, * right;
} Node;

typedef struct { //���� �� Ʈ���� �󵵼�
    Node* ptree;
    int key;
} element;

typedef struct { //�ּ� �� ����ü
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

Node* create_heap(char character, int frequency) { //���ο� ��� ���� �Լ� 
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) exit(1);
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int is_leaf(Node* node) { //���� ��� �Լ�
    return !(node->left) && !(node->right); // ����, ������ �ڽ��� ��� ���� ���
}

void swap(element* a, element* b) { //��ȯ �Լ�
    element temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(HeapType* h, int index) { //�ּ� �� ���� �Լ�
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->heap_size && h->heap[left].key < h->heap[smallest].key)
        smallest = left;
    if (right < h->heap_size && h->heap[right].key < h->heap[smallest].key)
        smallest = right;

    if (smallest != index) {
        swap(&h->heap[smallest], &h->heap[index]);
        min_heapify(h, smallest);
    }
}

Node* extract_min_heap(HeapType* h) { //������ ���� ���� �󵵼��� ���� ��带 �̾��ִ� �Լ�
    Node* temp = h->heap[0].ptree;
    h->heap[0] = h->heap[h->heap_size - 1];
    h->heap_size--;
    min_heapify(h, 0);
    return temp;
}

void print_heap(HeapType* h) { //�� ��� �Լ�
    for (int i = 0; i < h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_min_heap(HeapType* h, Node* item) { //���ο� ��� �߰� �Լ�
    h->heap[h->heap_size].ptree = item;
    h->heap[h->heap_size].key = item->frequency;
    h->heap_size++;

    int i = h->heap_size - 1;
    while (i && h->heap[i].key < h->heap[(i - 1) / 2].key) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    print_heap(h);
}

HeapType* create_min_heap() { //�ּ� �� ���� �Լ�
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    if (h == NULL) exit(1);
    h->heap_size = 0;
    return h;
}

HeapType* build_min_heap(char characters[], int frequencies[], int size) { //�ּ� �� ���� �Լ�
    HeapType* h = create_min_heap();
    for (int i = 0; i < size; i++) {
        insert_min_heap(h, create_heap(characters[i], frequencies[i]));
    }
    return h;
}

Node* buildHuffmanTree(char characters[], int frequencies[], int size) { //������ Ʈ�� �Լ�
    Node* left, * right, * top;
    HeapType* h = build_min_heap(characters, frequencies, size);

    while (h->heap_size > 1) { //���� �ϳ��� ���� ������ ��� �ݺ�
        left = extract_min_heap(h);
        right = extract_min_heap(h);
        top = create_heap('$', left->frequency + right->frequency); //�� ����� �󵵼��� ��ģ ���ο� ��� ����
        top->left = left;
        top->right = right;

        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency); //�� ��带 ������ �󵵼� ��� ���
        insert_min_heap(h, top); //�� ��带 ���� ����
    }

    return extract_min_heap(h);
}

void printCodes(Node* root, int codes[], int top) { //������ �ڵ� ��� �Լ�
    if (root->left) { //���� �ڽ� ��� 1 �Ҵ� 
        codes[top] = 1;
        printCodes(root->left, codes, top + 1);
    }
    if (root->right) { //������ �ڽ� ��� 0 �Ҵ�
        codes[top] = 0;
        printCodes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) { //���� ��忡 ������ ��, ������ �ڵ� ���
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++)
            printf("%d", codes[i]);
        printf("\n");
    }
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) { //������ Ʈ�� ���� �Լ�(�־��� ���ڿ� �󵵼���)
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[MAX_ELEMENT];
    int top = 0;
    printCodes(root, arr, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}