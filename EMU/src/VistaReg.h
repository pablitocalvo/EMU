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

class VistaPin : public  Vista
{private:
    PIN & pin;
    string v_value;

public:

    VistaPin(PIN & p)
            : pin (p)
    {
        v_value = val_of_pin_to_string( p.get_valore());

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
    {   attiva=true;
        v_value = "1";
    }

    void
    on_pin_writed_to_LOW(PIN * p)
    {   attiva=true;
        v_value = "0";
    }


public: string  vedi()
   {    string s;
       if (attiva)  s= pin.nome + " = [ " + v_value+" ]";
       else s= pin.nome + " =   " + v_value+"  ";
       return s;
   }






    string val_of_pin_to_string( ValueOfPin v)
    {
        if ( v=='1')  return "1";
        if ( v=='0')  return "0";
        if ( v=='z')  return "Z";
        return "ERRORE";
    }

};
class VistaPin_3State : public Vista
{private:
    PIN_3State & pin;
    string v_value;

public:
    VistaPin_3State(PIN_3State & p)
            : pin (p)
    {
        v_value = val_of_pin_to_string( p.get_valore());

        p.pin_writed_to_HIGH.connect( sigc::bind<0> (
                                            sigc::mem_fun (this, &VistaPin_3State::on_pin_writed_to_HIGH),
                                        &pin));
        p.pin_writed_to_LOW.connect( sigc::bind<0> (
                                            sigc::mem_fun (this, &VistaPin_3State::on_pin_writed_to_LOW),
                                        &pin));
        p.pin_enabled.connect( sigc::bind<0> (
                                            sigc::mem_fun (this, &VistaPin_3State::on_pin_enabled),
                                        &pin));
        p.pin_disabled.connect( sigc::bind<0> (
                                            sigc::mem_fun (this, &VistaPin_3State::on_pin_disabled),
                                        &pin));
    }

    void
    on_pin_enabled(PIN * p)
    {
        attiva=true;
        v_value=val_of_pin_to_string( p->valore);
    }

    void
    on_pin_disabled(PIN * p)
    {   attiva=true;
        v_value=PIN_Z;

    }

    void
    on_pin_writed_to_HIGH(PIN * p)
    {   attiva=true;
        v_value = "1";
    }

    void
    on_pin_writed_to_LOW(PIN * p)
    {   attiva=true;
        v_value = "0";
    }


public: string  vedi()
   {    string s;
       if (attiva)
           s= pin.nome + " = [ " + val_of_pin_to_string( pin.get_valore())+" ]";
       else s= pin.nome + " =   " + val_of_pin_to_string( pin.get_valore())+"  ";
       return s;
   }






    string val_of_pin_to_string( ValueOfPin v)
    {
        if ( v=='1')  return "1";
        if ( v=='0')  return "0";
        if ( v=='z')  return "Z";
        return "ERRORE";
    }

};

#endif /* VISTAREG_H_ */
