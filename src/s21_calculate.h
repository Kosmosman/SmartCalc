#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H

#define OK 1
#define ERROR 0

#define FLOAT_TYPE 0
#define CHAR_TYPE 1
#define STR_TYPE 2

#define DIGITS "0123456789"
// Заменим mod символом '%'. В калькуляторе будет иметь прежний вид
#define OPERATORS "(  +- */%^"
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define FUNCTIONS "acos asin atan sqrt log  cos  sin  tan ln"
#define SEPARATOR ' '

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct stack {
  void* data;
  int type;
  struct stack* next;
} stack;

/***************************** STACK **************************/

int s21_push(stack** head, char* lec);
int s21_pop(stack** head, void** ret);

/***************************** STACK **************************/

char* s21_parcing_string(stack** head, stack** num, char* str);
int s21_import_to_pn(stack** head, char* notation, void** pointer, int count);
int s21_prioritization(char str, stack* head);
void s21_zero_func(char* str, int* count);

void vizual_stack(stack* head);
void randomize(void);

#endif  // S21_CALCULATE_H