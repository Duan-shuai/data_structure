#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define NUM 20
#define INF 9999
#define N 20
#define path "labfour.txt"									

typedef char VertexType;	

//图的邻接矩阵表示
typedef struct {
	VertexType node[NUM];		
	int edge[NUM][NUM];			
	int n;						
	int e;					
} GMatrix;

typedef struct {
	int start;
	int end;
	int power;
} Edge;

typedef int ElementType;			//主要数据类型

typedef struct {					//优先队列的节点
	ElementType ele;				//元素
	int parent;						//下面为辅助信息
	int child;
} Node;

typedef struct {					//优先队列，利用堆来实现，这里是小顶堆
	Node node[NUM * NUM / 2];
	int num;						//队列中元素的个数
} Heap, PQueue;

typedef struct {
	int num;
	int father;
} Set[N];

void InitUFSet(int num, Set S) {
	int i; 
	for (i = 0; i < num; i++) {
		S[i].father = i;
		S[i].num = 1;
	}
}

int Find(int index, Set S) {
	if (S[index].father == index)return index;
	return Find(S[index].father, S);
}

void Union(int a, int b, Set S) {
	if (S[a].num > S[b].num) {
		S[b].father = a;
		S[a].num += S[b].num;
	}
	else {
		S[a].father = b;
		S[b].num += S[a].num;
	}
}

Heap CreatePQueue() {				//初始化并创建队列
	Heap heap;
	heap.num = 0;
	int i ;
	for (i = 0; i < NUM * NUM / 2; i++) {
		heap.node[i].ele = INT_MAX;
	}
	return heap;
}

void EnPQueue(ElementType ele, Heap* heap, int parent, int child) {		//向队列中插入节点
	heap->num++;
	int i;
	for (i = heap->num - 1; heap->node[(i - 1) / 2].ele > ele && (i > 0); i = (i - 1) / 2) {
		heap->node[i]= heap->node[(i - 1) / 2];
	}
	heap->node[i].ele = ele;
	heap->node[i].parent = parent;
	heap->node[i].child = child;
}

void DePQueue(Heap* heap) {												//弹出队首元素，维持小顶堆
	if (heap->node[0].ele == INT_MAX) {
		printf("Queue is NULL!\n");
		return;
	}
	int parent = 0;
	int child = parent * 2 + 1;
	while (child < heap->num) {
		if (child<heap->num - 1 && heap->node[child].ele > heap->node[child + 1].ele) child++;
		heap->node[parent] = heap->node[child];
		parent = child;
		child = parent * 2 + 1;
	}
	if (parent != heap->num - 1) {
		heap->node[parent] = heap->node[heap->num - 1];
	}
	heap->num--;
}

int PQueueIsEmpty(Heap heap) {		//判断堆是否为空
	if (heap.num == 0) return 1;
	return 0;
}

Node TopPQueue(Heap heap) {			//输出堆的首节点
	return heap.node[0];
}

void PrintQueue(Heap heap) {		//按照顺序打印数组
	int i;
	for (i = 0; i < heap.num; i++) {
		printf("%d  ", heap.node[i].ele);
	}
}

int FindNodeIndex_matrix(GMatrix G, VertexType node) 
{	
    int i;
	for (i = 0; i < G.n; i++)
    {
		if (G.node[i] == node)return i;
	}
	return -1;
}

GMatrix CreateGMatrix_file() {						

	FILE* fp;
	errno_t err;
	//const char* path = "graph.txt";
	err = fopen_s(&fp, path, "r");
	if (err != 0 || fp == NULL) {
		printf("File open error!\n");
		exit(-1);
	}

	GMatrix G;
	VertexType t1, t2;
	int power;
	int start, end;

	fscanf_s(fp, "%d", &G.n);
	fscanf_s(fp, "%d", &G.e);
    int i,j;
	for (i = 0; i < G.n; i++) {
		fscanf_s(fp, " %c", &G.node[i], 1);
	}

	for (i = 0; i < G.n; i++) {
		for (j = 0; j < G.n; j++) {
			G.edge[i][j] = INF;
		}
	}

	for (i = 0; i < G.e; i++) {

		fscanf_s(fp, " %c", &t1, 1);
		fscanf_s(fp, " %c", &t2, 1);
		fscanf_s(fp, "%d", &power);

		start = FindNodeIndex_matrix(G, t1);
		end = FindNodeIndex_matrix(G, t2);

		if (start != -1 && end != -1) {
			G.edge[start][end] = power;
			G.edge[end][start] = power;
		}
		else {
			printf("error!\n");
			exit(-2);
		}
	}

	fclose(fp);
	return G;
}

