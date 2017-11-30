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
}

void loop()
{

    canvas->drawRect(0, 0, 8, 8);

    delay(500);

    canvas->drawBorderRect(9, 0, 8, 8);

    delay(500);

    canvas->drawBorderRect(18, 0, 8, 8, 2);

    delay(500);

    canvas->drawBorderRect(27, 0, 8, 8, 3);

    delay(500);

    for (int thikness = 0; thikness < 5; thikness++)
    {
        canvas->drawBorderRect(36, 0, 8, 8, thikness);
        delay(300);
    }

    canvas->clear();

    for (int thikness = 0; thikness < 7; thikness++)
    {
        canvas->drawBorderRect(0, 0, 64, 16, thikness);
        delay(100);
    }

    delay(1000);

    canvas->clear();
}

void timeHandler()
{
    driver->scanLine();
}
