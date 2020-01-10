#ifndef _CUT_
#define _CUT_

#include "action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include "..\components\NAND2.h"
#include "..\components\AND2.h"
#include "..\components\LED.h"
#include "..\components\Switch.h"
#include "..\Components\INV.h"
#include "..\Components\NOR2.h"
#include "..\Components\OR2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\XOR2.h"

class Cut : public Action
{
private:

public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);
	Component* Cutitm;
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
