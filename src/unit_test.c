#include <check.h>

#include "backend/s21_calculate.h"

START_TEST(test_1) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(0, res);
  ck_assert_str_eq(ansver_str, "0");
}
END_TEST

START_TEST(test_2) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "1";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(0, res);
  ck_assert_str_eq(ansver_str, "1");
}
END_TEST

START_TEST(test_3) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "1)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_4) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "1+2";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "3");
}
END_TEST

START_TEST(test_5) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "2*5";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "10");
}
END_TEST

START_TEST(test_6) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "4/5";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.8");
}
END_TEST

START_TEST(test_7) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "3^3";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "27");
}
END_TEST

START_TEST(test_8) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "3*";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_9) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "2.5*3/8";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.9375");
}
END_TEST

START_TEST(test_10) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "***";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_11) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "25/0";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(UNDEFINED, res);
}
END_TEST

START_TEST(test_12) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sin";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_13) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sin(1)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.841471");
}
END_TEST

START_TEST(test_14) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "cos(1)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.540302");
}
END_TEST

START_TEST(test_15) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "log(5)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.69897");
}
END_TEST

START_TEST(test_16) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "ln(5)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1.609438");
}
END_TEST

START_TEST(test_17) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "asin(0.2)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.201358");
}
END_TEST

START_TEST(test_18) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "acos(0.2)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1.369438");
}
END_TEST

START_TEST(test_19) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "tan(0.8)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1.029639");
}
END_TEST

START_TEST(test_20) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "atan(0.8)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.674741");
}
END_TEST

START_TEST(test_21) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "2+7";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "9");
}
END_TEST

START_TEST(test_22) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "4.5*3";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "13.5");
}
END_TEST

START_TEST(test_23) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "1**24-1/0*sin()-1^^2";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_24) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sin(cos(sin(cos(";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_25) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "7(7";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_26) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sqrt(9)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "3");
}
END_TEST

START_TEST(test_27) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "2.6-1.11";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1.49");
}
END_TEST

START_TEST(test_28) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "7%3";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 0);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1");
}
END_TEST

START_TEST(test_29) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "x*2";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "10");
}
END_TEST

START_TEST(test_30) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "-1";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "-1");
}
END_TEST

START_TEST(test_31) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "+1";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "1");
}
END_TEST

START_TEST(test_32) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "2**2";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_33) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sin";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_36) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sqrt(-1)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_37) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "asin(5)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_38) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "acos(-5)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(ERROR, res);
}
END_TEST

START_TEST(test_39) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "x+5";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "10");
}
END_TEST

START_TEST(test_40) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "x*3";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "15");
}
END_TEST

START_TEST(test_41) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "x/2";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "2.5");
}
END_TEST

START_TEST(test_42) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "x%1.5";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "0.5");
}
END_TEST

START_TEST(test_43) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "sin(cos(2))";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "-0.404239");
}
END_TEST

START_TEST(test_44) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "ln(2)+ln(3)-4+(5*6)^3.2+sin(10)";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "53304.710856");
}
END_TEST

START_TEST(test_45) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "5-3*2^4+5*(2.2*4.3)^2.1*5";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "2757.988947");
}
END_TEST

START_TEST(test_46) {
  stack* head = NULL;
  stack* num = NULL;
  char* str = "asin(0.1)^(2+0.5)*3-1";
  char ansver_str[64] = {0};
  double ansver = 0;
  int res = s21_parcing_string(&head, &num, str, &ansver, 5);
  s21_double_to_str(ansver_str, ansver);
  ck_assert_int_eq(1, res);
  ck_assert_str_eq(ansver_str, "-0.990473");
}
END_TEST

START_TEST(test_47) {
  int term = 6;
  double amount = 100000;
  double rate = 8.5;
  char type = 'a';
  double result[3] = {0};
  s21_credit_calculator(amount, rate, term, result, type);
  ck_assert_double_eq_tol(17082.291434, result[0], 6);
  ck_assert_double_eq_tol(2493.748603, result[1], 6);
  ck_assert_double_eq_tol(102493.748603, result[2], 6);
}
END_TEST

START_TEST(test_48) {
  int term = 2;
  double amount = 100000;
  double rate = 8.5;
  char type = 'd';
  double result[4] = {0};
  s21_credit_calculator(amount, rate, term, result, type);
  ck_assert_double_eq_tol(50708.333333, result[0], 6);
  ck_assert_double_eq_tol(50354.166667, result[1], 6);
  ck_assert_double_eq_tol(1062.5, result[2], 6);
  ck_assert_double_eq_tol(101062.5, result[3], 6);
}
END_TEST

int main(void) {
  Suite* s = suite_create("suite_tests");
  TCase* tc = tcase_create("tests");
  SRunner* sr = srunner_create(s);
  int res = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);
  tcase_add_test(tc, test_33);
  tcase_add_test(tc, test_36);
  tcase_add_test(tc, test_37);
  tcase_add_test(tc, test_38);
  tcase_add_test(tc, test_39);
  tcase_add_test(tc, test_40);
  tcase_add_test(tc, test_41);
  tcase_add_test(tc, test_42);
  tcase_add_test(tc, test_43);
  tcase_add_test(tc, test_44);
  tcase_add_test(tc, test_45);
  tcase_add_test(tc, test_46);
  tcase_add_test(tc, test_47);
  tcase_add_test(tc, test_48);

  srunner_run_all(sr, CK_ENV);
  res = srunner_ntests_failed(sr);

  srunner_free(sr);
  return res == 0 ? 0 : 1;
}
