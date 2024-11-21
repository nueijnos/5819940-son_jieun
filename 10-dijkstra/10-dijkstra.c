#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100   
#define INF 1000L   /* ���Ѵ� �� (������ ���� ���) */

typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* ���� �������κ����� �ִ� ��� �Ÿ� */
int found[MAX_VERTICES];    /* �湮�� ���� ǥ�� */
int found_index = 0; //�湮 ���� �ε���
int found_order[MAX_VERTICES]; //�湮 ���� ���

void graph_init(GraphType* g) {
    g->n = 10;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = (i == j) ? 0 : INF;
        }
    }
}

/* ���� �߰� �Լ� */
void insert_edge(GraphType* g, int u, int v, int weight) {
    g->weight[u][v] = weight;
    g->weight[v][u] = weight; // ����� �׷����� ���
}

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
    int v = -1;
    for (int i = 1; i <= n; i++) {
        if (!found[i] && (v == -1 || distance[i] < distance[v])) { //���õ��� �ʰų� ���� �Ÿ����� ª�� �Ÿ��� �ִ� ���� ����
            v = i;
        }
    }
    return v;
}

void print_dijkstra(int n) { //���ͽ�Ʈ�� �˰����� ��������� distance ������ found�� ����ϴ� �Լ�
    printf("Distance: ");
    for (int j = 1; j <= n; j++) {
        if (distance[j] == INF)
            printf("* ");
        else
            printf("%d ", distance[j]); //���簡���� distance ���� ���
    }
    printf("\nFound:    ");
    for (int j = 1; j <= n; j++) {
        printf("%d ", found[j]); //found ���
    }
    printf("\n\n");
}

/* Dijkstra �˰��� �Լ� */
void dijkstra(GraphType* g, int start) {
    // �ʱ�ȭ
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n); //���� ª�� �Ÿ��� �湮���� ���� ������ ����
        found[u] = TRUE; //������ �湮 ó��
        found_order[found_index++] = u; //�湮 ���� ���

        print_dijkstra(g->n); //���� ���� ���

        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !found[v]) { //����� �湮���� ���� �����̸�
                if (distance[u] + g->weight[u][v] < distance[v]) {
                    distance[v] = distance[u] + g->weight[u][v]; //���ο� �Ÿ��� ������Ʈ
                }
            }
        }
    }

    printf("found order: "); //�湮�� ���� ���
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

/* �׷����� �����ϴ� �Լ� */
GraphType* GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);

    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);

    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);

    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);

    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);

    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    dijkstra(g, 1);

    free(g);
    return 0;
}
