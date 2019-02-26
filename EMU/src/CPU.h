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
		{	stato= "ON";

			CLK.rising.connect( sigc::bind( sigc::mem_fun(this, &CPU::onCLK_rising), &CLK ));
			CLK.falling.connect( sigc::bind( sigc::mem_fun(this, &CPU::onCLK_falling), &CLK ));

			//provvisoriamente  1 è l'opcode di inc A

			DR.setValore(1);
		}

		//string[]  CpuStati = { "F1", "F2", "F3", "D1", "D2" , "E1" };


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
			if (stato=="ON")
				setStato("F1");


			if (stato=="F1")
			{
				MR.MOV_from(PC);  // richiede un byte alla Ram

				IO.set_High();
				RW.set_High();
			}

			else if (stato=="F2")
			{
				//disabilita gli stati r/W dei componenti coinvolti prima...
					PC.set_stato('-');
					MR.set_stato('-');


				IR.MOV_from(DR);  // legge il byte dalla Ram



				IO.set_Low(); //low or none ??
				RW.set_Low();



			}
			else if (stato=="D1")
			{	//for now do nothiung ......
				// must we inform UI of decoding???

				char appo=PC.getValore(); // PC++
				appo++;
				PC.WRITE(appo);

			}
			else if (stato=="D2")
			{	//for now do nothiung ......
				// must we inform UI of decoding???


			}
			else if (stato=="E1")
			{	//for now do nothiung ......

				if (IR.getValore()==1)
				{    // inc A
					char appo=A.getValore();
					appo++;
					A.WRITE(appo);

				}
			}


		};

		void
		onCLK_falling( PinIN * clk)
		{
			if (stato=="F1")
			{
				setStato("F2");
			}
			else if (stato=="F2")
			{
				setStato("D1");
			}
			else if (stato=="D1")
			{
				setStato("D2");
			}
			else if (stato=="D2")
			{
				setStato("E1");
			}
			else if (stato=="E1")
			{
				setStato("E2");
			}
			else if (stato=="E2")
			{
				setStato("F1");
			}

		};



		string stato;
//signal

		sigc::signal<void> cpu_state_changed;
	private:



		void
		setStato( string s)
		{
			stato = s;
			cpu_state_changed.emit();


		}


};

#endif /* CPU_H_ */
