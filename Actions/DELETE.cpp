#include "DELETE.h"
#include "..\ApplicationManager.h"
#include "SELECT.h"

Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
	Type = DEL;
}

Delete::~Delete(void)
{

}

void Delete::Execute()
{
	UI* pUI = pManager->GetUI();

	for (int i = 0; i < pManager->CompCount; i++)
	{
		if (pManager->CompList[i]->selected == true)
		{
			if (pManager->CompList[i]->ComponentType != ADD_CONNECTION)
			{
				pUI->ClearComponent(pManager->CompList[i]->m_pGfxInfo);
				delete[] pManager->CompList[i];
				pManager->CompCount = pManager->CompCount - 1;
				break;
			}

			else if (pManager->CompList[i]->ComponentType == ADD_CONNECTION)
			{
				pUI->ClearConnection(pManager->CompList[i]->m_pGfxInfo);
				delete[] pManager->CompList[i];
				pManager->CompCount = pManager->CompCount - 1;
				break;
			}
		}
	}

	//Print Action Message
	pUI->PrintMsg("You clicked on delete.");

}

