/*
 * Vista.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTA_H_
#define VISTA_H_

class Vista
{
public:

    Vista(){vista_attiva=false;}
    virtual
    ~Vista(){};

    bool is_attiva(){ return vista_attiva;}

    virtual void attiva()=0;
    virtual void disattiva()=0;

    virtual string vedi()=0; // la classe è astratta e questo è un metodo virtuale puro


protected:
     bool vista_attiva;

};

#endif /* VISTA_H_ */
