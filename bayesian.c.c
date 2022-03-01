#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  argc = 2;

  char *option = malloc(100 * sizeof(char));

  strcpy(option, argv[1]);

  if (strcmp(option, "-c1") == 0) {
    FILE *fin = fopen("bnet.in", "r");
    FILE *fout = fopen("bnet.out", "w");

    task1(fin, fout);

    fclose(fout);
    fclose(fin);
  }

  if (strcmp(option, "-c2") == 0) {
    FILE *fin = fopen("bnet.in", "r");
    FILE *fout = fopen("bnet.out", "w");

    task2(fin, fout);

    fclose(fout);
    fclose(fin);
  }

  free(option);
  return argc;
}