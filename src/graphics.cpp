#include "graphics.h"

#include "ui_graphics.h"

Graphics::Graphics(QWidget *parent) : QWidget(parent), ui(new Ui::Graphics) {
  ui->setupUi(this);
}

Graphics::~Graphics() { delete ui; }

void Graphics::paint_grap(QVector<double> x, QVector<double> y, double x_s,
                          double y_s, double x_e, double y_e) {
  Graphics::setGeometry(1500, 300, 761, 721);
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(x_s, x_e);
  ui->widget->yAxis->setRange(y_s, y_e);
  ui->widget->replot();
}
