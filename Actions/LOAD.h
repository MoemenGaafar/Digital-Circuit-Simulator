#ifndef _LOAD_
#define _LOAD_

#include "action.h"
#include <fstream>
#include<sstream>
#include <iomanip>
using namespace std;
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

class Load : public Action
{
public:
	Load(ApplicationManager* pApp);
	virtual ~Load(void);
	ActionType Type = LOAD;
	string name;
	Action* LSave; 
	//Execute action (code depends on action type)
	virtual void Execute();

	

};

#endif

