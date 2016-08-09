#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#define DISPLAY_WIDTH   1000
#define DISPLAY_HEIGHT  400

class DisplayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DisplayWidget(QWidget *parent = 0);

  int videoBuffer[1000][400];
  QImage vBuffer;
  int fpsValue;
  int oscValue;
  QSize sizeHint() const;
  QSize minimumSizeHint() const;
  char getPhosphorValue();

protected:
  QTimer *fpsTimer;
  QTimer *decTimer;
  int fpsCounter;
  int oscCounter;
  int phosphorValue;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void countOsc();

signals:

private slots:
  void counter();

public slots:
  void setPhosphorValue(int val);
  void refresh();
  void digiP();
  void testSignal();
};

#endif // DISPLAYWIDGET_H
