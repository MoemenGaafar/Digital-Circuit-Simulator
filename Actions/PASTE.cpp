#include "PASTE.h"
#include "..\ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp) :Action(pApp)
{
}

Paste::~Paste(void)
{
}

void Paste::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("You clicked on paste.");


}

