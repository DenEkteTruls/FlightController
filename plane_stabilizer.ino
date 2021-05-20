#include "MPU9250.h"
#include "Servo.h"

#DEFINE activate A7

MPU9250 mpu;
Servo sideror;
int pitch_v_max_servo = 45;
int yaw_v_max_servo = 0;  // Denna må cmd endres
float turn_angle = 0;

void setup() {
  sideror.attach(23);
  sideror.write(90);
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  if (!mpu.setup(0x68)) {
    while (1) {
      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
      delay(5000);
    }
  }
}

void loop() {
  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    int ar = analogRead(activate);
    if((millis() - prev_ms >= 25) && ar >= 950) {
      prev_ms = millis();
      stabilize();
    }
  }
}

void stabilize() {
  //Serial.print("Yaw, Pitch, Roll: "); //
  Serial.print(mpu.getYaw(), 2);
  //Serial.print(", ");                 //
  Serial.println(mpu.getPitch(), 2);
  //Serial.print(", ");                 //
  //Serial.println(mpu.getRoll(), 2);   //
  
  float servo_pos = map(mpu.getPitch(), -pitch_v_max_servo - turn_angle, pitch_v_max_servo - turn_angle, 0, 180);
  float elevator_pos = map(mpu.getYaw(), yaw_v_mac_servo - yaw_angle, -yaw_v_max_servo - yaw_angle, 0, 180);
  Serial.println(servo_pos);
  sideror.write(servo_pos);
}
