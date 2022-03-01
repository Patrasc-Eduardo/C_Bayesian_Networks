#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_spaces(char *str) {
  int count = 0;
  for (size_t i = 0; i < strlen(str); i++)
    if (str[i] == ' ')
      count++;

  return count;
}

void printGraph(TGraph *graph, Pcontent *names) {
  printf("\n");
  printf("#####################################################################"
         "#######\n");
  for (int i = 0; i < graph->nn; i++) {
    printf("%s[%d]:", names[i]->name, names[i]->pos);
    ATNode aux = graph->adl[i];
    while (aux) {
      printf("%s(%d)", aux->content->name, aux->content->pos);
      aux = aux->next;
    }
    printf("\n");
  }
  printf("#####################################################################"
         "#######\n");
}

void getPositions(char *buff, int nr_nodes, Pcontent *names, int *position) {

  char *x = calloc(50, sizeof(char));
  char *y = calloc(50, sizeof(char));

  sscanf(buff, "%s ; %s |", x, y); // citim variabilele principale

  y[strcspn(y, "|")] = '\0'; // stergem caracterul "|" din cea de a doua variabila

  do {
    buff++;
  } while (buff[0] != '|');
  buff++; // bufferul contine acum tot ce este dupa "|"

  if (strlen(buff) == 1) { // daca nu avem variabile de observare

    for (int i = 0; i < nr_nodes; i++) { // actualizam vectorul de pozitii care o sa contina numai 0 si 1
      if (strcmp(names[i]->name, x) == 0)
        position[names[i]->pos]++;
      if (strcmp(names[i]->name, y) == 0)
        position[names[i]->pos]++;
    }

    free(x);
    free(y);
    return;
  } else { // daca exista variabile de observare

    for (int i = 0; i < nr_nodes; i++) { // actualizam vectorul de pozitii care o sa contina numai 0 si 1
      if (strcmp(names[i]->name, x) == 0)
        position[names[i]->pos]++;
      if (strcmp(names[i]->name, y) == 0)
        position[names[i]->pos]++;
    }

    int size = count_spaces(buff) + 1;

    char **variables = malloc(size * sizeof(char *));

    for (int i = 0; i < size; i++) {
      char *aux = calloc(50, sizeof(char));
      sscanf(buff, "%s ", aux);

      size_t k = 0;
      while (k < strlen(aux) + 1) {
        buff++;
        k++;
      }
      variables[i] = aux;
    }

    for (int i = 0; i < size; i++) { // actualizam vectorul de pozitii care o sa contina 0 1 si 2
      for (int j = 0; j < nr_nodes; j++) {
        if (strcmp(names[j]->name, variables[i]) == 0)
          position[names[j]->pos] = 2;
      }
    }

    for (int i = 0; i < size; i++) {
      free(variables[i]);
    }
    free(variables);
    free(x);
    free(y);
    return;
  }
  return;
}

List *createList(void) {
  List *newList = (List *)malloc(sizeof(List));
  newList->head = (ListNode *)malloc(sizeof(ListNode));
  newList->head->key = -1;
  newList->head->next = newList->head->prev = newList->head;
  return newList;
}
void destroyList(List *list) {
  ListNode *it = list->head->next;
  while (it != list->head) {
    ListNode *aux = it;
    it = it->next;
    free(aux);
  }
  free(list->head);
  free(list);
}

void push(List *list, int key) {
  ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
  newNode->key = key;

  newNode->next = list->head->next;
  newNode->prev = list->head;

  list->head->next->prev = newNode;
  list->head->next = newNode;
}

int contains(List *list, int *elem, int size) {

  ListNode *currentNode;
  int count = 0;

  currentNode = list->head->next;

  while (currentNode != list->head) {

    for (int i = 0; i < size; i++) {

      if (elem[currentNode->key]) {
        count++;
      }
    }
    currentNode = currentNode->next;
  }

  if (count)
    return 1;
  return 0;
}

