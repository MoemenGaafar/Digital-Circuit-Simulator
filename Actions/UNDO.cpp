#include "..\Defs.H"
#include "UNDO.h"

Undo::Undo(ApplicationManager* pApp) :Action(pApp) {};

Undo::~Undo(void) {};

void Undo::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->executed > 0)
	{
	//Print Action Message
	pUI->PrintMsg("You clicked on Undo.");

		pManager->Undone_Acts[pManager->Undone_count] = pManager->Done_Acts[pManager->executed-1];
		delete pManager->Done_Acts[pManager->executed-1];
		pManager->Undone_count++;
		pManager->executed--;

		pManager->Undone_Comps[pManager->undone_Compcount] = pManager->CompList[pManager->CompCount-1];
		delete pManager->CompList[pManager->CompCount-1];
		pManager->undone_Compcount++;
		pManager->CompCount--;

		//Clearing the deleted components/actions on the UI:

		if (pManager->Undone_Comps[pManager->undone_Compcount]->ComponentType == T_CONNECTION)
		{
			pUI->ClearConnection(pManager->Undone_Comps[pManager->undone_Compcount - 1]->m_pGfxInfo);
		}

		else if (pManager->Undone_Comps[pManager->undone_Compcount - 1]->ComponentType ==
			(T_SWITCH || T_LED || T_NOT || T_AND2 || T_OR2 || T_NAND2 || T_NOR2 || T_XOR2 || T_XNOR2))
		{
			pUI->ClearComponent(pManager->Undone_Comps[pManager->undone_Compcount]->m_pGfxInfo);
		}

		else if (pManager->Undone_Acts[pManager->Undone_count - 1]->Type == LOAD)
		{
			pUI->ClearDrawingArea();
		}
	}

	else
	{
		pUI->PrintMsg("You cannot undo unless you do something first!");
	}

}




