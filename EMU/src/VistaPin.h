/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN_H_
#define VISTAPIN_H_

#include "PIN.h"
#include <string>
using namespace std;

class VistaPin : public Vista
{
public:
    VistaPin(PIN & p)
            : pin (p)
    {
        s_vista = set_s_vista ();
    }
    ;
    virtual
    ~VistaPin()
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
    {
        s_vista = pin.get_nome () + pin_state_to_string (pin.get_value ());
        if (is_attiva ())
            " [ " + s_vista + " ] ";
        else
            "   " + s_vista + "   ";
    }

private:
    PIN & pin;
    string s_vista;
};

#endif /* VISTAPIN_H_ */
