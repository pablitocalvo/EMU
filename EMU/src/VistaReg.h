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
#include "PIN.h"

class VistaReg
{
	public:

		VistaReg(Registro & r)
				: reg (r)
		{
			label = "- " + to_string ((int) r.getValore ());

			//reg.reg_state_changed.connect (sigc::mem_fun (this, &VistaReg::on_reg_state_changed));
			reg.reg_state_changed.connect( sigc::bind<0> ( sigc::mem_fun(*this, &VistaReg::on_reg_state_changed ), &reg ));

		}

		void on_reg_state_changed(Registro * r, char c)
		//void
		//on_reg_state_changed(char c)
		{
			//cout<<"orhhdfgd"<<endl;
			if (c == '-')
				label = "- " + to_string ((int) r->getValore ());
			else if (c == 'W')
				label = "W " + to_string ((int) r->getValore ());
			else if (c == 'R')
				label = "R " + to_string ((int) r->getValore ());

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


class VistaPin
{
public:
    VistaPin( PIN & p ) :  pin(p)
    {
        label = "- " + to_string ((int) p.get_valore() );
    }
private:
       PIN & pin ;

       string label ;

};

#endif /* VISTAREG_H_ */
