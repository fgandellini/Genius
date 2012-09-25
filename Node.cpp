#include "Node.h"

namespace Genius {

Node::Node() {
	this->init();
}

Node::Node(int id) {
	this->init();
	this->id = id;
}

void Node::init() {
	this->id = ID_UNKNOWN;
//	this->previous = NULL;
	this->next = NULL;
}

Node::~Node() {
}

int Node::getId() const {
	return this->id;
}

void Node::setId(int id) {
	this->id = id;
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
