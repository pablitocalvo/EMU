/*
 * CPU.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef CPU_H_
#define CPU_H_


#include "Registro.h"
#include <sigc++/sigc++.h>
#include <iostream>


#include "PinIN.h"
#include "PinOUT.h"
using namespace std;


class CPU
{
	public:
		CPU()
		{	stato= F1;

			CLK.rising.connect( sigc::bind( sigc::mem_fun(this, &CPU::onCLK_rising), &CLK ));
			CLK.falling.connect( sigc::bind( sigc::mem_fun(this, &CPU::onCLK_falling), &CLK ));

			//provvisoriamente  1 è l'opcode di inc A

			DR.setValore(1);
		}

		enum CpuStati { F1, F2, F3, D1, D2 , E1 };


		Registro A  = Registro("A");
		Registro B  = Registro("B");
		Registro PC = Registro("PC");
		Registro DR = Registro("DR");
		Registro MR = Registro("MR");
		Registro IR = Registro("IR");
		Registro AR = Registro("AR");

		PinIN CLK= PinIN();

		PinOUT RW = PinOUT("RW");
		PinOUT IO = PinOUT("IO");



		void
		onCLK_rising( PinIN * clk )
		{
			if (stato==F1)
			{
				MR.MOV_from(PC);
				IO.set_High();
				RW.set_High();

				setStato(F2);

			}
			else if (stato==F2)
			{
				IR.MOV_from(DR);
				char appo=PC.getValore();
				appo++;
				PC.WRITE(appo);

				setStato(D1);

			}
			else if (stato==D1)
			{
				if (IR.getValore()==1)
				{    // inc A
					char appo=A.getValore();
					appo++;
					A.WRITE(appo);
					setStato(F1);
				}
			}


		};

		void
		onCLK_falling( PinIN * clk)
		{

		};




	private:

		CpuStati stato;

		void
		setStato( CpuStati s)
		{
			stato = s;


		}


};

#endif /* CPU_H_ */
