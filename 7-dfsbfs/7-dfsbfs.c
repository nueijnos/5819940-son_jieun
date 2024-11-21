#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 11

typedef struct GraphNode {
    int vertex;
    struct GraphNode* next;
} GraphNode;

typedef struct {
    GraphNode* adj[MAX_VERTICES];
    int visited[MAX_VERTICES];
} GraphType;

typedef struct {
    int data[MAX_VERTICES];
    int top;
} StackType;

typedef struct {
    int data[MAX_VERTICES];
    int front, rear;
} QueueType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty_stack(StackType* s) {
    return s->top == -1;
}

void push(StackType* s, int item) {
    s->data[++s->top] = item;
}

int pop(StackType* s) {
    return s->data[s->top--];
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {
    return q->front == q->rear;
}

void enqueue(QueueType* q, int item) {
    q->data[q->rear++] = item;
}

int dequeue(QueueType* q) {
    return q->data[q->front++];
}

void init_graph(GraphType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
        g->visited[i] = 0;
    }
}

void insert_edge_list(GraphType* g, int start, int end) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->vertex = end;
    newNode->next = g->adj[start];
    g->adj[start] = newNode;
}

//DFS �Լ�
void doDFS(GraphType* g, int start, int end) {
    int count = 0;
    StackType s;
    init_stack(&s);
    push(&s, start);

    while (!is_empty_stack(&s)) {
        int v = pop(&s);

        if (!g->visited[v]) { //������ �湮���� �ʾ��� ��
            g->visited[v] = 1;
            count++;
            printf("%d ", v);

            if (v == end) { //������ ã���� ��
                printf("\nŽ�� ����: %d\n", v);
                printf("�湮�� ����� ��: %d\n", count);
                return;
            }

            for (GraphNode* node = g->adj[v]; node != NULL; node = node->next) { //���� ��带 ���ÿ� ����
                if (!g->visited[node->vertex]) {
                    push(&s, node->vertex);
                }
            }
        }
    }
    printf("\nŽ�� ����\n");
    printf("Ž�� ������ ��: %d\n", end);
}

//BFS �Լ�
void doBFS(GraphType* g, int start, int end) {
    int count = 0;
    QueueType q;
    init_queue(&q);

    enqueue(&q, start);

    while (!is_empty_queue(&q)) {
        int v = dequeue(&q);

        if (!g->visited[v]) { //������ �湮���� �ʾ��� ��
            g->visited[v] = 1;
            count++;
            printf("%d ", v);

            if (v == end) { //������ ã���� ��
                printf("\nŽ�� ����: %d\n", v);
                printf("�湮�� ����� ��: %d\n", count);
                return;
            }

            for (GraphNode* node = g->adj[v]; node != NULL; node = node->next) { //���� ��带 ť�� ����
                if (!g->visited[node->vertex]) {
                    enqueue(&q, node->vertex);
                }
            }
        }
    }
    printf("\nŽ�� ����\n");
    printf("Ž�� ������ ��: %d\n", end);
}


//����� �޴� �������̽�
void runUserInterface(GraphType* g) {
    init_graph(g);
    insert_edge_list(g, 0, 2);
    insert_edge_list(g, 0, 9);
    insert_edge_list(g, 0, 5);
    insert_edge_list(g, 0, 6);
    insert_edge_list(g, 1, 4);
    insert_edge_list(g, 1, 7);
    insert_edge_list(g, 1, 5);
    insert_edge_list(g, 1, 10);
    insert_edge_list(g, 2, 0);
    insert_edge_list(g, 2, 3);
    insert_edge_list(g, 2, 4);
    insert_edge_list(g, 2, 5);
    insert_edge_list(g, 3, 5);
    insert_edge_list(g, 3, 2);
    insert_edge_list(g, 3, 4);
    insert_edge_list(g, 3, 5);
    insert_edge_list(g, 4, 0);
    insert_edge_list(g, 4, 1);
    insert_edge_list(g, 4, 2);
    insert_edge_list(g, 4, 3);
    insert_edge_list(g, 4, 6);
    insert_edge_list(g, 4, 7);
    insert_edge_list(g, 5, 0);
    insert_edge_list(g, 5, 1);
    insert_edge_list(g, 5, 3);
    insert_edge_list(g, 6, 0);
    insert_edge_list(g, 6, 4);
    insert_edge_list(g, 6, 7);
    insert_edge_list(g, 6, 8);
    insert_edge_list(g, 7, 1);
    insert_edge_list(g, 7, 4);
    insert_edge_list(g, 7, 6);
    insert_edge_list(g, 7, 10);
    insert_edge_list(g, 8, 6);
    insert_edge_list(g, 8, 7);
    insert_edge_list(g, 8, 9);
    insert_edge_list(g, 8, 10);
    insert_edge_list(g, 9, 0);
    insert_edge_list(g, 9, 8);
    insert_edge_list(g, 10, 1);
    insert_edge_list(g, 10, 7);
    insert_edge_list(g, 10, 8);

    int choice, start, target;

    printf("-----------------------\n");
    printf("|1  : ���� �켱 Ž��   |\n");
    printf("|2  : �ʺ� �켱 Ž��   |\n");
    printf("|3  : ����             |\n");
    printf("----------------------\n");

    while (1) {
        printf("\n\n�޴� �Է�: ");
        scanf(" %d", &choice);

        switch (choice) {
        case 1: //DFS ����
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                g->visited[i] = 0;
            }
            doDFS(g, start, target);
            break;
        case 2: //BFS ����
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                g->visited[i] = 0;
            }
            doBFS(g, start, target);
            break;
        case 3: //����
            printf("���α׷� ����!\n");
            return;
        default:
            printf("�߸��� �Է��Դϴ�!\n");
            break;
        }
    }
}

void free(GraphType* g) { //�׷��� ���� �޸� ���� �Լ�
    for (int i = 0; i < MAX_VERTICES; i++) {
        GraphNode* node = g->adj[i];

        while (node != NULL) {
            GraphNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main(void) {
    GraphType g;
    runUserInterface(&g);
    free(&g);
    return 0;
}
