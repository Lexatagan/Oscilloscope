#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#define DISPLAY_WIDTH   1000
#define DISPLAY_HEIGHT  400
#define MESH_CELL_WIDTH 50
#define MESH_CELL_HEIGTH 40

class DisplayWidget : public QWidget
{
  Q_OBJECT
private:

public:
  enum TChannel{
    channelA,
    channelB
  };

  explicit DisplayWidget(QWidget *parent = 0);
  unsigned int videoBuffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];
  int fpsValue;
  int oscValue;
  void array2VideoBuffer(unsigned int *data, TChannel channel);
  void makeMesh();
  void testSignal1(unsigned int *data);
  void testSignal2(unsigned int *data);
  QSize sizeHint() const;
  QSize minimumSizeHint() const;
  char getPhosphorValue();

private:
  struct TRgb{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
  };

  QTimer *counterTimer;
  QTimer *decTimer;
  int fpsCounter;
  int oscCounter;
  int phosphorValue;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void countOsc();
  void inc(unsigned char *res, unsigned char a);
  void dec(unsigned char *res, unsigned char a);

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
