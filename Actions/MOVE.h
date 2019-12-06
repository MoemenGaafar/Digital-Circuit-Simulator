#ifndef _MOVE_
#define _MOVE_

#include "action.h"
#include "..\Components\Component.h"

class Move : public Action
{
private:


public:
	Move(ApplicationManager* pApp);
	virtual ~Move(void);
	ActionType Type = MOVE;
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
