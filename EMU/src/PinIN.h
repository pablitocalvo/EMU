/*
 * PinIn.h
 *
 *  Created on: 24/feb/2019
 *      Author: paolo
 */

#ifndef PININ_H_
#define PININ_H_

#include <sigc++/sigc++.h>

class PinIN
{
	public:
		PinIN()
		{
			valore = false;
		}

		sigc::signal<void> rising;
		sigc::signal<void> falling;

		void
		toggle()
		{
			if (valore == false)
			{
				valore = true;
				rising.emit ();
			}
			else
			{
				valore = false;
				falling.emit ();
			}
		}

		bool
		getValore() const
		{
			return valore;
		}

		void
		setValore(bool valore)
		{
			this->valore = valore;
		}

	private:
		bool valore;
};

#endif /* PININ_H_ */
