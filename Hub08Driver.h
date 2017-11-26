#ifndef Hub08Driver_h
#define Hub08Driver_h

#include <Arduino.h>
#include <SPI.h>

class Hub08Driver
{
private:
  int pinOE;              //output enable
  int pinLA;              //line a 行信号 最低位
  int pinLB;              //line b 行信号
  int pinLC;              //line c 行信号
  int pinLD;              //line d 行信号 最高位
  int pinSTB;             // 595锁存信号
  int horizontalUnitSize; //水平最小LED单元级联数量
  int scanLineIndex = 0;
  byte *buffer;
  bool isEnable = true;
  bool isDebug = true;
  bool isReverse = false;

  //LED单元的边长,HL-M1388BR或者1088AS
  const int LED_UNIT_SIDE_SIZE = 8;

  void init();

  void resetScanLine();

  //从指定的行获取指定位置的byte数据
  byte getByteOfLine(int lineIndex, int byteIndex);

  //选择行
  void pickLine(int row);

  //选择列
  void pickColumns(int lineIndex);

  //锁定行
  void lockLine();

  int getBufferSize();

  void debug(String content);

public:
  //硬件SPI,不需要cs引脚,
  //高度必定是16,目前不支持垂直级联，只支持横向级联处理
  //r1=>mosi,stb=>any out pin,ck=>sck
  Hub08Driver(int horizontalUnitSize, int pinOE, int pinLA, int pinLB, int pinLC, int pinLD, int pinSTB);

  //开启LED模块
  void switchOn();

  //关闭LED模块
  void switchOff();

  //扫描行
  void scanLine();

  //反转
  void reverse();

  //清除所有的点阵数据
  void clear();

  //点亮所有的点
  void full();

  //获取画布缓冲
  byte *getBuffer();

  //绘制
  void draw(byte *buffer);
};

#endif //Hub08Driver.h
