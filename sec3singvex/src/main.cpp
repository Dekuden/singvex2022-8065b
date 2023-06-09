#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h" 

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// piston          digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;



// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//                                                                            
//    Project:                                               
//    Author:
//    Created:
//    Configuration:        
//                                                                            
// ----------------------------------------------------------------------------

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

motor leftfront = motor(PORT11,gearSetting::ratio18_1,false);
motor leftback = motor(PORT12,gearSetting::ratio18_1,false);
motor rightfront = motor(PORT3,gearSetting::ratio18_1,true);
motor rightback = motor(PORT4,gearSetting::ratio18_1,true);

motor topfly = motor(PORT5,gearSetting::ratio18_1,false);
motor botfly = motor(PORT6,gearSetting::ratio18_1,false);
motor intake = motor(PORT7,gearSetting::ratio18_1, true);

controller H = controller(primary);
controller V = controller(partner);
int maxspeed = 100;
int slwspeed =  .5 * maxspeed;

const float pi = M_PI;
// Include the V5 Library
#include "vex.h"
float dia = 4.85;

const float degToticks = 0.2235;
// Allows for easier use of the VEX Library

using namespace vex;


void movebase(int speed)
{
  leftfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
  rightfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  leftback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
  rightback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
}


void moveleft(int speed)
{    
  leftfront.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);  
  rightfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  leftback.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);  
  rightback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
}

void moveright(int speed)
{
  leftfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
  rightfront.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);
  leftback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
  rightback.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);
}

void moveintake(int speed)
{
  intake.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct); 
}



void timerfwd(int time, int speed)
{
  leftfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
  rightfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  vex::task::sleep(time);
  leftfront.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);  
  rightfront.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);
}

void encfwd(float dist, int speed)
{
  float val = 0;
  float RV;
  float LV;
  leftfront.resetRotation();
  rightfront.resetRotation();


  while(val<dist)
  {
    movebase(speed);
    RV = rightfront.rotation(rev)*pi*dia;
    LV = leftfront.rotation(rev)*pi*dia;
    val = (RV+LV)/2; 
  }

 movebase(speed*.1);
 task::sleep(100);
 movebase(0);

}



void intkfwd(int duration, int speed, int intspd)
{
  movebase(speed);
  moveintake(intspd);
  vex::task::sleep(duration);
  movebase(0);
  moveintake(0);
}

void advfwd(float dist, int speed,int slowspd)
{
  float val = 0;
  float LV;
  float RV;
  float slowdist;

  int run = 1;
  leftfront.resetRotation();
  rightfront.resetRotation();
  if(dist < 30)
  {
    slowdist = dist/5;
  }

  else if(dist > 30)
  {
    slowdist = dist/8;
  }

  while(run==1)
  {
    if(val < dist - slowdist )
    {
      movebase(speed);

      RV = rightfront.rotation(rev) * pi * dia;
      LV = leftfront.rotation(rev) * pi * dia;
      val = (RV+LV)/2;
    }

    else if(val > dist - slowdist && dist < val)
    {
      movebase(slowspd);
      RV = rightfront.rotation(rev) * pi * dia;
      LV = leftfront.rotation(rev) * pi * dia;
      val = (RV+LV)/2;
    }

    else if(val > dist)
    {
      movebase(-slowspd);
      RV = rightfront.rotation(rev) * pi * dia;
      LV = leftfront.rotation(rev) * pi * dia;
      val = (RV+LV)/2;
    }

    else
    {
      run = 0;
    }

    movebase(0);
  }
}

void advfwdWintake(float dist, int speed, int slowspd, int intakespd)
{
  float val = 0;
  float LV;
  float RV;
  float slowdist;

  int run = 1;
   
}
void rightsidemv(int dist, int speed){
   int x  = dist/10;
   rightfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
   rightback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
   vex::task::sleep(x*8);
   rightfront.spin(vex::directionType::fwd,speed/6,vex::velocityUnits::pct);
   rightback.spin(vex::directionType::fwd,speed/6,vex::velocityUnits::pct);
   vex::task::sleep(x*2);
   rightfront.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);
   rightback.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);





}


