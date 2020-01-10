#ifndef _DELETE_
#define _DELETE_

#include "action.h"
#include "..\Components\Component.h"

class Delete : public Action
{
private:
	

public:
	Component* deleted;
	Delete(ApplicationManager* pApp);
	virtual ~Delete(void);
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
