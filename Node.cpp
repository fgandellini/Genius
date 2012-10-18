#include "Node.h"

namespace Genius {

Node::Node() {
	this->Init(ID_UNKNOWN);
}

Node::Node(int id) {
	this->Init(id);
}

Node::~Node() {
}

void Node::Init(int id) {
	this->setPrevious(NULL);
	this->setNext(NULL);
	this->setId(id);
}

int Node::getId() const {
	return this->id;
}

pNode Node::setId(int id) {
	this->id = id;
	return this;
}

pNode Node::getPrevious() {
	return this->previous;
}

void Node::setPrevious(pNode node) {
	this->previous = node;
}

pNode Node::getNext() {
	return this->next;
}

void Node::setNext(pNode node) {
	this->next = node;
}

} /* namespace Genius */
