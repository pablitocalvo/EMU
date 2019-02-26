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
using namespace std;

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

			cpu.IO.setted_to_high.connect (
					sigc::bind (sigc::mem_fun (this, &UI::on_setted_to_high),
								&cpu.IO));
			cpu.IO.setted_to_low.connect (
					sigc::bind (sigc::mem_fun (this, &UI::on_setted_to_low),
								&cpu.IO));

			cpu.RW.setted_to_high.connect (
					sigc::bind (sigc::mem_fun (this, &UI::on_setted_to_high),
								&cpu.RW));
			cpu.RW.setted_to_low.connect (
					sigc::bind (sigc::mem_fun (this, &UI::on_setted_to_low),
								&cpu.RW));

			on_cpu_state_changed ();
		}
		;

		// handler per Cpu Changed

		void
		on_cpu_state_changed()
		{
			cout << "STATO " << cpu.stato << "    CLK =" << cpu.CLK.getValore ()
					<< endl;

			cout << vA.vedi () << "  ";
			cout << vPC.vedi () << "  ";
			cout << vIR.vedi () << "  ";
			cout << vDR.vedi () << "  ";
			cout << vMR.vedi () << endl;

		}

		// handler per PIn OUT
		void
		on_setted_to_low(PinOUT * p)
		{
		}
		void
		on_setted_to_high(PinOUT * p)
		{
		}
		;

	private:
		CPU & cpu;

		VistaReg vA = VistaReg (cpu.A);
		VistaReg vMR = VistaReg (cpu.MR);
		VistaReg vIR = VistaReg (cpu.IR);
		VistaReg vDR = VistaReg (cpu.DR);
		VistaReg vPC = VistaReg (cpu.PC);
};

#endif /* UI_H_ */
