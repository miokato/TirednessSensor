#define LED 5
#define VOLUME_SENSOR 0

// LED点滅のタイミング。周期。 
int time_interval_table[11] = {
  5,10,30,50,100,200,300,500,1000
};

boolean led_state = LOW;
unsigned long previous_millis = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(VOLUME_SENSOR);
  int comverted_value = map(raw, 0, 1024, 0, 8);
  Serial.println(comverted_value);
  BlinkLed(comverted_value);
}

void BlinkLed(int value) {
  long interval = time_interval_table[value];
  unsigned long current_millis = millis();

  if(current_millis - previous_millis >= interval) {
    previous_millis = current_millis;

    if(led_state == LOW) {
      led_state = HIGH;
    } else {
      led_state = LOW;
    }

    digitalWrite(LED, led_state);
  }

}

