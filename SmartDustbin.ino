#include <Servo.h>

#define IR_SENSOR_PIN 7

#define SERVO_DRY_PIN 8
#define SERVO_WET_PIN 9
#define SERVO_MATEL_PIN 10

#define RAIN_DROP_PIN A0
#define PROXI_PNP_PIN 11

Servo servoDry;
Servo servoWet;
Servo servoMatel;

void setup() {
  Serial.begin(9600);

  servoDry.attach(SERVO_DRY_PIN);
  servoWet.attach(SERVO_WET_PIN);
  servoMatel.attach(SERVO_MATEL_PIN);

  servoDry.write(0);
  servoWet.write(0);
  servoMatel.write(0);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(PROXI_PNP_PIN, INPUT);

  Serial.println("System Ready....");
}

void loop() {

  int proxiState = digitalRead(PROXI_PNP_PIN);

  if (proxiState == HIGH) {
    Serial.println("Metal Detected....!");
    openMetalLid();
  } else {
    int irState = digitalRead(IR_SENSOR_PIN);

    if (irState == LOW) {
      Serial.println("Object detected!");

      int moistureValue = getMoistureValue();

      Serial.print("Moisture: ");
      Serial.print(moistureValue);
      Serial.println("%");

      if (moistureValue > 20) {
        openWetLid();
      } else {
        openDrytLid();
      }

    } else {
      Serial.println("No Object Detected");
    }
  }

  delay(1000);
}

int getMoistureValue() {
  int fsoil = 0;
  int totalSoil = 0;

  for (int i = 0; i < 3; i++) {
    int soil = analogRead(RAIN_DROP_PIN);
    soil = constrain(soil, 485, 1023);
    totalSoil += map(soil, 485, 1023, 100, 0);
    delay(75);
  }

  fsoil = totalSoil / 3;

  return fsoil;
}

void openDrytLid() {
  servoDry.write(90);
  delay(1000);

  servoDry.write(0);
  // delay(1000);
}

void openWetLid() {
  servoWet.write(90);
  delay(1000);

  servoWet.write(0);
  // delay(1000);
}

void openMetalLid() {
  servoMatel.write(90);
  delay(1000);

  servoMatel.write(0);
  // delay(1000);
}
