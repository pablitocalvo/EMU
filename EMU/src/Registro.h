/*
 * Registro.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "common.h"
#include "EMUcomponent.h"

typedef enum Stato_registro
{
  READING, STANDBY, WRITING
};

class Registro : public EMU_component
{
public:
  Registro(string n)
      : EMU_component (n), valore (0), stato (STANDBY)
  {
  }
  ;
  virtual
  ~Registro()
  {
  }
  sigc::signal<void> sig_reg_setted_to_reading;
  sigc::signal<void> sig_reg_setted_to_writing;
  sigc::signal<void> sig_reg_setted_to_standby;
  sigc::signal<void> sig_reg_was_WRITE;
  sigc::signal<void> sig_reg_was_READ;

  bool
  is_reading()
  {
    return (stato == READING);
  }

  bool
  is_writing()
  {
    return (stato == WRITING);
  }

  bool
  is_standby()
  {
    return (stato == STANDBY);
  }

  void
  set_valore(char c)
  {
    valore = c;
  }
  char
  get_valore()
  {
    return valore;
  }

  void
  set_reading()
  {
    stato = READING;
  }

  void
  set_writing()
  {
    stato = WRITING;
  }

  void
  set_standby()
  {
    stato = STANDBY;
  }

  bool
  stato_uguale_a(EMU_component &c)
  {
    return stato_uguale_a ((Registro &) c);
  }

  bool
  stato_uguale_a(Registro & r)
  {
    return ((valore == r.valore) && (stato == r.stato));
  }

private:

  char valore;
  Stato_registro stato;

public:
};

#endif /* REGISTRO_H_ */
