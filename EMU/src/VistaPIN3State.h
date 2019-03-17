/*
 * VistaPin.h
 *
 *  Created on: 04/mar/2019
 *      Author: paolo
 */

#ifndef VISTAPIN3STATE_H_
#define VISTAPIN3STATE_H_

#include "common.h"
#include "PIN3state.h"
#include "Vista.h"

class VistaPIN3_State : public VistaPIN
{
public:
  VistaPIN3_State(PIN_3state & p)
      : VistaPIN (p)
  {
    p.sig_pin_enabled.connect (
        sigc::mem_fun (this, &VistaPIN3_State::set_s_vista));
    p.sig_pin_disabled.connect (
        sigc::mem_fun (this, &VistaPIN3_State::set_s_vista));
    ;
  }
  ;
  virtual
  ~VistaPIN3_State()
  {
  }

  void
  set_s_vista() //TODO inserire enable
  {
    s_vista = pin.get_nome () + " " + pin_state_to_string (pin.get_value ());
    if (is_attiva ())
      s_vista = " [ " + s_vista + " ] ";
    else
      s_vista = "   " + s_vista + "   ";
  }

};

#endif /* VISTAPIN_H_ */
