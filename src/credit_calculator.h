#ifndef CREDIT_CALCULATOR_H
#define CREDIT_CALCULATOR_H

#include <QDoubleValidator>
#include <QRegularExpression>
#include <QWidget>

#include "credit_c_a.h"

extern "C" {
#include "s21_calculate.h"
}

namespace Ui {
class credit_calculator;
}

class credit_calculator : public QWidget {
  Q_OBJECT

 public:
  explicit credit_calculator(QWidget *parent = nullptr);
  ~credit_calculator();

 private slots:
  void on_pushButton_clicked();
  void on_radioButton_An_clicked(bool checked);

 private:
  Ui::credit_calculator *ui;
  QDoubleValidator validator_d;
  QIntValidator validator_i;
  credit_c_a *vizual;
};

#endif  // CREDIT_CALCULATOR_H
