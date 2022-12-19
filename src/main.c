#include "s21_calculate.h"

int main(void) {
  stack* head = NULL;
  char* buffer = NULL;
  char dnt[256] = {0};
  printf("Введите выражение: ");
  scanf("%s", dnt);
  buffer = s21_parcing_string(&head, dnt);
  if (buffer) {
    printf("%s\n", buffer);
    free(buffer);
  }
  // randomize();
  return 0;
}