/*
 * Registro.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_
#include <sigc++/sigc++.h>
#include <string>
using namespace std;

class Registro
{
public:
    Registro(string n)
    {
        valore = 0;
        nome = n;
        stato = '-';
        //	vista=NULL;
    }

    sigc::signal<void, char> reg_state_changed;

    string nome;
    char stato;

    char
    getValore() const
    {
        return valore;
    }

    void
    setValore(char valore)
    {
        this->valore = valore;
    }

    void
    MOV_from(Registro & r)
    {
        WRITE (r.READ ());
    }

    char
    READ()
    {
        set_stato ('R');
        return valore;
    }

    void
    WRITE(char c)
    {
        valore = c;
        set_stato ('W');
    }

    void
    set_stato(char c)
    {
        stato = c;
        reg_state_changed (c);
    }

private:
    char valore;
};

#endif /* REGISTRO_H_ */
