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
  int width;
  int height;
  int column;
  byte *buffer;

  void init();
  void setPixelState(int x, int y, int bit);

  bool containPixel(int x, int y);

public:
  int bufferSize;

  BufferCanvas(byte *buffer, int bufferSize, int width, int height);

  static void shiftVerticalLineUp(byte *buffer, int start, int end, bool circular);

  static void shiftVerticalLineDown(byte *buffer, int start, int end, bool circular);

  static void shiftHorizontalLineRight(byte *buffer, int start, int end, bool circular);

  static void shiftHorizontalLineLeft(byte *buffer, int start, int end, bool circular);

  static void shiftBufferUp(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular);

  static void shiftBufferDown(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular);

  static void shiftBufferRight(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular);

  static void shiftBufferLeft(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular);

  int getWidth();

  int getHeight();

  void clear();

  void full();

  void reverse();

  void drawPixel(int x, int y);

  void clearPixel(int x, int y);

  void drawLine(int startX, int startY, int endX, int endY);

  void drawHorizontalLine(int startX, int startY, int length);

  void drawVerticalLine(int startX, int startY, int length);

  void drawRect(int x, int y, int width, int height);

  void drawBorderRect(int x, int y, int width, int height, int thikness);

  void drawBorderRect(int x, int y, int width, int height);

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
