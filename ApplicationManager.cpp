#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddINV.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddLED.h"
#include "Actions\AddCONNECTION.h"
#include "Actions\SELECT.h"
#include "Actions\SAVE.h"
#include "Actions\LOAD.h"
#include "Actions\Label.h"
#include "Actions\EditCONN.h"
#include "Actions\UNDO.h"
#include "Actions\REDO.h"
#include "Actions\DELETE.h"
#include "Actions\COPY.h"
#include "Actions\CUT.h"
#include "Actions\PASTE.h"





ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the UI Object & Initialize the UI	
	pUI = new UI;

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UnselectAll()
{
	    for (int i = 0; i < CompCount; i++)
			CompList[i]->selected = false;
		UpdateInterface();
}
////////////////////////////////////////////////////////////////////

int ApplicationManager::ReturnSelected() const {
	
	int SelectedCount = 0; 
	int Location; 
	
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected ==true) {
			SelectedCount++;
			Location = i;
		}
		if (SelectedCount == 2)
		{
			pUI->PrintMsg("You cannot perform this action for more than 1 component. Please select only 1.");
			return -1; 
		}
	}

	if (SelectedCount==0)
	{
		pUI->PrintMsg("Please select a component before you try to perform this action.");
		return -1;
	}

	if (SelectedCount == 1)
	{
		return Location;
	}
	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{

	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_INV:
		//Unselect any selected before next action 
		UnselectAll();
		pAct = new AddINV(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_AND_GATE_2:
		UnselectAll();
		pAct = new AddANDgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_OR_GATE_2:
		UnselectAll();
		pAct = new AddORgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_NAND_GATE_2:
		UnselectAll();
		pAct = new AddNANDgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_NOR_GATE_2:
		UnselectAll();
		pAct = new AddNORgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_XOR_GATE_2:
		UnselectAll();
		pAct = new AddXORgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_XNOR_GATE_2:
		UnselectAll();
		pAct = new AddXNORgate2(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_Switch:
		UnselectAll();
		pAct = new AddSWITCH(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_LED:
		UnselectAll();
		pAct = new AddLED(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_CONNECTION:
		UnselectAll();
		pAct = new AddConnection(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case ADD_Label:
		pAct = new Label(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case EDIT_Conn:
		pAct = new EditConn(this); 
		executed++;
		Done_Acts[executed] = pAct;
		break;
	
	case SELECT:
		pAct = new Select(this, pUI->PCx, pUI->PCy);
		break;

		//case DEL:
		//case MOVE:

	case SAVE:
		UnselectAll();
		pAct = new Save(this);
		break;

	case LOAD:
		UnselectAll();
		pAct = new Load(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case UNDO:
		UnselectAll();
		pAct = new Undo(this);
		pAct->Execute();
		break;

	case REDO:
		UnselectAll();
		pAct = new Redo(this);
		pAct->Execute();
		break;

	case DEL:
		pAct = new Delete(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case COPY:
		pAct = new Copy(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case CUT:
		pAct = new Cut(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case PASTE:
		pAct = new Paste(this);
		executed++;
		Done_Acts[executed] = pAct;
		break;

	case DSN_MODE:
		UnselectAll();
		pUI->CreateDesignToolBar();
		break;

	case SIM_MODE:
		UnselectAll();
		//Check all connected first
		pUI->CreateSimulationToolBar();
		break;

		//clicks here, changes switches, works
		// see UI for items  

	case EXIT:
		//ApplicationManager::~ApplicationManager(); 
		break;

	//  case STATUS_BAR:
	//	HeldString = pUI->GetString();
	//  break;

		//case DSN_TOOL: bc msh mafrood y7sal 7aga so htfdal pAct=NULL
	}
	if(pAct)
	{
		 
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(pUI);

}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete pUI;
	
}

