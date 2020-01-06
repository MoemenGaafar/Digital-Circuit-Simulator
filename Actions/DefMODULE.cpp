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

	string TempName = "ProgramTXTfiles\\DefaultModule.txt"; 

	DNamedModule->ExecutePart(TempName, pUI);


}
