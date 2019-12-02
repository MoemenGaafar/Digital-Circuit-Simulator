#ifndef _CUT_
#define _CUT_

#include "action.h"
#include "..\Components\Component.h"

class Cut : public Action
{
private:


public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
