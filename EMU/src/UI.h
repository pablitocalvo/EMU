#ifndef UI_H_
#define UI_H_
#include "common.h"

#include "VistaPin.h"
#include "VistaPin3State.h"
#include "VistaRegistro.h"

#include <list>

using namespace std;

class UI
{
public:
    UI(CPU & c)
            : cpu (c), vA (VistaRegistro (c.A)), vPC (VistaRegistro (c.PC)), vDR (
                    VistaRegistro (c.DR)), vIR (VistaRegistro (c.IR)), vAR (
                    VistaRegistro (c.AR)),

            vCLK (VistaPin (c.CLK)), vMREQ (VistaPin3_State (c.MREQ)), vRD (
                    VistaPin3_State (c.RD))

    {
        cpu.cpu_state_changed.connect (
                        sigc::mem_fun (this, &UI::on_cpu_state_changed));

        vA.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vA));

        vPC.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vPC));
        vDR.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vDR));
        vIR.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vIR));
        vAR.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vAR));
        vCLK.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vCLK));
        vMREQ.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vMREQ));
        vRD.vista_attivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_attivata ), vRD));

        vA.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vA));

        vPC.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vPC));
        vDR.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vDR));
        vIR.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vIR));
        vAR.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vAR));
        vCLK.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vCLK));
        vMREQ.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vMREQ));
        vRD.vista_disattivata.connect( sigc::bind<0> ( sigc::mem_fun (this, &UI::on_vista_disattivata ), vRD));

    }


    void
    on_vista_attivata(Vista & v, string s)
    {
        cout << "vista attivata ="<<s<<endl;
        viste_attive.push_back(&v) ;

    }

    void
    on_vista_disattivata(Vista & v, string s)
    {
        cout << "vista dis-attivata ="<<s<<endl;
    }

    void
    disattiva_le_viste_stato_precedente()
    {cout<<endl<<"disattiva le viste precedenti"<<endl;
        cout << "viste attive # "<<viste_attive.size()<< endl;
        cout << "viste attive vuota "<<viste_attive.empty()<< endl;

        while (!viste_attive.empty())
          {
            cout<<(viste_attive.back()->vedi());
            viste_attive.back()->disattiva();
            viste_attive.pop_back();

          }
        cout << "viste attive # "<<viste_attive.size()<< endl;
        cout << "viste attive vuota "<<viste_attive.empty()<< endl<< endl;


    }
    void
    on_cpu_state_changed()
    {
        disattiva_le_viste_stato_precedente();
        visualizza ();
    }
    void
    visualizza()
    {  //cout<<pin_state_to_string (cpu.CLK.get_value())<<endl;;
        cout << "STATO " << cpu.stato << "   " << vCLK.vedi () << vMREQ.vedi ()
                << vRD.vedi () << "   MREQ = "
                << pin_state_to_string (cpu.MREQ.get_value ()) << "   RD   = "
                << pin_state_to_string (cpu.RD.get_value ()) << endl;

        cout << vA.vedi () << "  ";
        cout << vPC.vedi () << "  ";
        cout << vDR.vedi () << "  ";
        cout << vAR.vedi () << "  ";
        cout << vIR.vedi () << "  ";

        cout << endl;
        cout << "A  = " << ((int) cpu.A.get_valore ()) << "  ";
        cout << "PC = " << ((int) cpu.PC.get_valore ()) << "  ";
        cout << "DR = " << ((int) cpu.DR.get_valore ()) << "  ";
        cout << "AR = " << ((int) cpu.AR.get_valore ()) << "  ";
        cout << "IR = " << ((int) cpu.IR.get_valore ()) << "  " << endl << endl;
        cout << "istr = " << cpu.mnemo << endl << endl;

    }

public:
    CPU & cpu;
    VistaRegistro vA;
    VistaRegistro vPC;
    VistaRegistro vDR;
    VistaRegistro vIR;
    VistaRegistro vAR;

    VistaPin vCLK;
    VistaPin3_State vMREQ;
    VistaPin3_State vRD;
private:

     list<Vista *> viste_attive;  //quali i rischi di un puntartore?

};

#endif /* UI_H_ */
