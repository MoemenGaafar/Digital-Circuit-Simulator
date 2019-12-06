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
		pManager->Undone_Acts[pManager->Undone_count-1] = NULL;
		pManager->Undone_count--;
		pManager->executed++;

		pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[pManager->undone_Compcount-1];
	    pManager->Undone_Comps[pManager->undone_Compcount-1]= NULL;
		pManager->CompCount++;
		pManager->undone_Compcount--;

		enum Type t = pManager->CompList[pManager->CompCount - 1]->ComponentType;

		if (t == T_SWITCH || t == T_LED || t == T_NOT || t == T_AND2 || t == T_OR2 || t == T_NAND2 || t == T_NOR2 || t == T_XOR2 || t == T_XNOR2)
		{
			pUI->LabelComp(pManager->CompList[pManager->CompCount - 1]->m_Label,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].y);
		}
	}
	else
	{
		pUI->PrintMsg("You cannot redo unless you have undone something!");
	}

}