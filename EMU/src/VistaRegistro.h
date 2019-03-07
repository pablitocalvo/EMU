/*
 * VistaRegistro.h
 *
 *  Created on: 06/mar/2019
 *      Author: paolo
 */

#ifndef VISTAREGISTRO_H_
#define VISTAREGISTRO_H_

#include "common.h"
#include "Registro.h"
#include "Vista.h"

class VistaRegistro : public Vista
{
public:
    VistaRegistro(Registro & r): reg(r)
    {
            set_s_vista ();

            reg.reg_state_writing.connect(sigc::bind<0> ( sigc::mem_fun (this, &VistaRegistro::on_reg_state_writing), r) );
            reg.reg_state_reading.connect(sigc::bind<0> ( sigc::mem_fun (this, &VistaRegistro::on_reg_state_reading), r) );
            reg.reg_state_standby.connect(sigc::bind<0> ( sigc::mem_fun (this, &VistaRegistro::on_reg_state_standby), r) );


            reg.reg_writed.connect(sigc::bind<0> ( sigc::mem_fun (this, &VistaRegistro::on_reg_writed), r) );
            reg.reg_read.connect(sigc::bind<0> ( sigc::mem_fun (this, &VistaRegistro::on_reg_read), r) );

 }

    ~VistaRegistro()
    {};

    void
    set_s_vista()
    {   //cout<< "set_s_vista.."+pin.get_nome () + pin_state_to_string (pin.get_value ())<<endl;

        string  s_stato = reg.is_reading() ? "r " : reg.is_writing() ? "w " : "- ";

        s_vista = s_stato+ reg.get_nome () +" = "+ to_string ((int)reg.get_valore ());

        if (is_attiva ())
            s_vista =" [ " + s_vista + " ] ";
        else
            s_vista ="   " + s_vista + "   ";
    }

private:
    Registro & reg;

    void on_reg_state_writing(Registro &)
    {attiva();}
    void on_reg_state_reading(Registro &)
    {attiva();}
    void on_reg_state_standby(Registro &)
    {attiva();}
    void on_reg_writed(Registro &)
    {attiva();}
    void on_reg_read(Registro &)
    {attiva();}



};

#endif /* VISTAREGISTRO_H_ */
