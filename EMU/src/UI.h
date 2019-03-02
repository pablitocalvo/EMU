/*
 * UI.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef UI_H_
#define UI_H_

#include "CPU.h"

#include <iostream>
#include <string>
//using namespace std;

#include <sigc++/sigc++.h>
#include "VistaReg.h"

class UI
{
public:
    UI(CPU & c)
            : cpu (c)
    {
        cpu.cpu_state_changed.connect (
                sigc::mem_fun (this, &UI::on_cpu_state_changed));

    }

    // handler per Cpu Changed

    void
    on_cpu_state_changed()
    {
        cout << "STATO " << cpu.stato << "    " << vCLK.vedi()
                                        << "   " << vMREQ.vedi()
                                        << "   " << vRD.vedi()
                                << endl;

        cout << vA.vedi () << "  ";
        cout << vPC.vedi () << "  ";
        cout << vIR.vedi () << "  ";
        cout << vDR.vedi () << "  ";
        cout << vMR.vedi () << endl;
    }


private:

    CPU & cpu;

    VistaReg vA = VistaReg (cpu.A);
    VistaReg vMR = VistaReg (cpu.MR);
    VistaReg vIR = VistaReg (cpu.IR);
    VistaReg vDR = VistaReg (cpu.DR);
    VistaReg vPC = VistaReg (cpu.PC);

    VistaPin vCLK = VistaPin(cpu.CLK);
    VistaPin vMREQ = VistaPin( cpu.MREQ);
    VistaPin vRD = VistaPin( cpu.RD);



};

#endif /* UI_H_ */
