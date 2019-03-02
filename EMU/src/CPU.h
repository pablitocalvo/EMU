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
        stato = "OFF";
        //TO DO : inserire accensione ....

        CLK.pin_toggled.connect(
                sigc::bind(
                        sigc::mem_fun (this, &CPU::on_CLK_toggled),
                        &CLK));



    }

    Registro A = Registro ("A");
    Registro B = Registro ("B");
    Registro PC = Registro ("PC");
    Registro DR = Registro ("DR");
    Registro MR = Registro ("MR");
    Registro IR = Registro ("IR");
    Registro AR = Registro ("AR");

    PIN CLK = PIN ("CLK",PIN_HIGH);

    PIN RW = PIN ("RW");
    PIN IO = PIN ("IO");



    string stato;

    sigc::signal<void> cpu_state_changed;



    void
    on_CLK_toggled(PIN * clk)
    {
        if (stato == "ON")
            setStato ("F1");
        else if (stato == "F1")
        {
            req_data_from_memory(PC);

            setStato ("F2");

        }

        else if (stato == "F2")
        {  // legge il byte dalla Ram
           // READ from Data BUS
           // in DR
           //provvisoriamente  1 è l'opcode di inc A

            DR.WRITE (1);
            setStato ("D1");
        }

        else if (stato == "D1")
        {
            IO.set_Low (); //low or none ??
            RW.set_Low ();

            IR.MOV_from (DR);

            //for now do nothiung ......
            // must we inform UI of decoding???
            //disabilita gli stati r/W dei componenti coinvolti prima...
            PC.set_stato ('-');
            MR.set_stato ('-');

            char appo = PC.getValore (); // PC++
            appo++;
            PC.WRITE (appo);

            setStato ("D2");
        }
        else if (stato == "D2")
        {	//for now do nothiung ......
            // must we inform UI of decoding???
            setStato ("E1");
        }
        else if (stato == "E1")
        {	//for now do nothiung ......

            if (IR.getValore () == 1)
            {    // inc A
                char appo = A.getValore ();
                appo++;
                A.WRITE (appo);

            }

            setStato ("F1");
        }

    }

public:
    void
    setStato(string s)
    {
        cpu_state_changed.emit ();
        stato = s;

    }

private:

    void
    req_data_from_memory(Registro & raddr)
    {
        MR.MOV_from (raddr);  // richiede un byte alla Ram
        IO.set_High ();
        RW.set_High ();
    }

    void post_read_from_memory( Registro & raddr)
    {

    };


    void mov_reg_reg(Registro & rsrc , Registro & rdst){}
    void post_reg_reg(){}

};

#endif /* CPU_H_ */
