#include "processor.h"

Processor::Processor(QObject *parent, Display *disp) : QObject(parent)
{
  display = disp;
}

void Processor::fpsCount()
{
  display->fpsValue = display->fpsCounter;
  display->fpsCounter = 0;
}

void Processor::digiPhos()
{
  for (int x = 0; x < 1000; x++)
    for (int y = 0; y < 400; y++)
      display->dataArray[x][y] = (display->dataArray[x][y] - 20) % 255;
      //display->dataArray[x][y] = display->dataArray[x][y] + qrand() % 3 - 1;*/
}
