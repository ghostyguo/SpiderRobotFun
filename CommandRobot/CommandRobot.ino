#include <Servo.h>

#define   CmdBufferLength        12
#define   NumberOfServo          12
#define   Code_OK    "OK"
#define   Code_ERR   "ERR"

Servo servo[NumberOfServo]; 
int servoPin[NumberOfServo]={2,3,4,5,6,7,8,9,A0,A1,A2,A3};
int servoAngle[NumberOfServo]={90,90,90,90,90,90,90,90,90,90,90,90};
char cmdBuffer[CmdBufferLength];
int  cmdLength=0;
  
void setup() {
    Serial.begin(9600);
    servoInit();
}

void loop() {
    if (getCommand()) {    
        for (int i=0; i<NumberOfServo; i++) {
            servo[i].write(servoAngle[i]);
        }
    }  
}

void servoInit()
{
    // 指定各個馬達使用腳位
    for (int i=0; i<12; i++) {
        servo[i].attach(servoPin[i]);
    }
}

int getCommand() 
{
    while (Serial.available()) {
        byte inByte = Serial.read();
        if (inByte=='$') { // Start Of Command
            cmdLength=0;
        }
        cmdBuffer[cmdLength++] = inByte;
        if (inByte=='#') {  // End Of Command
            if (parseCommand()>0) {
                //Serial.println("parse ok");
                return 1;  // success
            } else { 
                //Serial.println("parse fail");
                return 0;//fail
            } 
        } 
    }
    return 0;
}

int parseCommand()
{
    int retCode=0;
    
    if ((cmdBuffer[1]=='M') && (cmdBuffer[4]=='A') && (cmdBuffer[8]=='#'))
    { 
        // Command : Motor Angle 
        int motorID = (cmdBuffer[2]-'0')*10 + (cmdBuffer[3]-'0');
        servoAngle[motorID] = (cmdBuffer[5]-'0')*100 + (cmdBuffer[6]-'0')*10 + (cmdBuffer[7]-'0');
        retCode=1;
    } 
    cmdLength=0; //reset 
    for (int i=0; i<CmdBufferLength; i++) 
        cmdBuffer[i]=0;
    return retCode;
}

