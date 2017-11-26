Arduino LED点阵驱动,目前支持HUB08接口,MAX7219芯片驱动即将到来。

This is a "Led Matrix Driver" for arduino,supprted hub08 interface.max7219 driver is coming soon.


# 视频和照片(Youtube and photo)

## 视频
[Youtube视频](https://www.youtube.com/watch?v=_efVyvmUtT0)

## 照片
![](https://raw.githubusercontent.com/lsxiao/LMD4Arduino/master/preview.jpg)

# 注意(Attetion)
Just some simple methods to provide to control LED Matrix,because the main work of LMD4Arduino is render frame buffer on LED Matrix.so, a frame buffer Graphics library is needed to modify the LED Matrix pxiels of frambuffer.

由于LMD4Arduino的主要职责是将帧缓存绘制到LED点阵上，所以只提供了一些简单的控制LED点阵的方法。所以需要一个frambuffer图形库来操作framebuffer里面的点阵信息。

# 使用方法(Usage)
见示例
see simple.