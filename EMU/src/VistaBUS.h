/*
 * VistaBUS.h
 *
 *  Created on: 19/mar/2019
 *      Author: paolo
 */

#ifndef VISTABUS_H_
#define VISTABUS_H_

#include "VistaRegistro.h"
#include "BUS.h"
class VistaBUS : public VistaRegistro
{
public:
  VistaBUS(BUS bus):VistaRegistro(bus){};
  virtual
  ~VistaBUS();
};

#endif /* VISTABUS_H_ */
