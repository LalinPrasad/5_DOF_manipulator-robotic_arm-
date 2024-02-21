#include "HCPCA9685.h"      //library for controlling PCA9685
int arr[50];                //array is used for storing moves of the manipulator
int img;
int realpos1,realpos2,realpos3;
int bas=1000,sh=2000,el=3000,wr=4090,gri1=5000,gri2=6000;
int i;
unsigned int realpos;
#define I2CAdd 0x40
int shoulder;
int elbow;
int wrist;
int gripper_1;
int gripper_2;
int base;
void reseting();
void runservo();
HCPCA9685 hc(I2CAdd);

void setup() {
  // put your setup code here, to run once:
hc.Init(SERVO_MODE);
hc.Sleep(false);
Serial.begin(9600);
i=0;
}


void loop() {
if (Serial.available()>=2)                 //code to get the values from the app that we built using MIT app Inventer
{
 unsigned int servopos=Serial.read();
 unsigned int servopos1=Serial.read();
 realpos=((servopos1*256)+servopos);
Serial.println(realpos);


 if(realpos>=1000)
 {
  realpos1=realpos;
 }
 
 else if(realpos<=3)
 {
  realpos2=realpos;
  if (realpos2==1)
  {
   arr[i]=realpos1;  //stores in array when SAVE button is clicked 
   i=i+1;  
  }
  else if(realpos2==2)
  {
     reseting();    // calls the reseting() function when reset button is clicked eo erase all the previously saved values
  }
  else if(realpos2==3)
  {
    
  runservo();       //calls the run() function when RUN buttonis clicked to run the manipulator automatically according to the saved values
 }
 }
}
 
 if (realpos1>=1000 && realpos1<=1180)
  {
    base=map(realpos,1000,1180,420,10);   //mapping of values is done using map() function 
     hc.Servo(0,base);                    // hc.servo() is used to run the servo ,where 0 represents the 0th port in the pca9685 module 
  }
  
   else if (realpos>=2000 && realpos<=2180)
  {
    shoulder=map(realpos,2010,2180,420,10); 
     hc.Servo(3,shoulder);  
  }
  
 else if (realpos>=3000 && realpos<=3180)
  {
    elbow=map(realpos,3010,3180,420,10); 
     hc.Servo(7,elbow);  
  }
 
 else if (realpos>=4000 && realpos<=4180)
  {
    wrist=map(realpos,4000,4180,420,10); 
     hc.Servo(8,wrist);
  }
  else if (realpos>=5000 && realpos<=5180)
  {
    gripper_1=map(realpos,5000,5180,10,420); 
    hc.Servo(12,gripper_1);
  }
  
   else if (realpos>=6000 && realpos<=6180)
  {
    gripper_2=map(realpos,6000,6180,10,420); 
     hc.Servo(15,gripper_2);
  }
  
} 


 void runservo()
{
  while(realpos!=4)
  {
    if(Serial.available()>0)
    {
     unsigned int servopos=Serial.read();
 unsigned int servopos1=Serial.read();
 realpos=((servopos1*256)+servopos);
    }
  for(int j=0;j<sizeof(arr)/2;j++) //for loop is used to reduce the speed of manipulator's movement
  {
    
    if(arr[j]>=1000 and arr[j]<=1180)
    {
     if(bas<arr[j])
     {
      for(int k=bas;k<=arr[j];k++)
      {
        base=map(k,1000,1180,420,10); 
        hc.Servo(0,base);
        delay(10);
      }
     }
     else
     {
      for(int k=bas;k>=arr[j];k--)
      {
        base=map(k,1000,1180,420,10); 
        hc.Servo(0,base);
        delay(10);
     }
     
    }
    bas=arr[j];
    }
    
    else if(arr[j]>=2000 and arr[j]<=2180)
    {
 
       if(sh<arr[j])
     {
      for(int k=sh;k<=arr[j];k++)
      {
        shoulder=map(k,2000,2180,420,10); 
        hc.Servo(3,shoulder);
        delay(20);
      }
     }
     else
     {
      for(int k=sh;k>=arr[j];k--)
      {
        shoulder=map(k,2000,2180,420,10); 
        hc.Servo(3,shoulder);
        delay(20);
     }
     
     //delay(150);
    }
    sh=arr[j];
    }
    
    else if(arr[j]>=3000 and arr[j]<=3180)
    {
    
         if(el<arr[j])
     {
      for(int k=el;k<=arr[j];k++)
      {
        elbow=map(k,3000,3180,420,10); 
        hc.Servo(7,elbow);
        delay(10);
      }
     }
     else
     {
      for(int k=el;k>=arr[j];k--)
      {
        elbow=map(k,3000,3180,420,10); 
        hc.Servo(7,elbow);
        delay(10);
     }
     
    }
    el=arr[j]; 
    }
    
    else if(arr[j]>=4000 and arr[j]<=4180)
    {
      if(wr<arr[j])
     {
      for(int k=wr;k<=arr[j];k++)
      {
        wrist=map(k,4000,4180,420,10); 
        hc.Servo(8,wrist);
        delay(10);
      }
     }
     else
     {
      for(int k=wr;k>=arr[j];k--)
      {
        shoulder=map(k,4000,4180,420,10); 
        hc.Servo(8,wrist);
        delay(10);
     }
     
    }
    wr=arr[j];

    }
    
    else if(arr[j]>=5000 and arr[j]<=5180)
    {
      
    if(gri1<arr[j])
     {
      for(int k=gri1;k<=arr[j];k++)
      {
        gripper_1=map(k,5000,5180,10,420); 
        hc.Servo(12,gripper_1);
        delay(10);
      }
     }
     else
     {
      for(int k=gri1;k>=arr[j];k--)
      {
        gripper_1=map(k,5000,5180,10,420); 
        hc.Servo(12,gripper_1);
        delay(10);
     }
     
    }
    gri1=arr[j];
    }
    
    else if(arr[j]>=6000 and arr[j]<=6180)
    {
 
      if(gri2<arr[j])
     {
      for(int k=gri2;k<=arr[j];k++)
      {
        gripper_2=map(k,6000,6180,10,420); 
        hc.Servo(15,gripper_2);
        delay(10);
      }
     }
     else
     {
      for(int k=gri2;k>=arr[j];k--)
      {
        gripper_2=map(k,6000,6180,10,420); 
        hc.Servo(15,gripper_2);
        delay(10);
     }
     
    }
    gri2=arr[j];
     //delay(150);
    }
    
    else
    {
      continue;
    }
    
    Serial.println(arr[j]);
    delay(1000);
    
  }
}
}

void reseting()
{
  for(int j=0;j<sizeof(arr)/2;j++)
  {
    arr[j]=0;
  }
}
