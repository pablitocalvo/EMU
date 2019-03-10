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
    stato = "OFF";
    mnemo = " NOP ";

   CLK.sig_pin_toggled.connect( sigc::mem_fun (this, &CPU::run) );

  }

  string stato, mnemo;

  sigc::signal<void> cpu_state_changed;
  sigc::signal<void> sig_step_done;
  sigc::signal<void> sig_step_start;

  sigc::signal<void, CPU_component &> cpu_will_mod_comp;
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



//  typedef  void (&Ref_to_step_function )() ;
//
//  Ref_to_step_function rf1 = &CPU::FETCH_T1_HIGH;


  void
  FETCH_T1_HIGH()
  { //FETCH*************************************
    //stato = "FETCH-T1-HIGH";
    step_start ();

    MOV (AR, PC);

    step_done ();


  }
 void
  FETCH_T1_LOW()
 {
  //stato = "FETCH-T1-LOW";
        step_start ();


        set_STANDBY (PC);    //ora?

        set_high (RD);      //segnala alla ram....
        enable (RD);
        set_high (MREQ);
        enable (MREQ);

        step_done ();
 }
void FETCH_T2_HIGH()
{

       step_start ();


       // wait cicle.... tempo per informare il bus indirizzi...

       step_done ();
}

void FETCH_T2_LOW()
{
     // stato = "FETCH-T2-LOW";
       step_start ();
       // pone DR = ram( AR )...

       //DECODE *****************************************
       step_done ();
}


void DECODE_T1_HIGH()
{
     // stato = "DECODE-T1-HIGH";
       step_start ();

       set_STANDBY (AR);

       set_low (RD);
       disable (RD);
       set_low (MREQ);
       disable (MREQ);

       step_done ();
}



void DECODE_T1_LOW ()
    {
      //stato = "DECODE-T1-LOW";
      step_start ();



       mnemo = " INC A ";
       MOV (IR, DR);

       step_done ();
    }



void EXECUTE_T1_HIGH()
{

//stato = "EXECUTE-T1-HIGH";
  step_start ();
       // per ora nulla

       char appo = A.get_valore ();
       appo++;
       WRITE (A, appo);
       step_done ();
}

void EXECUTE_T1_LOW()
{
//stato = "EXECUTE-T1-LOW";
      step_start ();

       set_STANDBY(A);

       step_done ();
}


  void
  run()
  {
    if ((stato == "FETCH-T1-HIGH"))
                   {FETCH_T1_HIGH ();stato ="FETCH-T1-LOW" ;}
    else
    if ((stato == "FETCH-T1-LOW"))
                  {FETCH_T1_LOW (); stato="FETCH-T2-HIGH";}
    else
    if ((stato == "FETCH-T2-HIGH"))
                  {FETCH_T2_HIGH ();stato="FETCH-T2-LOW";}
    else
    if ((stato == "FETCH-T2-LOW"))
                  {FETCH_T2_LOW ();stato="DECODE_T1_HIGH";}
    else
    if ((stato == "DECODE_T1_HIGH"))
                  {DECODE_T1_HIGH ();stato="DECODE_T1_LOW";}

    else
    if ((stato == "DECODE_T1_LOW"))
                  {DECODE_T1_LOW ();stato="EXECUTE_T1_HIGH";}
    else
    if ((stato == "EXECUTE_T1_HIGH"))
                  { EXECUTE_T1_HIGH ();stato="EXECUTE_T1_LOW";}
    else
    if ((stato == "EXECUTE_T1_LOW"))
                  {EXECUTE_T1_LOW ();stato="FETCH-T1-HIGH";}

  }




  char
  READ(Registro & reg)
  {
   // cpu_will_mod_reg(reg);//VIENE CHIAMATA ANCHE DA ...

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

    reg.sig_reg_setted_to_reading();

  }
  void
  set_WRITING(Registro & reg)
  {
    cpu_will_mod_reg(reg);

    reg.set_writing ();

    reg.sig_reg_setted_to_writing();

  }
  void
  set_STANDBY(Registro & reg)
  { cpu_will_mod_reg(reg);

    reg.set_standby ();

    reg.sig_reg_setted_to_standby();

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
  setStato(string s)
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

