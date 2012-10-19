#include "Tour.h"

namespace Genius {

Tour::Tour() {
}

Tour::~Tour() {
}

int Tour::Length() const {
}

Tour* Tour::Append(int node) {
}



//int Tour::internalToursCounter = 0;
//
//Tour::Tour() {
//	this->id = Tour::internalToursCounter++;
//	this->nodes = new Nodes();
//	this->arcs = new Arcs();
//}
//
//Tour::~Tour() {
//	SAFE_DELETE_VECTOR(this->nodes);
//	SAFE_DELETE_VECTOR(this->arcs);
//}

//int Tour::getId() const {
//	return this->id;
//}
//

//
//bool Tour::add(pArc arc) {
//	this->nodes->push_back(arc->getStart());
//	this->nodes->push_back(arc->getEnd());
//
//	this->arcs->push_back(arc);

//	return true;
//}
//
//bool Tour::remove(pArc arc) {
//	return true;
//}

} /* namespace Genius */
