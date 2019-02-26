/*
 * VistaReg.h
 *
 *  Created on: 25/feb/2019
 *      Author: paolo
 */

#ifndef VISTAREG_H_
#define VISTAREG_H_

#include <string>
#include "Registro.h"

class Vista
{

};
class VistaReg
{
	public:

		VistaReg(Registro & r)
				: reg (r)
		{
			label = "- " + to_string ((int) r.getValore ());

			reg.reg_state_changed.connect (
					sigc::mem_fun (this, &VistaReg::on_reg_state_changed));
			//reg.reg_state_changed.connect( sigc::bind<0> ( sigc::mem_fun(*this, &VistaReg::on_reg_state_changed ), reg ));

		}

		//void on_reg_state_changed(Registro & r, char c)
		void
		on_reg_state_changed(char c)
		{

			if (c == 'R')
				label = "- " + to_string ((int) reg.getValore ());
			else if (c == 'R')
				label = "R " + to_string ((int) reg.getValore ());
			else if (c == '-')
				label = "- " + to_string ((int) reg.getValore ());

		}

		string
		vedi()
		{
			return (reg.nome + " = " + label);
		}

	private:
		Registro & reg;

		string label ;
};
#endif /* VISTAREG_H_ */
