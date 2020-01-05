#ifndef _Def_MODULE_H
#define _Def_MODULE_H
#include "NamedMODULE.h"


class DefModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	DefModule(ApplicationManager* pApp);
	virtual ~DefModule(void);

	NamedModule* DNamedModule = new NamedModule(pManager); 

	//Execute action (code depends on action type)
	virtual void Execute();


};

#endif
