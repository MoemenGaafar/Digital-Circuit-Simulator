#include "AddXORgate2.h"
#include "..\ApplicationManager.h"

AddXORgate2::AddXORgate2(ApplicationManager* pApp) :Action(pApp)
{
     Type = ADD_XOR_GATE_2;
}

AddXORgate2::~AddXORgate2(void)
{
}

void AddXORgate2::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input XOR Gate: Click to add the gate");

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
		XOR2* pA = new XOR2(pGInfo, Default_FANOUT);
		pManager->AddComponent(pA);
	}
}