void leftsidemv(int dist, int speed){
   int x  = dist/10;
   leftfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
   leftback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
   vex::task::sleep(x*8);
   leftfront.spin(vex::directionType::fwd,speed/6,vex::velocityUnits::pct);
   leftback.spin(vex::directionType::fwd,speed/6,vex::velocityUnits::pct);
   vex::task::sleep(x*2);
   leftfront.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);
   leftback.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);





}


void advrev(int dist, int speed,int slwspeed){

float val = 0;
float RV;
float LV;
float slwdist;
int run = 1;
leftfront.resetRotation();
rightfront.resetRotation();

if (dist < 30){


slwdist = dist/5;


}
else if(dist > 30){

slwdist = dist/8;

}

while (run == 1){



 if(val< dist - slwdist  ){
       Brain.Screen.clearScreen();
       movebase(-speed);

  
      RV = -rightfront.rotation(rev)*pi*dia;
      LV = -leftfront.rotation(rev)*pi*dia;
      val = (RV + LV)/2; 
      Brain.Screen.print("1");
      

 }

   else if(val >  dist - slwdist && dist<val ){


    Brain.Screen.clearScreen();
    movebase(-slwspeed);
     

    
    RV = -rightfront.rotation(rev)*pi*dia;
    LV = -leftfront.rotation(rev)*pi*dia;
    val = (RV + LV)/2; 
    Brain.Screen.print("3");

 }

 else if(val > dist){
      Brain.Screen.clearScreen();
      movebase(slwspeed);
     
 
    
    RV = -rightfront.rotation(rev)*pi*dia;
    LV = -leftfront.rotation(rev)*pi*dia;
    val = (RV + LV)/2; 
    Brain.Screen.print("3");

 }
 else{

   run = 0;
 }

}
  Brain.Screen.clearScreen();
  movebase(0);
  


  Brain.Screen.print("5");


}


 void encturnright (int dist, float speed){


  float val = 0;
  float LV;
  float RV;
  
  leftfront.resetRotation();
  rightfront.resetRotation();

     
  while(val<dist){

    

    
    leftfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
    rightfront.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);
    leftback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);  
    rightback.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);
    wait(10,msec);

    
    RV = rightfront.rotation(deg);
    LV = leftfront.rotation(deg);


    


    val = -(RV - LV)*degToticks;
    Brain.Screen.print(val);

    

  }

  
 leftfront.spin(vex::directionType::fwd,speed/10,vex::velocityUnits::pct);  
 rightfront.spin(vex::directionType::fwd,-speed/10,vex::velocityUnits::pct);
 leftback.spin(vex::directionType::fwd,speed/10,vex::velocityUnits::pct);  
 rightback.spin(vex::directionType::fwd,-speed/10,vex::velocityUnits::pct);
 task::sleep(50);
 movebase(0);



}

 void encturnleft (int dist, float speed){


  float val = 0;
  float LV;
  float RV;
  
  leftfront.resetRotation();
  rightfront.resetRotation();

     
  while(val<dist){

    

    
    leftfront.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);  
    rightfront.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    leftback.spin(vex::directionType::fwd,-speed,vex::velocityUnits::pct);  
    rightback.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    wait(10,msec);

    
    RV = rightfront.rotation(deg);
    LV = leftfront.rotation(deg);


    


    val = (RV - LV)*degToticks;
    Brain.Screen.print(val);

    

  }

  
 leftfront.spin(vex::directionType::fwd,-speed/10,vex::velocityUnits::pct);  
 rightfront.spin(vex::directionType::fwd,speed/10,vex::velocityUnits::pct);
 leftback.spin(vex::directionType::fwd,-speed/10,vex::velocityUnits::pct);  
 rightback.spin(vex::directionType::fwd,speed/10,vex::velocityUnits::pct);
 task::sleep(60);
 movebase(0);



}
 
