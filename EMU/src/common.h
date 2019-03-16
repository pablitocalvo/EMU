/*
 * Common.h
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <sigc++/sigc++.h>
#include <iostream>
#include <string>
using namespace std;

typedef enum Pin_3state_value
{
  PIN_LOW, PIN_Z, PIN_HIGH
};


typedef enum stati_cpu  {FETCH_T1_HIGH,FETCH_T1_LOW,
  FETCH_T2_HIGH,
  FETCH_T2_LOW,DECODE_T1_HIGH,
  DECODE_T1_LOW,EXECUTE_T1_HIGH,EXECUTE_T1_LOW

};


string
pin_state_to_string(Pin_3state_value stato)
{
  string appo;

  if (stato == PIN_LOW)
    appo = "0";
  else if (stato == PIN_HIGH)
    appo = "1";
  else if (stato == PIN_Z)
    appo = "Z";

  return appo;
}

#endif /* COMMON_H_ */
