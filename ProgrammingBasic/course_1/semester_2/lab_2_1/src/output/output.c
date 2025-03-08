#include "output.h"

#include <stdio.h>

void output_to_stdout(const char *message) {
  if (message) {
    printf("%s\n", message);
  }
}

void output_to_stderr(const char *message) {
  if (message) {
    fprintf(stderr, "%s\n", message);
  }
}
