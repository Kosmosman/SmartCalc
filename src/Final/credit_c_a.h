#ifndef CREDIT_C_A_H
#define CREDIT_C_A_H

#include <QWidget>

extern "C" {
#include "../s21_calculate.h"
}

namespace Ui {
class credit_c_a;
}

class credit_c_a : public QWidget {
  Q_OBJECT

 public:
  explicit credit_c_a(QWidget* parent = nullptr);
  ~credit_c_a();

 public slots:
  void vizual_result_an(double* data);
  void vizual_result_diff(double* data, int term);

 private:
  Ui::credit_c_a* ui;
};

#endif  // CREDIT_C_A_H
