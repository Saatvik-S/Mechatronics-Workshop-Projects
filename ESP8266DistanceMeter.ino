/*
 * Distance Meter with OLED display made By Saatvik Sehgal from Mechatronics Workshop. This is Arduino Version
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define CommonSenseMetricSystem //If you want the distance in "cm"
//#define ImperialNonsenseSystem // If you want the distance in "in"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// defines pins numbers
const int trigPin = D6;
const int echoPin = D5;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int distance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  #ifdef CommonSenseMetricSystem
  float distance = duration*0.034/2;
  #endif
  #ifdef ImperialNonsenseSystem
  float distance = (duration/2) / 73.914;
  #endif
  // Returning the distance
  return distance;
}
void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Clear the buffer
  display.clearDisplay();
}

void loop(){
  display.display();
  display.clearDisplay();
  display.setCursor(10,20);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println(distance());
  display.setCursor(90,20);
  display.setTextSize(3);
  
  #ifdef CommonSenseMetricSystem
  display.println("cm");
  #endif
  #ifdef ImperialNonsenseSystem
  display.println("in");
  #endif

  delay(5);
}
