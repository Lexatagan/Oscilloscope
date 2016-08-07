#include "mainwindow.h"
#include <QtWidgets>
#include <QApplication>
#include "display.h"
#include "processor.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  /*QGraphicsScene scene;

  Display *display;
  display = new Display;
  display->setPos(0,0);
  scene.addItem(display);

  QGraphicsView view(&scene);
  view.resize(1002, 402);
  view.show();

  Processor *processor = new Processor(0, display);
*/
  /*QTimer timer;
  QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
  timer.start(1);


  QTimer dpTimer;
  QObject::connect(&dpTimer, SIGNAL(timeout()), processor, SLOT(digiPhos()));
  dpTimer.start(5);*/

  return a.exec();
}
