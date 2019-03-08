/*
 * VistaRegistro.h
 *
 *  Created on: 06/mar/2019
 *      Author: paolo
 */

#ifndef VISTAREGISTRO_H_
#define VISTAREGISTRO_H_

#include "common.h"
#include "Registro.h"
#include "Vista.h"

class VistaRegistro : public Vista
{
public:
  VistaRegistro(Registro & r)
      : reg (r)
  {
    set_s_vista ();
  }

  ~VistaRegistro()
  {
  }
  ;

  void
  set_s_vista()
  { //cout<< "set_s_vista.."+pin.get_nome () + pin_state_to_string (pin.get_value ())<<endl;

    string s_stato = reg.is_reading () ? "r " : reg.is_writing () ? "w " : "- ";

    s_vista = s_stato + reg.get_nome () + " = "
        + to_string ((int) reg.get_valore ());

    if (is_attiva ())
      s_vista = " [ " + s_vista + " ] ";
    else
      s_vista = "   " + s_vista + "   ";
  }

private:
  Registro & reg;

};

#endif /* VISTAREGISTRO_H_ */
