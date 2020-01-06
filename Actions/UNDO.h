#pragma once
#include "Action.h"
#include "SAVE.h"
#include "LOAD.h"
#include "../ApplicationManager.h"

class Undo :public Action
{
public:

	Undo(ApplicationManager* pApp);
	~Undo(void);
	Save* USave = new Save(pManager); 
	Load* ULoad = new Load(pManager); 
	

	//Execute action (code depends on action type)
	virtual void Execute();

};
