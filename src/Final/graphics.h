#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>

#include "qcustomplot.h"

namespace Ui {
class Graphics;
}

class Graphics : public QWidget {
  Q_OBJECT

 public:
  explicit Graphics(QWidget *parent = nullptr);
  ~Graphics();

 public slots:
  void paint_grap(QVector<double> x, QVector<double> y, double x_s, double y_s,
                  double x_e, double y_e);

 private:
  Ui::Graphics *ui;
};

#endif  // GRAPHICS_H
