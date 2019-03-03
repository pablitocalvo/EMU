/*
 * PIN.h
 *
 *  Created on: 27/feb/2019
 *      Author: paolo
 */

#ifndef PIN_H_
#define PIN_H_
#include <sigc++/sigc++.h>

#include <string>
using namespace std;


typedef enum ValueOfPin {
    PIN_HIGH = (int)'1',
    PIN_Z    = (int)'Z',
    PIN_LOW  = (int)'0'
};

class PIN
{
public:
    PIN(string s)
            : nome (s)
    {
        valore = PIN_LOW;
    }

    PIN(string s, ValueOfPin v)
                : nome (s)
        {
            valore = v;
        }

    sigc::signal<void> pin_writed_to_LOW;
    sigc::signal<void> pin_writed_to_HIGH;
    sigc::signal<void> pin_toggled;


    string nome;
    string val_of_pin_to_string( ValueOfPin v)
        {
            if ( v=='1')  return "1";
            if ( v=='0')  return "0";
            if ( v=='z')  return "Z";
            return "ERRORE";
        }
public:
    ValueOfPin valore;


    ValueOfPin
    get_valore() const
    {
       return valore;
    }

    void
    set_Low()

    {
        if (valore == PIN_HIGH)
        {
            valore = PIN_LOW;
            pin_writed_to_LOW();
        }
       // cout<<nome + " "+val_of_pin_to_string(valore)+ " set to LOW"<<endl;
    }

    void
    set_High()
    {
        if (valore == PIN_LOW)
        {
            valore = PIN_HIGH;
            pin_writed_to_HIGH();
        }
       // cout<<nome + " "+val_of_pin_to_string(valore)+ " set to HIGH"<<endl;
    }

    void
    toggle()
    {
        if (valore == PIN_LOW)
            set_High();
        else   set_Low();
        pin_toggled();
    }
};


class PIN_3State : public PIN
{
public:
    ValueOfPin output,enable;
    sigc::signal<void> pin_enabled;
    sigc::signal<void> pin_disabled;
public:

    PIN_3State (string s)
            : PIN(s)
    {
         enable = PIN_LOW;
    }

    void enabled()
    {
        enable=PIN_HIGH;
        output=valore;
        pin_enabled();

    }

    void disabled()
    {
        enable=PIN_LOW;
        output=PIN_Z;
        pin_disabled();

    }

    ValueOfPin
    get_valore() const
    {
        ////TO DO pin_state_changed ('R');
        if (enable == PIN_LOW)
            return PIN_Z;
        else
            return this->valore;
    }



};
#endif /* PIN_H_ */
