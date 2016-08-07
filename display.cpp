#include "display.h"
#include <QPainter>

Display::Display()
{
  for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
      //dataArray[x][y] = qrand();
      dataArray[x][y] = 0x5050F0;
  fpsValue = 0;
  fpsCounter = 0;
}

void Display::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  /*for (int x = 0; x < 500; x++)
      for (int y = 0; y < 400; y++)
          dataArray[x][y] = qrand();*/

  QImage imgDisplay(1000,400,QImage::Format_RGB32);
  for (int x = 0; x < 1000; x++)
      for (int y = 0; y < 400; y++)
          imgDisplay.setPixel(QPoint(x,y), dataArray[x][y]);
  painter->drawImage(0, 0, imgDisplay);
  painter->drawText(QPoint(501, 300), "FPS -  " + QString().setNum(fpsValue, 10));
  fpsCounter++;
}

void Display::advance(int phase)
{
static int ang;
  if (!phase)
      return;
  /*for (int x = 0; x < 1000; x++)
      for (int y = 0; y < 400; y++)
          dataArray[x][y]++;// = qrand();*/
  setRotation(0);
}

QRectF Display::boundingRect() const
{
    return QRectF(0, 0, 1000, 400);
}

