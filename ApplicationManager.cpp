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
#include "Actions\MOVE.h"







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
			pUI->PrintMsg("You cannot perform this action for more than 1 component. Please select only 1 then try again.");
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
bool ApplicationManager::isAllConnected() const {
	for (int i = 0; i < CompCount; i++) {
		switch (CompList[i]->ComponentType) {
		case T_AND2:
		case T_OR2:
		case T_NAND2:
		case T_NOR2:
		case T_XOR2:
		case T_XNOR2:
		{
			if (CompList[i]->GetOutPinStatus() == NCON || CompList[i]->GetInputPinStatus(1) == NCON
				|| CompList[i]->GetInputPinStatus(2) == NCON) return 0; break;
		}
		case T_NOT:
		{
			if (CompList[i]->GetOutPinStatus() == NCON || CompList[i]->GetInputPinStatus(1) == NCON) return 0;
			break;
		}
		case T_SWITCH:
		{
			if (CompList[i]->GetOutPinStatus() == NCON) return 0;
			break;
		}
		case T_LED:
		{
			if (CompList[i]->GetInputPinStatus(1) == NCON) return 0;
			break;
		}
		case T_CONNECTION: continue;
		}
	}
	return 1;
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
		Done_Acts[executed++] = pAct;
		break;

	case ADD_AND_GATE_2:
		UnselectAll();
		pAct = new AddANDgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_OR_GATE_2:
		UnselectAll();
		pAct = new AddORgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_NAND_GATE_2:
		UnselectAll();
		pAct = new AddNANDgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_NOR_GATE_2:
		UnselectAll();
		pAct = new AddNORgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_XOR_GATE_2:
		UnselectAll();
		pAct = new AddXORgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_XNOR_GATE_2:
		UnselectAll();
		pAct = new AddXNORgate2(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_Switch:
		UnselectAll();
		pAct = new AddSWITCH(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_LED:
		UnselectAll();
		pAct = new AddLED(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_CONNECTION:
		UnselectAll();
		pAct = new AddConnection(this);
		Done_Acts[executed++] = pAct;
		break;

	case ADD_Label: //For adding and editing labels
		pAct = new Label(this);
		Done_Acts[executed++] = pAct;
		break;

	case EDIT_Conn:
		pAct = new EditConn(this); 
		Done_Acts[executed++] = pAct;
		break; 
	
	case SELECT:
		pAct = new Select(this, pUI->PCx, pUI->PCy);
		break;

	
	case SAVE:
		UnselectAll();
		pAct = new Save(this);
		break;

	case LOAD:
		UnselectAll();
		pAct = new Load(this);
		Done_Acts[executed++] = pAct;
		break;

	case UNDO:
		UnselectAll();
		pAct = new Undo(this);
		break;

	case REDO:
		UnselectAll();
		pAct = new Redo(this);
		break;

	case DEL:
		pAct = new Delete(this);
		Done_Acts[executed++] = pAct;
		break;

	case COPY:
		pAct = new Copy(this);
		Done_Acts[executed++] = pAct;
		break;

	case CUT:
		pAct = new Cut(this);
		Done_Acts[executed++] = pAct;
		break;

	case PASTE:
		pAct = new Paste(this);
		Done_Acts[executed++] = pAct;
		break;

	case MOVE:
		pAct = new Move(this);
		Done_Acts[executed++] = pAct;
		break;

	case DSN_MODE:
		UnselectAll();
		pUI->CreateDesignToolBar();
		break;

	case SIM_MODE:
		UnselectAll();
		if (isAllConnected())
			pUI->CreateSimulationToolBar();
		else
			pUI->PrintMsg("One or more components are not connected!");
		break;
		
	case EXIT:
		//ApplicationManager::~ApplicationManager(); 
		break;


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
	if(pUI->AppMode == SIMULATION)
    for(int j = 0; j < 2; j++)
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Operate();

for (int i = 0; i < CompCount; i++)
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

