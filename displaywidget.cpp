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
  painter.drawText(QPoint(921, 10), "FPS -  " + QString().setNum(fpsValue, 10));
  painter.drawText(QPoint(921, 20), "oscPS -  " + QString().setNum(oscValue, 10));
  makeMesh();
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
      pointBuffer->red = (pointBuffer->red > phosphorValue ? pointBuffer->red - phosphorValue: 0);
      pointBuffer->green = (pointBuffer->green > phosphorValue ? pointBuffer->green - phosphorValue: 0);
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

  for (int x = 0; x < DISPLAY_WIDTH - 1; x++)
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
