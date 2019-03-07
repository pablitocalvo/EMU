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

        sigc::signal<void> pin_writed_to_LOW;
        sigc::signal<void> pin_writed_to_HIGH;
        sigc::signal<void> pin_toggled;

    protected:
        Pin_3state_value valore ;
        string nome;

    public:
        bool is_high(){return valore==PIN_HIGH;}


        virtual void set_high(){valore=PIN_HIGH;pin_writed_to_HIGH();}
        virtual void set_low() {valore=PIN_LOW;pin_writed_to_LOW();}
        virtual void toggle() { if (valore==PIN_HIGH)
                              {set_low()  ;  pin_writed_to_LOW();}
                        else  {set_high() ;  pin_writed_to_LOW();}
                        pin_toggled();
                      }

        virtual Pin_3state_value
         get_value()
        {  return ( valore );  }

        string
        get_nome()
        { return nome;}



};

#endif /* PIN_H_ */
