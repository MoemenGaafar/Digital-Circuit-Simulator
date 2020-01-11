#ifndef _CUT_
#define _CUT_

#include "action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"
#include "Label.h"

class Cut : public Action
{
private:

public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);
	Component* Cutitm; //To be used in "Cut" execution

	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
