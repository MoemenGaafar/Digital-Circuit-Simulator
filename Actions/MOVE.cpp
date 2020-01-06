#include "MOVE.h"
#include "..\ApplicationManager.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
	 Type = MOVE;
}

Move::~Move(void)
{
}

void Move::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("You clicked on move.");


}
