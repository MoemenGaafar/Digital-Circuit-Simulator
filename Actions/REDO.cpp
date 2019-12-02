#include "REDO.h"

Redo::Redo(ApplicationManager* pApp) :Action(pApp) {};

Redo::~Redo(void) {};

void Redo::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->Undone_count > 0)
	{
	//Print Action Message
	pUI->PrintMsg("You clicked on Redo.");

		pManager->Done_Acts[pManager->executed] = pManager->Undone_Acts[pManager->Undone_count-1];
		delete pManager->Undone_Acts[pManager->Undone_count-1];
		pManager->Undone_count--;
		pManager->executed++;

		pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[pManager->undone_Compcount-1];
		delete pManager->Undone_Comps[pManager->undone_Compcount-1];
		pManager->CompCount++;
		pManager->undone_Compcount--;
	}
	else
	{
		pUI->PrintMsg("You cannot redo unless you have undone something!");
	}

}