/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN3STATE_H_
#define VISTAPIN3STATE_H_

#include "PIN3state.h"
#include "Vista.h"
#include <string>
using namespace std;

class VistaPin3_State : public Vista
{
public:

    VistaPin3_State(PIN_3state & p)
            : pin (p)
    {
        set_s_vista ();
        p.pin_writed_to_HIGH.connect( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_writed_to_HIGH), p));
        p.pin_writed_to_LOW.connect(  sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_writed_to_LOW ), p));

        //differetnte da VistaPIN
        p.pin_enabled.connect ( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_enabled  ), p));
        p.pin_disabled.connect( sigc::bind<0> ( sigc::mem_fun (this, &VistaPin3_State::on_pin_disabled ), p));
    }
    ;
    virtual
    ~VistaPin3_State()
    {
    }
    ;

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
    PIN_3state & pin;
    string s_vista;

    void on_pin_writed_to_HIGH(PIN_3state & pin ){attiva();}
    void on_pin_writed_to_LOW(PIN_3state & pin){attiva();}
    //differetnte da VistaPIN
    void on_pin_enabled(PIN_3state & pin ){attiva();}
    void on_pin_disabled(PIN_3state & pin ){attiva();}


};

#endif /* VISTAPIN_H_ */
