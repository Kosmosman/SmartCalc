#include "s21_calculate.h"

int s21_parcing_string(stack** head, char* str) {
  int i = 0, count = 0, func_count = 0;
  // notation - хранит польскую запись с разделителями в виде '|'
  char notation[512] = {0};
  // func - буффер под функции
  char func[5] = {0};
  char* p = NULL;
  while (str[i] != '\0') {
    // Если встречаем число - заносим его в нотацию. Точку относим к числу
    if (isdigit(str[i]) || str[i] == '.') {
      while (isdigit(str[i])) {
        notation[count++] = str[i++];
      }
      notation[count++] = '|';
    }
    // Если встречаем функцию - заносим её в стек
    if (isalpha(str[i])) {
      func_count = 0;
      while (isalpha(str[i])) {
        func[func_count++] = str[i++];
      }
      func[func_count] = '\0';
      s21_push(head, func);
      func[0] = '\0';
    }
    // Если встречаем оператор - работает в зависимости от приоритетности и
    // заполненности стека
    if (strchr(OPERATORS, str[i])) {
      if (*head != NULL) {
        if ((strchr(OPERATORS, str[i]) - &OPERATORS) >
            (strchr(OPERATORS, (*head)->data) - &OPERATORS)) {
          func[0] = str[i++];
          func[1] = '\0';
          s21_push(head, func);
          func[0] = '\0';
        }
      }
    }
  }
}