int isListEmpty(List *list) { return list->head->next == list->head; }
Queue *createQueue(void) { return createList(); }
void destroyQueue(Queue *queue) { destroyList(queue); }
void enqueue(Queue *queue, int key) { push(queue, key); }
void dequeue(Queue *queue) {
  ListNode *aux = queue->head->prev;
  queue->head->prev = queue->head->prev->prev;
  queue->head->prev->next = queue->head;
  free(aux);
}

int isQueueEmpty(Queue *queue) { return isListEmpty(queue); }
int front(Queue *queue) { return queue->head->prev->key; }

TGraph *createGraphAdjList(int numberOfNodes) {

  TGraph *graph = (TGraph *)malloc(sizeof(TGraph));

  graph->nn = numberOfNodes;
  graph->position = NULL;
  graph->names = NULL;
  graph->adl = (ATNode *)malloc(numberOfNodes * sizeof(ATNode));

  for (int i = 0; i < graph->nn; i++) {

    graph->adl[i] = NULL;
  }

  return graph;
}

void destroyGraphAdjList2(TGraph *graph) { // functia de free pentru taskul 2

  for (int i = 0; i < graph->nn; i++) {
    ATNode pos = graph->adl[i];
    while (pos) {
      ATNode aux = pos;
      pos = pos->next;
      free(aux->content->name);
      free(aux->content->parent);
      free(aux->content);
      free(aux);
    }
  }
  free(graph->adl);
  for (int i = 0; i < graph->nn; i++) {
    free(graph->names[i]->name);
    free(graph->names[i]->parent);
    free(graph->names[i]);
  }
  free(graph->names);
  free(graph->position);
  free(graph);
}

void destroyGraphAdjList(TGraph *graph) { // functia de free pentru taskul 1

  for (int i = 0; i < graph->nn; i++) {
    ATNode pos = graph->adl[i];
    while (pos) {
      ATNode aux = pos;
      pos = pos->next;
      free(aux->content->name);
      free(aux->content->parent);
      free(aux->content);
      free(aux);
    }
  }
  free(graph->adl);
  free(graph);
}

void addEdgeList(TGraph *graph, char *v1, char *v2, Pcontent *names,
                 int nrNodes) {
  ATNode cell_2 = (ATNode)malloc(sizeof(TNode));

  cell_2->content = malloc(sizeof(Tcontent));
  cell_2->content->parent = calloc(nrNodes, sizeof(int));

  int index_cell_1 = getIndex(names, v1, nrNodes); // preluam indexul in fucntie de vectorul "names"

  cell_2->content->name = v2;
  cell_2->content->pos = getIndex(names, v2, nrNodes);
  cell_2->next = NULL;

  names[cell_2->content->pos]->parent[index_cell_1] = 1; // actualizam vectorul de parinti
  names[cell_2->content->pos]->size_parent++;

  cell_2->next = graph->adl[index_cell_1]; // adaugma "unidirectional" pentru a fi graf orientat
  graph->adl[index_cell_1] = cell_2;
}

void removeEdgeList(TGraph *graph, int v1, int v2) {

  TNode *it = graph->adl[v1];
  TNode *prev = NULL;

  while (it != NULL && it->content->pos != v2) {
    prev = it;
    it = it->next;
  }

  if (it == NULL)
    return;

  if (prev != NULL)
    prev->next = it->next;
  else
    graph->adl[v1] = it->next;

  free(it->content->name);
  free(it->content->parent);
  free(it->content);
  free(it);
}

int getIndex(Pcontent *names, char *node, int numberNodes) {
  for (int i = 0; i < numberNodes; i++) {
    if (strcmp(names[i]->name, node) == 0)
      return names[i]->pos;
  }
  return -1;
}

int cycle_aux(TGraph *graph, int *visited, int *prev, int v) {

  if (visited[v] == 0) {
    visited[v] = 1;
    prev[v] = 1;

    ATNode curr = graph->adl[v];

    while (curr) {
      if (!visited[curr->content->pos] &&
          cycle_aux(graph, visited, prev, curr->content->pos))
        return 1;
      else if (prev[curr->content->pos])
        return 1;
      curr = curr->next;
    }
  }
  prev[v] = 0;
  return 0;
}

