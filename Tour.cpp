#include "Tour.h"

namespace Genius {

int Tour::internalToursCounter = 0;

Tour::Tour() {
	this->id = Tour::internalToursCounter++;
	this->nodes = new Nodes();
	this->arcs = new Arcs();
}

Tour::~Tour() {
	SAFE_DELETE_VECTOR(this->nodes);
	SAFE_DELETE_VECTOR(this->arcs);
}

int Tour::getId() const {
	return this->id;
}

int Tour::Length() const {
	return this->nodes->size();
}

bool Tour::add(pArc arc) {
//	this->nodes->push_back(arc->getStart());
//	this->nodes->push_back(arc->getEnd());
//
//	this->arcs->push_back(arc);

	return true;
}

bool Tour::remove(pArc arc) {
	return true;
}

} /* namespace Genius */
