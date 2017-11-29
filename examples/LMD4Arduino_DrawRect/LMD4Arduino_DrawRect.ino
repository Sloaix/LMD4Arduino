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

    canvas->drawRect(4, 4, 20, 10);
}

void loop()
{
}

void timeHandler()
{
    driver->scanLine();
}
