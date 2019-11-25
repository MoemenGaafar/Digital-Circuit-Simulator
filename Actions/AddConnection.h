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
	InputPin* inp;
	OutputPin* outp;
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);
	bool connectPin(int x, int y);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};