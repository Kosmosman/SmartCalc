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
      if (strchr(lec, '.')) {
        tmp->type = FLOAT_TYPE;
        double num1 = atof(lec);
        tmp->data = (double*)malloc(sizeof(double));
        res = tmp->data ? OK : ERROR;
        if (res) *((double*)(tmp->data)) = num1;
      } else {
        tmp->type = INT_TYPE;
        int num2 = atoi(lec);
        tmp->data = (int*)malloc(sizeof(int));
        res = tmp->data ? OK : ERROR;
        if (res) *((int*)(tmp->data)) = num2;
      }
    } else {
      tmp->type = CHAR_TYPE;
      tmp->data = (char*)malloc(sizeof(lec) + 1);
      res = tmp->data ? OK : ERROR;
      if (res) strcpy((char*)(tmp->data), lec);
    }
    *head = tmp;
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
///         Возвращает 1, если записанный элемент - целочисленное значение.
///         Возвращает 2, если записанный элемент - массив символов.
int s21_pop(stack** head, void** ret) {
  int out = 0;
  if ((*head) != NULL) {
    stack* tmp = *head;
    if ((*head)->type == FLOAT_TYPE) {
      *ret = (double*)malloc(sizeof(double));
      out = *ret ? OK : ERROR;
      if (out) **((double**)ret) = *(double*)(*head)->data;
    } else if ((*head)->type == INT_TYPE) {
      *ret = (int*)malloc(sizeof(int));
      out = *ret ? OK : ERROR;
      if (out) **((int**)ret) = *(int*)(*head)->data;
    } else {
      *ret = (char*)malloc(sizeof((*head)->data));
      out = *ret ? OK : ERROR;
      if (out) strcpy(*ret, (*head)->data);
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

// int main(void) {
//   stack* head = NULL;
//   int er = 0, type = 0;
//   void* out = NULL;
//   er = s21_push(&head, "123");
//   if (er) er = s21_push(&head, "+-/");
//   if (er) er = s21_push(&head, "456");
//   if (er) er = s21_push(&head, "789");
//   while (head != NULL) {
//     out = NULL;
//     type = s21_pop(&head, &out);
//     if (type == 0)
//       printf("%d\n", *(int*)out);
//     else if (type == 1)
//       printf("%lf\n", *(double*)out);
//     else if (type == 2)
//       printf("%s\n", (char*)out);
//     free(out);
//   }
// }
