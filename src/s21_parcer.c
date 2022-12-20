#include "s21_calculate.h"

/// @brief Функция преобразования входной строки в ОПЗ
/// @param head Указатель на верхушку стека
/// @param str Подаваемая на вход строка
/// @return Возвращает указатель на строку с ОПЗ
char* s21_parcing_string(stack** head, stack** num, char* str) {
  int i = 0, count = 0, func_count = 0, res = 0, priority = 0;
  double ansver = 0;
  void *num1 = 0, *num2 = 0;
  // notation - хранит польскую запись с разделителями в виде '|'
  char* notation = (char*)calloc(256, sizeof(char));
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
        s21_push(num, notation);
        s21_zero_func(notation, &count);
      }
      // Если встречаем функцию - заносим её в стек
      if (isalpha(str[i])) {
        while (isalpha(str[i])) func[func_count++] = str[i++];
        res = s21_push(head, func);
        s21_zero_func(func, &func_count);
      }
      // Если встречаем оператор - работает в зависимости от приоритетности и
      // заполненности стека
      if (strchr(OPERATORS, str[i]) && str[i] != '\0') {
        priority = s21_prioritization(str[i], *head);
        func[func_count++] = str[i++];
        while (priority && func[0] != OPEN_BRACKET) {
          s21_pop(num, &num2);
          s21_pop(num, &num1);
          count = s21_import_to_pn(head, notation, &pointer, count);
          priority = s21_prioritization(func[0], *head);
        }
        if (count >= 0) s21_push(head, func);
        s21_zero_func(func, &func_count);
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
          pointer = NULL;
        }
        i++;
      }
    }
    while (*head) {
      count = s21_import_to_pn(head, notation, &pointer, count);
    }
    if (count >= 0) free(*head);
    notation[count - 1] = '\0';
    notation = (char*)realloc(notation, strlen(notation) * sizeof(char));
  }
  return notation;
}

/// @brief Запись операции/функции в строку ОПЗ
/// @param head Указатель на верхушку стека
/// @param notation Указатель на строку с ОПЗ
/// @param pointer Указатель на данные, которые мы записываем по ОПЗ
/// @param count Конечный индекс строки с ОПЗ
/// @return Возвращает -1 в случае невыделения памяти под временную структуру
int s21_import_to_pn(stack** head, char* notation, void** pointer, int count) {
  int res = s21_pop(head, pointer);
  if (res == STR_TYPE) {
    for (int j = 0; (*((char**)pointer))[j] != '\0' && res != -1; j++) {
      notation[count++] = (*((char**)pointer))[j];
    }
  } else if (res == CHAR_TYPE) {
    notation[count++] = **((char**)pointer);
  }
  notation[count++] = SEPARATOR;
  if (res != -1)
    free(*pointer);
  else
    count = -1;
  *pointer = NULL;
  // vizual_stack(*head);
  return count;
}

/// @brief Функция определение приоритета записываемой функции по отношению к
/// верхушке стека
/// @param str Сравниваемый символ (если считываемый символ - буква, имеет
/// высший приоритет)
/// @param head Указатель на верхушку стека
/// @return Возвращает 1 в случае приоритет записываемой операции ниже или равен
/// приоритету верхушки стека
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

void s21_zero_func(char* str, int* count) {
  for (int i = 0; i < *count; i++) str[i] = 0;
  *count = 0;
}

void randomize(void) {
  int i = 0;
  time_t t = 0;
  char* str = "123456789";
  char* str2 = "+-/*^";
  srand((unsigned)time(&t));
  for (i = 0; i < 127; i++) {
    printf("%c", str[rand() % 9]);
    printf("%c", str2[rand() % 5]);
  }
}