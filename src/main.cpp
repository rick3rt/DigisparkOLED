#include <Arduino.h>
#include <TinyWireM.h>
// #include <Wire.h>
// #include <TinyI2CMaster.h>
#include "Tiny4kOLED.h"

int const sda = 0;
int const scl = 2;

void updateDisplay();

void setup()
{
    pinMode(1, OUTPUT);
    // Send the initialization sequence to the oled. This leaves the display turned off
    oled.begin();
    oled.setVcomhDeselectLevel(5);

    // Two rotations are supported,
    // The begin() method sets the rotation to 1.
    //oled.setRotation(0);

    // Some newer devices do not contain an external current reference.
    // Older devices may also support using the internal curret reference,
    // which provides more consistent brightness across devices.
    // The internal current reference can be configured as either low current, or high current.
    // Using true as the parameter value choses the high current internal current reference,
    // resulting in a brighter display, and a more effective contrast setting.
    //oled.setInternalIref(true);

    // Two fonts are supplied with this library, FONT8X16 and FONT6X8
    // Other fonts are available from the TinyOLED-Fonts library
    oled.setFont(FONT8X16);

    // Clear the memory before turning on the display
    oled.clear();

    // Turn on the display
    oled.on();

    // Switch the half of RAM that we are writing to, to be the half that is non currently displayed
    oled.switchRenderFrame();
}

bool LED_STATUS = false;
void loop()
{
    digitalWrite(1, LED_STATUS);
    LED_STATUS = !LED_STATUS;
    updateDisplay();
    // delay(50);
}

void updateDisplay()
{
    // Clear the half of memory not currently being displayed.
    oled.clear();

    // Position the text cursor
    // In order to keep the library size small, text can only be positioned
    // with the top of the font aligned with one of the four 8 bit high RAM pages.
    // The Y value therefore can only have the value 0, 1, 2, or 3.
    // usage: oled.setCursor(X IN PIXELS, Y IN ROWS OF 8 PIXELS STARTING WITH 0);
    oled.setCursor(0, 1);

    // Write text to oled RAM (which is not currently being displayed).
    oled.print("ms: ");

    // Write the number of milliseconds since power on.
    oled.print(millis());

    // Swap which half of RAM is being written to, and which half is being displayed.
    // This is equivalent to calling both switchRenderFrame and switchDisplayFrame.
    oled.switchFrame();
}