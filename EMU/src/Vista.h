/*
 * Vista.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTA_H_
#define VISTA_H_

#include "common.h"
#include <list>


class Vista
{
public:

    Vista()
        {vista_attiva=false;s_vista="";}
    virtual
    ~Vista(){};

    bool
    is_attiva()
    { return vista_attiva;}

    void
    attiva()
        {
            vista_attiva = true;
            set_s_vista ();
        }

    void
    disattiva()
        {
            vista_attiva = false;
            set_s_vista ();
        }

    string
    vedi()
        {

            return s_vista;
        }

    virtual void set_s_vista()=0; //pure virtual


protected:
     bool vista_attiva;
     string s_vista;

};

#endif /* VISTA_H_ */
