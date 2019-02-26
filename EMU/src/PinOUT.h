/*
 * PinOUT.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef PINOUT_H_
#define PINOUT_H_

#include <sigc++/sigc++.h>

class PinOUT
{
	public:
		PinOUT(string s)
				: nome (s)
		{
			valore = false;
		}

		sigc::signal<void> setted_to_low;
		sigc::signal<void> setted_to_high;

		void
		set_Low()
		{
			if (valore == true)
			{
				valore = false;
				setted_to_high.emit ();
			}
		}
		void
		set_High()
		{
			if (valore == false)
			{
				valore = true;
				setted_to_low.emit ();
			}
		}

		string
		get_nome()
		{
			return nome;
		}

		string nome;
		bool valore;
	private:

};

#endif /* PINOUT_H_ */
