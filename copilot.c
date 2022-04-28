#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include "stdbool.h"
struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
}Node;

typedef struct Employee NodeInfo;
typedef struct queue
{
	Node* head;
	Node* tail;
}Queue;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
void put(Queue* queue, NodeInfo* info);
bool isEmpty(Queue queue);
NodeInfo* get(Queue* queue);
void printInfo(NodeInfo* info);
void deleteQueue(Queue* queue);
void printList(Queue* queue);

void main()
{
	Queue queue = { .head = NULL, .tail = NULL };

	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			token = strtok(lineBuffer, sepList);
			code = atoi(token);
			name = strtok(NULL, sepList);
			dept = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			salary = atof(token);

			NodeInfo* info = createInfo(code, name, dept, salary);
			put(&queue, info);
		}

		/*	NodeInfo* info = get(&queue);*/
			//printInfo(info);
		printList(&queue);
		deleteQueue(&queue);
		printf("------------------\n The modified queue: \n");
		printList(&queue);

	}
}

//function 



void deleteQueue(Queue* queue)
{
	Node* node = queue->head;
	if (node->info->code % 2 == 0 && node->pNext == queue->tail) {
		free(node);
	}

	while (node->pNext != queue->tail) {

		if (node->pNext->info->code % 2 == 0) {
			Node* tmp = node->pNext;
			node->pNext = node->pNext->pNext;
			free(tmp);
		}
		node = node->pNext;
	}

	if (node->pNext->info->code % 2 == 0) {
		Node* tmp = node->pNext;
		node->pNext = node->pNext->pNext;
		free(tmp);
	}

}

bool isEmpty(Queue queue)
{
	return (queue.head == NULL && queue.tail == NULL);
}

NodeInfo* get(Queue* queue)
{
	NodeInfo* value = NULL;
	if (!isEmpty(*queue))
	{
		value = queue->head->info;
		Node* tmp = queue->head;
		if (queue->head == queue->tail)
			queue->head = queue->tail = NULL;
		else
			queue->head = tmp->pNext;
		free(tmp);
	}
	return value;
}

void put(Queue* queue, NodeInfo* info)
{
	Node* node = createNode(info);
	if (isEmpty(*queue))
		queue->head = queue->tail = node;
	else
	{
		queue->tail->pNext = node;
		queue->tail = node;
	}
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
}

NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}

Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}

//function to print list of nodes
void printList(Queue* queue)
{
    Node* node = queue->head;
    while (node != NULL)
    {
        printInfo(node->info);
        node = node->pNext;
    }
}

// void printList(Queue* queue) {
// 	Node* tmp = queue->head;

// 	while ((tmp->pNext) && (tmp->pNext->info != NULL)) {
// 		printf("Code: %d - Name: %s\n", tmp->info->code, tmp->info->name);
// 		tmp = tmp->pNext;

// 		if ((tmp->pNext == NULL) &&(tmp->info!=NULL)) {
// 			printf("Code: %d - Name: %s\n", tmp->info->code, tmp->info->name);
// 		}
// 	}
		
// }