void advturnleft(float degr, int speed, int swlspd){

  float val = 0;
float RV;
float LV;
float slwdist;
int run = 1;
leftfront.resetRotation();
rightfront.resetRotation();


if (degr < 30){


slwdist = degr/5;


}
else if(degr > 30){

slwdist = degr/8;

}

while (run == 1){



 if(val< degr - slwdist  ){
       Brain.Screen.clearScreen();
       moveleft(speed);

  
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
      

 }

   else if(val >  degr - slwdist && degr<val ){


    Brain.Screen.clearScreen();
    moveleft(slwspeed);
     

    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
    Brain.Screen.print("3");

 }

 else if(val > degr){
      Brain.Screen.clearScreen();
      moveleft(-slwspeed);
     
 
    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
    Brain.Screen.print("3");

 }
 else{

   run = 0;
 }

}
  Brain.Screen.clearScreen();
  movebase(0);
  


  Brain.Screen.print("5");


}

void reset(int duration, int speed){


movebase(speed);
vex::task::sleep(duration);
movebase(0);





}


void advturnleftWintake(float degr, int speed, int swlspd,int intkspd){

  float val = 0;
float RV;
float LV;
float slwdist;
int run = 1;
leftfront.resetRotation();
rightfront.resetRotation();


if (degr < 30){


slwdist = degr/5;


}
else if(degr > 30){

slwdist = degr/8;

}

while (run == 1){



 if(val< degr - slwdist  ){
       Brain.Screen.clearScreen();
       moveleft(speed);
       moveintake(intkspd);

  
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
      

 }

   else if(val >  degr - slwdist && degr<val ){


    Brain.Screen.clearScreen();
    moveleft(slwspeed);
    moveintake(intkspd);
     

    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
    Brain.Screen.print("3");

 }

 else if(val > degr){
      Brain.Screen.clearScreen();
      moveleft(-slwspeed);
      moveintake(intkspd);
     
 
    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (RV - LV)*degToticks;
    Brain.Screen.print("3");

 }
 else{

   run = 0;
 }

}
  Brain.Screen.clearScreen();
  movebase(0);
  moveintake(0);
  


  Brain.Screen.print("5");


}


void intakefwd(int duration, int basespeed, int intkspd){

 moveintake(intkspd);
 movebase(basespeed);
 vex::task::sleep(duration);
 moveintake(0);
 movebase(basespeed/10);
 vex::task::sleep(duration/10);
 movebase(0);




}

void advturnright(float degr, int speed, int swlspd){

  float val = 0;
float RV;
float LV;
float slwdist;
int run = 1;
leftfront.resetRotation();
rightfront.resetRotation();

 
if (degr < 30){


slwdist = degr/5;


}
else if(degr > 30){

slwdist = degr/8;

}

while (run == 1){



 if(val< degr - slwdist  ){
       Brain.Screen.clearScreen();
       moveright(speed);

  
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (LV - RV)*degToticks;
      

 }

   else if(val >  degr - slwdist && degr<val ){


    Brain.Screen.clearScreen();
    moveright(slwspeed);
     

    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (LV - RV)*degToticks;
    Brain.Screen.print("3");

 }

 else if(val > degr){
      Brain.Screen.clearScreen();
      moveright(-slwspeed);
     
 
    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (LV - RV)*degToticks;
    Brain.Screen.print("3");

 }
 else{

   run = 0;
 }

}
  Brain.Screen.clearScreen();
  movebase(0);
  


  Brain.Screen.print("5");


}

void shoot(int intime, float flyspeed){

      topfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
      botfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
vex::task::sleep(intime);
      topfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
      botfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
piston.set(false);
vex::task::sleep(400);
piston.set(true);






}
void flywheel(float flyspeed){
      topfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
      botfly.spin(directionType::fwd, flyspeed, voltageUnits::volt);
}


