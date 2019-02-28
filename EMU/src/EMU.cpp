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

CPU cpu = CPU ();
UI ui = UI (cpu);

int
main()
{  // cout <<"hdfgdfd"<<endl;
    cpu.setStato("ON");
    char c;

    while (1)
    {
        cin >> c;
        if (c == 't')
            cpu.CLK.toggle ();
        if (c == 'x')
        { cout <<"ciaoooooooooooooooo"; exit (0);}

    }

    return 0;
}
