#include "Label.h"
#include "..\ApplicationManager.h"

Label::Label(ApplicationManager* pApp) :Action(pApp)
{

}

Label::~Label(void)
{
}

void Label::Execute()
{

	int i = pManager->ReturnSelected(); // The location of the selected array in CompList

	if (i != -1) {

		//Get a Pointer to the user Interfaces
		UI* pUI = pManager->GetUI();

		
		if (pManager->CompList[i]->ComponentType != T_SWITCH && pManager->CompList[i]->ComponentType != T_LED)
		//Print Action Message
		pUI->PrintMsg("Type in a label other than '-' then click ENTER.");

		if ( pManager->CompList[i]->ComponentType == T_LED)
		pUI->PrintMsg("All LEDs must have labels at all times. Please type in a nonempty label other than '-' then click ENTER.");
		if (pManager->CompList[i]->ComponentType == T_SWITCH)
		pUI->PrintMsg("All switches must have labels at all times. Please type in a nonempty label other than '-' then click ENTER.");

		string Label;

		Label = pUI->GetString();

		while (Label.length() > 10)
		{
			pUI->PrintMsg("Please enter a string less than TEN characters!");
			Label = pUI->GetString();
		}

		if (pManager->CompList[i]->ComponentType != T_SWITCH || pManager->CompList[i]->ComponentType != T_LED) {
			while (Label == "-")
			{
				pUI->PrintMsg("This string is reserved by the program. Please enter a different label.");
				Label = pUI->GetString();
			}
		}

		if (pManager->CompList[i]->ComponentType == T_SWITCH || pManager->CompList[i]->ComponentType == T_LED) {
			while (Label == " " || Label == "-")
			{
				pUI->PrintMsg("Switches and LEDs must have valid labels at all times. Please enter a nonempty label other than '-'.");
				Label = pUI->GetString();
				while (Label.length() > 10)
				{
					pUI->PrintMsg("Please enter a string less than TEN characters!");
					Label = pUI->GetString();
				}

				while (Label == "-")
				{
					pUI->PrintMsg("This string is reserved by the program. Please enter a different label.");
					Label = pUI->GetString();
				}
			}
		}


		
			if (pManager->CompList[i]->ComponentType != T_CONNECTION) {
				

					pUI->LabelComp(Label, pManager->CompList[i]->m_pGfxInfo->PointsList[0].x, pManager->CompList[i]->m_pGfxInfo->PointsList[0].y);
					pManager->CompList[i]->m_Label = Label;

				
			}

			if (pManager->CompList[i]->ComponentType == T_CONNECTION) {
				

					pUI->LabelComp(Label, pManager->CompList[i]->m_pGfxInfo->PointsList[0].x, pManager->CompList[i]->m_pGfxInfo->PointsList[0].y);
					pManager->CompList[i]->m_Label = Label;

				
			}

			
		

		//Clear Status Bar
		pUI->ClearStatusBar();
	}
}

