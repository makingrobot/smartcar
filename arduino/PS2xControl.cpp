/* SmartCar - makingrobot.net
 * Copyright MakingRobot 2018
 * MIT License
 */
#include "PS2xControl.h"

#include <PS2X_lib.h>  //for v1.6

#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
int ps2x_error = 0;
byte ps2x_type = 0;
byte ps2x_vibrate = 0;

PS2xControl::PS2xControl(uint8_t clk, uint8_t cmd, uint8_t dat, uint8_t cs)
{
    delay(1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
    //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
    
    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    ps2x_error = ps2x.config_gamepad(clk, cmd, cs, dat, pressures, rumble);
    
    if(ps2x_error == 0){
      Serial.print("Found Controller, configured successful ");
      Serial.print("pressures = ");
      if (pressures)
        Serial.println("true ");
      else
        Serial.println("false");
      Serial.print("rumble = ");
      if (rumble)
        Serial.println("true)");
      else
        Serial.println("false");
        Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        Serial.println("holding L1 or R1 will print out the analog stick values.");
        Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }  
    else if(ps2x_error == 1)
      Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
     
    else if(ps2x_error == 2)
      Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  
    else if(ps2x_error == 3)
      Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
    
  //  Serial.print(ps2x.Analog(1), HEX);
    
    ps2x_type = ps2x.readType(); 
    switch(ps2x_type) {
      case 0:
        Serial.print("Unknown Controller type found ");
        break;
      case 1:
        Serial.print("DualShock Controller found ");
        break;
      case 2:
        Serial.print("GuitarHero Controller found ");
        break;
      case 3:
        Serial.print("Wireless Sony DualShock Controller found ");
        break;
     }
}

void PS2xControl::ReadInput()
{
  if (ps2x_error != 0)
    return;
    
  ps2x.read_gamepad(false, ps2x_vibrate); //read controller and set large motor to spin at 'vibrate' speed

  if(ps2x.Button(PSB_PAD_DOWN)){   //will be TRUE as long as button is pressed
    backwardPressState=1;
    carAngleValue=0;
  } else if(ps2x.Button(PSB_PAD_UP)) {   
    forwardPressState=1;
    carAngleValue=0;
  } else if(ps2x.Button(PSB_PAD_RIGHT)){
    rightPressState=1;
    
    if (carAngleValue<20)
      carAngleValue+=6;
    if (carAngleValue<35)
      carAngleValue+=4;
    else
      carAngleValue+=2;
      
    if (carAngleValue>45)
      carAngleValue=45;
  } else if(ps2x.Button(PSB_PAD_LEFT)){
    leftPressState=1;
    
    if (carAngleValue>-20)
      carAngleValue-=6;
    if (carAngleValue>-35)
      carAngleValue-=4;
    else
      carAngleValue-=2;
      
    if (carAngleValue<-45)
      carAngleValue=-45;
  }
   
  if (ps2x.Button(PSB_CIRCLE)) {
     accelPressState=1;
     if (carAccelValue < 100)
        carAccelValue+=1;
  } else {
    if (carAccelValue>0) {
      carAccelValue-=1;
    }
  }
  if (ps2x.Button(PSB_SQUARE)) {
     stopPressState=1;
     carAccelValue=0;
     carAngleValue=0;
  }   
}

PS2xControl::~PS2xControl()
{
}
