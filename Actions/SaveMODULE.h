#ifndef _Save_MODULE_H
#define _Save_MODULE_H

#include "action.h"

class SaveModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	SaveModule(ApplicationManager* pApp);
	virtual ~SaveModule(void);
	//Execute action (code depends on action type)
	//virtual void Execute();


};

#endif
