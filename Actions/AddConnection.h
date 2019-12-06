#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
#include "..\ApplicationManager.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"

class AddConnection : public Action {
private:
	int srcX, srcY, destX, destY;
	InputPin inp;
	OutputPin* outp;
	Component* component;  
	GraphicsInfo* pGInfo = new GraphicsInfo(2);
public:
	AddConnection(ApplicationManager* pApp);
	ActionType Type = ADD_CONNECTION;
	virtual ~AddConnection(void);
	int connectPin(int x, int y);

	//Execute action (code depends on action type)
	virtual void Execute();

};