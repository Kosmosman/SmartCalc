// Copyright joaquind 2023

#include "s21_calculate.h"

/// @brief Функция для считывания входной строки и проведения
/// операций над считанными данными
/// @param head Стек операторов/функций
/// @param num Стек чисел
/// @param str Считываемая строка с выражением
/// @param answer Указатель на полученный результат выражения
/// @param x Точка по оси абсцисс (для графиков)
/// @return Возвращает ERROR в случае невыделения памяти в одной из функций
int s21_parcing_string(stack** head, stack** num, char* str_in, double* answer,
                       double x) {
  int i = 0, res = 0, flag = 1;
  char* buff = (char*)calloc(256, sizeof(char));
  char* str = (char*)calloc(2048, sizeof(char));
  void* pointer = NULL;
  if (buff && str) {
    strncpy(str, str_in, 255);
    s21_create_dot_for_graph(str, x);
    while (str[i] != '\0' && res >= 0) {
      if (res >= 0) res = s21_check_digit(num, str, buff, &i, &flag);
      if (res >= 0) res = s21_check_functions(head, str, &i, &flag);
      if (res >= 0) res = s21_check_operators(head, num, str, &i, buff, &flag);
      if (res >= 0) res = s21_check_close_bracket(head, num, str, &i, buff);
      if (res == 5) res = -1;
      if (*head == NULL && *num == NULL) res = -1;
    }
    if (res >= 0) res = s21_to_empty_stacks(head, num, buff);
    s21_pop(num, &pointer);
    if (*num != NULL || *head != NULL) {
      s21_clean_stack(head, num);
      res = -1;
    }
    if (res != ERROR && pointer != NULL) {
      *answer = *(double*)pointer;
    }
    if (pointer != NULL) free(pointer);
    pointer = NULL;
  }
  if (buff) free(buff);
  if (str) free(str);
  pointer = buff = str = NULL;
  return res;
}

/// @brief Запись операции/функции в строку ОПЗ
/// @param head Стек с операторами/функциями
/// @param num Стек с числами
/// @param result Результат вычисления
/// @param buff Буффер
/// @return Возвращает ERROR в случае невыделения памяти под временную структуру
int s21_arithmetic(stack** head, stack** num, char* buff) {
  double result = 0;
  void* pointer = NULL;
  int res = s21_pop(head, &pointer);
  if (res == FUNCTIONS_TYPE) {
    res = s21_make_functions(num, &result, (char*)pointer);
  } else if (res == OPERATORS_TYPE) {
    res = s21_make_operators(num, &result, *(char*)pointer);
  }
  if (pointer) free(pointer);
  pointer = NULL;
  if (res >= 0) {
    sprintf(buff, "%.12lf", result);
    res = s21_push(num, buff);
    s21_zero_func(buff, (int)strlen(buff));
  }
  return res;
}

/// @brief Вычисление функции
/// @param num Стек с числами
/// @param result Результирующее значение
/// @param function Переданная функция
/// @return Возвращает ERROR в случае невыделения памяти под digit
int s21_make_functions(stack** num, double* result, char* function) {
  void* digit = NULL;
  int error = 0;
  error = s21_pop(num, &digit);
  if (error != ERROR) {
    switch ((strstr(FUNCTIONS, function) - &FUNCTIONS[0]) / 5) {
      case 0:
        *result = cos(*(double*)digit);
        break;
      case 1:
        *result = sin(*(double*)digit);
        break;
      case 2:
        *result = tan(*(double*)digit);
        break;
      case 3:
        if (*(double*)digit < 0)
          error = ERROR;
        else
          *result = sqrt(*(double*)digit);
        break;
      case 4:
        error = s21_validation_log(&result, log10(*(double*)digit),
                                   *(double*)digit);
        break;
      case 5:
        error = s21_validation_arcfunc(&result, acos(*(double*)digit),
                                       *(double*)digit);
        break;
      case 6:
        error = s21_validation_arcfunc(&result, asin(*(double*)digit),
                                       *(double*)digit);
        break;
      case 7:
        *result = atan(*(double*)digit);
        break;
      case 8:
        error =
            s21_validation_log(&result, log(*(double*)digit), *(double*)digit);
        break;
      default:
        error = ERROR;
        break;
    }
  }
  if (digit) free(digit);
  digit = NULL;
  return error;
}

/// @brief Проверка на корректность вводимых значений для arcsin и arccos
/// @param result Переменная, выделенная под результат вычислений
/// @param sample Выражение
/// @param digit Вводимое число
/// @return Возвращает ERROR при вводе данных, не вписывающихся в диапазон
/// допустимых значений
int s21_validation_arcfunc(double** result, double sample, double digit) {
  int error = 0;
  if (digit >= -1 && digit <= 1)
    **result = sample;
  else
    error = ERROR;
  return error;
}

