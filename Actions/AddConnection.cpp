#include "AddConnection.h"



AddConnection::AddConnection(ApplicationManager * pApp) :Action(pApp)
{
  Type = ADD_CONNECTION;
}

AddConnection::~AddConnection(void)
{
}

//The next commented part is supposed to be a function that returns whether the user clicks in empty space, input pin or output pin
//The problem is that pins are not defined for all components so one possible solution is to add the pins to the Component Class
//Another problem is to differentiate between input and output pins and to make sure no 2 inputs or outputs are connected to eachother cuz thats gay

int AddConnection::checkPin(int x, int y) {
	for (int i = 0; i < pManager->CompCount; i++) {


		int x1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].x;
		int y1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].y;
		int x2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x;
		int y2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;
		if (x > x1 && x < x2 && y > y1 && y < y2)
		{
			component = pManager->CompList[i];

			int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;
			switch (component->ComponentType) {
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
			{
				if (x > xhalf) {

					return 1;
				}
				else if (y > yhalf) {

					return 2;
				}
				else
				{
					return 3;
				}
			}
			case T_NOT: {
				if (x > xhalf) {

					return 1;
				}
				else
				{
					return 2;
				}
			}
			case T_SWITCH:
			{
				return 1;
			}
			case T_LED:
			{
				return 2;
			}
			}
		}
	}
	return 0;
}


void AddConnection::connectPin(int x, int y, int r) {

	int x1 = component->m_pGfxInfo->PointsList[0].x;
	int y1 = component->m_pGfxInfo->PointsList[0].y;
	int x2 = component->m_pGfxInfo->PointsList[1].x;
	int y2 = component->m_pGfxInfo->PointsList[1].y;
	int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;

	switch (component->ComponentType) {
	case T_AND2:
	case T_OR2:
	case T_NAND2:
	case T_NOR2:
	case T_XOR2:
	case T_XNOR2:
	{
		if (r == 1) {
			pGInfo->PointsList[0].x = x2;
			pGInfo->PointsList[0].y = y2 - 25;
		}
		else if (r == 2) {
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y2 - 13;
		}
		else
		{
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 13;
		}
		break;
	}
	case T_NOT: {
		if (r == 1) {
			pGInfo->PointsList[0].x = x2 - 1;
			pGInfo->PointsList[0].y = y2 - 24;
		}
		else
		{
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 26;
		}
		break;
	}
	case T_SWITCH:
	{
		pGInfo->PointsList[0].x = x2;
		pGInfo->PointsList[0].y = y2 - 25;
		break;
	}
	case T_LED:
	{
		pGInfo->PointsList[1].x = x1 + 15;
		pGInfo->PointsList[1].y = y2 - 8;
		break;
	}
	}

}



void AddConnection::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Connection: Click on the source pin");

	//Get Center point of the Gate
	pUI->GetPointClicked(srcX, srcY);
	pin = checkPin(srcX, srcY);

	while (pin != 1) {
		pUI->PrintMsg("Please click on a valid source pin");
		pUI->GetPointClicked(srcX, srcY);
		pin = checkPin(srcX, srcY);
	}

	connectPin(srcX, srcY, 1);
	Component* outComp = component;
	outp = component->m_OutputPin;

	pUI->PrintMsg("Connection: Click on the destination pin");
	pUI->GetPointClicked(destX, destY);
	pin = checkPin(destX, destY);

	while (pin != 2 && pin != 3) {
		pUI->PrintMsg("Please click on a valid destination pin");
		pUI->GetPointClicked(destX, destY);
		pin = checkPin(destX, destY);
	}

	Component* inComp = component;

	if (pin == 2)
	{
		connectPin(srcX, srcY, 2);
		inp = &component->m_InputPins[0];
	}
	if (pin == 3)
	{
		connectPin(srcX, srcY, 3);
		inp = &component->m_InputPins[1];
	}

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

			outComp->m_OutputPin->setStatus(LOW);
			inComp->m_InputPins[pin - 2].setStatus(LOW);
	}
	else pUI->PrintMsg("Connection failed: Destination gate already has an input.");
}