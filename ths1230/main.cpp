#include <Arduino.h>
#define   D0   11
#define   PINS 12

uint16_t measure;

void parallel_set_inputs(void) {
  REG_WRITE(GPIO_ENABLE_W1TC_REG, 0x1DFF << D0);
}
uint16_t parallel_read(void) {
  uint32_t input = REG_READ(GPIO_IN_REG);
  uint32_t value = input >> D0;
  uint32_t buffer = value >> 10;
  return (value - 512 * buffer);
}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < PINS+1; i++) {
    if (D0 + i != 20)
      pinMode(D0 + i, INPUT);
  }
  parallel_set_inputs();
  delay(1000);
}
void loop() {
  measure = parallel_read();
  Serial.println(measure);
  delay(500);
}
