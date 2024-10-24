/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

/*
  Defaults for the blink_rgb() routine
*/
#define DEFAULT_BLINK_RATE_MS     250
#define DEFAULT_NR_CYCLES         1

void blink_led (uint8_t pin, uint8_t blink_rate_ms=DEFAULT_BLINK_RATE_MS, uint8_t nr_cycles=DEFAULT_NR_CYCLES) {
  uint8_t count = 0;

  for (count=0; count < nr_cycles; count++) {
    digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(blink_rate_ms);                      // wait for a second
    digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW
    delay(blink_rate_ms);                      // wait for a second
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  blink_led(LED_BUILTIN);
}
