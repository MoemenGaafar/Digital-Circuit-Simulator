
#include <iostream>
#include <sstream>
#include <cmath>

#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		
		//Exexute the action
		AppManager.ExecuteAction(ActType);
	
					
		//Update the drawing window
		if(ActType!= EXIT )
		AppManager.UpdateInterface();

		/*if (ActType == LOAD) {
			cout << "i will draw.";
			AppManager.UpdateInterface();
			cout << "i am done drawing."; 
		}*/

	
		
		

	}while(ActType != EXIT);
		
	return 0;
}