/// @brief Проверка на корректность вводимых значений для log и ln
/// @param result Переменная, выделенная под результат вычислений
/// @param sample Выражение
/// @param digit Вводимое число
/// @return Возвращает ERROR при вводе данных, не вписывающихся в диапазон
/// допустимых значений
int s21_validation_log(double** result, double sample, double digit) {
  int error = 0;
  if (digit > 0)
    **result = sample;
  else
    error = ERROR;
  return error;
}

/// @brief Вычисление результата с оператором
/// @param num Стек с числами
/// @param res Результирующее значение
/// @param operator Переданный оператор
/// @return Возвращает ERROR в случае невыделения памяти под digit1 и/или digit2
int s21_make_operators(stack** num, double* res, char ch_operator) {
  void *digit1 = NULL, *digit2 = NULL;
  int error = 0;
  error = s21_pop(num, &digit2);
  if (error != ERROR) error = s21_pop(num, &digit1);
  if (error != ERROR) {
    switch (strchr(OPERATORS, ch_operator) - &OPERATORS[0]) {
      case 3:
        *res = *(double*)digit1 + *(double*)digit2;
        break;
      case 4:
        *res = *(double*)digit1 - *(double*)digit2;
        break;
      case 6:
        *res = *(double*)digit1 * *(double*)digit2;
        break;
      case 7:
        if (*(double*)digit2 == 0)
          error = -2;
        else
          *res = *(double*)digit1 / *(double*)digit2;
        break;
      case 8:
        *res = fmod(*(double*)digit1, *(double*)digit2);
        break;
      case 9:
        *res = pow(*(double*)digit1, *(double*)digit2);
        break;
      default:
        error = ERROR;
        break;
    }
  }
  if (digit1) free(digit1);
  if (digit2) free(digit2);
  digit1 = digit2 = NULL;
  return error;
}

/// @brief Проверка на число
/// @param num Стек с числами
/// @param str Считываемая строка с подсчитываемым выражением
/// @param buff Буффер
/// @param position Текущее положение по строке str
/// @return Возвращает 0 в случае невыделения памяти под структуру/элемент
/// структуры
int s21_check_digit(stack** num, char* str, char* buff, int* position,
                    int* flag) {
  int count = 0, res = 0;
  if (isdigit(str[*position]) || str[*position] == '.') {
    while ((isdigit(str[*position]) || str[*position] == '.')) {
      buff[count++] = str[(*position)++];
    }
    res = s21_push(num, buff);
    s21_zero_func(buff, count);
    *flag = 0;
  }
  return res;
}

/// @brief Проверка, встретили ли мы функцию
/// @param head Стек операторов и функций
/// @param str Считываемая строка
/// @param position Текущая позиция в считываемой строке
/// @param buff Буффер
/// @param flag Флаг, оповещающий о том, что был считан оператор
/// @return Возвращает ERROR в случае ошибки выделения памяти
int s21_check_functions(stack** head, char* str, int* position, int* flag) {
  char func[5] = {0};
  int func_position = 0, res = 0;
  if (isalpha(str[*position])) {
    while (isalpha(str[*position])) func[func_position++] = str[(*position)++];
    res = s21_push(head, func);
    *flag = 1;
  }
  return res;
}

/// @brief Проверка, является ли текущий символ оператором
/// @param head Стек операторов и функций
/// @param num Стек чисел
/// @param str Считываемая строка
/// @param position Текущая позиция в считываемой строке
/// @param buff Буффер
/// @return Возвращает ERROR в случае ошибки выделения памяти
int s21_check_operators(stack** head, stack** num, char* str, int* position,
                        char* buff, int* flag) {
  int ops_count = 0, priority = 0, res = 0;
  char ops[2] = {0};
  if (strchr(OPERATORS, str[*position]) && str[*position] != '\0') {
    if (*flag && str[*position] == '-') {
      s21_insert(str, NEGATIVE, *position);
    } else if (*flag && str[*position] == '+') {
      s21_insert(str, POSITIVE, *position);
    }
    priority = s21_prioritization(str[*position], *head);
    ops[ops_count++] = str[(*position)++];
    while (priority && ops[0] != OPEN_BRACKET && res >= 0 &&
           (*num != NULL || (*head)->type == 2)) {
      res = s21_arithmetic(head, num, buff);
      priority = s21_prioritization(ops[0], *head);
    }
    if (res >= 0) s21_push(head, ops);
    *flag = 1;
  }
  return res;
}

