#include"Global.h"
#include "Memory.h"


Memory* GMemory = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GMemory = new Memory();
	};
	~CoreGlobal()
	{
		delete GMemory;	
	};

}GCoreGlobal;