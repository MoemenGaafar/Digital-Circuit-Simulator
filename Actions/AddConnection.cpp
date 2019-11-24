#include "AddConnection.h"


AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
}

AddConnection::~AddConnection(void)
{
}

//The next commented part is supposed to be a function that returns whether the user clicks in empty space, input pin or output pin
//The problem is that pins are not defined for all components so one possible solution is to add the pins to the Component Class
//Another problem is to differentiate between input and output pins and to make sure no 2 inputs or outputs are connected to eachother cuz thats gay

//bool AddConnection::connectPin(int x, int y) {
//	for (int i = 0; i < pManager->getCount(); i++) {
//		Component* comp = pManager->CompList[i];
//		int x1 = comp->m_pGfxInfo->PointsList[0].x;
//		int y1 = comp->m_pGfxInfo->PointsList[0].y;
//		int x2 = comp->m_pGfxInfo->PointsList[1].x;
//		int y2 = comp->m_pGfxInfo->PointsList[1].y;
//		if (x > x1 || x < x2 || y > y1 || y < y2) {
//			return 0;
//		}
//		else
//		{
//			int xhalf = (x2 - x1) / 2, yhalf = (y2 - y1) / 2;
//			if (x > xhalf) {
//				inp = comp->m_InputPins;
//				return 1;
//			}
//		}
//	}
//}

void AddConnection::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Connection: Click on the source pin");

	//Get Center point of the Gate
	pUI->GetPointClicked(srcX, srcY);

    //CHECK WHETHER THE CLICKED POINT CONTAINS A COMPONENT THEN CHECK IF IT CONTAINS A PIN, RETURN PIN

	pUI->PrintMsg("Connection: Click on the destination pin");

	pUI->GetPointClicked(destX, destY);

	//CHECK WHETHER THE CLICKED POINT CONTAINS A COMPONENT THEN CHECK IF IT CONTAINS A PIN, RETURN PIN

	GraphicsInfo* pGInfo = new GraphicsInfo(2);
	pGInfo->PointsList[0].x = srcX;
	pGInfo->PointsList[0].y = srcY;
	pGInfo->PointsList[1].x = destX;
	pGInfo->PointsList[1].y = destY;


  //Connection *pC = new Connection(pGInfo,)
  //pManager->AddComponent(pC);
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}