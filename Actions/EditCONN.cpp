#include "EditConn.h"
#include "..\ApplicationManager.h"
#include "AddConnection.h"

EditConn::EditConn(ApplicationManager* pApp) :Action(pApp)
{
}

EditConn::~EditConn(void)
{
}

int EditConn::connectPin(int x, int y) {
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




void EditConn::Execute()
{

	int i = pManager->ReturnSelected(); // The location of the selected array in CompList

	if (i != -1)
	{
		
		//Get a Pointer to the user Interfaces
		UI* pUI = pManager->GetUI();

		if (pManager->CompList[i]->ComponentType == T_CONNECTION)
		{
			//Erase connection from UI to clear space for edited one
			pUI->ClearConnection(pManager->CompList[i]->m_pGfxInfo); 

			//Destination points of old connection (note: no two connections share a dest. point)
			int oldX = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x; 
			int oldY = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;

			//int to hold the source pin's number of connections
			int Num_Conn = pManager->CompList[i]->getSourcePin()->m_Conn; 

			//Find the connection in its original source pin's array of connections by comparing dest. points
			for (int j = 0; j < Num_Conn; j++) 
			{
				if (pManager->CompList[i]->getSourcePin()->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
					&& pManager->CompList[i]->getSourcePin()->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
				{
					//Delete connection from source pin's array
					for (int m = j; m < Num_Conn; m++)
						pManager->CompList[i]->getSourcePin()->m_Connections[m] = pManager->CompList[i]->getSourcePin()->m_Connections[m]; 
				}
			}

			//Subtract 1 from number of connections connected to original source pin
			pManager->CompList[i]->getSourcePin()->m_Conn--; 
			
			
			int pin;
			bool isAvailable;
			
		    //Select new source pin
			do 
			{
				//Print Action Message
				pUI->PrintMsg("Click on the new source pin");

				//Get Center point of the Gate
				pUI->GetPointClicked(srcX, srcY);
				pin = connectPin(srcX, srcY);

				while (pin != 1) {
					pUI->PrintMsg("Please click on a valid source pin");
					pUI->GetPointClicked(srcX, srcY);
					pin = connectPin(srcX, srcY);
				}
				outp = component->m_OutputPin;
				pManager->CompList[i]->setSourcePin(outp);

			    isAvailable = outp->ConnectTo(pManager->CompList[i]); 

				if (! isAvailable) 
					pUI->PrintMsg("This gate has reached the maximum number of outputs. Select another gate.");
				
			} while (! isAvailable); 
			
			
			
			//Select new destination pin
			isAvailable = 1; 
			do
			{
				pUI->PrintMsg("Connection: Click on the destination pin");
				pUI->GetPointClicked(destX, destY);
				pin = connectPin(destX, destY);

				while (pin != 2 && pin != 3) {
					pUI->PrintMsg("Please click on a valid destination pin");
					pUI->GetPointClicked(destX, destY);
					pin = connectPin(destX, destY);
				}

				//Ensures that no other connections are connected to this input pin. 

				destX = pGInfo->PointsList[1].x;
				destY = pGInfo->PointsList[1].y; 

				for (int j = 0; j < i; j++)
				{
					if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
						&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
					{
						isAvailable = 0;
						break;
					}
						
				}
				if (isAvailable == 1) {
					for (int j = i + 1; j < pManager->CompCount; j++)
					{
						if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
							&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
						{
							isAvailable = 0;
							break;
						}
					}
				}

				if(!isAvailable)
					pUI->PrintMsg("This input is already connected. Select another input.");
			} while (!isAvailable);


			if (pin == 2)
				inp = component->m_InputPins[0];
			if (pin == 3)
				inp = component->m_InputPins[1];

				pManager->CompList[i]->setDestPin(inp);

				pUI->ClearStatusBar();

				//Change graphics info
				pManager->CompList[i]->m_pGfxInfo = pGInfo;
			
			
		}
		else pUI->PrintMsg("A connection needs to be selected before this action could be performed. \n");
	}

}

void EditConn::Undo()
{}

void EditConn::Redo()
{}
