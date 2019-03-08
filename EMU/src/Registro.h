/*
 * Registro.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "common.h"
typedef enum Stato_registro { READING , STANDBY , WRITING };
class Registro
{

public:
    Registro(string n) : nome(n), valore(0) , stato(STANDBY) {};
    virtual
    ~Registro()
    {
    }

    bool is_reading(){return (stato==READING);}
    bool is_writing(){return (stato==WRITING);}
    bool is_standby(){return (stato==STANDBY);}

    void set_valore(char c){valore=c;}
    char get_valore(){return valore;}

    void set_reading() { stato=READING; }
    void set_writing() { stato=WRITING; }
    void set_standby() { stato=STANDBY; }

    string  get_nome() { return nome;   }


private:
    string nome;
    char valore;
    Stato_registro stato ;


public:
};

#endif /* REGISTRO_H_ */