void advturnrightWintake(float degr, int speed, int swlspd, int intakespd){

  float val = 0;
float RV;
float LV;
float slwdist;
int run = 1;
leftfront.resetRotation();
rightfront.resetRotation();


if (degr < 30){


slwdist = degr/5;


}
else if(degr > 30){

slwdist = degr/8;

}

while (run == 1){



 if(val< degr - slwdist  ){
       Brain.Screen.clearScreen();
       moveright(speed);
       moveintake(intakespd);

  
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (LV - RV)*degToticks;
      

 }

   else if(val >  degr - slwdist && degr<val ){


    Brain.Screen.clearScreen();
    moveright(slwspeed);
    moveintake(intakespd);
     

    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);
      


    


      val = (LV - RV)*degToticks;
    Brain.Screen.print("3");

 }

 else if(val > degr){
      Brain.Screen.clearScreen();
      moveright(-slwspeed);
      moveintake(intakespd);
      

     
 
    
      RV = rightfront.rotation(deg);
      LV = leftfront.rotation(deg);


    


      val = (LV - RV)*degToticks;
    Brain.Screen.print("3");

 }
 else{

   run = 0;
 }

}
  Brain.Screen.clearScreen();
  movebase(0);
  moveintake(0);
  


  Brain.Screen.print("5");


}
void timerleft(int duration, int speed){

int x = duration/100;
moveleft(speed);
vex::task::sleep(x*90);
moveleft(speed/10);
vex::task::sleep(x*10);
moveleft(0);


}

void BlueMk1(){

  
vex::task::sleep(100);
  advfwd(8.5,70,10);
  vex::task::sleep(210);
  advfwdWintake(16,12,5,100);
  vex::task::sleep(210);
  advturnleftWintake(28.86, 48, 10,100);
  vex::task::sleep(300);
  // intakefwd(280, 50, 100);
  moveintake(85);
  flywheel(10.45);
  vex::task::sleep(1825);
  shoot(575,10.55);
  shoot(1625,10.55);
  shoot(1625 ,10.55);
  flywheel(0);
  vex::task::sleep(200);
  moveintake(0);
  timerleft(284, -40);
  vex::task::sleep(400);
  reset(900, -80);
  vex::task::sleep(200);
  advfwd(5,50,10);
  vex::task::sleep(300); 
  advturnleft(90, 70, 10);
  vex::task::sleep(300);
  advfwd(7, 90, 10);
  vex::task::sleep(300);
  rightsidemv(800, 100);
  vex::task::sleep(200);
  reset(600, 40);
  vex::task::sleep(200);

  reset(200,-50);
  
}


void bluemk2(){
  advfwdWintake(27, 50, 10,100);
  vex::task::sleep(300);
  moveintake(100);
  reset(390, -50);
  vex::task::sleep(500);
  advturnright(100, 60, 10);
  vex::task::sleep(300);
  advfwd(8,50,10);
  vex::task::sleep(300);
  leftsidemv(900, 100);;
  vex::task::sleep(300);
  reset(600, 75);
  vex::task::sleep(300);
  reset(300,-50); 
  moveintake(0);
  vex::task::sleep(300);
  advturnright(208, 45,9);
  vex::task::sleep(300);
  advfwd(20, 75, 15);
  vex::task::sleep(300);
  flywheel(100);
  advturnright(56, 50, 10);
  vex::task::sleep(300);
  shoot(575,10.55);
  shoot(1625,10.55);
  shoot(1625 ,10.55);



}


