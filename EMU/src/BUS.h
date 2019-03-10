/*
 * BUS.h
 *
 *  Created on: 10/mar/2019
 *      Author: paolo
 */

#ifndef BUS_H_
#define BUS_H_
#include "common.h"

class BUS : public
{
public:
  BUS(string n):nome(n){};
  virtual
  ~BUS();
private:
  string nome;
};

#endif /* BUS_H_ */
