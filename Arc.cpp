#include "Arc.h"

namespace Genius {

Arc::Arc(pNode from, pNode to) {
	if (from != NULL && to != NULL) {
		this->init(from, to);
	} else {
		throw "InvalidArgument";
	}
}

Arc::Arc(int fromId, int toId) {
	if (fromId >= 0 && toId >= 0) {
		this->init(new Node(fromId), new Node(toId));
	} else {
		throw "InvalidArgument";
	}
}

void Arc::init(pNode from, pNode to) {
	this->start = from;
	this->end = to;
	this->start->setNext(this->end);
}

Arc::~Arc() {
	SAFE_DELETE(this->start);
	SAFE_DELETE(this->end);
}

pNode Arc::getStart() {
	return this->start;
}

pNode Arc::getEnd() {
	return this->end;
}

} /* namespace Genius */
