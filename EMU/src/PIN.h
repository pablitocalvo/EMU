/*
 * PIN.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef PIN_H_
#define PIN_H_

#include <sigc++/sigc++.h>
#include "common.h"
class PIN
{
    public:
        PIN(string n) : nome(n) {set_low();}

        virtual
        ~PIN(){}

        sigc::signal<void> pin_writed_to_LOW;
        sigc::signal<void> pin_writed_to_HIGH;
        sigc::signal<void> pin_toggled;

    private:
        Pin_3state_value valore ;
        string nome;

    public:

        void set_high(){valore=PIN_HIGH;pin_writed_to_HIGH();}
        void set_low() {valore=PIN_LOW;pin_writed_to_LOW();}
        void toggle() { if (valore==PIN_HIGH)  set_low(); else set_high() ;pin_writed_to_LOW();}

        Pin_3state_value
        get_value()
        {  return ( valore );  }

        string
        get_nome()
        { return nome;}



};

#endif /* PIN_H_ */
