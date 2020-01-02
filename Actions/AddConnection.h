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
	int pin;
	InputPin inp;
	OutputPin* outp;
	Component* component;  
	GraphicsInfo* pGInfo = new GraphicsInfo(2);
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);
	
	int checkPin(int x, int y); 
	void connectPin(int x, int y, int r);

	//Execute action (code depends on action type)
	virtual void Execute();

	void AddConnection::Undo();
	void AddConnection::Redo();

};