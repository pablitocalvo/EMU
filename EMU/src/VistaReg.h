/*
 * VistaReg.h
 *
 *  Created on: 25/feb/2019
 *      Author: paolo
 */

#ifndef VISTAREG_H_
#define VISTAREG_H_

#include <string>
#include "Registro.h"
#include "PIN.h"

class Vista
{
public:
    Vista()
    {attiva=false;}

bool attiva;
};



class VistaReg : Vista
{
public:

    VistaReg(Registro & r)
            : reg (r)
    {
        label = "- " + to_string ((int) r.getValore ());

        //reg.reg_state_changed.connect (sigc::mem_fun (this, &VistaReg::on_reg_state_changed));
        reg.reg_state_changed.connect (
                sigc::bind<0> (
                        sigc::mem_fun (this, &VistaReg::on_reg_state_changed),
                        &reg));

    }

    void
    on_reg_state_changed(Registro * r, char c)
    //void
    //on_reg_state_changed(char c)
    {
        if (c == '-')
            label = "- " + to_string ((int) r->getValore ());
        else if (c == 'W')
            label = "W " + to_string ((int) r->getValore ());
        else if (c == 'R')
            label = "R " + to_string ((int) r->getValore ());

    }

    string
    vedi()
    {
        return (reg.nome + " = " + label);
    }

private:
    Registro & reg;

    string label;
};

class VistaPin : Vista
{
public:
    VistaPin(PIN & p)
            : pin (p)
    {

        if (attiva) label = " [ " + val_of_pin_to_string( p.get_valore())+" ] ";
        else        label = "   " + val_of_pin_to_string( p.get_valore())+"   ";



        p.pin_writed_to_HIGH.connect(
                                sigc::bind<0> (
                                        sigc::mem_fun (this, &VistaPin::on_pin_writed_to_HIGH),
                                        &pin));
        p.pin_writed_to_LOW.connect(
                                sigc::bind<0> (
                                        sigc::mem_fun (this, &VistaPin::on_pin_writed_to_LOW),
                                        &pin));
   }


    void
    on_pin_writed_to_HIGH(PIN * p)
    {
        label = " [ " + val_of_pin_to_string( p->get_valore())+" ] ";
    }

    void
    on_pin_writed_to_LOW(PIN * p)
    {   label = " [ " + val_of_pin_to_string( p->get_valore())+" ] ";
    }


public: string  vedi()
       {
           return (pin.nome + " = " + label);
       }



private:
    PIN & pin;

    string label;

    string stato="-" ;


    string val_of_pin_to_string( ValueOfPin v)
    {
        if ( v=='1')  return "1";
        if ( v=='0')  return "0";
        if ( v=='z')  return "Z";
        return "ERRORE";
    }

};

#endif /* VISTAREG_H_ */
