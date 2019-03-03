/*
 * PIN3state.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef PIN3STATE_H_
#define PIN3STATE_H_
#include "common.h"


class PIN_3state
{
    public:

        PIN_3state(){ set_low(); disable(); };
        virtual
        ~PIN_3state(){};

    private:
        Pin_3state_value valore,en,output ;

    public:

        void enable() { en=PIN_HIGH; output=valore;}
        void disable() { en=PIN_LOW;output=PIN_Z;}

        void set_high(){valore=PIN_HIGH;}
        void set_low() {valore=PIN_LOW;}

        Pin_3state_value
        get_value(){  return ( (en==PIN_HIGH) ? valore : PIN_Z);  }
};

#endif /* PIN3STATE_H_ */
