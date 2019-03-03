/*
 * CPU.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef CPU_H_
#define CPU_H_

#include <sigc++/sigc++.h>
#include <iostream>
#include <string>
using namespace std;

#include "Registro.h"

#include "PIN.h"

class CPU
{
public:
    CPU()
    {
        stato="OFF";
    }

    string stato;

    Registro A = Registro ("A");
    Registro B = Registro ("B");
    Registro PC = Registro ("PC");
    Registro DR = Registro ("DR");
    Registro AR = Registro ("AR");
    Registro IR = Registro ("IR");

    PIN CLK = PIN ("CLK");

    PIN_3state MREQ = PIN_3state ("RW");
    PIN_3state IO = PIN_3state ("IO", false);


    void
    on_CLK_toggle()
    {
       if (stato == "ON")
            setStato ("F1");
       else if (stato == "F1")
        {

            setStato ("F2");

        }

        else if (stato == "F2")
        {  // legge il byte dalla Ram
           // READ from Data BUS
           // in DR
           //provvisoriamente  1 è l'opcode di inc A


            setStato ("D1");
        }

        else if (stato == "D1")
        {


            //for now do nothiung ......
            // must we inform UI of decoding???
            //disabilita gli stati r/W dei componenti coinvolti prima...

            setStato ("D2");
        }
        else if (stato == "D2")
        {	//for now do nothiung ......
            // must we inform UI of decoding???
            setStato ("E1");
        }
        else if (stato == "E1")
        {	//for now do nothiung ......

            if (IR.get_valore () == 1)
            {    // inc A
                char appo = A.get_valore ();
                appo++;
                A.set_valore(appo);

            }

            setStato ("F1");
        }

    }


public:    void
    setStato(string s)
    {   cpu_state_changed.emit ();
        stato = s;


    }

};

#endif /* CPU_H_ */



