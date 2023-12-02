#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>

int main() {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int sum = 0;

  fp = fopen("input.txt", "r");

  if (fp == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

  char first;
  char last;
  int i;
  char c;

  while(getline(&line, &len, fp) != -1) {
    first = 0;
    i = 0;
    size_t lineLen = strlen(line);
    while(i < lineLen) {
      c = line[i++];
      if (isdigit(c)) {
        if (!first) {
          first = c;
        }
        last = c;
      }
    }

    sum += (first - '0') * 10 + (last - '0');
  }

  fclose(fp);

  if (line) {
    free(line);
  }

  printf("Sum: %d \n", sum);
}



