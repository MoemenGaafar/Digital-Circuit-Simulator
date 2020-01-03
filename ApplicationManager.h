#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"


//Main class that manages everything in the application.
class ApplicationManager
{

private:
	enum { MaxCompCount = 200 };	//Max no of Components

	UI* pUI; //pointer to the UI

public:	
	string HeldString;
	ApplicationManager(); //constructor

	ActionType* Done_Acts = new ActionType[100000]; //Array of Done actions
	ActionType* Undone_Acts = new ActionType[100000]; //Array of undone actions
	int executed = 0; //Number of done actions
	int Undone_count = 0; //Number of undone actions

	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Component* Undone_Comps[MaxCompCount]; //Array of undone components
	int CompCount = 0;		//Actual number of Components
	int undone_Compcount = 0; //Number of undone components
	int LoadCount = 0;
	int UndoneLoadCount = 0; 

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Unselects selected components before new action is excuted (not used with all action types)
	void UnselectAll(); 

	//Checks that only one component is selected and returns its location
	int ReturnSelected() const; 

	//Checks if all components are connected before running the simulation
	bool isAllConnected() const;

	//Turns off all LEDs and Switches before going back to design mode
	void TurnOffAll();



	//destructor
	~ApplicationManager();
};

#endif