#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include "display.h"

class Processor : public QObject
{
  Q_OBJECT
public:
  explicit Processor(QObject *parent = 0, Display *disp = NULL);
  Display *display;

signals:

public slots:
  void fpsCount();
  void digiPhos();
};

#endif // PROCESSOR_H
