#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H

#define OK 1
#define ERROR 0

#define INT_TYPE 0
#define FLOAT_TYPE 1
#define CHAR_TYPE 2

#define DIGITS "0123456789"
// Заменим mod символом '%'. В калькуляторе будет иметь прежний вид
#define OPERATORS "(+-*/%%^"
#define OPEN_BRACKET "("
#define CLOSE_BRACKET ")"
#define FUNCTIONS "acos asin atan sqrt log  cos  sin  tan ln"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  void* data;
  int type;
  struct stack* next;
} stack;

/***************************** STACK **************************/

int s21_push(stack** head, char* lec);
int s21_pop(stack** head, void** ret);

/***************************** STACK **************************/

#endif  // S21_CALCULATE_H