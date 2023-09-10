

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MQUnifiedsensor.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define MQ4_Pin A0  // Analog pin connected to mq4 sensor
#define Board "Arduino UNO"

#define Voltage_Resolution 5
#define Type "MQ-4"
#define ADC_Bit_Resolution 10
#define RatioMQ4CleanAir 4.4

MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, MQ4_Pin, Type);
float methaneLevel;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();  // Initialize with the display off
  delay(2000);

  display.clearDisplay();
  display.display();

    //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setA(1012.7); MQ4.setB(-2.786); // Configure the equation to to calculate CH4 concentration
  /*
    Exponential regression:
  Gas    | a      | b
  LPG    | 3811.9 | -3.113
  CH4    | 1012.7 | -2.786
  CO     | 200000000000000 | -19.05
  Alcohol| 60000000000 | -14.01
  smoke  | 30000000 | -8.308
  */


  MQ4.init();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  methaneLevel = MQ4.readSensor();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Methane Level:"));
  display.setCursor(0, 10);
  display.print(methaneLevel);
  display.println(F(" ppm"));
  display.display();

  Serial.print(F("Methane Level: "));
  Serial.print(methaneLevel);
  Serial.println(F(" ppm"));

  delay(1000);
}
