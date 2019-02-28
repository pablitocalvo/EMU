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

class VistaReg
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

class VistaPin
{
public:
    VistaPin(PIN & p)
            : pin (p)
    {
        label = "- " + to_string ((int) p.get_valore ());
        p.pin_state_changed.connect (
                        sigc::bind<0> (
                                sigc::mem_fun (this, &VistaPin::on_pin_state_changed),
                                &pin));
    }



void
on_pin_state_changed(PIN * p, char c)
//void
//on_reg_state_changed(char c)
{  string s;

    if (p->valore==true)
            s= "1";
    else    s= "0";

    if (c == '-')
        label = string("- ") + s;
    else if (c == 'W')
        label = string("W " )+ s;
    else if (c == 'R')
        label = string("R ") + s;

}
public: string  vedi()
       {
           return (pin.nome + " = " + label);
       }



private:
    PIN & pin;

    string label;

};

#endif /* VISTAREG_H_ */
