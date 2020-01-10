#include "COPY.h"
#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp) :Action(pApp)
{
	Type = COPY;
}

Copy::~Copy(void)
{
}

void Copy::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	for (int i = 0; i < pManager->CompCount; i++)
	{
		if (pManager->CompList[i]->selected == true)
		{
			if (pManager->CompList[i]->ComponentType != T_CONNECTION)
			{
				//Print Action Message

				pUI->PrintMsg("You copied the selected component. Click where you'd like to paste.");

				int x, y;

				pUI->GetPointClicked(x, y); //Coordinates for copy's center

				int gateWidth = pUI->getGateWidth();
				int gateHeight = pUI->getGateHeight();

				GraphicsInfo* pGInfo = new GraphicsInfo(2); //To construct the copy

				pGInfo->PointsList[0].x = x - gateWidth / 2;
				pGInfo->PointsList[0].y = y - gateHeight / 2;
				pGInfo->PointsList[1].x = x + gateWidth / 2;
				pGInfo->PointsList[1].y = y + gateHeight / 2;

				//Cases of pasting on the tool bar or status bar

				if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight || pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight) {
					if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight)
						pUI->PrintMsg("You cannot paste the component on the toolbar. Action aborted.");
					if (pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
						pUI->PrintMsg("You cannot paste the component on the status bar. Action aborted.");

					pManager->Done_Acts[pManager->executed] = NI;
					pManager->executed--;
				}

				else
				{
					switch (pManager->CompList[i]->ComponentType)
					{
					case T_NAND2:
						copied = new NAND2(pGInfo, Default_FANOUT);
						break;
					case T_AND2:
						copied = new AND2(pGInfo, Default_FANOUT);
						break;
					case T_LED:
						copied = new LED(pGInfo, Default_FANOUT);
						break;
					case T_NOR2:
						copied = new NOR2(pGInfo, Default_FANOUT);
						break;
					case T_NOT:
						copied = new INV(pGInfo,Default_FANOUT);
						break;
					case T_OR2:
						copied = new OR2(pGInfo,Default_FANOUT);
						break;
					case T_SWITCH:
						copied = new Switch(pGInfo, Default_FANOUT);
						break;
					case T_XOR2:
						copied = new XOR2(pGInfo, Default_FANOUT);
						break;
					case T_XNOR2:
						copied = new XNOR2(pGInfo, Default_FANOUT);
						break;
					}

					pManager->AddComponent(copied);
					pManager->UnselectAll();
					pUI->PrintMsg("Copied component pasted successfully.");
				}
			}
		}
		else
		{
			pUI->PrintMsg("Nothing is selected. Please select a component to copy.");
		}
	}


}

