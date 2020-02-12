#include <Arduino.h>
#define   D0   8
#define   PINS 8

uint32_t measure;

void parallel_set_inputs(void) {
  REG_WRITE(GPIO_ENABLE_W1TC_REG, 0xFF << D0);
}
uint8_t parallel_read(void) {
  uint32_t input = REG_READ(GPIO_IN_REG);
  return (input >> D0);
}
void setup() {
  Serial.begin(115200);
  Serial.println("-----------------");
  for (int i = 0; i < PINS; i++) {
    pinMode(D0 + i, INPUT);
  }
  parallel_set_inputs();
}
void loop() {
  measure = parallel_read();
  Serial.println(measure);
}