int cycle(TGraph *graph) {

  int *visited = calloc(graph->nn, sizeof(int));
  int *prev = calloc(graph->nn, sizeof(int));

  for (int i = 0; i < graph->nn; i++) {
    if (cycle_aux(graph, visited, prev, i)) {
      free(visited);
      free(prev);
      return 1;
    }
  }
  free(visited);
  free(prev);
  return 0;
}

void dfsRecHelper(TGraph *graph, int *visited, List *path, int s) {

  visited[s] = 1;

  push(path, s);

  ATNode pos = graph->adl[s];

  while (pos) {

    int aux = pos->content->pos;

    if (visited[aux] != 1) {

      dfsRecHelper(graph, visited, path, aux);
    }

    pos = pos->next;
  }
}

List *dfsRecursive(TGraph *graph, int s, int size) {

  int *visited = calloc(size, sizeof(int));
  List *path = createList();

  if (graph->adl[s] == NULL) {
    push(path, s);
    free(visited);
    return path;
  }

  dfsRecHelper(graph, visited, path, s);

  free(visited);
  return path;
}

int not_duplicate(TGraph *graph, int aux, int i) {

  ATNode aux2 = graph->adl[aux];

  while (aux2) {

    if (aux2->content->pos == i)
      return 0;
    aux2 = aux2->next;
  }

  return 1;
}

int contains2(TGraph *graph, int i, int *position) {
  ATNode pos = graph->adl[i];

  while (pos != NULL) {
    if (position[pos->content->pos] == 2) {

      return 1;
    }
    pos = pos->next;
  }

  return 0;
}

TGraph *step_1(TGraph *graph, int *position, Pcontent *names, int nr_nodes,
               int *size_position) {

  int elim = 0;

  for (int i = 0; i < nr_nodes; i++) {

    List *path2 = dfsRecursive(graph, i - elim, nr_nodes);

    if (contains(path2, position, nr_nodes) == 0) { // daca nu apartine grafului ancestral
      for (int j = 0; j < nr_nodes; j++) {
        if (graph->adl[j] != NULL) {
          removeEdgeList(graph, j, i); // eliminal orice muchie care duce spre acest nod
        }
      }
      //eliminam nodul
      ATNode pos = graph->adl[i - elim];
      while (pos) {
        ATNode tmp = pos;
        pos = pos->next;
        free(tmp->content->name);
        free(tmp->content->parent);
        free(tmp->content);
        free(tmp);
      }

      free(names[i - elim]->name);
      free(names[i - elim]->parent);
      free(names[i - elim]);

      for (int k = i - elim; k < (graph->nn - 1); k++) {

        graph->adl[k] = graph->adl[k + 1];
        names[k] = names[k + 1];
        names[k]->pos--;
      }
      graph->nn--;

      for (int k = i - elim; k < (*size_position) - 1; k++) { //modificam vectorul de pozitii
        position[k] = position[k + 1];
      }
      (*size_position)--;

      elim++;
    }
    destroyList(path2);
  }

  for (int i = 0; i < graph->nn; i++) { // restituim indecsii
    ATNode aux = graph->adl[i];
    while (aux) {
      aux->content->pos = getIndex(names, aux->content->name, graph->nn);
      aux = aux->next;
    }
  }

  //printGraph(graph, names);
  graph->names = names;
  graph->position = position;
  return graph;
}

TGraph *step_2(TGraph *graph, Pcontent *names) {

  for (int i = 0; i < graph->nn; i++) { // verificam daca are 2 sau mai multi parinti
    for (int j = 0; j < graph->nn; j++) {
      if (names[i]->parent[j]) {
        for (int k = j + 1; k < graph->nn; k++) {
          if (names[i]->parent[k]) { // daca da, adaugam o muchie intre parinti

            if (not_duplicate(graph, j, k)) {
              char *name_j = strdup(names[j]->name);
              char *name_k = strdup(names[k]->name);
              addEdgeList(graph, name_j, name_k, names, graph->nn); 
              free(name_j);
            }
            if (not_duplicate(graph, k, j)) {

              char *name_j = strdup(names[j]->name);
              char *name_k = strdup(names[k]->name);
              addEdgeList(graph, name_k, name_j, names, graph->nn);
              free(name_k);
            }
          }
        }
      }
    }
  }

  //printGraph(graph, names);
  graph->names = names;
  return graph;
}

