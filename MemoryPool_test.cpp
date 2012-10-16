#include "MemoryPool.h"
#include "MemoryPoolTestClasses.h"
#include <CppUTest/TestHarness.h>

#include "CommonIncludes.h"

namespace Genius {

TEST_GROUP(MemoryPool) {
	void setup() {

	}

	void teardown() {
	}

	void CheckPoolableObjectIsNull(pPoolableObject pObj) {
		CHECK(pObj != NULL);
		CHECK(pObj->getI() == 0);
		CHECK(pObj->getS().compare("empty") == 0);
	}
};


TEST(MemoryPool, PoolShouldReturnAnInitializedInstanceOfObjAndReleaseIt) {
	pPoolableObject pObj = PoolableObject::Pool.New();
	CheckPoolableObjectIsNull(pObj);

	PoolableObject::Pool.Delete(pObj);
	CheckPoolableObjectIsNull(pObj);
}

TEST(MemoryPool, PoolShouldReinitializeInstancesWhenDeleteThem) {
	pPoolableObject pObj = PoolableObject::Pool.New();
	CheckPoolableObjectIsNull(pObj);

	pObj->setI(5);
	pObj->setS("test");
	CHECK(pObj->getI() == 5);
	CHECK(pObj->getS().compare("test") == 0);

	PoolableObject::Pool.Delete(pObj);
	CheckPoolableObjectIsNull(pObj);

	pObj = PoolableObject::Pool.New();
	CheckPoolableObjectIsNull(pObj);

	PoolableObject::Pool.Delete(pObj);
	CheckPoolableObjectIsNull(pObj);
}

/*
TEST(MemoryPool, PoolCanAllocateOnlyAGivenNumberOfInstances) {
	pPoolableObject pObjs[POOLABLE_OBJECT_POOL_INSTANCES];

	for (int i=0; i<POOLABLE_OBJECT_POOL_INSTANCES; ++i) {
		pObjs[i] = PoolableObject::Pool.New();
		CHECK(pObjs[i] != NULL);
	}

	try
	{
		pPoolableObject pObj = PoolableObject::Pool.New();
	}
	catch(exception& e) {
		STRCMP_EQUAL("MemoryPool is empty!", e.what());
	}

	for (int i=0; i<POOLABLE_OBJECT_POOL_INSTANCES; ++i) {
		PoolableObject::Pool.Delete(pObjs[i]);
		CHECK(pObjs[i] == NULL);
	}
}
*/

TEST(MemoryPool, IsFasterThanDefaultAllocation) {

	//const int N = 1;

	//MyObj* myObjs[] = new MyObj[N];
//	MyObj* myObjs[N];
//	time_t start = time(NULL);
//
//	for (int i=0; i<N; ++i) {
//		myObjs[i] = new MyObj();
//	}
//	for (int i=0; i<N; ++i) {
//		SAFE_DELETE(myObjs[i]);
//	}






//	time_t standardAllocationTime = time(NULL) - start;
//
//	start = time(NULL);
//
//	time_t poolAllocationTime = time(NULL);
//
//	CHECK(poolAllocationTime < standardAllocationTime);

}




}
