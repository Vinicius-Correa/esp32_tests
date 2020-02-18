#include <Arduino.h>

uint16_t measure;
uint32_t PINS=0x00EFF800;

void parallel_set_inputs(void) {
  REG_WRITE(GPIO_ENABLE_W1TC_REG, PINS);
}
uint16_t parallel_read(uint32_t entrada) {
   bool bit = 0, LSB = 0; 
   uint16_t output = 0;
   uint32_t input = REG_READ(GPIO_IN_REG);
   for(int i = 0; i < 32; i++) {
      LSB = entrada & 1;
      if (LSB == 1)
         bit = input & 1;
      if (bit == 1)
         output = output + 1;
      entrada = entrada >> 1;
      input = input >> 1;
      output = output << 1;
   }
   return(output);
}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 32; i++) {
    if (PINS && i == 1)
      pinMode(i, INPUT);
  }
  parallel_set_inputs();
  delay(1000);
}
void loop() {
  measure = parallel_read(PINS);
  Serial.println(measure);
  delay(500);
}
