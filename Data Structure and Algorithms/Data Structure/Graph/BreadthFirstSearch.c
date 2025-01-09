#include<stdio.h>
#include<stdbool.h>

#define MaxNodes 100
typedef struct 
{
    int data[MaxNodes];
 	int front;
	int rear;
}Quene;
 
void InitQuene(Quene* quene)
{
	quene->front = -1;
 	quene->rear = -1;
}
 
bool IsEmpty(Quene* quene)
{
 	return (quene->front == -1 && quene->rear == -1);
}
 
void Enquene(Quene* quene, int element)
{
 	if(quene->rear == MaxNodes)
	{
	 	printf("FULL\n");
	 	return;
	}
	 if(IsEmpty(quene))
	 	quene->front = 0;
	quene->rear++;
	quene->data[quene->rear] = element;
}
 
int Dequene(Quene* quene)
{
 	if(IsEmpty(quene))
	{
	 	printf("EMPTY\n");
	 	return -1;
	}
	int val = quene->data[quene->front];
	if(quene->front == quene->rear)
	{
		quene->front = -1;
		quene->rear = -1;
	}
	else
		quene->front++;
	return val;
}

void bfs(int graph[][MaxNodes], int NumNode, int StartNode)
{
	bool visited[MaxNodes] = {false};
	Quene quene;
	InitQuene(&quene);
	visited[StartNode] = true;
	Enquene(&quene, StartNode);
	while(!IsEmpty(&quene))
	{
		int current = Dequene(&quene);
		printf("%d ", current);
		for(int i = 0; i <= NumNode; i++)
		{
			if(graph[current][i] == 1 && !visited[i]) 
			{
				visited[i] = true;
				Enquene(&quene, i);
			}
		}
	}
	printf("\n");
}
 
int main()
{
	int t1[][MaxNodes] = {
		{0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1},
		{0, 1, 0, 1, 1, 1},
		{0, 0, 1, 0, 1, 0},
		{0, 0, 1, 1, 0, 1},
		{1, 1, 1, 0, 1, 0}};
	int NumNode = sizeof(t1) / sizeof(t1[0]);
	int StartNode = 0;
	bfs(t1, NumNode, StartNode);
	return 0;
}


//输出结果 0 1 5 2 4 3 