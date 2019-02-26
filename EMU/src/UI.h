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
using namespace std;
#include <sigc++/sigc++.h>
#include <map>
#include "VistaReg.h"


class UI
{
	public:
		UI(CPU & c) : cpu(c)
		{


			cpu.IO.setted_to_high.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_high ), &cpu.IO));
			cpu.IO.setted_to_low.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_low ), &cpu.IO));

			cpu.RW.setted_to_high.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_high ), &cpu.RW));
			cpu.RW.setted_to_low.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_low ), &cpu.RW));
		};



	// handler per Registri



	// handler per PIn OUT
	void on_setted_to_low(PinOUT * p)
	{
		cout<<"Pin "<< p->nome <<" to Low"<< p->valore <<endl;
	}
	void on_setted_to_high(PinOUT * p)
	{
		cout<<"Pin "<< p->nome <<" to High"<< p->valore <<endl;
	};

	private:
		CPU & cpu;

		VistaReg vA = VistaReg( cpu.A );
		VistaReg vMR= VistaReg( cpu.MR);
		VistaReg vIR= VistaReg( cpu.IR);
		VistaReg vDR= VistaReg( cpu.DR);
		VistaReg vPC= VistaReg( cpu.PC);

	//	map<*Registro,*VistaReg> vista_di ;

};

#endif /* UI_H_ */
