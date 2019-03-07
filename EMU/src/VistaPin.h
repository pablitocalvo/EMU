/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN_H_
#define VISTAPIN_H_

#include "PIN.h"
#include "Vista.h"
#include <string>
using namespace std;

class VistaPin : public Vista
{
public:

    VistaPin(PIN & p)
            : pin (p)
    {
        set_s_vista ();
        p.pin_writed_to_HIGH.connect( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin::on_pin_writed_to_HIGH), p));
        p.pin_writed_to_LOW.connect(  sigc::bind<0> ( sigc::mem_fun (this, &VistaPin::on_pin_writed_to_LOW ), p));
    }

    virtual
    ~VistaPin()
    {
    }



    void
    attiva()
    {
        vista_attiva = true;
        set_s_vista ();
    }

    void
    disattiva()
    {
        vista_attiva = false;
        set_s_vista ();
    }

    string
    vedi()
    {

        return s_vista;
    }

    void
    set_s_vista()
    {   //cout<< "set_s_vista.."+pin.get_nome () + pin_state_to_string (pin.get_value ())<<endl;

        s_vista = pin.get_nome () +" "+ pin_state_to_string (pin.get_value ());
        if (is_attiva ())
            s_vista =" [ " + s_vista + " ] ";
        else
            s_vista ="   " + s_vista + "   ";
    }

private:
    PIN & pin;
    string s_vista;

    void on_pin_writed_to_HIGH(PIN & pin ){attiva();}
    void on_pin_writed_to_LOW(PIN & pin){attiva();}


};

#endif /* VISTAPIN_H_ */