int not_duplicate_2(TGraph *graph, int aux, int i) {
  ATNode current = graph->adl[aux];
  while (current) {
    if (current->content->pos == i)
      return 0;
    current = current->next;
  }
  return 1;
}

TGraph *step_3(TGraph *graph, Pcontent *names) {

  for (int i = 0; i < graph->nn; i++) {
    ATNode aux = graph->adl[i];

    while (aux) {
      if (not_duplicate_2(graph, aux->content->pos, i)) { // transformam in neorientat
        char *name = strdup(names[i]->name);
        addEdgeList(graph, aux->content->name, name, names, graph->nn);
      }
      aux = aux->next;
    }
  }

  //printGraph(graph, names);
  graph->names = names;
  return graph;
}

TGraph *step_4(TGraph *graph, int *position, Pcontent *names,
               int *size_position) {

  int size = graph->nn;
  int elim = 0;

  for (int i = 0; i < size; i++) {

    if (contains2(graph, i, position)) {
      for (int j = 0; j < graph->nn; j++) {
        if (position[j] == 2) { // daca nodul este variabila secundara, aplicam procesul de eliminare ca in step_1()
          removeEdgeList(graph, i, j);
        }
      }
    }
  }

  for (int i = 0; i < graph->nn; i++) {
    if (position[i - elim] == 2) {

      ATNode pos = graph->adl[i - elim];
      while (pos) {
        ATNode tmp = pos;
        pos = pos->next;
        free(tmp->content->name);
        free(tmp->content->parent);
        free(tmp->content);
        free(tmp);
      }

      free(names[i - elim]->name);
      free(names[i - elim]->parent);
      free(names[i - elim]);

      for (int k = i - elim; k < graph->nn - 1; k++) {
        graph->adl[k] = graph->adl[k + 1];

        names[k] = names[k + 1];

        names[k]->pos--;
      }

      graph->nn--;

      for (int k = i - elim; k < (*size_position) - 1; k++) {

        position[k] = position[k + 1];
      }
      (*size_position)--;
      elim++;
    }

    for (int i = 0; i < graph->nn; i++) {
      ATNode aux = graph->adl[i];
      while (aux) {
        aux->content->pos = getIndex(names, aux->content->name, graph->nn);
        aux = aux->next;
      }
    }
  }

  //printGraph(graph, names);
  graph->names = names;
  graph->position = position;
  return graph;
}

TGraph *step_5(TGraph *graph, int *position, FILE *output, int *size_position) {

  int found = 0;
  int A = 0, B = 0;
  int indep = 1;

  for (int i = 0; i < graph->nn; i++) { // folosim vectorul de pozitii pentru a restitui variabilele principale
    if (position[i] == 1 && found == 0) {
      A = i;
      found = 1;
      continue;
    }
    if (position[i] == 1 && found == 1) {
      B = i;
      found = 2;
    }
  }

  if (found != 2) { // daca o variabila principala a disparut, automat rezulta independenta
    fprintf(output, "independente\n");
    return graph;
  }

  List *path2 = dfsRecursive(graph, A, (*size_position)); // cream "path-ul" pornind din prima variabila principala

  ListNode *aux = path2->head->next;

  while (aux != path2->head) {
    printf("%d ", aux->key);

    if (aux->key == B || path2->head->key == B) // daca in acest path, se afla a doua variabila principala atunci -> neindependente
      indep = 0;
    aux = aux->next;
  }
  destroyList(path2);

  if (indep)
    fprintf(output, "independente\n");
  else
    fprintf(output, "neindependente\n");

  graph->position = position;
  return graph;
}