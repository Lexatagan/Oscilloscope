#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "usbcommunicator.h"
#include "displaywidget.h"

class Manager : public QObject
{
  Q_OBJECT
private:
  int shiftA;
  int shiftB;
  int gainA;
  int gainB;
  Processor *processor;
  ushort readBuffer[CHANNEL_SAMPLE_VOLUME * 2];
  ushort channelABuffer[CHANNEL_SAMPLE_VOLUME];
  ushort channelBBuffer[CHANNEL_SAMPLE_VOLUME];

public:
  explicit Manager(QObject *parent = 0);
  void setShift(int shift, DisplayWidget::TChannel channel);
  void setGain(int gain, DisplayWidget::TChannel);

signals:
  void scaledReady(ushort *scaled, uint length, DisplayWidget::TChannel);

public slots:
  void receiveRaw(ushort *raw, USBCommunicator::TDataStructure structure);
};

#endif // MANAGER_H
