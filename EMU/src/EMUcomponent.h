/*
 * CPUcomponent.h
 *
 *  Created on: 08/mar/2019
 *      Author: paolo
 */

#ifndef EMUCOMPONENT_H_
#define EMUCOMPONENT_H_

#include "common.h"

class EMU_component
{
public:
  EMU_component(string n)
      : nome (n)
  {
  }
  ;
  virtual
  ~EMU_component()
  {
  }
  ;

protected:

  string nome;

public:
  string
  get_nome()
  {
    return nome;
  }

  virtual bool
  stato_uguale_a(EMU_component & c)
  {
    cout << "ERRORE !!!!!!!!" << endl;
    return true;
  }


};

#endif /* EMUCOMPONENT_H_ */
