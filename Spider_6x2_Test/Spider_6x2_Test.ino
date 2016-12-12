/*
 *    Spider_Test: Test PWM Control for 12 Servo Motors
 *    
 *    Note : Each RTOS task must be executed within 1ms (RTOS tick) to generate the correct PWM pulse width.
 */
 
#include <avr/wdt.h>
#include "RTOS.h"
#include "Spider.h"
#include "ServoPwm.h"
#include "CmdPC.h"
#include "CmdBT.h"
#include "CmdIR.h"
#include "SpiderAuto.h"
#include <SoftwareSerial.h>

#define DEBUG_LEVEL 1
#define UseBlueTooth
#define UseIrRemote

#if defined(UseBlueTooth)
  #define   BT_RX  10
  #define   BT_TX  11
  SoftwareSerial BTSerial(BT_RX, BT_TX); // RX | TX
#endif

#if defined(UseIrRemote)
#endif

void setup() {
    wdt_disable();    // immediately disable watchdog timer so set will not get interrupted
    
    Serial.begin(57600);        // PC port on Serial
    cmdPC.begin(&Serial);

    #if defined(UseBlueTooth)
      BTSerial.begin(9600);  // HC-05 default speed in AT command more
      cmdBT.begin(&BTSerial);
    #endif
    
    // Add tasks to RTOS
    motor.pPwmTask = RTOS.taskManager.addTask(MotorPwmTask, "MotorPwmTask", 20000); //50Hz Pulse, 20ms 
    cmdPC.pGetCommandTask = RTOS.taskManager.addTask(CmdPcTask, "CmdPcTask", 20000); //check input stream every 20ms 
    
    #if defined(UseBlueTooth)
      cmdBT.pGetCommandTask = RTOS.taskManager.addTask(CmdBtTask, "CmdPcTask", 20000); //check input stream every 100ms 
    #endif  

    #if defined(UseIrRemote)
       cmdIR.pGetCommandTask = RTOS.taskManager.addTask(CmdIrTask, "CmdIrTask", 20000); //check input stream every 20ms 
    #endif
    
    spiderAuto.pMoveTask = RTOS.taskManager.addTask(SpiderMoveTask, "SpiderMoveTask", 1000000); //move legs every 1s
    
    // init()
    RTOS.init();    
    wdt_enable(WDTO_1S); //RTOS Task cannot run exceed 1s
}

void loop() {
    wdt_reset();
    RTOS.run(); //Always run th OS
}

void MotorPwmTask()
{
    motor.PwmControl();
    //motor.report();           //cannot report in running mode
    //motor.pPwmTask->report();  //cannot report in running mode
}

void CmdPcTask()
{
    cmdPC.getCommand();  //get command from input stream
    //cmdPC.pGetCommandTask->report();  //cannot report in running mode
}

#if defined(UseBlueTooth)
void CmdBtTask()
{
    cmdBT.getCommand();  //get command from input stream
    //cmdBT.pGetCommandTask->report();  //cannot report in running mode
}
#endif


#if defined(UseIrRemote)
void CmdIrTask()
{
    cmdIR.getCommand();  //get command from input stream
    //cmdBT.pGetCommandTask->report();  //cannot report in running mode
}
#endif

void SpiderMoveTask()
{
    if (spiderAuto.actionType>0) {
        spiderAuto.nextMove();
    }
    //spiderAuto.pMoveTask->report();
}

