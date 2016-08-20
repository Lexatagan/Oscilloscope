#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  displayWidget = new DisplayWidget(this);
  QSlider *phosphorIncValueSlider = new QSlider(this);
  phosphorIncValueSlider->setMinimum(0);
  phosphorIncValueSlider->setMaximum(255);
  QSlider *phosphorDecValueSlider = new QSlider(this);
  phosphorDecValueSlider->setMinimum(0);
  phosphorDecValueSlider->setMaximum(50);
  QLabel *phosphorLabel = new QLabel("digiP", this);

  shiftASlider = new QSlider(this);
  shiftASlider->setMinimum(-400);
  shiftASlider->setMaximum(400);
  shiftASlider->setStyleSheet(SHIFT_SLIDER_STYLE_RED);

  shiftBSlider = new QSlider(this);
  shiftBSlider->setMinimum(-400);
  shiftBSlider->setMaximum(400);
  shiftBSlider->setStyleSheet(SHIFT_SLIDER_STYLE_GREEN);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(displayWidget, 0, 0, 2, 4);
  mainLayout->addWidget(phosphorLabel, 0, 5, 1, 2);
  mainLayout->addWidget(phosphorIncValueSlider, 1, 5, 1, 1);
  mainLayout->addWidget(phosphorDecValueSlider, 1, 6, 1, 1);
  mainLayout->addWidget(shiftASlider, 0, 3, 2, 1);
  mainLayout->addWidget(shiftBSlider, 0, 4, 2, 1);
  container = new QWidget(this);
  container->setLayout(mainLayout);
  setCentralWidget(container);

  this->setGeometry(50, 50, 1120, 400);

  tmr = new QTimer;
  QObject::connect(tmr, SIGNAL(timeout()), displayWidget, SLOT(refresh()));
  tmr->start(20);

  testSignalTimer = new QTimer;
  //QObject::connect(testSignalTimer, SIGNAL(timeout()), displayWidget, SLOT(testSignal()));
  QObject::connect(testSignalTimer, SIGNAL(timeout()), this, SLOT(tstSlot()));
  testSignalTimer->start(0);

  QObject::connect(phosphorIncValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorIncValue(int)));
  QObject::connect(phosphorDecValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorDecValue(int)));
  phosphorIncValueSlider->setValue(255);
  phosphorDecValueSlider->setValue(25);

  processor = new Processor();
}

MainWindow::~MainWindow()
{

}

void MainWindow::tstSlot()
{
  unsigned int scaled[SEQUENCE_LENGTH];
  processor->testSignal1(processor->getRawSequenceA());
  //processor->testSignalInt(processor->getRawSequenceA());
  processor->scaleSequence(processor->getRawSequenceA(), scaled, shiftASlider->value(), 0);
  displayWidget->scaled2VideoBuffer(scaled, DisplayWidget::channelA);
  processor->testSignal2(processor->getRawSequenceB());
  //processor->testSignalInt(processor->getRawSequenceB());
  processor->scaleSequence(processor->getRawSequenceB(), scaled, shiftBSlider->value(), 1);
  displayWidget->scaled2VideoBuffer(scaled, DisplayWidget::channelB);
}
