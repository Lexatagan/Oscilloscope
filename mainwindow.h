#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include "displayWidget.h"
#include "processor.h"

#define SHIFT_SLIDER_STYLE_RED      "QSlider::handle{"\
                                    "border: 1px solid #999999;"\
                                    "border-radius: 3px;"\
                                    "background: red;"\
                                    "}"

#define SHIFT_SLIDER_STYLE_GREEN    "QSlider::handle{"\
                                    "border: 1px solid #999999;"\
                                    "border-radius: 3px;"\
                                    "background: green;"\
                                    "}"

class MainWindow : public QMainWindow
{
  Q_OBJECT

private:
  DisplayWidget *displayWidget;
  QSlider *shiftASlider;
  QSlider *shiftBSlider;

  Processor *processor;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  QWidget *container;
  QTimer *tmr;
  QTimer *testSignalTimer;

private slots:
  void tstSlot();
};

#endif // MAINWINDOW_H
