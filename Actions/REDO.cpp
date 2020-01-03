#include "REDO.h"

Redo::Redo(ApplicationManager* pApp) :Action(pApp) {};

Redo::~Redo(void) {
	delete RSave; 
};

void Redo::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->Undone_count > 0)
	{
	  //Print Action Message
	  pUI->PrintMsg("You clicked on Redo.");

	    ActionType t1 = pManager->Undone_Acts[pManager->Undone_count - 1];

		pManager->Done_Acts[pManager->executed] = pManager->Undone_Acts[pManager->Undone_count-1];
		pManager->Undone_Acts[pManager->Undone_count-1] = NI;
		pManager->Undone_count--;
		pManager->executed++;

		if (t1 == ADD_COMP || t1 == ADD_CONNECTION) {

			pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[pManager->undone_Compcount - 1];
			pManager->Undone_Comps[pManager->undone_Compcount - 1] = NULL;
			pManager->CompCount++;
			pManager->undone_Compcount--;
			
			pUI->LabelComp(pManager->CompList[pManager->CompCount - 1]->m_Label,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].y);
			

		}

		else if (t1 == LOAD) {

			string TempName = "D:\\temporaryloadtype1file";
			TempName += to_string(pManager->LoadCount);
			TempName += ".txt";
			RSave->ExecutePart(TempName);

			pManager->UndoneLoadCount--;
			pManager->LoadCount++;


			string TempName2 = "D:\\temporaryloadtype2file";
			int number = pManager->UndoneLoadCount;
			TempName2 += to_string(number);
			TempName2 += ".txt";
			bool y = RLoad->ExecutePart(TempName2, pUI);


		}
	}
	else
	{
		pUI->PrintMsg("You cannot redo unless you have undone something!");
	}

}