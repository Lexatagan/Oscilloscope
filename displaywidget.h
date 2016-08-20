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
    channelA = 2,
    channelB = 1
  };

  explicit DisplayWidget(QWidget *parent = 0);
  QSize sizeHint() const;
  QSize minimumSizeHint() const;

  QImage *imageBuffer;
  uint *imageData;
  uint fpsValue;
  uint oscValue;
  void scaled2VideoBuffer(unsigned int *scaledArray, TChannel channel);
  void makeMesh();
  /*void testSignal1(unsigned int *data);
  void testSignal2(unsigned int *data);*/
  char getPhosphorIncValue();
  char getPhosphorDecValue();

private:
  /*struct TRgb{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
  };*/

  uint yOffsetLookUpTable[DISPLAY_HEIGHT];
  QTimer *counterTimer;
  QTimer *decTimer;
  int fpsCounter;
  int oscCounter;
  int phosphorIncValue;
  int phosphorDecValue;
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void countOsc();
  void inc(unsigned char *res, unsigned char a);
  void dec(unsigned char *res, unsigned char a);

signals:

private slots:
  void counter();

public slots:
  void setPhosphorIncValue(int val);
  void setPhosphorDecValue(int val);
  void refresh();
  void digiP();
};

#endif // DISPLAYWIDGET_H
