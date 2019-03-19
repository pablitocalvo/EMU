/*
 * BUS.h
 *
 *  Created on: 19/mar/2019
 *      Author: paolo
 */

#ifndef BUS_H_
#define BUS_H_
#include "common.h"
#include "EMUcomponent.h"
#include "PIN3state.h"
#include "Registro.h"

class BUS : public Registro
{
public:
  BUS(string n): Registro(n)
  {

  }
  virtual
  ~BUS(){}

 sigc::signal<void, Registro &> bus_will_mod_reg;



  void connect (PIN_3state & pin , Registro & reg)
  {
    //porta_del_pin.insert(pair<PIN_3state *, Registro *>( &pin , &reg));
    porta_del_pin[&pin]=&reg;

    //TODO pi.sig_pin_disabled ... quando l'ultimo pin ....
//    pin.sig_pin_enabled.connect(
//        sigc::bind(sigc::mem_fun (this, &BUS::on_pin_enabled), pin));
//
//    pin.sig_pin_disabled.connect(
//            sigc::bind(sigc::mem_fun (this, &BUS::on_pin_disabled), pin));
  }


private:
  map<PIN_3state  *, Registro *> porta_del_pin;

  void on_pin_disabled(PIN_3state & pin)
  {
    //TODO controlla se l'ultumo disabilitato ....




  }
  void on_pin_enabled(PIN_3state & pin)
  {
    Registro &reg = * porta_del_pin[&pin];
         if (pin.is_high())
    {  //la porta vuole leggere READ

      bus_will_mod_reg(reg);
      reg.set_writing();
      reg.sig_setted_to_writing();

      this->sig_setted_to_reading();
      reg.set_valore(this->get_valore());
      this->sig_was_WRITE();

    }

    else if (pin.is_low())
    { // la porta vuole scrivere WRITE to BUS

      bus_will_mod_reg(reg);
      reg.set_reading ();
      reg.sig_setted_to_reading();


     this->set_valore(reg.get_valore());
      this->sig_was_WRITE();



    }
    else
    {
      //assert ("ERRORE")
      cout <<"ERRORE ??' PIN ASSOCIato al bUS MA... "<<endl;
    }


  }



};

#endif /* BUS_H_ */
