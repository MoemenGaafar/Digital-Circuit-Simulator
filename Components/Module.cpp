#include "Module.h"

Module::Module(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 5, r_FanOut)
{
	ComponentType = T_Module;
}


// Function Draw
void Module::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawModule(*m_pGfxInfo, selected); 
}

//returns status of outputpin
int Module::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int Module::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Module::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}