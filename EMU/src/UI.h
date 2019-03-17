#ifndef UI_H_
#define UI_H_
#include "common.h"

#include "VistaRegistro.h"

#include <list>
#include <map>
#include "Vista.h"
#include "VistaPIN.h"
#include "VistaPIN3State.h"
#include "CPUcomponent.h"

using namespace std;

class UI
{
public:
  UI(CPU & c)
      : cpu (c), vA (VistaRegistro (c.A)), vPC (VistaRegistro (c.PC)), vDR (
          VistaRegistro (c.DR)), vIR (VistaRegistro (c.IR)), vAR (
          VistaRegistro (c.AR)),

      vCLK (VistaPIN (c.CLK)), vMREQ (VistaPIN3_State (c.MREQ)), vRD (
          VistaPIN3_State (c.RD))

  {

    vista_del_comp[&cpu.A] = &vA;
    vista_del_comp[&cpu.PC] = &vPC;
    vista_del_comp[&cpu.DR] = &vDR;
    vista_del_comp[&cpu.IR] = &vIR;
    vista_del_comp[&cpu.AR] = &vAR;

    vista_del_comp[&cpu.CLK] = &vCLK;
    vista_del_comp[&cpu.RD] = &vRD;
    vista_del_comp[&cpu.MREQ] = &vMREQ;

  }

  string
  to_string(stati_cpu s)
  {
    switch (s)
      {
      case FETCH_T1_HIGH:
        return "FETCH_T1_HIGH";
      case FETCH_T1_LOW:
        return "FETCH_T1_LOW";
      case FETCH_T2_HIGH:
        return "FETCH_T2_HIGH";
      case FETCH_T2_LOW:
        return "FETCH_T2_LOW";
      case DECODE_T1_HIGH:
        return "DECODE_T1_HIGH";
      case DECODE_T1_LOW:
        return "DECODE_T1_LOW";
      case EXECUTE_T1_HIGH:
        return "EXECUTE_T1_HIGH";
      case EXECUTE_T1_LOW:
        return "EXECUTE_T1_LOW";
      }
  }

  void
  visualizza()
  {  //cout<<pin_state_to_string (cpu.CLK.get_value())<<endl;;
    cout << "STATO " << to_string (cpu.stato) << "   " << vCLK.vedi ()
        << vMREQ.vedi () << vRD.vedi () << endl;

    cout << vA.vedi () << "  ";
    cout << vPC.vedi () << "  ";
    cout << vDR.vedi () << "  ";
    cout << vAR.vedi () << "  ";
    cout << vIR.vedi () << "  ";

    cout << endl << endl;

  }

public:
  Vista &
  vista_del_componente(CPU_component & comp)
  {
    Vista * v = vista_del_comp[&comp];
    return *v;
  }

public:
  CPU & cpu;
  VistaRegistro vA;
  VistaRegistro vPC;
  VistaRegistro vDR;
  VistaRegistro vIR;
  VistaRegistro vAR;

  VistaPIN vCLK;
  VistaPIN3_State vMREQ;
  VistaPIN3_State vRD;
private:

  list<CPU_component *> lista_componenti_attivi; //quali i rischi di un puntartore?
  std::map<CPU_component *, Vista *> vista_del_comp;

};

#endif /* UI_H_ */
