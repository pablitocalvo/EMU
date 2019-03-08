/*
 * CPUcomponent.h
 *
 *  Created on: 08/mar/2019
 *      Author: paolo
 */

#ifndef CPUCOMPONENT_H_
#define CPUCOMPONENT_H_

#include "common.h"

class CPU_component
{
public:
  CPU_component(string n)
      : nome (n)
  {
  }
  ;
  virtual
  ~CPU_component()
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
  stato_uguale_a(CPU_component & c){cout<<"ERRORE !!!!!!!!"<<endl; return true;};

};

#endif /* CPUCOMPONENT_H_ */
