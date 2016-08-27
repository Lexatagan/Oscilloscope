#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QThread>
#include "usbcommunicator.h"
#include "displayWidget.h"
#include "manager.h"

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
  QRadioButton *gainAx1RadioButton;
  QRadioButton *gainAx2RadioButton;
  QRadioButton *gainAx4RadioButton;
  QRadioButton *gainAx8RadioButton;
  QRadioButton *gainAx16RadioButton;
  QRadioButton *gainBx1RadioButton;
  QRadioButton *gainBx2RadioButton;
  QRadioButton *gainBx4RadioButton;
  QRadioButton *gainBx8RadioButton;
  QRadioButton *gainBx16RadioButton;
  Manager *manager;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  QWidget *container;
  QTimer *testSignalTimer;

private slots:
  void changeGain();
  void changeShiftA(int val);
  void changeShiftB(int val);
};

#endif // MAINWINDOW_H
