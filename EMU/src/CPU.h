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

#include "common.h"
#include "Registro.h"

#include "PIN.h"
#include "PIN3state.h"

class CPU
{
public:
  CPU()
  {
    stato = FETCH_T1_HIGH; //TODO basta stringhe!!!!!!!!!!!!!!!!!!!!!!!1
    mnemo = " NOP ";

   CLK.sig_pin_toggled.connect( sigc::mem_fun (this, &CPU::run) );

  }

  stati_cpu stato;
  string mnemo;

  sigc::signal<void> cpu_state_changed;
  sigc::signal<void> sig_step_done;
  sigc::signal<void> sig_step_start;

  sigc::signal<void, EMU_component &> cpu_will_mod_comp;
  sigc::signal<void, Registro &> cpu_will_mod_reg;
  sigc::signal<void, PIN &> cpu_will_mod_pin;




  Registro A = Registro ("A");
  Registro B = Registro ("B");
  Registro PC = Registro ("PC");
  Registro DR = Registro ("DR");
  Registro AR = Registro ("AR");
  Registro IR = Registro ("IR");

  PIN CLK = PIN ("CLK");

  PIN_3state MREQ = PIN_3state ("MREQ");
  PIN_3state RD = PIN_3state ("RD");

  void
  DO_FETCH_T1_HIGH()
  { //FETCH*************************************

    MOV (AR, PC);
  }

 void
 DO_FETCH_T1_LOW()
 {
  //stato = "FETCH-T1-LOW";

        set_STANDBY (PC);    //ora?
        set_high (RD);      //segnala alla ram....
        enable (RD);
        set_high (MREQ);
        enable (MREQ);
 }

 void  DO_FETCH_T2_HIGH()
{
     //  step_start ();
       // wait cicle.... tempo per informare il bus indirizzi...
      // step_done ();
}

void  DO_FETCH_T2_LOW()
{
       // pone DR = ram( AR )...

       //DECODE *****************************************

}


void  DO_DECODE_T1_HIGH()
{
     // stato = "DECODE-T1-HIGH";
     //  step_start ();

       set_STANDBY (AR);

       set_low (RD);
       disable (RD);
       set_low (MREQ);
       disable (MREQ);


}



void  DO_DECODE_T1_LOW ()
    {
      //stato = "DECODE-T1-LOW";
     // step_start ();



       mnemo = " INC A ";
       MOV (IR, DR);


    }



void DO_EXECUTE_T1_HIGH()
{

//stato = "EXECUTE-T1-HIGH";
 // step_start ();
       // per ora nulla

       char appo = A.get_valore ();
       appo++;
       WRITE (A, appo);

}

void  DO_EXECUTE_T1_LOW()
{
//stato = "EXECUTE-T1-LOW";
   //   step_start ();

       set_STANDBY(A);
}


  void
  run() //TODO ottimizzare ....
  {
    step_start ();
    if ((stato == FETCH_T1_HIGH))
                   { DO_FETCH_T1_HIGH (); step_done ();stato =FETCH_T1_LOW ;}
    else
    if ((stato == FETCH_T1_LOW))
                  { DO_FETCH_T1_LOW (); step_done (); stato=FETCH_T2_HIGH;}
    else
    if ((stato == FETCH_T2_HIGH))
                  { DO_FETCH_T2_HIGH (); step_done ();stato=FETCH_T2_LOW;}
    else
    if ((stato == FETCH_T2_LOW))
                  { DO_FETCH_T2_LOW (); step_done ();stato=DECODE_T1_HIGH;}
    else
    if ((stato == DECODE_T1_HIGH))
                  { DO_DECODE_T1_HIGH (); step_done ();stato=DECODE_T1_LOW;}
    else
    if ((stato == DECODE_T1_LOW))
                  { DO_DECODE_T1_LOW (); step_done ();stato=EXECUTE_T1_HIGH;}
    else
    if ((stato == EXECUTE_T1_HIGH))
                  {  DO_EXECUTE_T1_HIGH (); step_done ();stato=EXECUTE_T1_LOW;}
    else
    if ((stato == EXECUTE_T1_LOW))
                  { DO_EXECUTE_T1_LOW (); step_done ();stato=FETCH_T1_HIGH;}

  }




  char
  READ(Registro & reg)
  {
    set_READING(reg);
    return reg.get_valore ();
  }

  void
  WRITE(Registro & reg, char valore)
  { //cpu_will_mod_reg(reg); //VIENE CHIAMATA ANCHE DA ...
    set_WRITING(reg);


    reg.set_valore(valore);

  }

  void
  MOV(Registro & dst, Registro & src)
  {
    WRITE (dst, READ (src));
  }

  void
  set_READING(Registro & reg)
  {
    cpu_will_mod_reg(reg);

    reg.set_reading ();

    reg.sig_setted_to_reading();

  }
  void
  set_WRITING(Registro & reg)
  {
    cpu_will_mod_reg(reg);

    reg.set_writing ();

    reg.sig_setted_to_writing();

  }
  void
  set_STANDBY(Registro & reg)
  { cpu_will_mod_reg(reg);

    reg.set_standby ();

    reg.sig_setted_to_standby();

  }

  void
   set_high(PIN & p)
   { cpu_will_mod_pin(p);
     p.set_high ();
    p.sig_pin_setted_to_HIGH();
   }
     void
   set_low(PIN & p)
   {cpu_will_mod_pin(p);
     p.set_low ();
     p.sig_pin_setted_to_LOW();
   }
   void
   enable(PIN_3state & p)
   { cpu_will_mod_pin(p);
     p.enable ();
    p.sig_pin_enabled();
   }
   void
   disable(PIN_3state & p)
   { cpu_will_mod_pin(p);
     p.disable ();
     p.sig_pin_disabled();

   }





public:
  void
  setStato(stati_cpu s)
  {
    stato = s;
  }

  void
  step_done()
  {
    sig_step_done();
  }

  void
  step_start()
  {
    sig_step_start ();
  }

};

#endif /* CPU_H_ */

