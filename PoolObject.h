#ifndef POOLOBJECT_H_
#define POOLOBJECT_H_

#include <vector>

namespace Genius {
/*
class PoolObject {
private:
	static PoolObject* pool[100];
	static vector<PoolObject*> freeObjs;

	PoolObject() {
		for(int i=0; i<N; ++i) {
			pool[i] = new T();
			freeObjs.push_back(pool[i]);
		}
	}

public:
	static int INST;

	static PoolObject* New() {
		return PoolObject::freeObjs.pop_back();
	}

	void Delete() {
		memset(this, 0, sizeof(PoolObject));
		return PoolObject::freeObjs.push_back(this);
	}
};
*/

template <class T, int N>
class MemoryPool {
private:
	T* pool[N];
	std::vector<T*> freeObjs;

public:
	MemoryPool() {
		for(int i=0; i<N; ++i) {
			pool[i] = new T();
			freeObjs.push_back(pool[i]);
		}
	}

	T* New() {
		T* obj = freeObjs.back();
		freeObjs.pop_back();
		return obj;
	}

	void Delete(T* object) {
		memset(object, 0, sizeof(object));
		freeObjs.push_back(object);
	}
};
/*
class PoolObject
{
public:
    void* operator new(size_t uiSize)
    {
        //return (void *)buf;
        return (void*)FreeTestPool.pop_back();
    }
    void operator delete(void *p)
    {
    	//memset(this, 0, sizeof(PoolObject));
    	FreeTestPool.push_back(this);
    }
}
*/

/*
char buf[4100];  //Simple Memory Pool

class CTestClass
{
    char m_chBuf[4096];
public:
    void *operator new(unsigned int uiSize)
    {
        return (void *)buf;
        return (void*)PoolObject::freeObjs.pop_back();
    }
    void  operator delete(void *p)
    {
    }
};
*/

} /* namespace Genius */
#endif /* POOLOBJECT_H_ */
