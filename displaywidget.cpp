#include <QTimer>
#include "displaywidget.h"
#include <QPainter>
#include <QDebug>
#include <math.h>

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
  /*for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
      dataArray[x][y] = rand();*/
  phosphorValue = 40;
  fpsTimer = new QTimer;
  QObject::connect(fpsTimer, SIGNAL(timeout()), this, SLOT(fpsCount()));
  fpsTimer->start(1000);

  //decTimer = new QTimer;
  //QObject::connect(decTimer, SIGNAL(timeout()), this, SLOT(digiP()));
  //decTimer->start(50);



  update();
}

void DisplayWidget::paintEvent(QPaintEvent * /* event */)
{
  digiP();
  fpsCounter++;
  /*static const QPoint points[4] =
  {
    QPoint(10, 80),
    QPoint(20, 10),
    QPoint(80, 30),
    QPoint(90, 70)
  };*/

  QImage *img = new QImage(1000, 400, QImage::Format_RGB32);

  for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
      img->setPixel(x, y, videoBuffer[x][y]);

  QPainter painter(this);
  painter.drawImage(QPoint(0,0), *img);
  img->~QImage();
  //painter.drawPolygon(points, 4);
  painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

  /*painter.save();
  painter.setPen(QPen(qrand()));
  for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
    {
      painter.setPen(dataArray[x][y]);
      painter.drawPoint(x, y);
    }
  painter.restore();*/
  /*for (int x = 0; x < width(); x += 100)
  {
    for (int y = 0; y < height(); y += 100)
    {
      painter.save();
      painter.translate(x, y);
      painter.drawPolygon(points, 4);
      painter.restore();
    }
  }
*/
  //painter.setRenderHint(QPainter::Antialiasing, false);
  //painter.setPen(palette().dark().color());
  //painter.setBrush(Qt::NoBrush);
  //painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
  painter.setPen(0xFFFFFF);
  painter.drawText(QPoint(501, 300), "FPS -  " + QString().setNum(fpsValue, 10));
}

void DisplayWidget::fpsCount()
{
  fpsValue = fpsCounter;
  fpsCounter = 0;
}

void DisplayWidget::refresh()
{
  float add = 0;
  int t;
  int y, z;
  for (int x = 0; x < 1000; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    y = (int) (200 + 100 * (sin((float)x / 100 - add)));
    videoBuffer[x][y] = 255;
    t = qrand() % 5000;
    if (t == 0)
    {
      t = 50 + qrand() % 50;
      for (z = y; z < y + t; z++)
        videoBuffer[x][z] = 255;
    }
  }

  update();
}

void DisplayWidget::digiP()
{
  for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
    {
      videoBuffer[x][y] -= phosphorValue;
      if (videoBuffer[x][y] < 0)
        videoBuffer[x][y] = 0;
    }
}

//void

void DisplayWidget::setPhosphorValue(char val)
{
  phosphorValue = val;
}

char DisplayWidget::getPhosphorValue()
{
  return phosphorValue;
}
