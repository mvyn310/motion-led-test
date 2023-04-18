// developed by abhi velaga
// github.com/avelaga
// abhi.work

#include <FastLED.h>

#define NUM_LEDS 300
#define LED_PIN 8
#define PIR_PIN 2

int pirState = LOW;
int val = 0;
CRGB leds[NUM_LEDS];
int currSat = 0;
bool goingUp = true;


// variables for you to play with
int distance = 5;
int delayTime = 30;
int hue = 200;
int maxBrightness = 100; // max of 255

void setup() {
  LEDS.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(maxBrightness);
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  clearAll();
}

void clearAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB( 0, 0, 0);
    FastLED.show();
  }
}

// led code to run when motion is detected
void animate() {
//  Serial.println("enetered animate");
//  Serial.println(currSat);
  for (int i = 0; i < NUM_LEDS; i++) {
    
    leds[i] = CHSV(hue, currSat, currSat);
    if (goingUp) {
      currSat += distance;
    }
    else {
      currSat -= distance;
    }

    if(currSat >= 255){
      goingUp = false;
    }
    if(currSat <= 0){
      goingUp = true;
    }
  }
  FastLED.show();
  delay(delayTime);
//  Serial.println("exited animate");
}

void readMotion() {
  val = digitalRead(PIR_PIN);
//  Serial.println(val);
  if (val == HIGH) { // if there's motion then run led pattern
//    Serial.println("MOTION!");
     animate(); // run led pattern
  } else { // if theres no motion, turn leds off
//    Serial.println("no motion :(");
     clearAll(); // turns led strip off
  }
}


void loop() {
  readMotion();
//animate(); // only for working on animation, leave commented out for normal use
}
