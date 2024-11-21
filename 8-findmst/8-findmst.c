#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// �θ� ���

// �ʱ�ȭ
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// ��Ʈ 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�. 
	int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�. 
	if (root1 != root2) 	// ���Ѵ�. 
		parent[root1] = root2;
}

struct Edge {			// ������ ��Ÿ���� ����ü
	int start, end, weight;
};

typedef struct GraphType { //�׷��� ����ü
	int n;	// ������ ����
	int vertex; //������ ��
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ(�����ϴ� ������ ������ ����, �׸��� ����ġ�� �ʱ�ȭ)
void graph_init(GraphType* g) 
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()�� ���Ǵ� �Լ�(���� �� �Լ�)
int compare(const void* a, const void* b) 
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

typedef struct MinHeap { //�ּ� �� ����ü
	struct Edge edges[2 * MAX_VERTICES];
	int heap_size;
} MinHeap;


void init_minheap(MinHeap* h) { //minheap �ʱ�ȭ
	h->heap_size = 0;
}


void swap(struct Edge* a, struct Edge* b) { //��ȯ �Լ�
	struct Edge temp = *a;
	*a = *b;
	*b = temp;
}

void min_heapify(MinHeap* h, int index) { //�ּ� �� heapify �Լ�
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < h->heap_size && h->edges[left].weight < h->edges[smallest].weight)
		smallest = left;
	if (right < h->heap_size && h->edges[right].weight < h->edges[smallest].weight)
		smallest = right;

	if (smallest != index) {
		swap(&h->edges[index], &h->edges[smallest]);
		min_heapify(h, smallest);
	}
}

void insert_minheap(MinHeap* h, struct Edge e) { //minheap ���� ���� �Լ�
	int i = h->heap_size++;
	while (i > 0 && e.weight < h->edges[(i - 1) / 2].weight) {
		h->edges[i] = h->edges[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	h->edges[i] = e;  //�� ���� ����
}

struct Edge delete_minheap(MinHeap* h) { //minheap �ּ� ���� ���� �Լ�
	struct Edge min_edge = h->edges[0];
	h->edges[0] = h->edges[--h->heap_size];
	min_heapify(h, 0); //�ּ� �� ���� ����
	return min_edge;
}

void QuickKruskal(GraphType* g) { // kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�(qsort ���)
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->n);				// ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Quick Based Kruskal \n");
	int i = 0;
	while (edge_accepted < (g->vertex - 1))	// ������ �� < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ 
		vset = set_find(e.end);		// ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("Edge (%d,%d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
		i++;
	}
}


void MinHeapKruskal(GraphType* g) { //minheap ��� kruskal
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;
	MinHeap heap;

	set_init(g->vertex);				// ���� �ʱ�ȭ
	init_minheap(&heap); 

	//��� ������ �ּ� ���� ����
	for (int i = 0; i < g->n; i++) {
		insert_minheap(&heap, g->edges[i]);
	}

	printf("\nMinheap Based Kruskal \n");
	while (edge_accepted < (g->vertex - 1) && heap.heap_size > 0)	// ������ �� < (n-1)
	{
		e = delete_minheap(&heap); //������ �ּ� ���� ����
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ 
		vset = set_find(e.end);		// ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("Edge (%d,%d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
	}
}

GraphType* GenerateGraph(GraphType *g) {
	g->vertex = 10; //���� �� ����
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

	QuickKruskal(g); 
	MinHeapKruskal(g);

	free(g);
	return 0;
}