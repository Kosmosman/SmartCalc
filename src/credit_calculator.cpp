#include "credit_calculator.h"

#include "ui_credit_calculator.h"

credit_calculator::credit_calculator(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::credit_calculator),
      validator_d(0, 1000000, 2, this),
      validator_i(0, 1000000, this) {
  ui->setupUi(this);
  ui->radioButton_An->isCheckable();
  ui->radioButton_An->setChecked(true);

  validator_d.setNotation(QDoubleValidator::StandardNotation);
  ui->lineEdit_amount->setValidator(&validator_d);
  ui->lineEdit_rate->setValidator(&validator_d);
  ui->lineEdit_term->setValidator(&validator_i);
}

credit_calculator::~credit_calculator() { delete ui; }

void credit_calculator::on_pushButton_clicked() {
  char type = ' ';
  double *res =
      (double *)calloc(2 + ui->lineEdit_term->text().toUInt(), sizeof(double));
  if (ui->radioButton_An->isChecked()) {
    type = 'a';
  } else {
    type = 'd';
  }
  if (res && !ui->lineEdit_amount->text().isEmpty() &&
      !ui->lineEdit_term->text().isEmpty() &&
      !ui->lineEdit_rate->text().isEmpty()) {
    s21_credit_calculator(ui->lineEdit_amount->text().toDouble(),
                          ui->lineEdit_rate->text().toDouble(),
                          ui->lineEdit_term->text().toInt(), res, type);
    credit_c_a *vizual = new credit_c_a();
    if (type == 'a')
      vizual->vizual_result_an(res);
    else
      vizual->vizual_result_diff(res, ui->lineEdit_term->text().toInt());
    vizual->show();
  }
  if (res != NULL) free(res);
  res = NULL;
  ui->lineEdit_term->clear();
  ui->lineEdit_amount->clear();
  ui->lineEdit_rate->clear();
}

void credit_calculator::on_radioButton_An_clicked(bool checked) {
  if (checked) {
    ui->radioButton_An->setChecked(true);
  } else {
    ui->radioButton_An->setChecked(true);
  }
}
