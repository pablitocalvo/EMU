/*
 * Registro.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_
#include <sigc++/sigc++.h>
#include <string>
using namespace std;
#include "Vista.h"

class Registro
{
	public:
		Registro(string n)
		{
			valore = 0;
			nome=n;
			vista=NULL;
		};


		sigc::signal<void> reg_is_read;
		sigc::signal<void> reg_is_write;


		char
		getValore() const
		{
			return valore;
		}

		void
		setValore(char valore)
		{
			this->valore = valore;
		}

		void
		MOV_from(const Registro & r)
		{	r.reg_is_read.emit();
			valore=r.valore;
			this->reg_is_write.emit();
		}

		char
		READ()
		{	reg_is_read.emit();
			return valore;
		}

		void
		WRITE(char c)
		{	valore=c;
			reg_is_write.emit();
		}

		string nome;
		Vista * vista;

	private:
		char valore;
};

#endif /* REGISTRO_H_ */
