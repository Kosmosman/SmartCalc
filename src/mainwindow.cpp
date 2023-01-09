#include "mainwindow.h"

#include <QApplication>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      validator_d(-1000000, 1000000, 2, this),
      validator_i(-1000000, 1000000, this) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(input_digit()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(input_operators()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(input_operators()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(input_operators()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(input_operators()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_operators()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(input_operators()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(input_operators()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(input_operators()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(input_functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(input_functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(input_functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(input_functions()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(input_dot()));

  connect(ui->pushButton_result, SIGNAL(clicked()), this, SLOT(input_result()));

  connect(ui->pushButton_delete, SIGNAL(clicked()), this, SLOT(input_delete()));

  ui->pushButton_result->setCheckable(true);
  ui->pushButton_x->setCheckable(true);
  ui->pushButton_dot->setCheckable(false);

  validator_d.setNotation(QDoubleValidator::StandardNotation);
  ui->lineEdit_value->setValidator(&validator_d);
  ui->lineEdit_x_start->setValidator(&validator_i);
  ui->lineEdit_y_start->setValidator(&validator_i);
  ui->lineEdit_x_end->setValidator(&validator_i);
  ui->lineEdit_y_end->setValidator(&validator_i);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::input_digit() {
  QPushButton *button = (QPushButton *)sender();
  QString result = 0;
  if (ui->pushButton_result->isChecked()) {
    ui->label->setText("");
    check_empty_and_error();
  }
  result = ui->label->text() + button->text();
  if (button->text() == "x") ui->pushButton_x->setChecked(true);
  ui->label->setText(result);
}

void MainWindow::input_dot() {
  int len = ui->label->text().length();
  char *str = new char(ui->label->text().length());
  int flag = 0;
  QByteArray tmp = ui->label->text().toLatin1();
  strlcpy(str, tmp, ui->label->text().length() + 1);
  for (int i = 0; i < len; i++) {
    if (str[i] == '.') {
      flag = 1;
    }
    if (!(std::isdigit(str[i])) && str[i] != '.' && str[i] != 'x') {
      flag = 0;
    }
  }
  if (flag == 0) ui->label->setText(ui->label->text() + ".");
  if (str) delete (str);
}

void MainWindow::input_operators() {
  QPushButton *button = (QPushButton *)sender();
  QString result = 0;
  check_empty_and_error();
  if (button->text() == "mod")
    result = ui->label->text() + "%";
  else
    result = ui->label->text() + button->text();
  ui->label->setText(result);
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::input_functions() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->pushButton_result->isChecked()) {
    ui->label->setText("");
    check_empty_and_error();
  }
  QString result = 0;
  result = ui->label->text() + button->text() + "(";
  ui->label->setText(result);
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::input_result() {
  stack *head = NULL;
  stack *num = NULL;
  double result = 0;
  double x = 0;
  if (ui->pushButton_x->isChecked()) x = ui->lineEdit_value->text().toDouble();
  char *str = new char(ui->label->text().length());
  QByteArray tmp = ui->label->text().toLatin1();
  strlcpy(str, tmp, ui->label->text().length() + 1);
  int res = s21_parcing_string(&head, &num, str, &result, x);
  if (res == ERROR) {
    ui->label->setText("Error!");
  } else if (res == UNDEFINED) {
    ui->label->setText("undefined");
  } else {
    char ansver[256] = {'\0'};
    s21_double_to_str(ansver, result);
    ui->label->setText(ansver);
  }
  ui->pushButton_result->setChecked(true);
  ui->pushButton_x->setChecked(false);
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::input_delete() {
  ui->label->setText("");
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::check_empty_and_error() {
  ui->pushButton_result->setChecked(false);
  if (ui->label->text() == "Error!" || ui->label->text() == "undefined")
    ui->label->setText("");
}

void MainWindow::create_graphic() {
  stack *head = NULL, *num = NULL;
  Graphics *grap = new Graphics();
  double x_start = ui->lineEdit_x_start->text().toDouble();
  double y_start = ui->lineEdit_y_start->text().toDouble();
  double x_end = ui->lineEdit_x_end->text().toDouble();
  double y_end = ui->lineEdit_y_end->text().toDouble();
  if (x_start >= x_end || y_start >= y_end) {
    x_start = y_start = -10;
    x_end = y_end = 10;
  }
  int max =
      (x_end - x_start) > (y_end - y_start) ? x_end - x_start : y_end - y_start;
  QVector<double> x(max * 10 + 1), y(max * 10 + 1);
  double result = 0, topBorder = (x_end - x_start) * 10 + 1,
         downBorder = x_start;
  int error = 0;
  char *str = new char(ui->label->text().length());
  QByteArray tmp = ui->label->text().toLatin1();
  strlcpy(str, tmp, ui->label->text().length() + 1);
  setBorders(&topBorder, &downBorder);
  for (int i = 0; i < topBorder && error != ERROR; i++) {
    x[i] = downBorder + i / 10.0;
    error = s21_parcing_string(&head, &num, str, &result, x[i]);
    y[i] = result;
  }
  if (error != ERROR) {
    grap->paint_grap(x, y, x_start, y_start, x_end, y_end);
    grap->show();
    delete (str);
    ui->label->clear();
  } else {
    delete (grap);
    ui->label->setText("Error!");
  }
}

void MainWindow::on_pushButton_credit_calculate_clicked() {
  credit_calculator *cc = new credit_calculator;
  cc->show();
}

void MainWindow::on_pushButton_graphic_clicked() {
  check_empty_and_error();
  create_graphic();
  ui->pushButton_x->setChecked(false);
  ui->pushButton_result->setChecked(true);
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::setBorders(double *topBorder, double *downBorder) {
  if ((ui->label->text().contains("l") || ui->label->text().contains("sqrt")) &&
      ui->lineEdit_x_start->text().toDouble() <= 0) {
    *downBorder = 0.01;
  }
  if (ui->label->text().contains("acos") ||
      ui->label->text().contains("asin")) {
    *topBorder = 21;
    *downBorder = -1;
  }
}
