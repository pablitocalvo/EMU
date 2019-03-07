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

        PIN_3state(string n) : nome(n){ set_low(); disable(); };
        virtual
        ~PIN_3state(){};

        sigc::signal<void> pin_writed_to_LOW;
        sigc::signal<void> pin_writed_to_HIGH;
        sigc::signal<void> pin_toggled;
        sigc::signal<void> pin_enabled;
        sigc::signal<void> pin_disabled;


    private:
        Pin_3state_value valore,en,output ;
        string nome;


    public:

        void enable()  { en=PIN_HIGH; output=valore; pin_enabled(); }
        void disable() { en=PIN_LOW ; output=PIN_Z ; pin_disabled();}

        void set_high(){ valore=PIN_HIGH; pin_writed_to_HIGH(); }
        void set_low() { valore=PIN_LOW;  pin_writed_to_LOW();  }
        void toggle()  { if (valore==PIN_HIGH)
                                      {set_low()  ;  pin_writed_to_LOW();}
                                else  {set_high() ;  pin_writed_to_LOW();}
                                pin_toggled();
                        }

        Pin_3state_value
        get_value(){  return ( (en==PIN_HIGH) ? valore : PIN_Z);  }

        string
        get_nome()
        { return nome;}

};

#endif /* PIN3STATE_H_ */
