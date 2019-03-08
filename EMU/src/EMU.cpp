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

void on_cpu_step_done()
{
    char c;
    do
    {   cin >> c;
       // if (c == 't') break;

    } while( c!= 't');
}
int
main()
{  // cout <<"hdfgdfd"<<endl;
    cpu.PC.set_valore(30);
    cpu.DR.set_valore(1);

    cpu.cpu_step_dones.connect( &on_cpu_step_done );

    cpu.run();



    return 0;
}



