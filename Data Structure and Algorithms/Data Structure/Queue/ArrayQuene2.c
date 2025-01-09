#include<stdio.h>

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
 
int IsEmpty(Quene* quene)
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

int main()
{
    Quene aq;
	InitQuene(&aq);
    Enquene(&aq, 3);
    Enquene(&aq, 5);
    Enquene(&aq, 4);
    printf("%d\n", Dequene(&aq));
    return 0;
}