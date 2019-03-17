/*
 * PIN3state.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef PIN3STATE_H_
#define PIN3STATE_H_
#include "common.h"

class PIN_3state : public PIN
{
public:
  PIN_3state(string n)
      : PIN (n)
  {
    disable ();
  }

  virtual
  ~PIN_3state()
  {
  }

  sigc::signal<void> sig_pin_enabled;
  sigc::signal<void> sig_pin_disabled;

private:
  Pin_3state_value en, output;

public:

  void
  enable()
  {
    en = PIN_HIGH;
    output = valore;

  }
  void
  disable()
  {
    en = PIN_LOW;
    output = PIN_Z;

  }

  bool is_disabled(){ return ( en == PIN_LOW) ;)
  Pin_3state_value
  get_value()
  {
    return ((en == PIN_HIGH) ? valore : PIN_Z);

  }

  bool
  stato_uguale_a(EMU_component &c)
  {
    return stato_uguale_a ((PIN_3state &) c);
  }

  bool
  stato_uguale_a(PIN_3state & p)
  {
    return ((valore == p.valore) && (en == p.en));
  }

};

#endif /* PIN3STATE_H_ */
