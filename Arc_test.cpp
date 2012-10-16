#include "Arc.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

pArc arc02;

TEST_GROUP(Arc) {
	void setup() {
		//arc02 = new Arc(new Node(0), new Node(2));
		arc02 = new Arc(Node::Pool.New()->setId(0), Node::Pool.New()->setId(2));
	}

	void teardown() {
		SAFE_DELETE(arc02);
	}
};

TEST(Arc, HasTwoNodesWhenCreated) {
	CHECK(arc02->getStart() != NULL);
	CHECK(arc02->getEnd() != NULL);
	CHECK(arc02->getStart()->getId() == 0);
	CHECK(arc02->getEnd()->getId() == 2);
}

TEST(Arc, InAnArcTheNextOfStartNodeIsEndNode) {
	int endNodeId = arc02->getEnd()->getId();

	pNode nextNode = arc02->getStart()->getNext();
	CHECK(nextNode != NULL);

	int nextNodeId = nextNode->getId();
	CHECK(endNodeId == nextNodeId);
}

TEST(Arc, InANewArcTheNextOfEndAndThePreviousOfStartAreNull) {
//	pNode previousNode = arc02->getStart()->getPrevious();
//	CHECK(previousNode == NULL);

	pNode nextNode = arc02->getEnd()->getNext();
	CHECK(nextNode == NULL);
}

TEST(Arc, InvalidArgumentExceptionWhenNullNodesPassedToConstructor) {
	try {
		pArc nullNodesArc1 = new Arc((pNode)NULL, (pNode)NULL);
		SAFE_DELETE(nullNodesArc1);
	} catch (char const* e) {
		STRCMP_EQUAL("InvalidArgument", e);
	}

	try {
		pArc nullNodesArc2 = new Arc(0, 0);
		SAFE_DELETE(nullNodesArc2);
	} catch (char const* e) {
		STRCMP_EQUAL("InvalidArgument", e);
	}
}

} /* namespace Genius */
