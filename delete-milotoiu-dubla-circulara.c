#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

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
	struct node* pPrev;
}Node;

typedef struct Employee NodeInfo;
typedef struct node Queue;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/

void put(Queue**, NodeInfo*);
NodeInfo* get(Queue**);
NodeInfo* peek(const Queue*);
void printInfo(NodeInfo*);
void deleteEven(Queue** queueHead);


void main()
{
	Queue* queue = NULL;

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

		deleteEven(&queue);

		NodeInfo* info = NULL;
		while ((info = get(&queue)) != NULL)
			printInfo(info);
	}
}

void deleteEven(Queue** queueHead) {
	//variabila cu care verific daca reiau nodurile
	NodeInfo* check = NULL;
	//cat timp queue-ul nu e null
	while ((*queueHead))
	{
		//extrag informatia primului element
		NodeInfo* info = get(queueHead);
		//daca codul e par
		if (info->code % 2 == 0) {
			//sterg informatia
			free(info->dept);
			free(info->name);
			free(info);
		}
		//daca e impar
		else
		{
			//pun informatia la capatul listei
			put(queueHead, info);
			//daca check e null
			if (!check)
				//ia valoarea lui info (amandoi sunt pointeri, deci arata spre aceeasi chestie)
				//(se intampla o singura data, ca sa stiu cand sa ma opresc)
				check = info;
			//daca informatia din capul listei e egala cu check
			//(daca am ajuns la primul element bagat inapoi in lista)
			if ((*queueHead)->info == check) {
				//ies din while
				break;
			}
		}
	}
}


void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
}

NodeInfo* get(Queue** queueHead)
{
	NodeInfo* value = NULL;
	if (*queueHead != NULL)
	{
		value = (*queueHead)->info;
		Node* tmp = *queueHead;
		if (tmp->pNext != tmp && tmp->pPrev != tmp)
		{
			tmp->pNext->pPrev = tmp->pPrev;
			tmp->pPrev->pNext = tmp->pNext;
			*queueHead = tmp->pNext;
		}
		else
			*queueHead = NULL;
		free(tmp);
	}
	return value;
}

void put(Queue** queueHead, NodeInfo* info)
{
	Node* node = createNode(info);
	if (*queueHead == NULL)
	{
		node->pNext = node->pPrev = node;
		*queueHead = node;
	}
	else
	{
		node->pNext = *queueHead;
		node->pPrev = (*queueHead)->pPrev;

		(*queueHead)->pPrev->pNext = node;
		(*queueHead)->pPrev = node;
	}
}
NodeInfo* peek(const Queue*);


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
	node->pPrev = NULL;
	return node;
}