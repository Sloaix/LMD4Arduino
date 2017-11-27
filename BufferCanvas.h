#ifndef BufferCanvas_h
#define BufferCanvas_h

#include <Arduino.h>

/**
 * BufferCanvas，可以在指定宽高的Buffer上使用更多方法绘制1bit位图
 */
class BufferCanvas
{
private:
  const int MODE_FILL = 0x00;
  const int MODE_CLEAR = MODE_FILL << 1;
  byte *buffer;
  int width;
  int height;
  int horizontalUnitSize;

  void init();

  int getBufferSize();

  void shiftRightByteArray(int start, int end,bool circular);

  void shiftLeftByteArray(int start, int end,bool circular);

public:
  BufferCanvas(byte *buffer, int width, int height);

  int getWidth();

  int getHeight();

  int getHorizontalUnitSize();

  void clear();

  void full();

  void reverse();

  void drawPixel(int x, int y);

  void drawLine(int startX, int startY, int endX, int endY);

  void drawHorizontalLine(int startX, int startY, int length);

  void drawVerticalLine(int startX, int startY, int length);

  void drawRect(int x, int y, int width, int height);

  void drawBorderRect(int x, int y, int width, int height, int border);

  void drawOverlay(byte *buffer, int byteNumEachLine);

  void drawBuffer(byte *buffer, int byteNumEachLine);

  void drawCanvas(BufferCanvas *canvas);

  void shiftUp(int distance, bool circular);

  void shiftRight(int distance, bool circular);

  void shiftDown(int distance, bool circular);

  void shiftLeft(int distance, bool circular);

  void rotateRight90();

  void rotateRight180();

  void rotateRight270();

  void rotateRight360();

  void rotateLeft90();

  void rotateLeft180();

  void rotateLeft270();

  void rotateLeft360();

  void flipHorizontal();

  void flipVertical();
};

#endif //BufferCanvas.h
