#include "s21_calculate.h"

int main(void) {
  stack* head = NULL;
  stack* num = NULL;
  double result = 0;
  char dnt[256] = {0};
  printf("Введите выражение: ");
  scanf("%s", dnt);
  // char* dnt = "+1";
  int error = s21_parcing_string(&head, &num, dnt, &result);
  if (error != -1) {
    printf("%lf\n", result);
  }
  // randomize();
  // char a[10] = "abcd";
  // s21_insert(a, "oz", 2);
  // printf("str = %s\n", a);
  return 0;
}