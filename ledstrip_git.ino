#define IO_USERNAME    "mig3linho"
#define IO_KEY         
#define WIFI_SSID      
#define WIFI_PASS      

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#define greenPin 15
#define bluePin  13
#define redPin  12

float r = 100;
float g = 100;
float b = 100;
String hex;
int brightness = 100;

#include <AdafruitIO.h>
#include <ArduinoHttpClient.h>


// set up the 'ledcolor' feed
AdafruitIO_Feed *ledcolor = io.feed("ledcolor");
AdafruitIO_Feed *brightnes = io.feed("brightness");

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT); 
// start the serial connection
  Serial.begin(115200);
  
  //light up the led-strip to inform the device is on
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  
  
  // wait for serial monitor to open
  while(! Serial);
 
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  ledcolor->onMessage(handleMessage);
  brightnes->onMessage(handleBrightness);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.println("Connecting...");
  //blink the leds to inform the connection is being established  
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(100);
    
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
    delay(100);
    
    delay(300);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  //Set the leds to green to inform the connection is established
    
    analogWrite(redPin, 54);
    analogWrite(greenPin, 251);
    analogWrite(bluePin, 2);
    delay(100);


  
  // set analogWrite range for ESP8266
  #ifdef ESP8266
    analogWriteRange(255);
  #endif
}

// this function is called whenever a 'color' message
// is received from Adafruit IO. it was attached to
// the color feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  r = data->toRed();
  g = data->toGreen();
  b = data->toBlue();
  hex = data->value();
 
  // print RGB values and hex value
  Serial.println("Received:");
  Serial.print("  - R: ");
  Serial.println(r);
  Serial.print("  - G: ");
  Serial.println(g);
  Serial.print("  - B: ");
  Serial.println(b);
  Serial.print("  - HEX: ");
  Serial.println(hex);
  

  
  // invert RGB values for common anode LEDs
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
 
}
//this function is called whenever the brighness feed value is changed

void handleBrightness(AdafruitIO_Data *data) {
   
  brightness = data->toInt();
  
  float jakaja = 100;
  float a = brightness;

  float kerroin = a / jakaja;
  
  float r2 = (r * kerroin);
  float g2 = (g * kerroin);
  float b2 = (b * kerroin);
  
  analogWrite(redPin, r2);
  analogWrite(greenPin, g2);
  analogWrite(bluePin, b2);
  
  Serial.println("handleBrightness:");
  Serial.print("  - R: ");
  Serial.println(r2);
  Serial.print("  - G: ");
  Serial.println(g2);
  Serial.print("  - B: ");
  Serial.println(b2);
  Serial.print("  - HEX: ");
  Serial.println(hex);
  Serial.print("  - BRIGHTNESS: ");
  Serial.println(brightness);
}

void loop() {  
  
  io.run();
      
} 




