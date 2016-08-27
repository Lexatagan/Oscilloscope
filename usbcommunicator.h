#ifndef USBCOMMUNICATOR_H
#define USBCOMMUNICATOR_H

#include <QObject>
#include "processor.h"
#include <math.h>

#define SERVICE_DATA_LENGTH     10
#define CHANNEL_SAMPLE_VOLUME   1024

class USBCommunicator : public QObject
{
  Q_OBJECT

private:
  ushort readBuffer[SERVICE_DATA_LENGTH + CHANNEL_SAMPLE_VOLUME * 2];

public:
  enum TDataStructure{
    Single,
    Dual
  };
  explicit USBCommunicator(QObject *parent = 0);

signals:
  void receivedSingle(ushort*, uint);
  void receivedDual(ushort*, uint);
  void rawReady(ushort*, USBCommunicator::TDataStructure);

public slots:
  void process();
  void stop();
};

#endif // USBCOMMUNICATOR_H
