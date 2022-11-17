#include <stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct {
	int n;
	int* visited;
	int** adj_mat;
} GraphType;

typedef struct {
	int top;
	int st_size;
	int* stack;
}StackType;

typedef struct {
	int* queue;
	int que_size;
	int front, rear;
}QueueType;

void makeGraph(GraphType* gr, int no) {
	gr->n = no;
	gr->visited = (int*)malloc(sizeof(int) * (no + 1));
	gr->adj_mat = (int**)malloc((sizeof(int*) * (no + 1)));

	for (int i = 1; i <= no; i++) {
		gr->adj_mat[i] = (int*)malloc(sizeof(int) * (no + 1));
		gr->visited[i] = 0;
	}

	for (int i = 1; i <= no; i++) {
		gr->visited[i] = 0;
		for (int j = 1; j <= no; j++)
			gr->adj_mat[i][j] = 0;
	}
}

void addGraphEdge_bothside(GraphType* gr, int a, int b)
{
	gr->adj_mat[a][b] = 1;
	gr->adj_mat[b][a] = 1;
}

void addGraphEdge_oneside(GraphType* gr, int a, int b) {
	gr->adj_mat[a][b] = 1;
}

void init_visited(GraphType* gr) {
	for (int i = 0; i <= gr->n; i++)
		gr->visited[i] = 0;

}

int dequeue(QueueType* que) {
	if (que->rear == que->front) {
		return NULL;
	}
	que->front = (que->front + 1);
	return que->queue[que->front];
}

void enqueue(QueueType* que, int n) {
	que->rear = que->rear + 1;
	que->queue[que->rear] = n;
}

void st_push(StackType* st, int n)
{
	if (st->top == st->st_size - 1)
		return;		// full
	st->stack[++(st->top)] = n;
}

int st_pop(StackType* st)
{
	if (st->top == -1)
		return NULL;		// empty
	return st->stack[(st->top)--];
}

void DFS_stack(GraphType* gr, int v)
{
	StackType st;
	int w;

	st.top = -1;
	st.st_size = gr->n + 1;
	st.stack = (int*)malloc(sizeof(int) * st.st_size);
	st_push(&st, v);
	gr->visited[v] = 1;		 
	while (st.top != -1) {
		v = st_pop(&st);
		printf("%d ", v);		
		for (w = gr->n; w >= 1; w--) 		
			if (gr->adj_mat[v][w] && !gr->visited[w]) {
				st_push(&st, w);
				gr->visited[w] = 1;		
			}
	}
}

void BFS_queue(GraphType* gr, int v) {
	QueueType que;
	int w;

	que.front = que.rear = 0;
	que.que_size = gr->n + 1;
	que.queue = (int*)malloc(sizeof(int) * que.que_size);
	enqueue(&que, v);
	gr->visited[v] = 1;

	while (que.front != que.rear) {
		v = dequeue(&que);
		printf("%d ", v);

		for (w = 1; w <= gr->n; w++) {
			if (gr->adj_mat[v][w] && !gr->visited[w]) {
				gr->visited[w] = 1;
				enqueue(&que, w);
			}
			
		}

	}

}

int main()
{

	GraphType gr1;
	int no, no2, DFS_BFS, v, edge;
	int start, end;

	no = 0;

	while (1) {
		no2 = -1;
		DFS_BFS = -1;

		printf("노드의 개수 (-1입력시 종료) >> ");
		scanf_s("%d", &no);
		if (no == -1) break;

		printf("간선의 개수 >> ");
		scanf_s("%d", &edge);

		//입력오류시 루프
		while (no2!=0 && no2!=1) {
			printf("무방향 그래프면 0입력, 방향그래프면 1입력 >> ");
			scanf_s("%d", &no2);
			
			if (no2 != 0 && no2 != 1) {
				printf("\n잘못입력했습니다\n");
			}
		}
		
		makeGraph(&gr1, no);	//그래프 생성

		//무방향 그래프 입력
		if (no2 == 0) {
			for (int i = 0; i < edge; i++) {
				printf("시작 >> ");
				scanf_s("%d", &start);
				printf("끝 >> ");
				scanf_s("%d", &end);
				
				addGraphEdge_bothside(&gr1, start, end);
			}
		}

		//방향 그래프 입력
		else if (no2 == 1) {
			for (int i = 0; i < edge; i++) {
				printf("시작 >> ");
				scanf_s("%d", &start);
				printf("끝 >> ");
				scanf_s("%d", &end);

				addGraphEdge_oneside(&gr1, start, end);
			}
		}
		
		/*
		addGraphEdge(&gr1, 1, 2);
		addGraphEdge(&gr1, 1, 7);
		addGraphEdge(&gr1, 2, 3);
		addGraphEdge(&gr1, 2, 6);
		addGraphEdge(&gr1, 3, 1);
		addGraphEdge(&gr1, 3, 4);
		addGraphEdge(&gr1, 4, 5);
		*/
		//입력오류시 루프
		printf("시작노드를 입력 1~%d >> ", no);
		scanf_s("%d", &v);

		printf("\n");
		//DFS로 출력
		printf("DFS 경로 >> ");
		DFS_stack(&gr1, v);
		printf("\n\n");

		//그래프 visited 초기화
		init_visited(&gr1);

		//BFS로 출력
		printf("BFS 경로 >> ");
		BFS_queue(&gr1, v);
		
		printf("\n\n");
		printf("아무키나 누르세요 ...");
		_getch();
		system("cls");
	}
}

