#include "CUT.h"
#include "..\ApplicationManager.h"

Cut::Cut(ApplicationManager* pApp) :Action(pApp)
{
}

Cut::~Cut(void)
{
}

void Cut::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("You clicked on cut.");


}

