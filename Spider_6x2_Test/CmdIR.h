/*
 *    Module: CmdIR.h
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Command from BT
 *        
 */

#include <Arduino.h>
#include "Spider.h"
#include "IRremote.h"
#include "RTOS.h"

#ifndef CmdIR_h
#define CmdIR_h

class CmdIR {
    public:             
        Task* pGetCommandTask;   

        // methods
        CmdIR(); //constructor
        void getCommand(); //Task for get command   
};

extern CmdIR cmdIR;

#endif //CmdIR_h
//
// END OF FILE
//
