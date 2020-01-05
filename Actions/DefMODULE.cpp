#include "DefMODULE.h"
#include "..\ApplicationManager.h"


DefModule::DefModule(ApplicationManager* pApp) :Action(pApp)
{	
	Type = NamedMODULE;
};


DefModule::~DefModule(void) {
	delete DNamedModule; 
};

void DefModule::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Insert Default Module: Click to add the module.");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();

	string TempName = "ProgramTXTfiles\\DefaultModule.txt"; 

	DNamedModule->ExecutePart(TempName, pUI);


}
