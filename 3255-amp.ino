#define SMPS_INHIBIT 8
#define POWER_BUTTON 2
#define POWER_LED 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(POWER_BUTTON, INPUT_PULLUP);
  
  pinMode(SMPS_INHIBIT, OUTPUT); // IO8, enbles 48V SMPS
  pinMode(SMPS_INHIBIT, OUTPUT); // IO8, enbles 48V SMPS
  
  digitalWrite(SMPS_INHIBIT, HIGH);
  digitalWrite(POWER_LED, LOW);
}

unsigned char b;
unsigned int power_state = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
int buttonState = HIGH;   // the previous reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void loop() {
  // put your main code here, to run repeatedly:

  b = digitalRead(POWER_BUTTON);
  
  // If the switch changed, due to noise or pressing:
  if (b != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (b != buttonState) {
      buttonState = b;

      // only toggle if the new button state is HIGH
      if (buttonState == HIGH) {
        power_state = !power_state;
      }
    }
  }

  // set the LED:
  digitalWrite(POWER_LED, power_state);
  digitalWrite(SMPS_INHIBIT, !power_state);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = b;
}
