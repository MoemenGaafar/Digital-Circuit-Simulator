#include "UNDO.h"



Undo::Undo(ApplicationManager* pApp) :Action(pApp) {};

Undo::~Undo(void) {
	delete USave; 
	delete ULoad; 
};

void Undo::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->executed > 0)
	{
	//Print Action Message
	pUI->PrintMsg("You clicked on Undo.");

		pManager->Undone_Acts[pManager->Undone_count] = pManager->Done_Acts[pManager->executed-1];
		pManager->Done_Acts[pManager->executed-1] = NI;
		pManager->Undone_count++;
		pManager->executed--;

				
		
		ActionType t1 = pManager->Undone_Acts[pManager->Undone_count - 1];
		
	
	 if (t1 == ADD_COMP || t1 == ADD_CONNECTION)
	 {
		
		//Clearing the deleted components/actions on the UI:

		pManager->Undone_Comps[pManager->undone_Compcount] = pManager->CompList[pManager->CompCount - 1];
		

		if (t1 == ADD_CONNECTION)
		{
			pUI->ClearConnection(pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo);
			pUI->LabelComp("               ",
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].y);
		}

		else 
		{
			pUI->ClearComponent(pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo);
			pUI->LabelComp("               ",
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[pManager->CompCount - 1]->m_pGfxInfo->PointsList[0].y);
		}

		pManager->CompList[pManager->CompCount - 1] = NULL;
		pManager->undone_Compcount++;
		pManager->CompCount--;

	 } 

	 else if (t1 == LOAD)
	 {
		 string TempName = "ProgramTXTfiles\\temporaryloadtype2file";
		 TempName += to_string(pManager->UndoneLoadCount);
		 TempName += ".txt";
		 bool x= USave-> ExecutePart(TempName);

		 pManager->UndoneLoadCount++; 
		 pManager->LoadCount--; 

		 		 
		 string TempName2 = "ProgramTXTfiles\\temporaryloadtype1file";
		 int number = pManager->LoadCount; 
		 TempName2 += to_string(number);
		 TempName2 += ".txt";
		 bool y= ULoad->ExecutePart(TempName2, pUI, 0);

	 }

	 else if (t1 == EDIT_Conn) 
	 {
		 pManager->UndoneEditConn[pManager->UndoneEditConnCount] = new Connection(pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount-1]]->m_pGfxInfo, pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]-> getSourcePin(), pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->getDestPin());
		
		 pUI->ClearConnection(pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->m_pGfxInfo);
		 
		 pManager->UndoneEditConn [pManager->UndoneEditConnCount]->m_Label = pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->m_Label;
		 
		 pUI->LabelComp("               ",
			 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount-1]]->m_pGfxInfo->PointsList[0].x,
			 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount-1]]->m_pGfxInfo->PointsList[0].y);

		 pManager->UndoneEditConnCount++; 

		 
		 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]] = new Connection(pManager->DoneEditConn[pManager->EditConnCount - 1]->m_pGfxInfo, pManager->DoneEditConn[pManager->EditConnCount - 1]->getSourcePin(), pManager->DoneEditConn[pManager->EditConnCount - 1]->getDestPin());
		
		 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->m_Label = pManager->DoneEditConn[pManager->EditConnCount - 1]->m_Label;
		
		 pUI->LabelComp(pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]] ->m_Label,
			 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->m_pGfxInfo->PointsList[0].x,
			 pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount - 1]]->m_pGfxInfo->PointsList[0].y);

		 
		 pManager->EditConnCount--; 
	 }

		

	}

	else
	{
		pUI->PrintMsg("You cannot undo unless you do something first!");
	}

}



