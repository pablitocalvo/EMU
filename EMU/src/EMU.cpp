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
string livello="CLK";

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
  //cout<<"on_on_cpu_step_done() ";
//cout <<endl<<"          livello= "<<livello<<endl;
//cout <<endl<<"          stato ="<<cpu.stato<<"## "<<endl;

  //if(livello != "IST") cout <<endl<<"         xxxxxxxxxxxxxxxxxxxxxxxx"<<cpu.stato<<endl;

  if (livello == "CLK")
  {
    //cout <<endl<<"         CCCCCCCCCCCCoppooooooooooooooCCCC"<<cpu.stato<<endl;
      ui.visualizza ();return;
  }

  if((livello == "IST")&&(cpu.stato == EXECUTE_T1_LOW))
  {
    //cout <<endl<<"         ciaoooooooooooooooooo"<<cpu.stato<<endl;
  ui.visualizza ();return;
  }

  if ((livello == "FDE") and (cpu.stato == EXECUTE_T1_LOW))
  {
    //cout <<endl<<"         ciaoooooooooooooooooo"<<cpu.stato<<endl;
        ui.visualizza ();return;
    }

  if ((livello == "FDE")  and (cpu.stato == DECODE_T1_LOW))
  {
    //cout <<endl<<"         ciaoooooooooooooooooo"<<cpu.stato<<endl;
           ui.visualizza ();return;
       }


  if ((livello == "FDE")  and (cpu.stato == FETCH_T1_LOW))
    {
    //cout <<endl<<"         ciaoooooooooooooooooo"<<cpu.stato<<endl;
             ui.visualizza ();return;
         }

}

void
on_cpu_step_start()
{
//  cout << "on_cpu_step_start()" << endl;
//  cout <<endl<<"          livello= "<<livello<<endl;
//  cout <<endl<<"          stato ="<<cpu.stato<<"## "<<endl;
// //non sempre finito uno step devo disattivare le viste..
  //
  if ((livello == "IST") and (cpu.stato != FETCH_T1_HIGH))
  {
//      cout <<endl<<"on_cpu_step_start() ----------1111111 "<<cpu.stato<<endl;
        ;return;
    }

  if ((livello == "FDE")
        and ((cpu.stato != EXECUTE_T1_LOW) and (cpu.stato != DECODE_T1_LOW)
            and (cpu.stato != FETCH_T2_LOW)))
  {
//        cout <<endl<<"on_cpu_step_start() ----------222222222 "<<cpu.stato<<endl;
          ;return;
   }


//  cout <<endl<<"on_cpu_step_start() ----------33333333333 "<<cpu.stato<<endl;
          ;


//disattiva_le_viste_stato_precedente();
   while (! lista_componenti_attivi.empty() )
  {
//         //cout<<(viste_attive.back()->vedi());

     CPU_component * comp=lista_componenti_attivi.back();
     Vista & v = ui.vista_del_componente(*comp);
//     cout << "distattivo" << v.vedi() << endl;
     v.disattiva();

        lista_componenti_attivi.pop_back ();
//
 }
     ;
}

void
on_cpu_will_mod_reg(Registro & reg)
{//TODO collauadare quando cpu ciclo è ben stabile livello FDE ..

//  cout<<"on_cpu_will_mod_reg() ";
//  cout <<endl<<"          livello= "<<livello<<endl;
//  cout <<endl<<"          stato ="<<cpu.stato<<"## "<<endl;

  if (livello == "CLK")
  {
//    cout<<"salvo attivo.1."<<reg.get_nome()<<endl;
    salva_componente_attiva ( reg );

  }
  else if (livello == "FDE")
  {
//    cout<<"salvo attivo.2."<<reg.get_nome()<<endl;
    salva_componente_attiva ( reg) ;

  }
  else // (livello=="IST)
  {
//    cout<<cpu.stato<<endl;
    if ((cpu.stato == EXECUTE_T1_HIGH) or (cpu.stato == EXECUTE_T1_LOW))
    {
//      cout<<"salvo attivo.3."<<reg.get_nome()<<endl;
      salva_componente_attiva (reg);
    }
  }
  cout <<endl;
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


void on_clk_toggle()
{

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

  cpu.setStato(FETCH_T1_HIGH);
  ui.visualizza();

  char c;
    while (1)
    {
      cin >> c;
      if (c == 't')
        cpu.CLK.toggle();
      if (c == 'x')
        break;
    };



 // cpu.run ();

  return 0;
}