/// @brief Проверка на наличие закрывающей скобки
/// @param head Стек операторов и функций
/// @param num Стек чисел
/// @param str Считываемая строка
/// @param position Текущая позиция в считываемой строке
/// @param buff Буффер
/// @return Возвращает ERROR в случае ошибки выделения памяти
int s21_check_close_bracket(stack** head, stack** num, char* str, int* position,
                            char* buff) {
  int res = 0;
  void* pointer = NULL;
  if (str[*position] == CLOSE_BRACKET) {
    while (*head && *(char*)(*head)->data != '(' && res >= 0) {
      res = s21_arithmetic(head, num, buff);
    }
    if (*head != NULL && *(char*)(*head)->data == '(') {
      res = s21_pop(head, &pointer);
      if (pointer != NULL) free(pointer);
      pointer = NULL;
    } else {
      res = ERROR;
    }
    *position += 1;
  }
  return res;
}

/// @brief Выполнение всех операций в стеке после считывания входной строки до
/// конца
/// @param head Стек с операторами/функциями
/// @param num Стек с числами
/// @param buff Буффер
/// @return Возвращает ERROR в случае ошибки выделения памяти
int s21_to_empty_stacks(stack** head, stack** num, char* buff) {
  int res = 0;
  void* pointer = NULL;
  while (*head) {
    if ((*head)->type == OPERATORS_TYPE && *(char*)(*head)->data == '(')
      res = s21_pop(head, &pointer);
    else
      res = s21_arithmetic(head, num, buff);
    if (pointer != NULL) free(pointer);
    pointer = NULL;
  }
  return res;
}

/// @brief Функция определение приоритета записываемой функции по отношению
/// к верхушке стека
/// @param str Сравниваемый символ (если считываемый символ - буква, имеет
/// высший приоритет)
/// @param head Указатель на верхушку стека
/// @return Возвращает 1 в случае приоритет записываемой операции ниже или
/// равен приоритету верхушки стека
int s21_prioritization(char str, stack* head) {
  int priority_str = 0, priority_stack = 0, res = 0;
  if (head != NULL) {
    priority_str = (strchr(&OPERATORS[0], str) - &OPERATORS[0]) / 3;
    priority_stack =
        (strchr(&OPERATORS[0], *(char*)(head)->data) - &OPERATORS[0]) / 3;
    if (priority_str <= priority_stack || (priority_stack < 0)) res = 1;
  }
  return res;
}

/// @brief Вставка в строку другой строки
/// @param str Заполняемая строка
/// @param small_str Вставляемая строка
/// @param position Место вставки
void s21_insert(char* str, char* small_str, int position) {
  int len_s = (int)strlen(small_str);
  int len = (int)strlen(str);
  for (int i = len; i >= position; i--) {
    str[len_s + i] = str[i + 1];
  }
  for (int i = position, j = 0; i < position + len_s; i++, j++) {
    str[i] = small_str[j];
  }
}

/// @brief Заполенение массива нулями
/// @param str Заполняемая строка
/// @param count Число заполняемых элементов
void s21_zero_func(char* str, int count) {
  for (int i = 0; i < count; i++) str[i] = 0;
}

/// @brief Перевод числа с плавающей точкой в строку с удалением незначащих
/// нулей
/// @param str Строка для записи числа в char представлении
/// @param num Число с плавающей точкой
void s21_double_to_str(char* str, double num) {
  sprintf(str, "%.6lf", num);
  int len = (int)strlen(str) - 1, out = 1;
  for (; str[len] == '0'; len--) str[len] = '\0';
  if (str[len] == '.' || str[len] == ',') str[len] = '\0';
  len = (int)strlen(str);
  for (int i = 0; i < len && out; i++) {
    if (str[i] == ',') {
      str[i] = '.';
      out = 0;
    }
  }
}

/// @brief Функция очищения стаков в случае обнаружения ошибки
/// @param head Стек операторов/функций
/// @param num Стек чисел
void s21_clean_stack(stack** head, stack** num) {
  void* tmp = NULL;
  while (*head != NULL) {
    s21_pop(head, &tmp);
  }
  while (*num != NULL) {
    s21_pop(num, &tmp);
  }
  if (tmp != NULL) free(tmp);
  head = num = tmp = NULL;
}

/// @brief Функция подстановки х на переденные координаты точек
/// @param head Стек операторов/функций
/// @param num Стек чисел
/// @param str_in Входная строка
/// @param dot Число (точка), подставляемая заместо числа
void s21_create_dot_for_graph(char* str_in, double dot) {
  char number[32] = {0};
  sprintf(number, "(%lf)", dot);
  char* pointer = NULL;
  while ((pointer = strchr(str_in, 'x'))) {
    s21_insert(str_in, number, pointer - str_in);
  }
}
