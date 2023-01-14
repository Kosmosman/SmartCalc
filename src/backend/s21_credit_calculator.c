// Copyright joaquind 2023

#include "s21_calculate.h"

void s21_credit_calculator(double amount, double rate, int term, double* result,
                           char type) {
  rate /= 1200;
  if (type == 'a') {
    result[0] =
        amount * rate * pow((1 + rate), term) / (pow((1 + rate), term) - 1);
    result[1] = result[0] * term - amount;
    result[2] = result[0] * term;
  } else {
    double loan_body_mounth = amount / term;
    for (int i = 0; i < term; i++) {
      result[i] = loan_body_mounth + (amount - loan_body_mounth * i) * rate;
      result[term] = result[term] + result[i] - loan_body_mounth;
    }
    result[term + 1] = amount + result[term];
  }
}