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

class PIN
{

public:
    PIN(string s)
            : nome (s)
    {
        stato = '-';
        valore = false;
    }


    sigc::signal<void, char> pin_state_changed;
    const string nome;
protected:


    char stato;

public:
bool valore;
    bool
    get_valore() const
    {
        pin_state_changed ('R');
        return valore;
    }

//    void
//    set_valore(bool valore)
//    {
//        this->valore = valore;
//    }

    void
    set_Low()
    {
        if (valore == true)
        {
            valore = false;
            pin_state_changed ('W');
        }
    }

    void
    set_High()
    {
        if (valore == false)
        {
            valore = true;
            pin_state_changed ('W');
        }
    }

    void toggle()
    {
        valore = ! valore ;
        pin_state_changed ('W');
    }
};


#endif /* PIN_H_ */
