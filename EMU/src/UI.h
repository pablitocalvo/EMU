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
    cpu.cpu_state_changed.connect (
        sigc::mem_fun (this, &UI::on_cpu_state_changed));

    cpu.cpu_comp_will_mod.connect (sigc::mem_fun (this, &UI::on_cpu_comp_will_mod));



    cpu.cpu_step_dones.connect (sigc::mem_fun (this, &UI::on_cpu_step_done));

    cpu.cpu_step_starts.connect (sigc::mem_fun (this, &UI::on_cpu_step_start));

    cpu.cpu_reg_set_reading.connect (sigc::mem_fun (this, &UI::on_cpu_reg_mod));
    cpu.cpu_reg_set_writing.connect (sigc::mem_fun (this, &UI::on_cpu_reg_mod));
    cpu.cpu_reg_set_standby.connect (sigc::mem_fun (this, &UI::on_cpu_reg_mod));

    cpu.cpu_reg_WRITE.connect (sigc::mem_fun (this, &UI::on_cpu_reg_mod));
    cpu.cpu_reg_READ.connect (sigc::mem_fun (this, &UI::on_cpu_reg_mod));

//
    cpu.cpu_pin_writed_to_LOW.connect (
        sigc::mem_fun (this, &UI::on_cpu_pin_mod));
    cpu.cpu_pin_writed_to_HIGH.connect (
        sigc::mem_fun (this, &UI::on_cpu_pin_mod));

    cpu.cpu_pin_enabled.connect (sigc::mem_fun (this, &UI::on_cpu_pin_mod));
    cpu.cpu_pin_disabled.connect (sigc::mem_fun (this, &UI::on_cpu_pin_mod));

    vista_del_reg[&cpu.A] = &vA;
    vista_del_reg[&cpu.PC] = &vPC;
    vista_del_reg[&cpu.DR] = &vDR;
    vista_del_reg[&cpu.IR] = &vIR;
    vista_del_reg[&cpu.AR] = &vAR;

    vista_del_pin[&cpu.CLK] = &vCLK;
    vista_del_pin[&cpu.RD] = &vRD;
    vista_del_pin[&cpu.MREQ] = &vMREQ;

    vista_del_comp[&cpu.A] = &vA;
    vista_del_comp[&cpu.PC] = &vPC;
    vista_del_comp[&cpu.DR] = &vDR;
    vista_del_comp[&cpu.IR] = &vIR;
    vista_del_comp[&cpu.AR] = &vAR;

    vista_del_comp[&cpu.CLK] = &vCLK;
    vista_del_comp[&cpu.RD] = &vRD;
    vista_del_comp[&cpu.MREQ] = &vMREQ;

  }

  void
  on_cpu_comp_will_mod(CPU_component & c)
  {

    componenti_attivi.push_back ({ & c, c });

  }

  void
  on_cpu_step_done()
  {
    while (!componenti_attivi.empty ())
    {


      Comp_Stato c=componenti_attivi.back();
      componenti_attivi.pop_back ();

      if ( ! c.c->stato_uguale_a(c.s)  )
      {
          //CPU_component * cp= c.c;
          Vista * v=vista_del_comp[c.c];
          v->attiva();
          viste_attive.push_back (v);

      }

    }
    visualizza ();
  }

  void
  on_cpu_step_start()
  {
    disattiva_le_viste_stato_precedente();
  }

  void
  on_cpu_pin_mod(PIN & pin)
  {
//    VistaPIN * v = vista_del_pin[&pin];
//    v->set_s_vista();
//
//    //cout << "vista attivata ="<<v->vedi()<<endl;
//    viste_attive.push_back (v);

  }

  void
  on_cpu_reg_mod(Registro & reg)
  {
//    VistaRegistro * v = vista_del_reg[&reg];
//    v->set_s_vista();
//
//    // cout << "vista attivata ="<<v->vedi()<<endl;
//    viste_attive.push_back (v);

  }

  void
  disattiva_le_viste_stato_precedente()
  {
    // cout<<endl<<"disattiva le viste precedenti"<<endl;
//        cout << "viste attive # "<<viste_attive.size()<< endl;
//        cout << "viste attive vuota "<<viste_attive.empty()<< endl;

    while (!viste_attive.empty ())
    {
      //cout<<(viste_attive.back()->vedi());
      viste_attive.back ()->disattiva ();
      viste_attive.pop_back ();

    }
//        cout << "viste attive # "<<viste_attive.size()<< endl;
//        cout << "viste attive vuota "<<viste_attive.empty()<< endl<< endl;

  }
  void
  on_cpu_state_changed()
  {
//    disattiva_le_viste_stato_precedente ();
//    visualizza ();
//
    }
  void
  visualizza()
  {  //cout<<pin_state_to_string (cpu.CLK.get_value())<<endl;;
    cout << "STATO " << cpu.stato << "   " << vCLK.vedi () << vMREQ.vedi ()
        << vRD.vedi ()
        << endl;

    cout << vA.vedi () << "  ";
    cout << vPC.vedi () << "  ";
    cout << vDR.vedi () << "  ";
    cout << vAR.vedi () << "  ";
    cout << vIR.vedi () << "  ";

    cout << endl;

//        cout << "A  = " << ((int) cpu.A.get_valore ()) << "  ";
//        cout << "PC = " << ((int) cpu.PC.get_valore ()) << "  ";
//        cout << "DR = " << ((int) cpu.DR.get_valore ()) << "  ";
//        cout << "AR = " << ((int) cpu.AR.get_valore ()) << "  ";
//        cout << "IR = " << ((int) cpu.IR.get_valore ()) << "  " << endl << endl;
//        cout << "istr = " << cpu.mnemo << endl << endl;

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

  struct Comp_Stato
  {
    CPU_component * c;
    CPU_component s;
  };

  list<Vista *> viste_attive;  //quali i rischi di un puntartore?
  list<Comp_Stato> componenti_attivi;  //quali i rischi di un puntartore?

  std::map<CPU_component *, Vista *> vista_del_comp;

  std::map<Registro *, VistaRegistro *> vista_del_reg;
  std::map<PIN *, VistaPIN *> vista_del_pin;

};

#endif /* UI_H_ */
