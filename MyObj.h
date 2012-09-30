#ifndef MYOBJ_H_
#define MYOBJ_H_

#include "CommonIncludes.h"

namespace Genius {

class MyObj {
private:
	static int InternalIdCounter;

	int id;
	string name;
	MyObj* prev;
	MyObj* next;

public:
	MyObj();
	virtual ~MyObj();
};
typedef MyObj* pMyObj;

} /* namespace Genius */
#endif /* MYOBJ_H_ */
