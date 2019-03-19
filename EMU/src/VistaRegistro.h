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
    r.sig_setted_to_reading.connect (
        sigc::mem_fun (this, &VistaRegistro::set_s_vista));
    r.sig_setted_to_writing.connect (
        sigc::mem_fun (this, &VistaRegistro::set_s_vista));
    r.sig_setted_to_standby.connect (
        sigc::mem_fun (this, &VistaRegistro::set_s_vista));

    r.sig_was_READ.connect (
        sigc::mem_fun (this, &VistaRegistro::on_reg_WRITE));
    r.sig_was_WRITE.connect (
        sigc::mem_fun (this, &VistaRegistro::on_reg_READ));
  }

  ~VistaRegistro()
  {
  }

  void
  prova()
  {
  }
  ;

  void
  set_s_vista()
  {
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

  void
  on_reg_set_reading()
  {
    set_s_vista ();
  }
  void
  on_reg_set_writing()
  {
    set_s_vista ();
  }
  void
  on_reg_set_standby()
  {
    set_s_vista ();
  }

  void
  on_reg_WRITE()
  {
    set_s_vista ();
  }
  void
  on_reg_READ()
  {
    set_s_vista ();
  }

};

#endif /* VISTAREGISTRO_H_ */
