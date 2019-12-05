#include "AddConnection.h"
#include <iostream>
using namespace std; 


AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
}

AddConnection::~AddConnection(void)
{
}

//The next commented part is supposed to be a function that returns whether the user clicks in empty space, input pin or output pin
//The problem is that pins are not defined for all components so one possible solution is to add the pins to the Component Class
//Another problem is to differentiate between input and output pins and to make sure no 2 inputs or outputs are connected to eachother cuz thats gay

int AddConnection::connectPin(int x, int y) {
	Component* comp;
	for (int i = 0; i < pManager->CompCount; i++) {
		comp = pManager->CompList[i];
		int c = 0;
		int x1 = comp->m_pGfxInfo->PointsList[0].x;
		int y1 = comp->m_pGfxInfo->PointsList[0].y;
		int x2 = comp->m_pGfxInfo->PointsList[1].x;
		int y2 = comp->m_pGfxInfo->PointsList[1].y;
		if (x > x1 && x < x2 && y > y1 && y < y2)
		{
			this->component = comp;

			int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;
			switch (comp->ComponentType) {
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
			{
				if (x > xhalf) {
					pGInfo->PointsList[0].x = x2;
					pGInfo->PointsList[0].y = y2 - 25;
					return 1;
				}
				else if (y > yhalf) { 
					pGInfo->PointsList[1].x = x1;
					pGInfo->PointsList[1].y = y2 - 13;
					return 2; 
				}
				else
				{
					pGInfo->PointsList[1].x = x1;
					pGInfo->PointsList[1].y = y1 + 13;
					return 3;
				}
			}
			case T_NOT: {
				if (x > xhalf) {
					pGInfo->PointsList[0].x = x2 - 1;
					pGInfo->PointsList[0].y = y2 - 24;
					return 1;
				}
				else
				{
					pGInfo->PointsList[1].x = x1;
					pGInfo->PointsList[1].y = y1 + 26;
					return 2;
				}
			}
			case T_SWITCH:
			{
				pGInfo->PointsList[0].x = x2;
				pGInfo->PointsList[0].y = y2 - 25;
				return 1;
			}
			case T_LED:
			{
				pGInfo->PointsList[1].x = x1 + 15;
				pGInfo->PointsList[1].y = y2 - 8;
				return 2;
			}
			}
		}
	}
	return 0;
}

void AddConnection::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Connection: Click on the source pin");

	//Get Center point of the Gate
	pUI->GetPointClicked(srcX, srcY);
	int pin = connectPin(srcX, srcY);

	while (pin != 1) {
		pUI->PrintMsg("Please click on a valid source pin");
		pUI->GetPointClicked(srcX, srcY);
		pin = connectPin(srcX, srcY);
	}

	outp = component->m_OutputPin;

	pUI->PrintMsg("Connection: Click on the destination pin");
	pUI->GetPointClicked(destX, destY);
	pin = connectPin(destX, destY);

	while (pin != 2 && pin != 3) {
		pUI->PrintMsg("Please click on a valid destination pin");
		pUI->GetPointClicked(destX, destY);
		pin = connectPin(destX, destY);
	}

	
	if (pin == 2)
	    inp = component->m_InputPins[0]; 
	if (pin == 3)
		inp = component->m_InputPins[1];

	pUI->ClearStatusBar();

	destX = pGInfo->PointsList[1].x;
	destY = pGInfo->PointsList[1].y;

	
	//Check that no other connections are connected to destination pin
	bool isDestAvailable = 1; 
	for (int j = 0; j < pManager->CompCount; j++)
	{
	
			if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
				&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
			{
				isDestAvailable = 0;
				break;
			}
	}
	


	if (isDestAvailable)
	{
		Connection* pC = new Connection(pGInfo, outp, inp);
		if (!outp->ConnectTo(pC)) {
			pUI->PrintMsg("Connection failed: Source gate has reached the maximum number of outputs.");
		}
		else
			pManager->AddComponent(pC);
	}
	else pUI->PrintMsg("Connection failed: Destination gate already has an input.");

	cout << pGInfo->PointsList[0].x << endl << pGInfo->PointsList[0].y << endl << pGInfo->PointsList[1].x << endl << pGInfo->PointsList[1].y << endl; 

}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}