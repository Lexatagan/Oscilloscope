#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include "display.h"

#define SEQUENCE_LENGTH 1000
#define DIRECT_BIAS     2048

class Processor : public QObject
{
  Q_OBJECT
private:
  unsigned int rawSequenceA[SEQUENCE_LENGTH];
  unsigned int rawSequenceB[SEQUENCE_LENGTH];
public:
  explicit Processor(QObject *parent = 0);
  unsigned int* getRawSequenceA();
  unsigned int* getRawSequenceB();
  void scaleSequence(uint *raw, uint *scaled, int shift, uint gain);
  void testSignalInt(uint *raw);
  void testSignal1(uint *raw);
  void testSignal2(uint *raw);

signals:

public slots:
};

#endif // PROCESSOR_H
