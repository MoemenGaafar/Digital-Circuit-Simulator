#ifndef _Def_MODULE_H
#define _Def_MODULE_H

#include "action.h"

class DefModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	DefModule(ApplicationManager* pApp);
	virtual ~DefModule(void);
	//Execute action (code depends on action type)
	//virtual void Execute();


};

#endif
