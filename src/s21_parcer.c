#include "s21_calculate.h"

/// @brief Функция для считывания входной строки и проведения
/// операций над считанными данными
/// @param head Стек операторов/функций
/// @param num Стек чисел
/// @param str Считываемая строка с выражением
/// @param ansver Указатель на полученный результат выражения
/// @return Возвращает ERROR в случае невыделения памяти в одной из функций
double s21_parcing_string(stack** head, stack** num, char* str_in,
                          double* ansver) {
  int i = 0, res = 0, flag = 1;
  char* buff = (char*)calloc(256, sizeof(char));
  char* str = (char*)calloc(512, sizeof(char));
  void* pointer = NULL;
  if (buff && str) {
    strcpy(str, str_in);
    while (str[i] != '\0' && res != ERROR) {
      if (res != ERROR) res = s21_check_digit(num, str, buff, &i, &flag);
      if (res != ERROR) res = s21_check_functions(head, str, &i, &flag);
      if (res != ERROR)
        res = s21_check_operators(head, num, str, &i, buff, &flag);
      if (res != ERROR) res = s21_check_close_bracket(head, num, str, &i, buff);
    }
    while (*head && res != ERROR) {
      res = s21_arithmetic(head, num, buff);
    }
    if (res != ERROR) free(*head);
    res = s21_pop(num, &pointer);
    if (res != ERROR) {
      *ansver = *(double*)pointer;
      free(pointer);
    }
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
  if (res != ERROR) {
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
  void* digit = 0;
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
        *result = sqrt(*(double*)digit);
        break;
      case 4:
        *result = log10(*(double*)digit);
        break;
      case 5:
        *result = acos(*(double*)digit);
        break;
      case 6:
        *result = asin(*(double*)digit);
        break;
      case 7:
        *result = atan(*(double*)digit);
        break;
      case 8:
        *result = log(*(double*)digit);
        break;
      default:
        break;
    }
  }
  if (digit) free(digit);
  digit = NULL;
  return error;
}

/// @brief Вычисление результата с оператором
/// @param num Стек с числами
/// @param res Результирующее значение
/// @param operator Переданный оператор
/// @return Возвращает ERROR в случае невыделения памяти под digit1 и/или digit2
int s21_make_operators(stack** num, double* res, char operator) {
  void *digit1 = NULL, *digit2 = NULL;
  int error = 0;
  error = s21_pop(num, &digit2);
  if (error != ERROR) error = s21_pop(num, &digit1);
  if (error != ERROR) {
    switch (strchr(OPERATORS, operator) - &OPERATORS[0]) {
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
        *res = *(double*)digit1 / *(double*)digit2;
        break;
      case 8:
        *res = fmod(*(double*)digit1, *(double*)digit2);
        break;
      case 9:
        *res = pow(*(double*)digit1, *(double*)digit2);
        break;
      default:
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
    while (isdigit(str[*position]) || str[*position] == '.') {
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
    while (priority && ops[0] != OPEN_BRACKET && res != ERROR &&
           ((*num)->next != NULL || (*head)->type == 2)) {
      res = s21_arithmetic(head, num, buff);
      priority = s21_prioritization(ops[0], *head);
    }
    if (res != ERROR) s21_push(head, ops);
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
    while (*(char*)(*head)->data != '(' && res != ERROR) {
      res = s21_arithmetic(head, num, buff);
    }
    if (*(char*)(*head)->data == '(') {
      res = s21_pop(head, &pointer);
      if (res != ERROR) free(pointer);
      pointer = NULL;
    }
    *position += 1;
  }
  return res;
}

/// @brief Функция определение приоритета записываемой функции по отношению к
/// верхушке стека
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