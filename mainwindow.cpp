
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

  /*------Shift A---------------------------------------------------------------------*/
  shiftASlider = new QSlider(this);
  shiftASlider->setMinimum(DIRECT_BIAS - 3200);        //6400/16 = DISPLAY_HEIGTH
  shiftASlider->setMaximum(DIRECT_BIAS + 3200);
  shiftASlider->setValue(DIRECT_BIAS);
  shiftASlider->setStyleSheet(SHIFT_SLIDER_STYLE_RED);

  /*------Shift B---------------------------------------------------------------------*/
  shiftBSlider = new QSlider(this);
  shiftBSlider->setMinimum(DIRECT_BIAS - 3200);        //6400/16 = DISPLAY_HEIGTH
  shiftBSlider->setMaximum(DIRECT_BIAS + 3200);
  shiftBSlider->setValue(DIRECT_BIAS);
  shiftBSlider->setStyleSheet(SHIFT_SLIDER_STYLE_GREEN);

  /*------Gain A----------------------------------------------------------------------*/
  QGroupBox *channelAGainGroupBox = new QGroupBox(this);
  channelAGainGroupBox->setTitle(tr("Gain A"));
  gainAx1RadioButton = new QRadioButton(tr(" x1"));
  gainAx2RadioButton = new QRadioButton(tr(" x2"));
  gainAx4RadioButton = new QRadioButton(tr(" x4"));
  gainAx8RadioButton = new QRadioButton(tr(" x8"));
  gainAx16RadioButton = new QRadioButton(tr("x16"));

  gainAx1RadioButton->setChecked(true);
  QVBoxLayout *gainALayout = new QVBoxLayout;
  gainALayout->addWidget(gainAx1RadioButton);
  gainALayout->addWidget(gainAx2RadioButton);
  gainALayout->addWidget(gainAx4RadioButton);
  gainALayout->addWidget(gainAx8RadioButton);
  gainALayout->addWidget(gainAx16RadioButton);
  channelAGainGroupBox->setLayout(gainALayout);

  /*------Gain B----------------------------------------------------------------------*/
  QGroupBox *channelBGainGroupBox = new QGroupBox(this);
  channelBGainGroupBox->setTitle(tr("Gain B"));
  gainBx1RadioButton = new QRadioButton(tr(" x1"));
  gainBx2RadioButton = new QRadioButton(tr(" x2"));
  gainBx4RadioButton = new QRadioButton(tr(" x4"));
  gainBx8RadioButton = new QRadioButton(tr(" x8"));
  gainBx16RadioButton = new QRadioButton(tr("x16"));
  gainBx1RadioButton->setChecked(true);

  QVBoxLayout *gainBLayout = new QVBoxLayout;
  gainBLayout->addWidget(gainBx1RadioButton);
  gainBLayout->addWidget(gainBx2RadioButton);
  gainBLayout->addWidget(gainBx4RadioButton);
  gainBLayout->addWidget(gainBx8RadioButton);
  gainBLayout->addWidget(gainBx16RadioButton);
  channelBGainGroupBox->setLayout(gainBLayout);

  /*------Gain------------------------------------------------------------------------*/
  QHBoxLayout *controlsLayout = new QHBoxLayout;
  controlsLayout->addWidget(channelAGainGroupBox);
  controlsLayout->addWidget(channelBGainGroupBox);
  controlsLayout->addStretch(1);

  /*------Common----------------------------------------------------------------------*/
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

  QThread *usbReaderThread = new QThread;
  USBCommunicator *communicator = new USBCommunicator();
  communicator->moveToThread(usbReaderThread);
  connect(usbReaderThread, SIGNAL(started()), communicator, SLOT(process()));
  usbReaderThread->start();
  manager = new Manager;
  connect(communicator, SIGNAL(rawReady(ushort*,USBCommunicator::TDataStructure)), manager, SLOT(receiveRaw(ushort*,USBCommunicator::TDataStructure)));
  connect(manager, SIGNAL(scaledReady(ushort*,uint,DisplayWidget::TChannel)), displayWidget, SLOT(scaled2VideoBuffer(ushort*,uint,DisplayWidget::TChannel)));


  connect(phosphorIncValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorIncValue(int)));
  connect(phosphorDecValueSlider, SIGNAL(valueChanged(int)), displayWidget, SLOT(setPhosphorDecValue(int)));
  phosphorIncValueSlider->setValue(255);
  phosphorDecValueSlider->setValue(25);

  connect(gainAx1RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainAx2RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainAx4RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainAx8RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainAx16RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainBx1RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainBx2RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainBx4RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainBx8RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(gainBx16RadioButton, SIGNAL(released()), this, SLOT(changeGain()));
  connect(shiftASlider, SIGNAL(valueChanged(int)), this, SLOT(changeShiftA(int)));
  connect(shiftBSlider, SIGNAL(valueChanged(int)), this, SLOT(changeShiftB(int)));
  changeGain();
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeGain()
{
  if (gainAx1RadioButton->isChecked())
    manager->setGain(4, DisplayWidget::channelA);
  if (gainAx2RadioButton->isChecked())
    manager->setGain(3, DisplayWidget::channelA);
  if (gainAx4RadioButton->isChecked())
    manager->setGain(2, DisplayWidget::channelA);
  if (gainAx8RadioButton->isChecked())
    manager->setGain(1, DisplayWidget::channelA);
  if (gainAx16RadioButton->isChecked())
    manager->setGain(0, DisplayWidget::channelA);

  if (gainBx1RadioButton->isChecked())
    manager->setGain(4, DisplayWidget::channelB);
  if (gainBx2RadioButton->isChecked())
    manager->setGain(3, DisplayWidget::channelB);
  if (gainBx4RadioButton->isChecked())
    manager->setGain(2, DisplayWidget::channelB);
  if (gainBx8RadioButton->isChecked())
    manager->setGain(1, DisplayWidget::channelB);
  if (gainBx16RadioButton->isChecked())
    manager->setGain(0, DisplayWidget::channelB);
}

void MainWindow::changeShiftA(int val)
{
  manager->setShift(val, DisplayWidget::channelA);
}

void MainWindow::changeShiftB(int val)
{
  manager->setShift(val, DisplayWidget::channelB);
}
