#include "CUT.h"
#include "..\ApplicationManager.h"

Cut::Cut(ApplicationManager* pApp) :Action(pApp)
{
	 Type = CUT;
}

Cut::~Cut(void)
{
}

void Cut::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	for (int i = 0; i < pManager->CompCount; i++)
	{
		if (pManager->CompList[i]->selected == true)
		{
			Cutitm = pManager->CompList[i];

			pUI->ClearComponent(Cutitm->m_pGfxInfo);

			pUI->PrintMsg("You cut the selected component. Click where you'd like to paste.");

			//Finding connections to clear them

			//For the connections of the output pin and the 1st input pin.
			GraphicsInfo* pGInfo1 = new GraphicsInfo(2);

			//For the connections of the output pin and the 2nd input pin, if exists.
			GraphicsInfo* pGInfo2 = new GraphicsInfo(2);

			//Setting the points
			int x1 = Cutitm->m_pGfxInfo->PointsList[0].x;
			int y1 = Cutitm->m_pGfxInfo->PointsList[0].y;
			int x2 = Cutitm->m_pGfxInfo->PointsList[1].x;
			int y2 = Cutitm->m_pGfxInfo->PointsList[1].y;
			int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;

			//To set the pGInfos

			switch (Cutitm->ComponentType)
			{
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
				//For all components with 2 pins we'll use the two pGInfos:

				pGInfo1->PointsList[0].x = x2;
				pGInfo1->PointsList[0].y = y2 - 25;
				pGInfo1->PointsList[1].x = x1;
				pGInfo1->PointsList[1].y = y2 - 13;

				pGInfo2->PointsList[0].x = x2;
				pGInfo2->PointsList[0].y = y2 - 25;
				pGInfo2->PointsList[1].x = x1;
				pGInfo2->PointsList[1].y = y1 + 13;

				break;

			case T_NOT:

				pGInfo1->PointsList[0].x = x2 - 1;
				pGInfo1->PointsList[0].y = y2 - 24;
				pGInfo1->PointsList[1].x = x1;
				pGInfo1->PointsList[1].y = y1 + 26;

				break;

			case T_SWITCH:

				pGInfo1->PointsList[0].x = x2;
				pGInfo1->PointsList[0].y = y2 - 25;

				break;

			case T_LED:

				pGInfo1->PointsList[1].x = x1 + 15;
				pGInfo1->PointsList[1].y = y2 - 8;
				break;
			}

			//Finding the connections associated with the cut component and removing them

			for (int n = 0; n < pManager->CompCount; n++)
			{
				if (pManager->CompList[n]->ComponentType == T_CONNECTION)
				{
					if ((Cutitm->ComponentType != T_LED) && (Cutitm->ComponentType != T_SWITCH))
					{
						if (((pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo1->PointsList[0].x)
							&& (pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo1->PointsList[0].y))
							|| ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[1].x)
								&& (pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[1].y))
							|| ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo2->PointsList[1].x)
								&& (pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo2->PointsList[1].y)))
						{
							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							pManager->CompList[n] = NULL;
						}
					}
					else if (Cutitm->ComponentType != T_LED)
					{
						if (((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[1].x)
							&& (pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[1].y)))
						{
							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							pManager->CompList[n] = NULL;
						}
					}
					else if (Cutitm->ComponentType != T_SWITCH)
					{
						if ((pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo1->PointsList[0].x) &&
							(pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo1->PointsList[0].y))
						{
							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							pManager->CompList[n] = NULL;
						}
					}
				}
			}

			pManager->CompList[i] = NULL;
			//Re-sorting the component list
			int k = 0;

			for (int j = 0; j < pManager->CompCount; j++)
			{
				if (pManager->CompList[j] != NULL)
				{
					pManager->CompList[k] = pManager->CompList[j];
					k = k + 1;
				}
				pManager->CompCount = k + 1;
			}

			//Setting new position to paste a component

			int x, y;

			pUI->GetPointClicked(x, y); //Coordinates for copy's center

			int gateWidth = pUI->getGateWidth();
			int gateHeight = pUI->getGateHeight();

			//Graphics info to construct the copy
			GraphicsInfo* pGInfo = new GraphicsInfo(2);

			pGInfo->PointsList[0].x = x - gateWidth / 2;
			pGInfo->PointsList[0].y = y - gateHeight / 2;
			pGInfo->PointsList[1].x = x + gateWidth / 2;
			pGInfo->PointsList[1].y = y + gateHeight / 2;

			//Cases of pasting on the tool bar or status bar

			if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight || pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
			{
				if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight)
					pUI->PrintMsg("You cannot paste the component on the toolbar. Action aborted.");

				if (pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
					pUI->PrintMsg("You cannot paste the component on the status bar. Action aborted.");

				pManager->Done_Acts[pManager->executed] = NI;
				pManager->executed--;
				break;
			}

			else
			{
				Cutitm->m_pGfxInfo = pGInfo;
				pManager->CompList[pManager->CompCount - 1] = Cutitm;
				pManager->UnselectAll();
				pUI->PrintMsg("Cut component pasted successfully.");
			}

		}

		//In case no component is selected for cutting
		else
		{
			pUI->PrintMsg("Nothing is selected. Please select a component to cut.");
		}
	}
}

