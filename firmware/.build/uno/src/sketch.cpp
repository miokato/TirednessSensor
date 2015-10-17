#include <Arduino.h>

void setup();
void loop();
void BlinkLed(int value);
#line 1 "src/sketch.ino"
#define LED 5
#define VOLUME_SENSOR 0

// LED点滅のタイミング。周期。 
// 20 -> 30 hz
float time_interval_table[] = {
  25000, 23809, 22727, 21739, 20833,
  20000, 19230, 18518, 17857, 17241, 16666
};

boolean led_state = LOW;
unsigned long previous_micros = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int raw = analogRead(VOLUME_SENSOR);
  int comverted_value = map(raw, 0, 1024, 0, 10);
  Serial.println(comverted_value);
  BlinkLed(comverted_value);
}

void BlinkLed(int value) {
  unsigned long interval = time_interval_table[value];
  unsigned long current_micros = micros();

  if(current_micros - previous_micros >= interval) {
    previous_micros = current_micros;

    if(led_state == LOW) {
      led_state = HIGH;
    } else {
      led_state = LOW;
    }

    digitalWrite(LED, led_state);
  }

}

