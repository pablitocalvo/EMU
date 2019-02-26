/*
 * VistaReg.h
 *
 *  Created on: 25/feb/2019
 *      Author: paolo
 */

#ifndef VISTAREG_H_
#define VISTAREG_H_
#include "Vista.h"

class VistaReg : Vista
{public:


	VistaReg(  Registro & r ): reg(r)
	{ stato ='-';
	 //r.vista =  this;

	};

//	string vedi()
//	{
//		return ( reg.nome + " " + stato + " " + to_string( (int)reg.getValore()  ) );
//	};

private:
	Registro  & reg;
	char stato ; // r w -;


};
#endif /* VISTAREG_H_ */
