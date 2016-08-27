#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include "displaywidget.h"

#define DIRECT_BIAS           2048
#define DINAMIC_RANGE         4096

class Processor : public QObject
{
  Q_OBJECT
private:
public:
  explicit Processor(QObject *parent = 0);
  void scaleRaw(ushort *raw, uint length, ushort *scaled, int shift, uint gain);
  void testSignalInt(uint *raw);
  void testSignal1(uint *raw);
  void testSignal2(uint *raw);
  void deserialize(ushort *dual, uint eachLength, ushort *channelA, ushort *channelB);

signals:
  void scaledReady(ushort*, uint, DisplayWidget::TChannel);

public slots:
};

#endif // PROCESSOR_H
