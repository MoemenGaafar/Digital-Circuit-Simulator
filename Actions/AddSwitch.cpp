#include "AddSWITCH.h"
#include "..\ApplicationManager.h"
#include "Label.h"

AddSWITCH::AddSWITCH(ApplicationManager* pApp) :Action(pApp)
{
	Type = ADD_Switch;
}

AddSWITCH::~AddSWITCH(void)
{
}

void AddSWITCH::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Switch: Click to add ");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the gate

	pGInfo->PointsList[0].x = Cx - gateWidth / 2;
	pGInfo->PointsList[0].y = Cy - gateHeight / 2;
	pGInfo->PointsList[1].x = Cx + gateWidth / 2;
	pGInfo->PointsList[1].y = Cy + gateHeight / 2;
	if (pGInfo->PointsList[0].y < pUI->ToolBarHeight || pGInfo->PointsList[1].y < pUI->ToolBarHeight) {
		pUI->PrintMsg("YOU CAN'T PLACE A COMPONENT ON THE TOOLBAR!!");
	}
	else {
		Switch* pA = new Switch(pGInfo, Default_FANOUT);
		pManager->AddComponent(pA);
	}
	
	
	Label temp(pManager); 
	temp.Execute(); 
}

