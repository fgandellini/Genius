/*
 * Node_test.cpp
 *
 *  Created on: 24/set/2012
 *      Author: fede
 */

#include "Node.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

pNode unknownNode;
pNode node7;

TEST_GROUP(Node) {
	void setup() {
		unknownNode = new Node();
		node7 = new Node(7);
	}

	void teardown() {
		delete unknownNode;
		delete node7;
	}
};

TEST(Node, WhenCreatedIdIsUnknown) {
	CHECK(unknownNode->getId() == Node::ID_UNKNOWN);
}

TEST(Node, WhenCreatedPreviousAndNextAreNull) {
	CHECK(unknownNode->getNext() == NULL);
	CHECK(node7->getNext() == NULL);
//	CHECK(unknownNode->getPrevious() == NULL);
//	CHECK(node7->getPrevious() == NULL);
}

TEST(Node, CanSetAnId) {
	unknownNode->setId(4);
	CHECK(unknownNode->getId() == 4);

	CHECK(node7->getId() == 7);
}

TEST(Node, NodePool) {

	time_t start = time(NULL);
	for (long int i=0; i<100000000; ++i) {
		pNode myNode = new Node();
		delete myNode;
	}
	time_t standardAllocationTime = time(NULL) - start;

	start = time(NULL);
	for (long int i=0; i<100000000; ++i) {
		pNode myNode = Node::Pool.New();
		Node::Pool.Delete(myNode);
	}
	time_t poolAllocationTime = time(NULL) - start;

	CHECK(poolAllocationTime < standardAllocationTime);
}

} /* namespace Genius */
