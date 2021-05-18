/*
      Author: Robert Brenner Marhtins
      Version: 0.1.00
      Comments:

*/

#include "MPU9250.h"
#include "Servo.h"

MPU9250 mpu;
Servo sideror;
int pitch_v_max_servo = 45;
float turn_angle = 0;

void setup() {
  sideror.attach(23);
  sideror.write(90);
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  if (!mpu.setup(0x68)) {  // change to your own address
    while (1) {
      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
      delay(5000);
    }
  }
}

void loop() {
  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
      turn();
      prev_ms = millis();
    }
  }
}

void turn() {
  //Serial.print("Yaw, Pitch, Roll: ");
  //Serial.print(mpu.getYaw(), 2);
  //Serial.print(", ");
  Serial.println(mpu.getPitch(), 2);
  //Serial.print(", ");
  //Serial.println(mpu.getRoll(), 2);
  
  float servo_pos = map(mpu.getPitch(), -pitch_v_max_servo - turn_angle, pitch_v_max_servo - turn_angle, 0, 180);
  Serial.println(servo_pos);
  sideror.write(servo_pos);
}
