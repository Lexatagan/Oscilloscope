#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

class DisplayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DisplayWidget(QWidget *parent = 0);

  int videoBuffer[1000][400];
  int fpsValue;
  void setPhosphorValue(char val);
  char getPhosphorValue();

protected:
  QTimer *fpsTimer;
  QTimer *decTimer;
  int fpsCounter;
  int phosphorValue;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
  void fpsCount();
  void refresh();
  void digiP();
};

#endif // DISPLAYWIDGET_H
