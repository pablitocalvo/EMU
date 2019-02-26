//============================================================================
// Name        : EMU.cpp
// Author      : Paolo Sabatini
// Version     :
// Copyright   : GPL - 3.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "CPU.h"
#include "UI.h"


#include <sigc++/sigc++.h>
#include <iostream>
#include <string>
#include "PinIN.h"


CPU cpu = CPU();
UI ui = UI(cpu);

void
m_onCLK_rising(PinIN *clk)
{
	cout << " CLK Rising val=" << clk->getValore () << endl;

}
;

void
m_onCLK_falling(PinIN * clk)
{
	cout << " CLK Falling val=" << clk->getValore () << endl;
}
;



int main()  {


//	cpu.CLK.rising.connect( sigc::bind( sigc::ptr_fun( m_onCLK_rising), &cpu.CLK ));
//	cpu.CLK.falling.connect( sigc::bind( sigc::ptr_fun( m_onCLK_falling),  &cpu.CLK ));

//

//	std::thread first (mezzo_clock);




	char c;

	while (1)
	{
		cin >> c;
		cout << c << endl;
		if (c=='t') cpu.CLK.toggle();
		if (c=='x') exit (0);

	}


	return 0;
}
