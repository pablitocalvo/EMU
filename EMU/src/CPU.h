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
  }

  string stato, mnemo;

  sigc::signal<void> cpu_state_changed;
  sigc::signal<void> cpu_step_dones;
  sigc::signal<void> cpu_step_starts;

  sigc::signal<void, CPU_component &> cpu_comp_will_mod;

  sigc::signal<void, Registro &> cpu_reg_set_reading;
  sigc::signal<void, Registro &> cpu_reg_set_writing;
  sigc::signal<void, Registro &> cpu_reg_set_standby;

  sigc::signal<void, Registro &> cpu_reg_WRITE;
  sigc::signal<void, Registro &> cpu_reg_READ;

  sigc::signal<void, PIN &> cpu_pin_writed_to_LOW;
  sigc::signal<void, PIN &> cpu_pin_writed_to_HIGH;

  sigc::signal<void, PIN_3state &> cpu_pin_enabled;
  sigc::signal<void, PIN_3state &> cpu_pin_disabled;

  void
  set_high(PIN & p)
  { cpu_comp_will_mod(p);
    p.set_high ();
   // cpu_pin_writed_to_HIGH (p);
  }
  void
  set_low(PIN & p)
  {cpu_comp_will_mod(p);
    p.set_low ();
    //cpu_pin_writed_to_LOW (p);
  }

  void
  enable(PIN_3state & p)
  { cpu_comp_will_mod(p);
    p.enable ();
   // cpu_pin_enabled (p);
  }
  void
  disable(PIN_3state & p)
  { cpu_comp_will_mod(p);
    p.disable ();
   // cpu_pin_disabled (p);
  }

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
  run()
  {
    while (1)
    {   //assert stato==F1

//FETCH*************************************

      stato = "FETCH-T1-HIGH";
      step_start ();
//      set_READING (PC); //TODO spostare a carico della mov read write , penso di si ? ?
//      set_WRITING (AR);
        MOV (AR, PC);
        step_done ();


///////////////////////////

      stato = "FETCH-T1-LOW";
      step_start ();


      set_STANDBY (PC);    //ora?

      set_high (RD);
      enable (RD);
      set_high (MREQ);
      enable (MREQ);

      step_done ();

///////////////////////////

      stato = "FETCH-T2-HIGH";
      step_start ();


      // wait cicle....

      step_done ();

///////////////////////////

      stato = "FETCH-T2-LOW";
      step_start ();
      // pone DR = ram( AR )...

      //DECODE *****************************************
      step_done ();
      step_start ();
      stato = "DECODE-T1-HIGH";
      set_STANDBY (AR);

      set_low (RD);
      disable (RD);
      set_low (MREQ);
      disable (MREQ);

      step_done ();

///////////////////////////////

      stato = "DECODE-T1-LOW";
      step_start ();
      mnemo = " INC A ";
      MOV (IR, DR);
      //EXECUTE *******************************************
      step_done ();

      stato = "EXECUTE-T1-HIGH";
      step_start ();
      // per ora nulla

      char appo = A.get_valore ();
      appo++;
      WRITE (A, appo);
      step_done ();



      stato = "EXECUTE-T1-LOW";
      step_start ();

      set_STANDBY(A);

      step_done ();

      //****************************************************
    }

  }

  char
  READ(Registro & reg) const
  { cpu_comp_will_mod(reg);
    reg.set_reading ();
    cpu_reg_READ (reg);
    return reg.get_valore ();
  }

  void
  WRITE(Registro & reg, char valore)
  { cpu_comp_will_mod(reg);
    reg.set_writing ();
    reg.set_valore (valore);
    cpu_reg_WRITE (reg);
  }

  void
  MOV(Registro & dst, Registro & src)
  {
    WRITE (dst, READ (src));
  }

  void
  set_READING(Registro & reg)
  {
    cpu_comp_will_mod(reg);
    reg.set_reading ();
    cpu_reg_set_reading (reg);
  }
  void
  set_WRITING(Registro & reg)
  { cpu_comp_will_mod(reg);
    reg.set_writing ();
    cpu_reg_set_writing (reg);
  }
  void
  set_STANDBY(Registro & reg)
  { cpu_comp_will_mod(reg);
    reg.set_standby ();
    cpu_reg_set_standby (reg);
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
    cpu_step_dones();
  }

  void
  step_start()
  {
    cpu_step_starts ();
  }

};

#endif /* CPU_H_ */

