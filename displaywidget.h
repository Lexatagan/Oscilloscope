#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#define DISPLAY_WIDTH           1000
#define DISPLAY_HEIGHT          400
#define MESH_CELL_WIDTH         50
#define MESH_CELL_HEIGTH        40
#define DEFAULT_REFRESH_DELAY   20

class DisplayWidget : public QWidget
{
  Q_OBJECT
private:
  QTimer *refreshTimer;
  QTimer *counterTimer;
  QImage *imageBuffer;
  uint *imageData;
  uint fpsValue;
  uint oscValue;
  uint yOffsetLookUpTable[DISPLAY_HEIGHT];
  int fpsCounter;
  int oscCounter;
  int phosphorIncValue;
  int phosphorDecValue;

  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void countOsc();
  void inc(unsigned char *res, unsigned char a);
  void dec(unsigned char *res, unsigned char a);
  void digiP();
  void drawMesh();

public:
  enum TChannel{
    channelA = 2,
    channelB = 1,
    channelMesh = 0
  };

  explicit DisplayWidget(QWidget *parent = 0);
  QSize sizeHint() const;
  QSize minimumSizeHint() const;
  void setRefreshDelay(uint val);
  /*void testSignal1(unsigned int *data);
  void testSignal2(unsigned int *data);*/
  char getPhosphorIncValue();
  char getPhosphorDecValue();

signals:

private slots:
  void counter();

public slots:
  void scaled2VideoBuffer(ushort *scaled, uint length, DisplayWidget::TChannel channel);
  void setPhosphorIncValue(int val);
  void setPhosphorDecValue(int val);
  void refresh();
};

#endif // DISPLAYWIDGET_H
