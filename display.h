#ifndef DISPLAY_H
#define DISPLAY_H
#include <QObject>
#include <QGraphicsItem>


class Display : public QGraphicsItem
{
public:
  Display();
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  void advance(int phase);
  unsigned int dataArray[1000][400];
  int fpsCounter;
  int fpsValue;
};

#endif // DISPLAY_H
