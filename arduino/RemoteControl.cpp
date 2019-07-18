#include "RemoteControl.h"

void RemoteControl::Execute(MotorDriver driver)
{
   leftPressState=0;
   rightPressState=0;
   forwardPressState=0;
   backwardPressState=0;

   accelPressState=0;
   stopPressState=0;
   
    this->ReadInput();

   if (forwardPressState==1)
    Serial.println("Up held this hard: ");

  if (rightPressState==1)
    Serial.println("Right held this hard: ");

  if (leftPressState==1)
    Serial.println("Left held this hard: ");

  if (backwardPressState==1)  
     Serial.println("Down held this hard: ");

  if (accelPressState==1) {  
     Serial.println("Circle just pressed");
  }

  if (stopPressState==1)   
     Serial.println("Square just pressed");

  if (carAccelValue >0) {
     Serial.print("Accel value: ");
     Serial.println(carAccelValue);
  }
  
   if (stopPressState==1) {
    driver.Stop();  
  } else {
    if (forwardPressState==1) {
      int power = carAccelValue / 100.0 * (MotoPowerMax - MotoPowerMin) + MotoPowerMin;
      if (power > MotoPowerMax)
         power = MotoPowerMax;
      driver.Forward(power);
    } else if (leftPressState==1) {
      int power = MotoPowerTurnMax + carAngleValue / 45.0 * (MotoPowerTurnMax - MotoPowerMin);
      if (power < 0)
        power = MotoPowerTurnMax - 16;
      if (power > MotoPowerTurnMax)
        power = MotoPowerTurnMax;
      driver.TurnLeft(power);
    } else if (rightPressState==1) {
      int power = MotoPowerTurnMax - carAngleValue / 45.0 * (MotoPowerTurnMax - MotoPowerMin);
        if (power < 0)
           power = MotoPowerTurnMax - 16;
        if (power > MotoPowerTurnMax)
          power = MotoPowerTurnMax;
      driver.TurnRight(power);
    } else if (backwardPressState==1) {
      int power = carAccelValue / 100.0 * (MotoPowerMax - MotoPowerMin) + MotoPowerMin;
      if (power > MotoPowerMax)
         power = MotoPowerMax;
      driver.Backward(power);
    }
  }
  
  delay(100);
}
