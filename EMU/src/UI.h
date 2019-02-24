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

class UI
{
	public:
		UI(CPU & c) : cpu(c)
		{
			cpu.A.reg_is_read.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_read ), &cpu.A ));
			cpu.A.reg_is_write.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_write ), &cpu.A ));

			cpu.MR.reg_is_read.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_read ), &cpu.MR ));
			cpu.MR.reg_is_write.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_write ), &cpu.MR ));

			cpu.IR.reg_is_read.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_read ), &cpu.IR ));
			cpu.IR.reg_is_write.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_write ), &cpu.IR ));

			cpu.DR.reg_is_read.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_read ), &cpu.DR ));
			cpu.DR.reg_is_write.connect( sigc::bind( sigc::mem_fun(this, &UI::on_reg_is_write ), &cpu.DR ));



			cpu.IO.setted_to_high.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_high ), &cpu.IO));
			cpu.IO.setted_to_low.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_low ), &cpu.IO));

			cpu.RW.setted_to_high.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_high ), &cpu.RW));
			cpu.RW.setted_to_low.connect(sigc::bind( sigc::mem_fun(this, &UI::on_setted_to_low ), &cpu.RW));

		};

		virtual
		~UI();

	// handler per Registri

	void on_reg_is_read(Registro * R)
	{
		cout<<"reg "<< R->nome <<" read"<< R->getValore() <<endl;

	};
	void on_reg_is_write(Registro * R)
	{
			cout<<"reg "<< R->nome <<" Write "<<R->getValore()<<endl;
	};

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

};

#endif /* UI_H_ */
