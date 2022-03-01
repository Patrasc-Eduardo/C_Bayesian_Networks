#include <stdio.h>
#include <stdlib.h>
#ifndef UTIL_H_
#define UTIL_H_

typedef struct ListNode{
	int key;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

typedef struct List{
	ListNode* head;
}List;

typedef List Queue;

typedef struct content{
	int pos;
	char* name;
	int* parent;
	int size_parent;
}Tcontent, *Pcontent;

typedef struct TNode{
	Pcontent content; 
	struct TNode *next;
}TNode, *ATNode;

typedef struct{
	int nn; 
	Pcontent* names;
	int* position;
	ATNode *adl;
}TGraph;

void task1(FILE* input, FILE* output);
void task2(FILE* input, FILE* output);
void getPositions(char* buff, int nr_nodes, Pcontent* names, int* position);
TGraph* createGraphAdjList(int numberOfNodes);
void destroyGraphAdjList2(TGraph * graph);
void destroyGraphAdjList(TGraph* graph);
void addEdgeList(TGraph* graph, char* v1, char* v2, Pcontent* names, int nrNodes);
int getIndex(Pcontent* names, char* node, int numberNodes);
int cycle(TGraph *graph);
void removeSpaces(char *str);
int cycle_aux(TGraph *graph, int *visited, int* prev, int s);
TGraph * step_1(TGraph *graph, int*position, Pcontent* names, int nr_nodes, int* size_position);
TGraph * step_2(TGraph *graph,  Pcontent* names);
TGraph * step_3(TGraph *graph, Pcontent* names);
TGraph * step_4(TGraph *graph, int*position, Pcontent* names, int* size_position);
TGraph * step_5(TGraph *graph, int*position, FILE* output, int* size_position);
List* dfsRecursive(TGraph* G, int s, int size);
List* createList(void);
void destroyList(List* list);
void push(List* list, int key);
#endif