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
            : cpu (c),
              vA   ( VistaRegistro   (c.A   ) ),
              vPC  ( VistaRegistro   (c.PC  ) ),
              vDR  ( VistaRegistro   (c.DR  ) ),
              vIR  ( VistaRegistro   (c.IR  ) ),
              vAR  ( VistaRegistro   (c.AR  ) ),

              vCLK ( VistaPin        (c.CLK ) ) ,
              vMREQ( VistaPin3_State (c.MREQ) ) ,
              vRD  ( VistaPin3_State (c.RD  ) )


    {
        cpu.cpu_state_changed.connect (
            sigc::mem_fun (this, &UI::on_cpu_state_changed));
    }

    void on_cpu_state_changed(){ visualizza();}
    void
    visualizza()
    {  //cout<<pin_state_to_string (cpu.CLK.get_value())<<endl;;
        cout << "STATO " << cpu.stato<<"   "
             << vCLK.vedi()
             << vMREQ.vedi()
             << vRD.vedi()
             << "   MREQ = " <<  pin_state_to_string(cpu.MREQ.get_value())
             << "   RD   = " << pin_state_to_string(cpu.RD.get_value())
        << endl;

        cout << vA.vedi()   << "  ";
        cout << vPC.vedi()   << "  ";
        cout << vDR.vedi()   << "  ";
        cout << vAR.vedi()   << "  ";
        cout << vIR.vedi()   << "  ";

        cout << endl;
                cout << "A  = "<<((int) cpu.A.get_valore()) << "  ";
                cout << "PC = "<<((int) cpu.PC.get_valore()) << "  ";
        cout << "DR = "<<((int) cpu.DR.get_valore()) << "  ";
        cout << "AR = "<<((int) cpu.AR.get_valore()) << "  ";
        cout << "IR = "<<((int) cpu.IR.get_valore()) << "  " << endl<< endl;
        cout << "istr = "<<cpu.mnemo<< endl<< endl;


    }


public:
    CPU & cpu;
    VistaRegistro vA;
    VistaRegistro vPC;
    VistaRegistro vDR;
    VistaRegistro vIR;
    VistaRegistro vAR;

    VistaPin vCLK ;
    VistaPin3_State vMREQ ;
    VistaPin3_State vRD ;
private:

   // list<Vista & > viste_attive ={};

};

#endif /* UI_H_ */
