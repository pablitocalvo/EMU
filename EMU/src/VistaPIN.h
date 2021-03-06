/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN_H_
#define VISTAPIN_H_

#include "common.h"
#include "PIN.h"
#include "Vista.h"

class VistaPIN : public Vista
{
public:
  VistaPIN(PIN & p)
      : pin (p)
  {
    set_s_vista ();

    p.sig_pin_setted_to_HIGH.connect (
        sigc::mem_fun (this, &VistaPIN::set_s_vista));
    p.sig_pin_setted_to_LOW.connect (
        sigc::mem_fun (this, &VistaPIN::set_s_vista));

  }

  virtual
  ~VistaPIN()
  {
  }

  void
  virtual
  set_s_vista()
  {
    s_vista = pin.get_nome () + " " + pin_state_to_string (pin.get_value ());
    if (is_attiva ())
      s_vista = " [ " + s_vista + " ] ";
    else
      s_vista = "   " + s_vista + "   ";
  }

protected:
  PIN & pin;

};

#endif /* VISTAPIN_H_ */
