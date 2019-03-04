#ifndef UI_H_
#define UI_H_
#include "common.h"

#include "VistaPin.h"


class UI
{



public:
    UI(CPU & c)
            : cpu (c), vCLK(VistaPin( c.CLK ) )
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
             << "   MREQ = " << pin_state_to_string(cpu.MREQ.get_value())
             << "   RD   = " << pin_state_to_string(cpu.RD.get_value())
        << endl;

        cout << "A  = "<<((int) cpu.A.get_valore()) << "  ";
        cout << "B  = "<<((int) cpu.B.get_valore()) << "  ";
        cout << "PC = "<<((int) cpu.PC.get_valore()) << "  ";
        cout << "DR = "<<((int) cpu.DR.get_valore()) << "  ";
        cout << "AR = "<<((int) cpu.AR.get_valore()) << "  ";
        cout << "IR = "<<((int) cpu.IR.get_valore()) << "  " << endl<< endl;
        cout << "istr = "<<cpu.mnemo<< endl<< endl;


    }


public:
    CPU & cpu;

    VistaPin vCLK ;

};

#endif /* UI_H_ */
