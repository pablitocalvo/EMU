/*
 * PIN.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef PIN_H_
#define PIN_H_
#include "common.h"
#include "CPUcomponent.h"
class PIN : public CPU_component
{
public:
  PIN(string n)
      : CPU_component (n), valore (PIN_LOW)
  {
  }

  virtual
  ~PIN()
  {
  }

  sigc::signal<void> sig_pin_setted_to_LOW;
  sigc::signal<void> sig_pin_setted_to_HIGH;
  sigc::signal<void> sig_pin_toggled;

protected:
  Pin_3state_value valore;

public:
  bool
  is_high()
  {
    return valore == PIN_HIGH;
  }

  virtual void
  set_high()
  {
    valore = PIN_HIGH;
  }
  virtual void
  set_low()
  {
    valore = PIN_LOW;
  }
  virtual void
  toggle()
  {
    if (valore == PIN_HIGH)
    {
      valore = PIN_LOW;
    }
    else
    {
      valore = PIN_HIGH;
    }
    sig_pin_toggled ();
  }

  virtual Pin_3state_value
  get_value()
  {
    return (valore);
  }

  virtual bool
  stato_uguale_a(CPU_component &c)
  {
    return stato_uguale_a ((PIN &) c);
  }

  bool
  stato_uguale_a(PIN & p)
  {
    return ((valore == p.valore));
  }

};

#endif /* PIN_H_ */
