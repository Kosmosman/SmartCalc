#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>

#include <QDoubleValidator>
#include <QMainWindow>

#include "credit_calculator.h"
#include "graphics.h"

extern "C" {
#include "../backend/s21_calculate.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void input_digit();
  void input_dot();
  void input_operators();
  void input_functions();
  void input_result();
  void input_delete();
  void check_empty_and_error();
  void create_graphic();

  void on_pushButton_credit_calculate_clicked();

  void on_pushButton_graphic_clicked();

  void setBorders(double *, double *);

signals:
  void to_graphic();

 private:
  Ui::MainWindow *ui;
  Graphics *grap;
  credit_calculator *cc;
  QDoubleValidator validator_d;
  QIntValidator validator_i;
};
#endif  // MAINWINDOW_H
