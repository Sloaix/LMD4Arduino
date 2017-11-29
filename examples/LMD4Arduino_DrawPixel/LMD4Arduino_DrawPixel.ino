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
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            delay(5);
            canvas->drawPixel(x, y);
        }
    }

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            delay(10);
            canvas->clearPixel(x, y);
        }
    }
}

void timeHandler()
{
    driver->scanLine();
}