void redmk1(){


  reset(200,-50);
  vex::task::sleep(100);
  advfwd(15,60,10);
  vex::task::sleep(210);
  advfwdWintake(15,25,10,100);
  vex::task::sleep(210);
  advturnrightWintake(20, 50, 10,100);
  moveintake(100);
  flywheel(100);
  vex::task::sleep(3400);
  moveintake(0);
  shoot(400,100);
  shoot(400,100);
  shoot(400,100);
  vex::task::sleep(200);
  advturnleft(20, 50, 10);
  vex::task::sleep(200);
  advrev(27,40,5);
  vex::task::sleep(300);
  advturnright(90, 50, 10);
  vex::task::sleep(300);
  advfwd(24, 50, 10);
  vex::task::sleep(300);
  advturnright(90, 50, 10);
  vex::task::sleep(300);
  reset(1100, 70);
  vex::task::sleep(300);
  advrev(7, 40, 10);
  vex::task::sleep(300);
  advturnright(125, 50, 10);
  vex::task::sleep(300);
  advfwd(24, 35,10);
  vex::task::sleep(200);
  intakefwd(1600, 35, 100);
  moveintake(100);
  vex::task::sleep(350);
  advrev(10,60,10);
  vex::task::sleep(300);
  advturnrightWintake(100, 70, 10, 100);
  moveintake(100);
  flywheel(100);
  vex::task::sleep(700);
  moveintake(0);
  shoot(1000,100);
  shoot(1000,100);

}


void redmk2(){
    advfwd(5, 50, 10);
  vex::task::sleep(300);
  advturnleft(90, 60, 10);
  vex::task::sleep(300);
  advfwd(10,50,10);
  vex::task::sleep(300);
  advturnleft(90, 60, 10);
  vex::task::sleep(300);
  reset(800, 60);
  vex::task::sleep(300);
  advrev(5, 55, 6);
  vex::task::sleep(300);
  advturnleft(135, 45,9);
  vex::task::sleep(300);
  advfwd(20, 75, 15);
  vex::task::sleep(300);
  advfwdWintake(10, 50, 6, 100);
  vex::task::sleep(300);
  flywheel(100);
  advturnleftWintake(45, 50, 10, 100);
  vex::task::sleep(300);
  shoot(600, 100);
  shoot(600,100);
  shoot(600,100);
  advturnright(45, 50, 10);
  vex::task::sleep(300);
  advfwdWintake(40, 60, 10, 100);
  flywheel(100);
  vex::task::sleep(300);
  advturnleftWintake(95, 60, 15, 100);
  shoot(600,100);
  shoot(600,100);

}

// Begin project code

void preAutonomous(void) {
  // actions to do when the program starts
  Brain.Screen.clearScreen();
  Brain.Screen.print("pre auton code");
  piston.set(true);
  wait(1, seconds);
}

void autonomous(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.print("autonomous code");
  // place automonous code here
  piston.set(true);
  bluemk2();
  




}

void userControl(void) {
  Brain.Screen.clearScreen();
  // place driver control in this while loop
  while (true) {



rightfront.spin(vex::directionType::fwd, H.Axis2.value(),vex::velocityUnits::pct);
leftfront.spin(vex::directionType::fwd, H.Axis3.value(),vex::velocityUnits::pct);
rightback.spin(vex::directionType::fwd, H.Axis2.value(),vex::velocityUnits::pct);
leftback.spin(vex::directionType::fwd, H.Axis3.value(),vex::velocityUnits::pct);

    if(V.ButtonR2.pressing()==1)
    {
      topfly.spin(directionType::fwd, 10.2, voltageUnits::volt);
      botfly.spin(directionType::fwd, 10.2, voltageUnits::volt);
    }

    else if(V.ButtonR1.pressing()==1)
    {

      topfly.spin(directionType::fwd, 9.05, voltageUnits::volt);
      botfly.spin(directionType::fwd, 9.05, voltageUnits::volt);
    }

    else 
    {
      topfly.spin(directionType::fwd,0,velocityUnits::pct);
      botfly.spin(directionType::fwd,0,velocityUnits::pct);
    }

       if(V.ButtonL2.pressing()==1)
    {
      piston.set(false);
      

    }
    else{
      piston.set(true);
    }

    intake.spin(vex::directionType::fwd, V.Axis2.value(),vex::velocityUnits::pct);

  }

 


    vex::task::sleep(20);
  }


int main() {
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
 
    wait(1,msec);
  }
}
