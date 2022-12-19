#include "s21_calculate.h"

int main(void) {
  stack* head = NULL;
  char* buffer = NULL;
  char* dnt = "(1+2)*3";
  buffer = s21_parcing_string(&head, dnt);
  if (buffer) {
    printf("%s\n", buffer);
    free(buffer);
  }
  // randomize();
  return 0;
}