#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  DisplayWidget *displayWidget = new DisplayWidget(this);
  QSlider *phosphorValueSlider = new QSlider(this);
  phosphorValueSlider->setMinimum(0);
  phosphorValueSlider->setMaximum(50);
  QLabel *phosphorLabel = new QLabel("digiP", this);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(displayWidget, 0, 0, 2, 4);
  mainLayout->addWidget(phosphorLabel, 0, 3, 1, 1);
  mainLayout->addWidget(phosphorValueSlider, 1, 3, 1, 1);
  container = new QWidget(this);
  container->setLayout(mainLayout);
  setCentralWidget(container);

  this->setGeometry(50, 50, 1050, 400);

  tmr = new QTimer;
  QObject::connect(tmr, SIGNAL(timeout()), displayWidget, SLOT(refresh()));
  tmr->start(20);

  testSignalTimer = new QTimer;
  QObject::connect(testSignalTimer, SIGNAL(timeout()), displayWidget, SLOT(testSignal()));
  testSignalTimer->start(0);

  QObject::connect(phosphorValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorValue(int)));
  phosphorValueSlider->setValue(25);
}

MainWindow::~MainWindow()
{

}
