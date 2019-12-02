
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
		if (ActType == LOAD)
					
		//Update the drawing window
		if(ActType!= EXIT && ActType != LOAD)
		AppManager.UpdateInterface();
		if (ActType == LOAD)
			AppManager.UpdateInterface();

	
		
		

	}while(ActType != EXIT);
		
	return 0;
}

