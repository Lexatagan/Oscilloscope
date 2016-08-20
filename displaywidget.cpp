#include <QTimer>
#include "displaywidget.h"
#include <QPainter>
#include <QDebug>
#include <math.h>

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
  for (int i = 0; i < DISPLAY_HEIGHT; i++)
    yOffsetLookUpTable[i] = i * DISPLAY_WIDTH;

  phosphorIncValue = 0;

  counterTimer = new QTimer;
  QObject::connect(counterTimer, SIGNAL(timeout()), this, SLOT(counter()));
  counterTimer->start(1000);

  imageBuffer = new QImage(DISPLAY_WIDTH, DISPLAY_HEIGHT, QImage::Format_RGB32);
  imageData = (uint*)imageBuffer->scanLine(0);
  makeMesh();

  update();
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
  digiP();
  fpsCounter++;

  QPainter painter(this);
  painter.drawImage(QPoint(0,0), *imageBuffer);

  painter.setPen(0xFFFFFF);
  painter.drawText(QPoint(921, 10), "FPS -  " + QString().setNum(fpsValue, 10));
  painter.drawText(QPoint(921, 20), "oscPS -  " + QString().setNum(oscValue, 10));
}

void DisplayWidget::refresh()
{
  update();
}

void DisplayWidget::digiP()
{
  uint *point = imageData;
  for(int x = 0; x < DISPLAY_WIDTH * DISPLAY_HEIGHT; x++)
  {
    dec((uchar*)point + 1, phosphorDecValue);
    dec((uchar*)point + 2, phosphorDecValue);
    point++;
  }
}

void DisplayWidget::setPhosphorIncValue(int val)
{
  phosphorIncValue = val;
}

char DisplayWidget::getPhosphorIncValue()
{
  return phosphorIncValue;
}

void DisplayWidget::setPhosphorDecValue(int val)
{
  phosphorDecValue = val;
}

char DisplayWidget::getPhosphorDecValue()
{
  return phosphorDecValue;
}

void DisplayWidget::countOsc()
{
  oscCounter++;
}

void DisplayWidget::counter()
{
  oscValue = oscCounter;
  oscCounter = 0;
  fpsValue = fpsCounter;
  fpsCounter = 0;
}

QSize DisplayWidget::sizeHint() const
{
  return QSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

QSize DisplayWidget::minimumSizeHint() const
{
  return QSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

void DisplayWidget::scaled2VideoBuffer(unsigned int *scaledArray, TChannel channel)
{
  uint *x = imageData;
  uint *y0 = yOffsetLookUpTable;
  uint i;

  for (int t = 0; t < DISPLAY_WIDTH - 1; t++)
  {
    i = 0;
    if (*(scaledArray + 1) == *scaledArray)
      inc((uchar*)(x + *(y0 + *scaledArray)) + channel, phosphorIncValue);
    else if (*(scaledArray + 1) < *scaledArray)
      while (*scaledArray - i > *(scaledArray + 1))
      {
        inc((uchar*)(x + *(y0 + *scaledArray - i)) + channel, phosphorIncValue);
        i++;
      }
    else
      while (*scaledArray + i < *(scaledArray + 1))
      {
        inc((uchar*)(x + *(y0 + *scaledArray + i)) + channel, phosphorIncValue);
        i++;
      }
    scaledArray++;
    x++;
  }
  countOsc();
}

void DisplayWidget::makeMesh()
{
  uint *pointBuffer = imageData;
  for (int n = 0; n < DISPLAY_HEIGHT / MESH_CELL_HEIGTH; n++)       //Horizontal lines
  {
    for (int i = 0; i < DISPLAY_WIDTH; i++)
    {
      *pointBuffer++ = 255;
    }
    pointBuffer += DISPLAY_WIDTH * MESH_CELL_HEIGTH;
  }
  pointBuffer = imageData;
  for (int n = 0; n < DISPLAY_HEIGHT; n++)                          //Vertical lines
  {
    for (int i = 0; i < DISPLAY_WIDTH / MESH_CELL_WIDTH; i++)
    {
      *pointBuffer = 255;
      pointBuffer += MESH_CELL_WIDTH;
    }
  }
}

void DisplayWidget::inc(unsigned char *res, unsigned char a)
{
  *res = (255 - *res > a ? *res + a: 255);
}

void DisplayWidget::dec(unsigned char *res, unsigned char a)
{
  *res = (*res > a ? *res - a: 0);
}

/*void DisplayWidget::testSignal1(unsigned int *data)
{
  float add;
  unsigned int y;
  *(data++) = 0;
  *(data++) = 1;
  *(data++) = 2;
  *(data++) = 3;
  *(data++) = 4;
  *(data++) = 5;
  *(data++) = 6;
  *(data++) = 7;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 390;
  *(data++) = 7;
  *(data++) = 6;
  *(data++) = 5;
  *(data++) = 4;
  *(data++) = 3;
  *(data++) = 2;
  *(data++) = 1;
  *(data++) = 0;
  for (int x = 24; x < DISPLAY_WIDTH; x++)

  //for (int x = 0; x < DISPLAY_WIDTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    y = (unsigned int) (200 + 100 * (sin((float)x / 100 - 1*add)));
    *data = y;
    data++;
  }

}

void DisplayWidget::testSignal2(unsigned int *data)
{
  float add;
  unsigned int y;
  for (int x = 0; x < DISPLAY_WIDTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    y = (unsigned int) (200 + 100 * (cos((float)x / 100 - add)));
    *data = y;
    data++;
  }
}*/
