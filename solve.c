#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1(FILE *input, FILE *output) {
  int nr_nodes, nr_edges;
  Pcontent *names = NULL;
  TGraph *graph = NULL;

  fscanf(input, "%d %d\n", &nr_nodes, &nr_edges);

  names = malloc(nr_nodes * sizeof(Pcontent));

  for (int i = 0; i < nr_nodes; i++) {
    char *buff = calloc(100, sizeof(char));
    fscanf(input, "%s", buff);
    names[i] = malloc(sizeof(Tcontent));
    names[i]->name = buff;
    names[i]->pos = i;
    names[i]->parent = malloc(nr_nodes * sizeof(int));
  }

  graph = createGraphAdjList(nr_nodes);

  for (int i = 0; i < nr_edges; i++) {
    char *v1 = calloc(100, sizeof(char));
    char *v2 = calloc(100, sizeof(char));
    fscanf(input, "%s %s", v1, v2);

    addEdgeList(graph, v1, v2, names, nr_nodes);
    free(v1);
  }

  if (cycle(graph) == 1)
    fprintf(output, "imposibil\n");
  else
    fprintf(output, "corect\n");

  for (int i = 0; i < nr_nodes; i++) {
    free(names[i]->name);
    free(names[i]->parent);
    free(names[i]);
  }
  free(names);
  destroyGraphAdjList(graph);
}

void task2(FILE *input, FILE *output) {

  int nr_nodes = 0, nr_edges = 0;
  int numInter = 0;

  fscanf(input, "%d %d\n", &nr_nodes, &nr_edges);

  for (int i = 0; i < nr_nodes; i++) {
    char *buff = calloc(100, sizeof(char));
    fscanf(input, "%s", buff);
    free(buff);
  }

  for (int i = 0; i < nr_edges; i++) {
    char *v1 = calloc(100, sizeof(char));
    char *v2 = calloc(100, sizeof(char));
    fscanf(input, "%s %s", v1, v2);
    free(v1);
    free(v2);
  }

  fscanf(input, "%d\n", &numInter);

  for (int i = 0; i < numInter; i++) {

    TGraph *graph = NULL;
    Pcontent *names = NULL;
    char *buff = NULL;
    int *position = NULL;
    int *size_position = NULL;

    fseek(input, 0, SEEK_SET);

    fscanf(input, "%d %d\n", &nr_nodes, &nr_edges);

    names = malloc(nr_nodes * sizeof(Pcontent));

    for (int i = 0; i < nr_nodes; i++) {
      char *buff = calloc(100, sizeof(char));
      fscanf(input, "%s", buff);
      names[i] = malloc(sizeof(Tcontent));
      names[i]->name = buff;
      names[i]->pos = i;
      names[i]->parent = calloc(nr_nodes, sizeof(int));
    }

    graph = createGraphAdjList(nr_nodes);

    graph->names = names;

    for (int i = 0; i < nr_edges; i++) {
      char *v1 = calloc(100, sizeof(char));
      char *v2 = calloc(100, sizeof(char));
      fscanf(input, "%s %s", v1, v2);

      addEdgeList(graph, v1, v2, names, nr_nodes);
      free(v1);
    }

    int aux3 = 0;
    fscanf(input, "%d\n", &aux3);

    buff = calloc(100, sizeof(char));

    for (int k = 0; k <= i; k++) {
      fgets(buff, 100, input);
    }

    position = calloc(nr_nodes, sizeof(int));

    getPositions(buff, nr_nodes, names, position);
    graph->position = position;
    size_position = &nr_nodes;

    graph =
        step_1(graph, graph->position, graph->names, nr_nodes, size_position);
    graph = step_2(graph, names);
    graph = step_3(graph, names);
    graph = step_4(graph, graph->position, graph->names, size_position);
    graph = step_5(graph, graph->position, output, size_position);

    free(buff);
    destroyGraphAdjList2(graph);
  }
  return;
}
