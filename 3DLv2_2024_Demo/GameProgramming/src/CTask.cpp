#include "CTask.h"
#include "CTaskManager.h"

CTask::CTask()
	: mpNext(nullptr), mpPrev(nullptr), mEnabled(true) //, mPriority(0)
{
	//CTaskManager::Instance()->Add(this);
}

CTask::~CTask()
{
	//CTaskManager::Instance()->Remove(this);
}
