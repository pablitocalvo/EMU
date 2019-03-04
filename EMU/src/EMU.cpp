/*
 * EMU.cpp
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

//============================================================================
// Name        : EMU.cpp
// Author      : Paolo Sabatini
// Version     :
// Copyright   : GPL - 3.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

#include "CPU.h"
#include "UI.h"
#include "common.h"

CPU cpu = CPU ();
UI ui = UI (cpu);

int
main()
{  // cout <<"hdfgdfd"<<endl;
    cpu.PC.set_valore(30);
    cpu.DR.set_valore(1);
    cpu.setStato("ON");
    char c;
    ui.visualizza ();



    while (1)
    {
        cin >> c;
        if (c == 't')
        {   cpu.CLK.toggle();
            //ui.visualizza();
        }
        if (c == 'x')
        { cout <<"ciaoooooooooooooooo"; exit (0);}

    }

    return 0;
}



