#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class Undo :public Action
{
public:

	Undo(ApplicationManager* pApp);
	~Undo(void);

	//Execute action (code depends on action type)
	virtual void Execute();

};
