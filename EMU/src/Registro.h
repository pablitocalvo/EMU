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

typedef enum Stato_registro { READING , STANDBY , WRITING };
public:
    Registro(string n) : nome(n), valore(0) , stato(STANDBY) {};
    virtual
    ~Registro()
    {
    }

    sigc::signal<void> reg_writing;
    sigc::signal<void> reg_reading;
    sigc::signal<void> reg_standby;

    char
    READ() const { return valore;  }

    void
    WRITE (char valore){ this->valore = valore; }

    void set_READING() { stato=READING;reg_reading(); }
    void set_WRITING() { stato=WRITING;reg_writing(); }
    void set_STANDBY() { stato=STANDBY;reg_standby(); }



private:
    char valore;
    string nome;
    Stato_registro stato ;


public:
};

#endif /* REGISTRO_H_ */
