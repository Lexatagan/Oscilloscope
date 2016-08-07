#include "mainwindow.h"
#include <QtWidgets>
#include "displayWidget.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  DisplayWidget *displayWidget = new DisplayWidget(this);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(3, 1);
  mainLayout->addWidget(displayWidget, 0, 0, 1, 4);
  setLayout(mainLayout);
  displayWidget->setGeometry(0, 0, 1000, 400);
  displayWidget->show();

  this->setGeometry(50, 50, 1200, 500);
  //resize(400, 400);
  //setCentralWidget(displayWidget);
  tmr = new QTimer;
  displayWidget->setPhosphorValue(6);
  QObject::connect(tmr, SIGNAL(timeout()), displayWidget, SLOT(refresh()));
  tmr->start(20);
}

MainWindow::~MainWindow()
{

}
