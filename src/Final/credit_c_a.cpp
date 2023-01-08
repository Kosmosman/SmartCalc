#include "credit_c_a.h"

#include "ui_credit_c_a.h"

credit_c_a::credit_c_a(QWidget *parent)
    : QWidget(parent), ui(new Ui::credit_c_a) {
  ui->setupUi(this);
}

credit_c_a::~credit_c_a() { delete ui; }

void credit_c_a::vizual_result_an(double *data) {
  ui->textBrowser->setText(QString::number(data[0], 'f', 6));
  ui->label_ovp->setText(QString::number(data[1], 'f', 6));
  ui->label_fp->setText(QString::number(data[2], 'f', 6));
}

void credit_c_a::vizual_result_diff(double *data, int term) {
  QString tmp = 0;
  for (int i = 0; i < term; i++) {
    tmp.append(QString::number(i + 1));
    tmp.append(" - ");
    tmp.append(QString::number(data[i], 'f', 6));
    if (i != (term - 1)) tmp.append('\n');
  }
  ui->textBrowser->setText(tmp);
  ui->label_ovp->setText(QString::number(data[term], 'f', 6));
  ui->label_fp->setText(QString::number(data[term + 1], 'f', 6));
}
