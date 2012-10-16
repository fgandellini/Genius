#ifndef POOLOBJECT_H_
#define POOLOBJECT_H_

#include <string>
#include <vector>
#include <exception>
#include <typeinfo>
using namespace std;

namespace Genius {

class MemoryPoolEmptyException : public exception {
	virtual const char* what() const throw() { return "MemoryPool is empty!"; }
};

class IPoolable {
public:
	virtual void Init(void) = 0;
	virtual ~IPoolable() {};
};
typedef IPoolable* pIPoolable;

template <class T, int N>
class MemoryPool {
private:
	T* pool[N];
	vector<T*> freeObjs;

public:
	MemoryPool(void) {
		for(int i=0; i<N; ++i) {
			pool[i] = new T();
			dynamic_cast<pIPoolable>(pool[i])->Init();
			freeObjs.push_back(pool[i]);
		}
	}

	T* New(void) {
		T* obj = NULL;
		if (!freeObjs.empty()) {
			obj = freeObjs.back();
			freeObjs.pop_back();
		} else {
			throw MemoryPoolEmptyException();
		}
		return obj;
	}

	void Delete(T* object) {
		dynamic_cast<pIPoolable>(object)->Init();
		freeObjs.push_back((T*)object);
	}
};

} /* namespace Genius */
#endif /* POOLOBJECT_H_ */
