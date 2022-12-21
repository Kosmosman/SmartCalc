#include "s21_calculate.h"

/// @brief Занесение структуры в стек
/// @param head Адрес верхнего элемента стека
/// @param lec Передаваемая строка (число, знак, функция)
/// @return Возвращает 1 в случае успешной записи в стэк. Возвращает 0 в случае
/// невыделения памяти под структуру/элемент структуры
int s21_push(stack** head, char* lec) {
  int res = OK;
  stack* tmp = (stack*)malloc(sizeof(stack));
  if (tmp) {
    tmp->next = *head;
    if (strpbrk(lec, DIGITS)) {
      tmp->type = FLOAT_TYPE;
      double num = atof(lec);
      tmp->data = (double*)malloc(sizeof(double));
      res = tmp->data ? OK : ERROR;
      if (res) *((double*)(tmp->data)) = num;
    } else if (strpbrk(lec, OPERATORS)) {
      tmp->type = OPERATORS_TYPE;
      tmp->data = (char*)malloc(sizeof(char));
      res = tmp->data ? OK : ERROR;
      if (res) *(char*)(tmp->data) = lec[0];
    } else {
      tmp->type = FUNCTIONS_TYPE;
      tmp->data = (char*)malloc(sizeof(strlen(lec) + 1));
      res = tmp->data ? OK : ERROR;
      if (res) strcpy((char*)(tmp->data), lec);
    }
    if (res)
      *head = tmp;
    else {
      free(tmp);
    }
  } else {
    res = ERROR;
  }
  return res;
}

/// @brief Извлечение верхнего элемента из стека с его последующей очисткой
/// @param head Адрес верхнего элемента
/// @param ret Указатель на извлекаемое значение элемента стека
/// @return Возвращает -1 в случае невыделения памяти.
///         Возвращает 0, если записанный элемент - число с плавающей точкой.
///         Возвращает 1, если записанный элемент - оператор.
///         Возвращает 2, если записанный элемент - функция.
int s21_pop(stack** head, void** ret) {
  int out = 0;
  if ((*head) != NULL) {
    stack* tmp = *head;
    if ((*head)->type == FLOAT_TYPE) {
      *ret = (double*)malloc(sizeof(double));
      out = *ret ? OK : ERROR;
      if (out) **((double**)ret) = *(double*)(*head)->data;
    } else if ((*head)->type == OPERATORS_TYPE) {
      *ret = (char*)malloc(sizeof(char));
      out = *ret ? OK : ERROR;
      if (out) **((char**)ret) = *(char*)(*head)->data;
    } else {
      *ret = (char*)malloc(sizeof((*head)->data));
      out = *ret ? OK : ERROR;
      if (out) strcpy(*(char**)ret, (char*)(*head)->data);
    }
    if (out) {
      out = (*head)->type;
      *head = (*head)->next;
      free(tmp->data);
      free(tmp);
    } else {
      out = -1;
    }
  } else {
    free(head);
  }
  return out;
}

void vizual_stack(stack* head) {
  stack* tmp = head;
  while (tmp) {
    printf("stack - ");
    if ((tmp)->type == FLOAT_TYPE) printf("%lf\n", *(double*)(tmp)->data);
    if ((tmp)->type == OPERATORS_TYPE) printf("%c\n", *(char*)(tmp)->data);
    if ((tmp)->type == FUNCTIONS_TYPE) printf("%s\n", (char*)(tmp)->data);
    tmp = tmp->next;
  }
  printf("\n");
}