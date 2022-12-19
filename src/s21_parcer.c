#include "s21_calculate.h"

char* s21_parcing_string(stack** head, char* str) {
  int i = 0, count = 0, func_count = 0, res = 0, priority = 0;
  // notation - хранит польскую запись с разделителями в виде '|'
  char* notation = (char*)calloc(512, sizeof(char));
  // func - буффер под функции
  char func[5] = {0};
  void* pointer = NULL;
  if (notation) {
    while (str[i] != '\0') {
      // Если встречаем число - заносим его в нотацию. Точку относим к числу
      if (isdigit(str[i]) || str[i] == '.') {
        while (isdigit(str[i]) || str[i] == '.') {
          notation[count++] = str[i++];
        }
        notation[count++] = SEPARATOR;
      }
      // Если встречаем функцию - заносим её в стек
      if (isalpha(str[i])) {
        func_count = 0;
        while (isalpha(str[i])) {
          func[func_count++] = str[i++];
        }
        func[func_count] = '\0';
        res = s21_push(head, func);
        func[0] = '\0';
      }
      // Если встречаем оператор - работает в зависимости от приоритетности и
      // заполненности стека
      if (strchr(OPERATORS, str[i]) && str[i] != '\0') {
        priority = s21_prioritization(str[i], *head);
        func[0] = str[i];
        func[1] = '\0';
        while (priority && str[i] != OPEN_BRACKET) {
          count = s21_import_to_pn(head, notation, &pointer, count);
          priority = s21_prioritization(str[i], *head);
        }
        i++;
        if (count >= 0) s21_push(head, func);
        func[0] = '\0';
        // vizual_stack(*head);
      }
      // Если встречаем закрывающую скобку - переносим из стека в выходную
      // строку операторы до момента нахождения открыващей скобки
      if (str[i] == CLOSE_BRACKET) {
        while (*(char*)(*head)->data != '(' && count != -1) {
          count = s21_import_to_pn(head, notation, &pointer, count);
        }
        if (*(char*)(*head)->data == '(') {
          res = s21_pop(head, &pointer);
          if (res != -1) free(pointer);
        }
        i++;
      }
    }
    while (*head) {
      count = s21_import_to_pn(head, notation, &pointer, count);
    }
    if (count >= 0) free(*head);
    notation[count - 1] = '\0';
  }
  return notation;
}

int s21_import_to_pn(stack** head, char* notation, void** pointer, int count) {
  int res = s21_pop(head, pointer);
  for (int j = 0; (*((char**)pointer))[j] != '\0' && res != -1; j++) {
    notation[count++] = (*((char**)pointer))[j];
  }
  notation[count++] = SEPARATOR;
  if (res != -1)
    free(*pointer);
  else
    count = -1;
  // vizual_stack(*head);
  return count;
}

int s21_prioritization(char str, stack* head) {
  int priority_str = 0, priority_stack = 0, res = 0;
  if (head != NULL) {
    priority_str = (strchr(&OPERATORS[0], str) - &OPERATORS[0]) / 3;
    priority_stack =
        (strchr(&OPERATORS[0], *(char*)(head)->data) - &OPERATORS[0]) / 3;
    if (priority_str <= priority_stack || priority_stack < 0) res = 1;
  }
  return res;
}

void randomize(void) {
  int i = 0;
  time_t t = 0;
  char* str = "123456789";
  char* str2 = "+-/*^";

  /* Intializes random number generator */
  srand((unsigned)time(&t));

  /* Print 5 random numbers from 0 to 49 */
  for (i = 0; i < 127; i++) {
    printf("%c", str[rand() % 9]);
    printf("%c", str2[rand() % 5]);
  }
}