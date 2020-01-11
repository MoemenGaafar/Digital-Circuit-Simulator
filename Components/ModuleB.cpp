#include "ModuleB.h"

ModuleB::ModuleB(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 5, r_FanOut)
{
	ComponentType = T_ModuleB;
}


// Function Draw
void ModuleB::Draw(UI* pUI)
{
}

//returns status of outputpin
int ModuleB::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int ModuleB::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void ModuleB::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}