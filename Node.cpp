#include "Node.h"

namespace Genius {

MemoryPool<Node, 100> Node::Pool;

Node::Node() {
}

void Node::Init(void) {
	this->setId(ID_UNKNOWN);
//	this->previous = NULL;
	this->setNext(NULL);
}

Node::~Node() {
}

int Node::getId() const {
	return this->id;
}

pNode Node::setId(int id) {
	this->id = id;
	return this;
}

//pNode Node::getPrevious() {
//	return this->previous;
//}
//
//void Node::setPrevious(pNode node) {
//	this->previous = node;
//}

pNode Node::getNext() {
	return this->next;
}

void Node::setNext(pNode node) {
	this->next = node;
}

} /* namespace Genius */
