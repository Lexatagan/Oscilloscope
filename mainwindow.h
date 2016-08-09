#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "displayWidget.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

private:
  //DisplayWidget *displayWidget;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  QWidget *container;
  QTimer *tmr;
  QTimer *testSignalTimer;

private slots:
  //void changePhosphorValue(int val);
};

#endif // MAINWINDOW_H
