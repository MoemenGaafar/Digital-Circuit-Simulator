#ifndef _PASTE_
#define _PASTE_

#include "action.h"
#include "..\Components\Component.h"

class Paste : public Action
{
private:


public:
	Paste(ApplicationManager* pApp);
	virtual ~Paste(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
