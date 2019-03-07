/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN_H_
#define VISTAPIN_H_

#include "common.h"
#include "PIN.h"
#include "Vista.h"

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
    virtual set_s_vista()
    {   //cout<< "set_s_vista.."+pin.get_nome () + pin_state_to_string (pin.get_value ())<<endl;

        s_vista = pin.get_nome () +" "+ pin_state_to_string (pin.get_value ());
        if (is_attiva ())
            s_vista =" [ " + s_vista + " ] ";
        else
            s_vista ="   " + s_vista + "   ";
    }

protected:
    PIN & pin;


    void on_pin_writed_to_HIGH(PIN & pin ){attiva();}
    void on_pin_writed_to_LOW(PIN & pin){attiva();}


};

#endif /* VISTAPIN_H_ */
