/*
 * CPU.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef CPU_H_
#define CPU_H_

#include <sigc++/sigc++.h>
#include <iostream>
#include <string>
using namespace std;

#include "Registro.h"

#include "PIN.h"
#include "PIN3state.h"


class CPU
{
public:
    CPU()
    {
        stato="OFF";mnemo=" NOP ";


    }

    string stato,mnemo;

    sigc::signal<void> cpu_state_changed;

    Registro A = Registro ("A");
    Registro B = Registro ("B");
    Registro PC = Registro ("PC");
    Registro DR = Registro ("DR");
    Registro AR = Registro ("AR");
    Registro IR = Registro ("IR");

    PIN CLK = PIN ("CLK");

    PIN_3state MREQ = PIN_3state ("MREQ");
    PIN_3state RD = PIN_3state ("RD");

void run()
{
    while(1)
    {   //assert stato==F1

     //FETCH*************************************
     // T1-HIGH

        PC.set_READING();  //TODO spostare a carico dei registri ?
        AR.set_WRITING();
        AR.WRITE(PC.READ());

    //cpu_step_done(); //cpu_start_step();
    // T1-LOW

        PC.set_STANDBY();    //ora?
        //AR.set_STANDBY();  //ora?

        RD.set_high ();
        RD.enable ();

        MREQ.set_high ();
        MREQ.enable ();

    //cpu_step_done(); //cpu_start_step();
    // T2-HIGH

            // wait cicle....

    //cpu_step_done(); //cpu_start_step();
    // T2-LOW
            // pone DR = ram( AR )...

    //DECODE *****************************************
    //cpu_step_done(); //cpu_start_step();
    // T1-HIGH

        RD.set_low ();
        RD.disable ();
        MREQ.set_low ();
        MREQ.disable ();
    //cpu_step_done(); //cpu_start_step();
    // T2-LOW
        mnemo = " INC A ";

    //EXECUTE *******************************************
    //cpu_step_done(); //cpu_start_step();
    // T1-HIGH

        // per ora nulla


    //cpu_step_done(); //cpu_start_step();
    // T2-LOW

        char appo = A.get_valore ();
        appo++;
        A.WRITE(appo);
    //****************************************************
    }

}



public:    void
    setStato(string s)
    {
        stato = s;
   }




};

#endif /* CPU_H_ */



