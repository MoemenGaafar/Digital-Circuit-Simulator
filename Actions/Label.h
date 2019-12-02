#ifndef _LABEL
#define _LABEL

#include "action.h"
#include "..\Components\AND2.h"

class Label : public Action
{
private:
	int Cx, Cy;

public:
	Label(ApplicationManager* pApp);
	virtual ~Label(void);
	ActionType Type = ADD_Label;
	//Execute action (code depends on action type)
	virtual void Execute();

	


};

#endif
