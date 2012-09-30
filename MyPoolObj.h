#ifndef MYPOOLOBJ_H_
#define MYPOOLOBJ_H_

#include "PoolObject.h"
#include "CommonIncludes.h"

namespace Genius {

class MyPoolObj 	{
private:
	static int InternalIdCounter;

	int id;
	string name;
	MyPoolObj* prev;
	MyPoolObj* next;
public:

	static MyPoolObj* New();

	MyPoolObj();
	virtual ~MyPoolObj();
};
typedef MyPoolObj* pMyPoolObj;

} /* namespace Genius */
#endif /* MYPOOLOBJ_H_ */
