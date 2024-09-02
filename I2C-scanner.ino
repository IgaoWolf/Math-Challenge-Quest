#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // Aguardar a inicialização da Serial
  Serial.println("\nI2C Scanner");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Encontrado dispositivo I2C no endereço 0x");
      Serial.println(address, HEX);
      delay(500);
    }
  }
}

void loop() {
  // Não é necessário executar nada no loop
}
