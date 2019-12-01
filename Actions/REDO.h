#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class Redo :public Action
{

public:

	Redo(ApplicationManager* pApp);
	~Redo(void);

	//Execute action (code depends on action type)
	virtual void Execute();

};