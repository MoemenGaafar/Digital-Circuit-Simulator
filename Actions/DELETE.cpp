#include "DELETE.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
	Type = DEL;
}

Delete::~Delete(void)
{
}

void Delete::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("You clicked on delete.");


}

