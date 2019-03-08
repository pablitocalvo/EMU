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

        CLK.pin_toggled.connect (
                      //  sigc::bind (
                                sigc::mem_fun (this, &CPU::on_CLK_toggle)
                        //, &CLK)
        )      ;

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

    void
    on_CLK_toggle()
    {
        if (stato == "OFF")
            return;

        if (((stato == "ON") && CLK.is_high()  ) || (stato == "E2"))
        {
            setStato ("F1");


            PC.set_READING();  //TODO spostare a carico dei registri ?
            AR.set_WRITING();
            AR.WRITE(PC.READ());

        }
        else if (stato == "F1")
        {
            setStato ("F2");

            PC.set_STANDBY();
            AR.set_STANDBY();

            RD.set_high ();
            RD.enable ();

            MREQ.set_high ();
            MREQ.enable ();


        }
        else if (stato == "F2")
        {


            setStato ("F3");
            //non fa nioente wait per RAM (pone DR= ram(addr)

        }
        else if (stato == "F3")
        {
            setStato ("F4");

            RD.set_low ();
            RD.enable ();
            MREQ.set_low ();
            MREQ.enable ();

        }
        else if (stato == "F4")
        {
            setStato ("D1");

            IR.set_valore (DR.get_valore ());

        }
        else if (stato == "D1")
        {
            setStato ("D2");
            //DECODING ISTRUZIONE
            execute( IR.get_valore ());
        }
        else if (stato == "D2")
        {
            setStato ("E1");

            execute( IR.get_valore ());
            //EXECUTING INSTRUCTION
//            if (IR.get_valore () == 1)
//            {    // inc A
//                char appo = A.get_valore ();
//                appo++;
//                A.set_valore (appo);
//            }
        }
        else if (stato == "E1")
        {
            setStato ("E2");
        }

        cpu_state_changed() ;//TODO non è sempre necessario ..vedi primi due if ...
    }

public:    void
    setStato(string s)
    {
        stato = s;
   }



private:
 void execute( char opcode)
 {
     if (opcode==1)
     {    if (stato=="D2")
             {     mnemo = " INC A ";
             }
             else if (stato=="E1")
             {    // inc A
                             char appo = A.get_valore ();
                             appo++;
                             A.WRITE(appo);
             }
     }

     if (opcode==2)
     {    if (stato=="D2")
                  {     mnemo = " INC B ";
                  }
                  else if (stato=="E1")
                  {    // inc B
                              char appo = B.get_valore ();
                              appo++;
                              B.set_valore (appo);
                  }
     }



 }

};

#endif /* CPU_H_ */



