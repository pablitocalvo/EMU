/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN3STATE_H_
#define VISTAPIN3STATE_H_

#include "common.h"
#include "PIN3state.h"
#include "Vista.h"

class VistaPin3_State : public VistaPin
{
public:
    VistaPin3_State(PIN_3state & p)
            : VistaPin(p)
    {
        p.pin_enabled.connect ( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_enabled  ), p));
        p.pin_disabled.connect( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_disabled ), p));
    }
    ;
    virtual
    ~VistaPin3_State()
    {
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

    void on_pin_enabled(PIN_3state & pin ){attiva();}
    void on_pin_disabled(PIN_3state & pin ){attiva();}


};

#endif /* VISTAPIN_H_ */
