/*
 * Registro.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <list>
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

    sigc::signal<void> reg_state_writing;
    sigc::signal<void> reg_state_reading;
    sigc::signal<void> reg_state_standby;
    sigc::signal<void> reg_writed; //sono necessari veramente??
    sigc::signal<void> reg_read;   //sono necessary veramente??

    char
    READ() const { reg_read();return valore;  }

    void
    WRITE (char valore){ this->valore = valore; reg_writed(); }

    void set_READING() { stato=READING;reg_state_reading(); }
    void set_WRITING() { stato=WRITING;reg_state_writing(); }
    void set_STANDBY() { stato=STANDBY;reg_state_standby(); }


    bool is_reading(){return (stato==READING);}
    bool is_writing(){return (stato==WRITING);}
    bool is_standby(){return (stato==STANDBY);}

    void set_valore(char c){valore=c;}
    char get_valore(){return valore;}

    string
    get_nome()
    {
        return nome;
    }


private:
    string nome;
    char valore;
    Stato_registro stato ;


public:
};

#endif /* REGISTRO_H_ */
