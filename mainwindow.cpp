//#include <QtWidgets>
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
  shiftASlider->setMinimum(2048 - 3200);        //6400/16 = DISPLAY_HEIGTH
  shiftASlider->setMaximum(2048 + 3200);
  shiftASlider->setValue(2048);
  shiftASlider->setStyleSheet(SHIFT_SLIDER_STYLE_RED);

  shiftBSlider = new QSlider(this);
  shiftBSlider->setMinimum(2048 - 3200);        //6400/16 = DISPLAY_HEIGTH
  shiftBSlider->setMaximum(2048 + 3200);
  shiftBSlider->setValue(2048);
  shiftBSlider->setStyleSheet(SHIFT_SLIDER_STYLE_GREEN);

  QGroupBox *channelAGainGroupBox = new QGroupBox(this);
  channelAGainGroupBox->setTitle(tr("Gain A"));
  gainAx1RadioButton = new QRadioButton(tr(" x1"));
  gainAx2RadioButton = new QRadioButton(tr(" x2"));
  gainAx4RadioButton = new QRadioButton(tr(" x4"));
  gainAx8RadioButton = new QRadioButton(tr(" x8"));
  gainAx16RadioButton = new QRadioButton(tr("x16"));

  gainAx16RadioButton->setChecked(true);
  QVBoxLayout *gainALayout = new QVBoxLayout;
  gainALayout->addWidget(gainAx1RadioButton);
  gainALayout->addWidget(gainAx2RadioButton);
  gainALayout->addWidget(gainAx4RadioButton);
  gainALayout->addWidget(gainAx8RadioButton);
  gainALayout->addWidget(gainAx16RadioButton);
  channelAGainGroupBox->setLayout(gainALayout);

  QGroupBox *channelBGainGroupBox = new QGroupBox(this);
  channelBGainGroupBox->setTitle(tr("Gain B"));
  gainBx1RadioButton = new QRadioButton(tr(" x1"));
  gainBx2RadioButton = new QRadioButton(tr(" x2"));
  gainBx4RadioButton = new QRadioButton(tr(" x4"));
  gainBx8RadioButton = new QRadioButton(tr(" x8"));
  gainBx16RadioButton = new QRadioButton(tr("x16"));
  gainBx16RadioButton->setChecked(true);
  QVBoxLayout *gainBLayout = new QVBoxLayout;
  gainBLayout->addWidget(gainBx1RadioButton);
  gainBLayout->addWidget(gainBx2RadioButton);
  gainBLayout->addWidget(gainBx4RadioButton);
  gainBLayout->addWidget(gainBx8RadioButton);
  gainBLayout->addWidget(gainBx16RadioButton);
  channelBGainGroupBox->setLayout(gainBLayout);

  QHBoxLayout *controlsLayout = new QHBoxLayout;
  controlsLayout->addWidget(channelAGainGroupBox);
  controlsLayout->addWidget(channelBGainGroupBox);
  controlsLayout->addStretch(1);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(displayWidget, 0, 0, 2, 4);
  mainLayout->addWidget(phosphorLabel, 0, 5, 1, 2);
  mainLayout->addWidget(phosphorIncValueSlider, 1, 5, 1, 1);
  mainLayout->addWidget(phosphorDecValueSlider, 1, 6, 1, 1);
  mainLayout->addWidget(shiftASlider, 0, 3, 2, 1);
  mainLayout->addWidget(shiftBSlider, 0, 4, 2, 1);
  mainLayout->addLayout(controlsLayout, 2, 0, 1, 1);
  container = new QWidget(this);
  container->setLayout(mainLayout);
  setCentralWidget(container);

  this->setGeometry(50, 50, 1120, 500);

  tmr = new QTimer;
  QObject::connect(tmr, SIGNAL(timeout()), displayWidget, SLOT(refresh()));
  tmr->start(20);

  testSignalTimer = new QTimer;
  QObject::connect(testSignalTimer, SIGNAL(timeout()), this, SLOT(tstSlot()));
  testSignalTimer->start(0);

  QObject::connect(phosphorIncValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorIncValue(int)));
  QObject::connect(phosphorDecValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorDecValue(int)));
  phosphorIncValueSlider->setValue(255);
  phosphorDecValueSlider->setValue(25);

  QObject::connect(gainAx1RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainAx2RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainAx4RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainAx8RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainAx16RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainBx1RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainBx2RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainBx4RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainBx8RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  QObject::connect(gainBx16RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  changeGain();
  processor = new Processor();
}

MainWindow::~MainWindow()
{

}

void MainWindow::tstSlot()
{
  unsigned int scaled[SEQUENCE_LENGTH];
  processor->testSignal1(processor->getRawSequenceA());
  processor->scaleSequence(processor->getRawSequenceA(), scaled, shiftASlider->value(), gainA);
  displayWidget->scaled2VideoBuffer(scaled, DisplayWidget::channelA);
  processor->testSignal2(processor->getRawSequenceB());
  processor->scaleSequence(processor->getRawSequenceB(), scaled, shiftBSlider->value(), gainB);
  displayWidget->scaled2VideoBuffer(scaled, DisplayWidget::channelB);
}

void MainWindow::changeGain()
{
  qDebug() << "yeee";
  if (gainAx1RadioButton->isChecked())
      gainA = 4;
  if (gainAx2RadioButton->isChecked())
      gainA = 3;
  if (gainAx4RadioButton->isChecked())
      gainA = 2;
  if (gainAx8RadioButton->isChecked())
      gainA = 1;
  if (gainAx16RadioButton->isChecked())
      gainA = 0;

  if (gainBx1RadioButton->isChecked())
      gainB = 4;
  if (gainBx2RadioButton->isChecked())
      gainB = 3;
  if (gainBx4RadioButton->isChecked())
      gainB = 2;
  if (gainBx8RadioButton->isChecked())
      gainB = 1;
  if (gainBx16RadioButton->isChecked())
      gainB = 0;
}
