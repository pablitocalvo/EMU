/*
 * PIN.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef PIN_H_
#define PIN_H_

#include "common.h"
class PIN
{
    public:
        PIN(string n) : nome(n) {set_low();}

        virtual
        ~PIN(){}

    private:
        Pin_3state_value valore ;
        string nome;

    public:

        void set_high(){valore=PIN_HIGH;}
        void set_low() {valore=PIN_LOW;}
        void toggle() { if (valore==PIN_HIGH)  set_low(); else set_high() ;}

        Pin_3state_value

        get_value(){  return ( valore );  }



};

#endif /* PIN_H_ */
