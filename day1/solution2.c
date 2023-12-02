#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>

size_t isnbrspelled(const char *substring) {
  const char *numberNames[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  for (int i = 0; i < 10; ++i) {
    if (strcmp(substring, numberNames[i]) == 0) {
      return i;
    }
  }
  return -1;
}

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

  int first;
  int last;
  int i;
  char c;

  size_t count = 0;

  while(getline(&line, &len, fp) != -1) {
    first = 0;
    i = 0;
    size_t lineLen = strlen(line);
    for (int i = 0; i < lineLen; i++) {
      c = line[i];
      if (isdigit(c)) {
        if (!first) {
          first = c - '0';
        }
        last = c - '0';
      } else {
        for (int j = 1; j <= 5; j++) {
          if (i + j <= lineLen) {
            char substring[j+1];
            strncpy(substring, &line[i], j);
            substring[j] = '\0';
            ssize_t number;
            if ((number = isnbrspelled(substring)) != -1) {
              if (!first) {
                first = number;
              }
              last = number;
            }
          }
        }
      }
    }
    printf("first: %d last: %d num: %zu\n", first, last, ++count);
    sum += first * 10 + last;
  }

  fclose(fp);

  if (line) {
    free(line);
  }

  printf("Sum: %d \n", sum);
}
