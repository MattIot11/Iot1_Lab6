#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_BMP280 bmp;
float temperature;
float Altitude;
float pressure;
unsigned long time = 0; 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 10
#define OLED_RST 8

Adafruit_SSD1306 display(
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	OLED_MOSI,
	OLED_CLK,
	OLED_DC,
	OLED_RST,
	OLED_CS
);




void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Program Started");
  Wire.begin();
  Serial.println("I2C Started");
  


  if (bmp.begin(0x76))
    {
     Serial.println("BMP280 Found at 0x76");
    }
  else if (bmp.begin(0x77))
    {
      Serial.println("BMP280 Found at 0x77");
    }
  else
    {
      Serial.println("BMP280 Not Found");
    }

  display.begin(
    SSD1306_SWITCHCAPVCC
  );

  display.clearDisplay();

  display.setTextSize(1);

  display.setTextColor(SSD1306_WHITE);

  display.display();


}

void loop() {
  // put your main code here, to run repeatedly:

  time = millis() / 1000;

  temperature = bmp.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);

  Altitude = bmp.readAltitude(1013.25);

  Serial.print("Altitude: ");
  Serial.print(Altitude);
  Serial.println(" %");
  delay(1000);

  pressure = bmp.readPressure() / 100;
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Time:");
  Serial.print(time);
  Serial.println("Seconds");

  display.clearDisplay();

  display.setCursor(1,0);

  display.print("Temp:");
  display.print(temperature);
  display.println("C");

  display.print("Hum:");
  display.print(Altitude);
  display.println("%");

  display.print("Pres:");
  display.print(pressure);
  display.println("hPa");

  display.print("Time:");
  display.print(time);
  display.println("Seconds");

  display.display();

  delay(1000);



}

