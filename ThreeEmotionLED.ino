
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6 // define the LED Strips Signal pin
#define SOUND         A0// sound sensor pin
#define NUMPIXELS      60// maximum led number

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for 10ms
int Signal = 1;// catch a ball signal
int sound = 0;
void setup() {
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(SOUND, INPUT);  
}

void loop() 
{

  sound = analogRead(SOUND);
  Serial.println(sound);
 // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.  
// BLUE: when no ball is catched and in quite environment
  if (Signal == 0){
    //state = blue;
    for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,60,240)); // Moderately bright blue color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }
  }

  else if(Signal == 1)
  { 
    //GREEN: when ball is catched and no noise disturbing
    if(sound<=60){
      //state = green;
      for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(0,120,0)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).
      }
    }

    //RED: when noise is detected, free the ball and set signal = 0
    else{
      Signal = 0;
      for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright red color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).   
      }
      delay(3000);
    
    }

  }
}
