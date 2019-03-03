/*
 * Registro.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string>
using namespace std;


class Registro
{
public:
    Registro(string n) : nome(n){ set_valore(0);};
    virtual
    ~Registro()
    {
    }

    char
    get_valore() const {  return valore; }

    void
    set_valore (char valore){ this->valore = valore; }

    void enable () { en=true; }
    void disable() { en=false; }





private:
    char valore;
    string nome;
    bool en;


public:
};

#endif /* REGISTRO_H_ */