void Prim(GMatrix M) {
	int LOWCOST[NUM];
	int CLOSSET[NUM];
	int MST[NUM] = { 0 };
	int index, min;
    int i,j;
	for (i = 0; i < M.n; i++) {
		LOWCOST[i] = M.edge[0][i];
		CLOSSET[i] = 0;
	}

	LOWCOST[0] = INT_MAX;

	for (i = 1; i < M.n; i++) {
		min = LOWCOST[0];
		index = 0;
		for (j = 0; j < M.n; j++) {
			if (LOWCOST[j] < min) {
				min = LOWCOST[j];
				index = j;
			}
		}
		LOWCOST[index] = INT_MAX;
		MST[index] = CLOSSET[index];
		for (j = 0; j < M.n; j++) {
			if (M.edge[index][j] < LOWCOST[j] && LOWCOST[j] < INT_MAX) {
				LOWCOST[j] = M.edge[index][j];
				CLOSSET[j] = index;
			}
		}
	}

	printf("Prim算法\n");
	for (i = 1; i < M.n; i++) {
		printf("%c %c,%d\n", M.node[MST[i]], M.node[i], MST[i]);
	}
	printf("\n");
}

void Prim_heap(GMatrix M) {
	int visited[NUM] = { 0 };
	int cnt = M.n;
	PQueue Q = CreatePQueue();
	int MST[NUM] = { 0 };
	int index;
	int parent;
    int i;
	visited[0] = 1; cnt--;
	for (i = 0; i < M.n; i++) {
		EnPQueue(M.edge[0][i], &Q, 0, i);
	}

	while (cnt && !PQueueIsEmpty(Q)) {
		index = TopPQueue(Q).child;
		parent = TopPQueue(Q).parent;
		if (!visited[index]) {
			visited[index] = 1; cnt--;
			MST[index] = parent;
			DePQueue(&Q);
			parent = index;
			for (i = 0; i < M.n; i++) {
				if (!visited[i]) {
					EnPQueue(M.edge[index][i], &Q, parent, i);
				}
			}
		}
		else DePQueue(&Q);
	}
	
	printf("堆进行优化的Prim算法\n");
	for (i = 1; i < M.n; i++) {
		printf("%c %c,%d\n", M.node[MST[i]], M.node[i], MST[i]);
	}
	printf("\n");
}

void Sort(Edge* arr, int num) {
	int i, j, flag = 1;
	Edge t;
	for (i = 0; i < num - 1 && flag; i++) {
		flag = 0;
		for (j = 0; j < num - i - 1; j++) {
			if (arr[j].power > arr[j + 1].power) {
				t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
				flag = 1;
			}
		}
	}
}

void Kruskal(GMatrix M) {
	Edge edgeset[NUM * NUM / 2];
	Edge mst[NUM];
	Set S;
	int i, j, k = 0, num = 0;
	for (i = 0; i < M.n; i++) {
		for (j = i; j < M.n; j++) {
			if (M.edge[i][j] != INF) {
				edgeset[k].power = M.edge[i][j];
				edgeset[k].start = i;
				edgeset[k].end = j;
				k++;
			}
		}
	}
	Sort(edgeset, k);
	InitUFSet(k, S);
	printf("Kruskal算法：\n");
	for (i = 0; i < k && num < M.n - 1; i++) {
		if (Find(edgeset[i].start, S) != Find(edgeset[i].end, S)) {
			printf("%c %c,%d\n", edgeset[i].power+65, edgeset[i].start+65, edgeset[i].end);
			mst[num].start = edgeset[i].start;
			mst[num].end = edgeset[i].end;
			mst[num].power = 0;
			Union(Find(edgeset[i].start, S), Find(edgeset[i].end, S), S);
			num++;
		}
	}

}

int main() {
	GMatrix M = CreateGMatrix_file();
	Prim(M);
	Prim_heap(M);
	Kruskal(M);
	return 0;
}
