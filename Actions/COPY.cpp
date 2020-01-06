#include "COPY.h"
#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp) :Action(pApp)
{
	Type = COPY;
}

Copy::~Copy(void)
{
}

void Copy::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("You clicked on copy.");


}

