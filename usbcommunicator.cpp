#include "usbcommunicator.h"
#include <QDebug>
#include <windows.h>

USBCommunicator::USBCommunicator(QObject *parent) : QObject(parent)
{
  qRegisterMetaType<USBCommunicator::TDataStructure>("USBCommunicator::TDataStructure");
}

void USBCommunicator::process()
{
  float add;
  ushort *raw;

  while (true)
  {
    add = 0;
    raw = readBuffer;
    for (int x = 0; x < CHANNEL_SAMPLE_VOLUME * 2; x++)
    {
      add += ((float)(qrand() % 20 - 10)) / 1000;
      *(raw++) = (uint)(DIRECT_BIAS + 100 * (sin((float)x / 100 - 1 * add)));
    }
    emit rawReady(readBuffer, Dual);
    emit rawReady(readBuffer, Single);
    //Sleep(1000);
  }
}

void USBCommunicator::stop()
{
  this->~QObject();
}
