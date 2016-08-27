#include "processor.h"
#include "displaywidget.h"
#include <math.h>
#include <QDebug>

Processor::Processor(QObject *parent) : QObject(parent)
{
}

void Processor::scaleRaw(ushort *raw, uint length, ushort *scaled, int shift, uint gain)
{
  int tmp;
  for (uint i = 0; i < length; i++)
  {
    tmp = DISPLAY_HEIGHT / 2 + ((DINAMIC_RANGE - shift - *((ushort*)raw + i)) >> gain);
    if (tmp < 0)
      tmp = 0;
    if (tmp >= DISPLAY_HEIGHT)
      tmp = DISPLAY_HEIGHT - 1;
    *(scaled + i) = (uint) tmp;
  }
}

void Processor::testSignalInt(uint *raw)
{
  /*int add = 0;

  for (int x = 0; x < SEQUENCE_LENGTH; x++)
  {
    *(raw++) = (uint) (DIRECT_BIAS * 0 + (4*x));// 100 * (sin((float)x / 100 - 1 * add)));
  }*/
}

void Processor::testSignal1(uint *raw)
{
  /*float add = 0;

  for (int x = 0; x < SEQUENCE_LENGTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    *(raw++) = (uint) (DIRECT_BIAS + 100 * (sin((float)x / 100 - 1 * add)));
  }*/
}

void Processor::testSignal2(uint *raw)
{
  /*float add = 0;

  for (int x = 0; x < SEQUENCE_LENGTH; x++)
  {
    add += ((float)(qrand() % 20 - 10)) / 1000;
    *(raw++) = (uint) (DIRECT_BIAS + 2048 * (cos((float)x / 100 - 1 * add)));
  }*/
}

void Processor::deserialize(ushort *dual, uint eachLength, ushort *channelA, ushort *channelB)
{
  for (uint i = 0; i < eachLength; i++)
  {
    *channelA++ = *dual++;
    *channelB++ = *dual++;
  }
}
