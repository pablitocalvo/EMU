/*
 * RAM.h
 *
 *  Created on: 17/mar/2019
 *      Author: paolo
 */

#ifndef RAM_H_
#define RAM_H_
#include "common.h"

class RAM: public EMU_component
{
public:
  RAM(string n):EMU_component(n){};
  virtual
  ~RAM(){};

private:

  char celle[256];

};

#endif /* RAM_H_ */
