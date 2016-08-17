#include <QTimer>
#include "displaywidget.h"
#include <QPainter>
#include <QDebug>
#include <math.h>

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
  for (int x = 0; x < DISPLAY_WIDTH; x++)
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
      videoBuffer[x][y] = 0;
  phosphorValue = 0;

  counterTimer = new QTimer;
  QObject::connect(counterTimer, SIGNAL(timeout()), this, SLOT(counter()));
  counterTimer->start(1000);

  makeMesh();

  update();
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
  digiP();
  fpsCounter++;
  QImage *img = new QImage(DISPLAY_WIDTH, DISPLAY_HEIGHT, QImage::Format_RGB32);

  for (int x = 0; x < DISPLAY_WIDTH; x++)
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
      img->setPixel(x, y, videoBuffer[x][y]);
  /*for (int i = 0; i < 300; i++)
    *(img->scanLine(i) + 21) = 0xFF;*/
  /*const char *buf = (const char*)videoBuffer;
  img->loadFromData(buf);*/

  QPainter painter(this);
  painter.drawImage(QPoint(0,0), *img);
  img->~QImage();

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
  TRgb *pointBuffer;
  for (int x = 0; x < DISPLAY_WIDTH; x++)
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
      pointBuffer = (TRgb*)(&videoBuffer[x][y]);
      dec(&pointBuffer->red, phosphorValue);
      dec(&pointBuffer->green, phosphorValue);
      //pointBuffer->red = (pointBuffer->red > phosphorValue ? pointBuffer->red - phosphorValue: 0);
      //pointBuffer->green = (pointBuffer->green > phosphorValue ? pointBuffer->green - phosphorValue: 0);
      //pointBuffer->blue = (pointBuffer->blue > phosphorValue ? pointBuffer->blue - phosphorValue: 0);
    }
}

void DisplayWidget::setPhosphorValue(int val)
{
  phosphorValue = val;
}

char DisplayWidget::getPhosphorValue()
{
  return phosphorValue;
}

void DisplayWidget::testSignal()
{
  unsigned int Data[DISPLAY_WIDTH];
  testSignal1(Data);
  array2VideoBuffer(Data, channelA);
  testSignal2(Data);
  array2VideoBuffer(Data, channelB);
  //countOsc();
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

void DisplayWidget::array2VideoBuffer(unsigned int *data, TChannel channel)
{
  unsigned int color;
  unsigned int *pointBuffer;
  unsigned int i = 0;
  pointBuffer = (unsigned int*)videoBuffer;
  if (channel == channelA)
    color = 255 * 256 * 256; //Red
  else
    color = 255 * 256; //Green

  /*for (int x = 0; x < DISPLAY_WIDTH - 1; x++)
  {
    i = 0;
    if (*(data + 1) == *data)
      *(pointBuffer + *data) = color;
    else if (*(data + 1) < *data)
      while ((*data) - i > *(data + 1))
      {
        *(pointBuffer + *data - i) = color;
        i++;
      }
    else
      while ((*data) + i < *(data + 1))
      {
        *(pointBuffer + *data + i) = color;
        i++;
      }

    data++;
    pointBuffer += DISPLAY_HEIGHT;
  }*/
  if (channel == channelA)
    color = 1;
  else
    color = 2;
  for (int x = 0; x < DISPLAY_WIDTH - 1; x++)
  {
    i = 0;
    if (*(data + 1) == *data)
      inc((unsigned char*)(pointBuffer + *data) + color, 255);
      //*(pointBuffer + *data) = color;
    else if (*(data + 1) < *data)
      while ((*data) - i > *(data + 1))
      {
        //*(pointBuffer + *data - i) = color;
        inc((unsigned char*)(pointBuffer + *data - i) + color, 255);
        i++;
      }
    else
      while ((*data) + i < *(data + 1))
      {
        //*(pointBuffer + *data + i) = color;
        inc((unsigned char*)(pointBuffer + *data + i) + color, 255);
        i++;
      }

    data++;
    pointBuffer += DISPLAY_HEIGHT;
  }

  countOsc();
}

void DisplayWidget::testSignal1(unsigned int *data)
{
  float add;
  unsigned int y;
  /**(data++) = 0;
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
  *(data++) = 0;*/

  for (int x = 0; x < DISPLAY_WIDTH; x++)
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
}

void DisplayWidget::makeMesh()
{
  int color = 255; //blue
  unsigned int *pointBuffer;
  pointBuffer = (unsigned int*)videoBuffer;
  for (int n = 0; n < DISPLAY_WIDTH / MESH_CELL_WIDTH; n++)
  {
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
      *pointBuffer++ = color;
    }
    pointBuffer += DISPLAY_HEIGHT * MESH_CELL_WIDTH;
  }
  pointBuffer = (unsigned int*)videoBuffer;
  for (int n = 0; n < DISPLAY_WIDTH; n++)
  {
    for (int i = 0; i < DISPLAY_HEIGHT / MESH_CELL_HEIGTH; i++)
    {
      *pointBuffer = color;
      pointBuffer += MESH_CELL_HEIGTH;
    }
  }
}

void DisplayWidget::inc(unsigned char *res, unsigned char a)
{
  /*int tmp;
  tmp = (int) *res + a;
  if (tmp > 255)
    tmp = 255;
  *res = (unsigned char) tmp;*/
  *res = (255 - *res > a ? *res + a: 255);
}

void DisplayWidget::dec(unsigned char *res, unsigned char a)
{
  /*int tmp;
  tmp = (int) *res - a;
  if (tmp < 0)
    tmp = 0;
  *res = (unsigned char) tmp;*/
  *res = (*res > a ? *res - a: 0);
}

