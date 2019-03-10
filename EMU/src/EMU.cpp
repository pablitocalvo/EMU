/*
 * EMU.cpp
 *
 *  Created on: 03/mar/2019
 *      Author: paolo
 */

//============================================================================
// Name        : EMU.cpp
// Author      : Paolo Sabatini
// Version     :
// Copyright   : GPL - 3.0
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>

using namespace std;

#include "CPU.h"
#include "UI.h"
#include "common.h"

CPU cpu = CPU ();
UI ui = UI (cpu);
string livello="IST";

list<CPU_component * > lista_componenti_attivi;  //quali i rischi di un puntartore?
void
salva_componente_attiva(CPU_component & c)
{
    Vista & v = ui.vista_del_componente(c);
    v.attiva();
    lista_componenti_attivi.push_back(&c);
}

void
on_cpu_step_done()
{
  char c;
  while (1)
  {
    cin >> c;
    if (c == 't')
      break;

  };

  if ((livello == "IST") and (cpu.stato != "EXECUTE-T1-LOW"))
    return;

  if ((livello == "FDE")
      and ((cpu.stato != "EXECUTE-T1-LOW") and (cpu.stato != "DECODE-T1-LOW")
          and (cpu.stato != "FETCH-T1-LOW")))
    return;
  cout << " cpu da EMU" << endl;
  ui.visualizza ();
}

void
on_cpu_step_start()
{
  //disattiva_le_viste_stato_precedente();
   while (! lista_componenti_attivi.empty() )
  {
//         //cout<<(viste_attive.back()->vedi());

     CPU_component * comp=lista_componenti_attivi.back();
     Vista & v = ui.vista_del_componente(*comp);
     cout << "distattivo" << v.vedi() << endl;
     v.disattiva();

        lista_componenti_attivi.pop_back ();
//
 }
     ;
}

void
on_cpu_will_mod_reg(Registro & reg)
{//TODO collauadare quando cpu ciclo è ben stabile livello FDE ..

  if (livello == "CLK")
  {
    salva_componente_attiva ( reg );

  }
  else if (livello == "FDE")
  {
    salva_componente_attiva ( reg) ;

  }
  else // (livello=="FDE
  { cout<<cpu.stato;
    if ((cpu.stato == "EXECUTE-T1-HIGH") or (cpu.stato == "EXECUTE-T2_LOW"))
    { cout<<"salvo attivo.."<<reg.get_nome();
      salva_componente_attiva (reg);
    }
  }

}

void
on_cpu_will_mod_pin(PIN & p)
{//TODO collauadare quando cpu ciclo è ben stabile livello FDE ..
  //TODO per MOV da memoria????..
if ((livello == "CLK") or (livello == "FDE"))
{
salva_componente_attiva (p);
}

}

int
main()
{

  //TODO : cercare di unificare ... cpu emette.. un solo segnale
  //un solo handler polimorfico??

 // cpu.cpu_will_mod_comp.connect (sigc::mem_fun (this, &UI::on_cpu_will_mod_comp));

  cpu.cpu_will_mod_reg.connect (&on_cpu_will_mod_reg);

  cpu.cpu_will_mod_pin.connect (&on_cpu_will_mod_pin);
  cpu.sig_step_done.connect (&on_cpu_step_done);
  cpu.sig_step_start.connect (&on_cpu_step_start);



  ui.visualizza();


  cpu.run ();

  return 0;
}

