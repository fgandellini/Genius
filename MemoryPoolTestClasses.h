#ifndef MEMORYPOOLTESTCLASSES_H_
#define MEMORYPOOLTESTCLASSES_H_

#include "CommonIncludes.h"

namespace Genius {

#define POOLABLE_OBJECT_POOL_INSTANCES 10
class PoolableObject : public IPoolable {
private:
	int i;
	string s;
public:
	virtual void Init(void) { this->i = 0; this->s = "empty"; };
	static MemoryPool<PoolableObject, POOLABLE_OBJECT_POOL_INSTANCES> Pool;

	int getI() const { return i; }
	void setI(int i) { this->i = i; }
	const string& getS() const { return s; }
	void setS(const string& s) { this->s = s; }

	~PoolableObject() { this->s.clear(); };
};
typedef PoolableObject* pPoolableObject;
MemoryPool<PoolableObject, POOLABLE_OBJECT_POOL_INSTANCES> PoolableObject::Pool;

class NotPoolableObject {
private:
	int i;
	string s;
public:
	int getI() const { return i; }
	void setI(int i) { this->i = i; }
	const string& getS() const { return s; }
	void setS(const string& s) { this->s = s; }
};
typedef NotPoolableObject* pNotPoolableObject;

} /* namespace Genius */
#endif /* MEMORYPOOLTESTCLASSES_H_ */
