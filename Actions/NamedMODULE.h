#ifndef _Named_MODULE_H
#define _Named_MODULE_H

#include "action.h"

class NamedModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	NamedModule(ApplicationManager* pApp);
	virtual ~NamedModule(void);
	//Execute action (code depends on action type)
	//virtual void Execute();


};

#endif
