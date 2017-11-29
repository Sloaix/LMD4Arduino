#include <Arduino.h>
#include <TimerOne.h>
#include <SPI.h>
#include <Hub08Driver.h>
Hub08Driver *driver;
BufferCanvas *canvas;

void setup()
{
    Serial.begin(115200);

    driver = new Hub08Driver(8, 3, 4, 5, 6, 7, 8);

    Timer1.initialize(200);
    Timer1.attachInterrupt(timeHandler);

    canvas = driver->getCanvas();

    //初始线长度
    int length = 1;

    //用线画一个直角三角形
    for (int i = 0; i < 16; i++)
    {
        canvas->drawHorizontalLine(0, i, length++);
    }
}

void loop()
{
    canvas->shiftRight(1, true);
    delay(20);
}

void timeHandler()
{
    driver->scanLine();
}
