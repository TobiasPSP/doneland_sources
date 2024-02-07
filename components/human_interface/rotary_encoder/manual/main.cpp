#include <Arduino.h>

// define input pins
#define CLK_PIN D7  // pin D7 connected to the rotary encoder's CLK (OUT A) pin
#define DT_PIN D6   // pin D6 connected to the rotary encoder's DT (OUT B) pin
#define SW_PIN D5   // pin D5 connected to the rotary encoder's SW (SWITCH) pin

// define modes of movement
#define DIRECTION_R 0   // turned right
#define DIRECTION_L 1   // turned left

// define state variables
int counter = 0;
int direction = DIRECTION_R;
int CLKstate;
int buttonState;
int prev_CLKstate;
int prev_buttonState;

void setup() {
  // make sure the baud rate matches your settings
  Serial.begin(115200);

  // configure pins and activate pullup
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);
  
  // initialize the previous CLK state (status of internal switch A)
  prev_CLKstate = digitalRead(CLK_PIN);
  prev_buttonState = digitalRead(SW_PIN);
}

void loop() {
  // manually monitoring and post-processing rotary encoder signals
  
  // monitor the rotating knob first:

  // check current state of switch A
  CLKstate = digitalRead(CLK_PIN);

  // any change from before? Then is it now ON (HIGH)?
  if (CLKstate != prev_CLKstate && CLKstate == HIGH) {
    // let's check switch B to find out the direction
    // in clockwise direction, A fires before B, so switch B should be HIGH 
    // (HIGH = switch is NOT ON (all inputs are pulled up and connect to GND when switch is active))
    if (digitalRead(DT_PIN) == HIGH) {
      counter++;
      direction = DIRECTION_R;
    } else {
      counter--;
      direction = DIRECTION_L;
    }

    Serial.print("Direction: ");
    if (direction == DIRECTION_R)
      Serial.print("to the right");
    else
      Serial.print("to the left");

    Serial.print(" - Increments: ");
    Serial.println(counter);
  }

  // remember current state for next time
  prev_CLKstate = CLKstate;

  // pins are HIGH by default and switch to LOW when a switch contacts GND:
  buttonState = digitalRead(SW_PIN);
  if (buttonState != prev_buttonState) 
  {
    if (buttonState == LOW)
      Serial.println("The button was PRESSED.");
    else
      Serial.println("The button was RELEASED.");
    // remember current state for next time:
    prev_buttonState = buttonState; 
  }
}
