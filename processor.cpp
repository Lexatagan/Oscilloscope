#include "processor.h"
#include "displaywidget.h"
#include <math.h>
#include <QDebug>

Processor::Processor(QObject *parent) : QObject(parent)
{
  for (int i = 0; i < SEQUENCE_LENGTH; i++)
  {
    rawSequenceA[i] = 0;
    rawSequenceB[i] = 0;
  }
  unsigned int u = 8;
  //u = u >> 1;
  qDebug() << (-(signed int)u >> 1);
}

void Processor::scaleSequence(unsigned int *raw, unsigned int *scaled, int shift, unsigned int gain)
{
signed int tmp;
  for (int i = 0; i < SEQUENCE_LENGTH; i++)
  {
    tmp = DISPLAY_HEIGHT / 2 - shift + ((signed int)(DIRECT_BIAS - *(raw + i))) >> gain;
    if (tmp < 0)
      tmp = 0;
    if (tmp >= DISPLAY_HEIGHT)
      tmp = DISPLAY_HEIGHT - 1;
    *(scaled + i) = (unsigned int) tmp;
  }
}

void Processor::testSignal1(unsigned int *raw)
{
  float add;

  for (int x = 0; x < SEQUENCE_LENGTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    *(raw + x) = (unsigned int) (DIRECT_BIAS + 100 * (sin((float)x / 100 - 1*add)));
  }
}

void Processor::testSignal2(unsigned int *raw)
{
  float add;

  for (int x = 0; x < SEQUENCE_LENGTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    *(raw + x) = (unsigned int) (DIRECT_BIAS + 100 * (cos((float)x / 100 - 1*add)));
  }
}

unsigned int* Processor::getRawSequenceA()
{
  return rawSequenceA;
}

unsigned int* Processor::getRawSequenceB()
{
  return rawSequenceB;
}

