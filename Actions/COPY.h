#ifndef _COPY_
#define _COPY_

#include "action.h"
#include "..\Components\Component.h"

class Copy : public Action
{
private:


public:
	Copy(ApplicationManager* pApp);
	virtual ~Copy(void);
	ActionType Type = COPY;
	//Execute action (code depends on action type)
	virtual void Execute();



};

#endif