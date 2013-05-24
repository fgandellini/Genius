#include "Node.h"
#include "Instance.h"

namespace Genius {

Node::Node(int id, double x, double y) {
	this->Id = id;
	this->X = x;
	this->Y = y;
	this->Priority = 0;
	this->Instance = NULL;
}

Node::Node(int id, double x, double y, int priority) {
	this->Id = id;
	this->X = x;
	this->Y = y;
	this->Priority = priority;
	this->Instance = NULL;
}

Node::~Node() {
}

string Node::ToString() {
	ostringstream convert;
	convert << this->Id;

	if (this->Priority != 0) {
		convert << "p" << this->Priority;
	}

	return convert.str();
}

int Node::Compare(Node* node) const {
	return (this->Id == node->Id) ? 0 : ((this->Id > node->Id) ? 1 : -1);
}

double Node::DistanceFrom(Node* node) {
//	double d;

//	if (this->Instance != NULL) {
//		pInstance instance = (pInstance)this->Instance;
//		d = instance->Distances[this->Id - 1][node->Id - 1];
//	} else {
//		double xi = this->X;
//		double yi = this->Y;
//		double xj = node->X;
//		double yj = node->Y;
//
//		double xx = ( (xi - xj) * (xi - xj) );
//		double yy = ( (yi - yj) * (yi - yj) );
//		d = sqrt(xx + yy);
//	}

//	return d;

	return ((pInstance)this->Instance)->Distances[this->Id - 1][node->Id - 1];
}

Node* Node::Clone() {
	pNode clonedNode = new Node(this->Id, this->X, this->Y, this->Priority);
	clonedNode->Instance = this->Instance;
	return clonedNode;
}

} /* namespace Genius */
