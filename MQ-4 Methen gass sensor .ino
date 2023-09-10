#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int AO_Pin = A0;
float AO_Out;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();

  pinMode(AO_Pin, INPUT);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

}

// Main loop
void loop()
{
  AO_Out= analogRead(AO_Pin);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Methane Level:"));
  display.setCursor(0, 10);
  display.print(AO_Out);
  display.println(F(" ppm"));
  display.display();
  Serial.print("AO: ");
  Serial.println(AO_Out);

  delay(1000); 
}