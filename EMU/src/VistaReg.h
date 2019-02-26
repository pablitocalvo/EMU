/*
 * VistaReg.h
 *
 *  Created on: 25/feb/2019
 *      Author: paolo
 */

#ifndef VISTAREG_H_
#define VISTAREG_H_

#include "Registro.h"


#include <string>
using namespace std;
class Vista
{

};
class VistaReg : Vista
{public:

	VistaReg(  Registro & r ): reg(r)
	{
		//stato ='-';
	reg.reg_is_read.connect( sigc::bind( sigc::mem_fun(this, &VistaReg::on_reg_is_read ), &reg ));
	reg.reg_is_write.connect( sigc::bind( sigc::mem_fun(this, &VistaReg::on_reg_is_write ), &reg ));

	};

	void on_reg_is_read(Registro * R)
	{
		//stato='R';
		cout<<vedi()<<endl;


	};

	void on_reg_is_write(Registro * R)
	{	//stato='W';
		cout<<vedi()<<endl;
	};


	string vedi()
	{
		return ( reg.nome + " = " + to_string( (int) reg.getValore()) + reg.stato);
	}

private:
	Registro  & reg;
	//char stato ; // r w -;

};
#endif /* VISTAREG_H_ */
