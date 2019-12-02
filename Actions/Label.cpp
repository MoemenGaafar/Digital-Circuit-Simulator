#include "Label.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;

Label::Label(ApplicationManager* pApp) :Action(pApp)
{

}

Label::~Label(void)
{
}

void Label::Execute()
{
	
	cout << "iamexcuetingmommy"; 
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("I am in label");

	int i = pManager->ReturnSelected(); // The location of the selected array in CompList

	if (i != -1) {

		//Get a Pointer to the user Interfaces
		//UI* pUI = pManager->GetUI();

		//Print Action Message
		pUI->PrintMsg("Type your label");

		string Label;

		Label = pUI->GetString();




		
			if (pManager->CompList[i]->ComponentType != T_CONNECTION) {
				

					pUI->LabelComp(Label, pManager->CompList[i]->m_pGfxInfo->PointsList[0].x, pManager->CompList[i]->m_pGfxInfo->PointsList[1].y);
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

void Label::Undo()
{}

void Label::Redo()
{}
