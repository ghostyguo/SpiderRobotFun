/*
 *    Module: CmdIR.cpp
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Command from IR
 *        
 */ 

#include "CmdIR.h"

CmdIR  cmdIR;  //External

#define IR_RECV 12

IRrecv irrecv(IR_RECV);  
decode_results results;
  
CmdIR::CmdIR()  //constructor
{
    irrecv.enableIRIn(); // Start the receiver
}

void CmdIR::getCommand() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}



