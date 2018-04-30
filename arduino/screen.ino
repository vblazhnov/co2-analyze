#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define WARNING_INDEX 2

SSD1306AsciiAvrI2c oled;

const uint graduates[] = {450UL, 600UL, 800UL, 1200UL};
const char* labels[] = {"Awesome", "Good", "Normal", "Bad", "ALARM"};
const char* texts[] = {"Be happy", "Don't worry", "Window", "Windows", "ALL WINDOWS"};
const byte indexes_len = 4;

void setup_print()
{
  Serial.begin(9600);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.print("Hello v0.0.2");
}

void print_ppm(uint ppm)
{
  if (ppm == CO2_SENSOR_ERROR)
  {
    print_error(0);
  }
  else
  {
    byte index = get_index(ppm);
    if (index > indexes_len)
    {
      print_error(1);
    }
    else {
      const char* label = labels[index];
      const char* text = texts[index];
      if (index < WARNING_INDEX)
      {
        print_normal(ppm, label, text);
      }
      else
      {
        print_warning(ppm, label, text);
      }
    }
  }
}

void print_normal(uint ppm, const char* label, const char* text)
{
  Serial.print(label);
  Serial.print(' ');
  Serial.print(text);
  Serial.print(' ');
  Serial.println(ppm);

  oled.clear();
  oled.set2X();
  oled.println(' ');
  oled.println(label);
  oled.set1X();
  oled.println(text);
  oled.print(ppm);
}

void print_warning(uint ppm, const char* label, const char* text)
{
  Serial.print(label);
  Serial.print(' ');
  Serial.print(text);
  Serial.print(' ');
  Serial.print(ppm);
  Serial.println("WARNING");

  oled.clear();
  oled.set2X();
  oled.println("WARNING");
  oled.println(label);
  oled.set1X();
  oled.println(text);
  oled.print(ppm);
}

void print_error(byte code)
{
  Serial.print("ERROR ");
  Serial.println(code);

  oled.clear();
  oled.println("ERROR");
  oled.println(code);
}

byte get_index(uint ppm)
{

  byte index;
  for (index = 0; index < indexes_len; ++index)
  {
    if (ppm < graduates[index])
    {
      return index;
    }
  }
  return index;
}

