//Copyright joaquind 2023

#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H

#define _CRT_SECURE_NO_WARNINGS

#define OK 1
#define ERROR -1
#define UNDEFINED -2

#define FLOAT_TYPE 0
#define OPERATORS_TYPE 1
#define FUNCTIONS_TYPE 2

#define DIGITS ".0123456789"
// Заменим mod символом '%'. В калькуляторе будет иметь прежний вид
#define OPERATORS "(  +- */%^"
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define FUNCTIONS "cos  sin  tan  sqrt log  acos asin atan ln"
#define SEPARATOR ' '
#define NEGATIVE "(0-1)*"
#define POSITIVE "(1)*"

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

/***************************** PARSING **************************/

int s21_parcing_string(stack** head, stack** num, char* str_in, double* answer,
                       double x);
int s21_arithmetic(stack** head, stack** num, char* notation);
int s21_prioritization(char str, stack* head);
void s21_zero_func(char* str, int count);
void s21_insert(char* str, char* small_str, int position);
void s21_double_to_str(char* str, double num);
int s21_to_empty_stacks(stack** head, stack** num, char* buff);
void s21_clean_stack(stack** head, stack** num);
void s21_create_dot_for_graph(char* str_in, double dot);

int s21_make_functions(stack** num, double* result, char* function);
int s21_make_operators(stack** num, double* res, char ch_operator);
int s21_validation_arcfunc(double** result, double sample, double digit);
int s21_validation_log(double** result, double sample, double digit);

int s21_check_operators(stack** head, stack** num, char* str, int* position,
                        char* notation, int* flag);
int s21_check_digit(stack** num, char* str, char* buff, int* position,
                    int* flag);
int s21_check_functions(stack** head, char* str, int* position, int* flag);
int s21_check_close_bracket(stack** head, stack** num, char* str, int* position,
                            char* notation);
/***************************** PARSING **************************/

void s21_credit_calculator(double amount, double rate, int term, double* result,
                           char type);

#endif  // S21_CALCULATE_H
