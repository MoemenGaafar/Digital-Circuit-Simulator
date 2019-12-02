#ifndef _EDIT_CONN
#define _EDIT_CONN

#include "action.h"
#include "..\Components\Connection.h"

class EditConn : public Action
{
private:

	int srcX, srcY, destX, destY;	//Points Clicked
	InputPin inp;
	OutputPin* outp;
	Component* component; //Destination component 
	GraphicsInfo* pGInfo = new GraphicsInfo(2);

public:
	EditConn(ApplicationManager* pApp);
	virtual ~EditConn(void);

	int connectPin(int x, int y); 

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
