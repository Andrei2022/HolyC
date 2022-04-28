#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <stdbool.h>

#define FILE_NAME "Data.txt"
#define BUFFER_SIZE 128

typedef struct Employee {
	int code;
	char* name;
	char* dep;
	double salary;
} NodeInfo, Employee;

typedef struct List {
	Employee* info;
	struct List* pNext;
} List, Node;

bool deleteEven(List**);
void addList(List**, Employee*);
Node* createNode(Employee*);
void printList(List*);

void main() {
	FILE* file = fopen(FILE_NAME, "r");
	List* tail = NULL;
	char buffer[BUFFER_SIZE], sep_list[] = ",\n", * token;
	int index = 0;

	if (file) {
		printf("File \"%s\" opened!\n", FILE_NAME);
		while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
			Employee* emp = (Employee*)malloc(sizeof(Employee));
			token = strtok(buffer, sep_list);
			emp->code = atoi(token);
			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);
			token = strtok(NULL, sep_list);
			emp->dep = (char*)malloc(strlen(token) + 1);
			strcpy(emp->dep, token);
			token = strtok(NULL, sep_list);
			emp->salary = atof(token);
			index++;

			addList(&tail, emp);

			//printf("\nEmployee %d %s %s %f", emp->code, emp->name, emp->dep, emp->salary);
		}

		fclose(file);

		printList(tail);

		// deleting the even code employees
		bool del;
		for (int i = 0; i < index && tail != NULL; i++) {
			del = deleteEven(&tail);
			if (tail != NULL && del == false)
				tail = tail->pNext;
		}

		printf("\n\n\nAfter we deleted the employees with even codes\n\n");
		printList(tail);
	}
	else {
		printf("File \"%s\" could not be opened.\n", FILE_NAME);
	}

	int a = 2;
}

// function that creates a Node that will later be added to the list
Node* createNode(Employee* info) {
	Node* toReturn = (Node*)malloc(sizeof(Node));
	toReturn->info = info;
	toReturn->pNext = NULL;

	return toReturn;
}

// function that adds an element at the end of the list
void addList(List** tail, Employee* info) {
	Node* toAdd = createNode(info);
	// if the list is empty
	if (*tail == NULL) {
		// when we have only one element the circularity with be with itself
		*tail = toAdd;
		(*tail)->pNext = *tail;
	}
	else {	// we have elements in the list
		// if we have only one element
		if ((*tail) == (*tail)->pNext) {
			(*tail)->pNext = toAdd;
			toAdd->pNext = *tail;
			*tail = toAdd;	// we move the tail
		}
		else {
			// we have more than one element
			toAdd->pNext = (*tail)->pNext;
			(*tail)->pNext = toAdd;
			*tail = toAdd;
		}
	}
}

// function that deletes the head of the list (tail->pNext) IF the code is even; 
// this way we avoid having to go through the list again to assign a new tail after deletion
bool deleteEven(List** tail) {
	bool deleted = false;
	if (*tail != NULL) {
		if ((*tail)->pNext->info->code % 2 == 0) {
			Node* toDelete = (*tail)->pNext;
			// if the node we want to delete is the only node in the structure
			if ((*tail) == (*tail)->pNext) {
				free(toDelete->info->name);
				free(toDelete->info->dep);
				free(toDelete->info);
				free(toDelete);
				*tail = (*tail)->pNext = NULL;
			}
			else {	// if there are two or more nodes
				(*tail)->pNext = (*tail)->pNext->pNext;
				free(toDelete->info->name);
				free(toDelete->info->dep);
				free(toDelete->info);
				free(toDelete);
			}
			deleted = true;
		}
	}
	return deleted;
}

// function for printing the list;
// displays a message if the list is empty
void printList(List* tail) {
	if (tail != NULL) {
		Node* saved = tail->pNext;
		tail = tail->pNext;
		printf("\nEmployee - Code: %d; Name: %s; Department: %s; \n\tSalary: %.3f", tail->info->code, tail->info->name, tail->info->dep, tail->info->salary);
		while (tail->pNext != saved) {
			tail = tail->pNext;
			printf("\nEmployee - Code: %d; Name: %s; Department: %s; \n\tSalary: %.3f", tail->info->code, tail->info->name, tail->info->dep, tail->info->salary);
		}
	}
	else
		printf("\nList is empty!\n");
}