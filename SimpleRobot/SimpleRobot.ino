#include <Servo.h>

Servo servo[12]; 
int servoPin[12]={2,3,4,5,6,7,8,9,A0,A1,A2,A3};

int spiderMove[]  = { 
         200, 150,  90,    60,  90,    90,  90,   150,  90,    60,  90,    90,  90, //put leg set 2 
         200, 150,  90,    60,  45,    90,  90,   150, 135,    60,  90,    90, 135, //lift leg set 1
         200,  90,  90,    60,  45,    30,  90,   150, 130,   120,  90,    90, 135, //backward leg set 2
         200,  90,  90,   120,  45,    30,  90,    90, 130,   120,  90,    30, 135, //forward leg set 1
         200,  90,  90,   120,  90,    30,  90,    90,  90,   120,  90,    30,  90, //21 put leg set 1
         200,  90,  45,   120,  90,    30,  45,    90,  90,   120, 135,    30,  90, //lift leg set 2
         200,  90,  45,    60,  90,    30,  45,   150,  90,   120, 135,    90,  90, //backward leg set 1
         200, 150,  45,    60,  90,    90,  45,   150,  90,    60, 135,    90,  90, //forward leg set 2  
    //repeat put leg set 2         
};
    
void setup() {
    Serial.begin(9600);
    servoInit();
}

void loop() {
    for (int cmd=0; cmd<8; cmd++) {
        Serial.print("Command");
        Serial.print(cmd);
        Serial.print(":");
        for (int i=0; i<12; i++) {
            servo[i].write(spiderMove[cmd*13+i+1]);
            Serial.print(spiderMove[cmd*13+i+1]);
            Serial.print(" ");
        }
        delay(spiderMove[cmd*13]);    
        Serial.println(spiderMove[cmd*13]);                
    }
}

void servoInit()
{
    // 指定各個馬達使用腳位
    for (int i=0; i<12; i++) {
        servo[i].attach(servoPin[i]);
    }

    //servo1.attach(2);
    //servo2.attach(3);
    //servo3.attach(4);
    //servo4.attach(5);
    //servo5.attach(6);
    //servo6.attach(7);
    //servo7.attach(8);
    //servo8.attach(9);
    //servo9.attach(A0);
    //servo10.attach(A1);
    //servo11.attach(A2);
    //servo12.attach(A3);  
}

