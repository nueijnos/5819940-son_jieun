#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType { //�׷��� ����ü
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES]; //���� ���
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->n = 11;  // ���� ���� ����
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->weight[i][j] = INF;
		}
		selected[i] = FALSE;
		distance[i] = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int weight) { //���� ���� �Լ�
	g->weight[start][end] = weight;
	g->weight[end][start] = weight; // ������ �׷���
}

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
	int v = -1;
	for (int i = 1; i < n + 1; i++) {
		if (!selected[i] && (v == -1 || distance[i] < distance[v])) { //���õ��� �ʰų� ���� �Ÿ����� ª�� �Ÿ��� �ִ� ���� ����
			v = i;
		}
	}
	return v;
}

//prim �˰���(MST ã��)
void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return;
		printf("���� %d �߰�\n", u);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
	}
}

void FindPrimMST(GraphType* g) { //prim mst�� ã�� �Լ�
	printf("Prim MST Algorithm\n");
	for (int i = 0; i < MAX_VERTICES; i++) {
		selected[i] = FALSE;
	}
	prim(g, 1); //���� ������ 1�� ����
}

GraphType* GenerateGraph(GraphType* g) { //�׷��� ���� �Լ�
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

	GenerateGraph(g); //�׷��� ���� �Լ�

	FindPrimMST(g);

	free(g);
	return 0;
}
