#include "Node.h"

namespace Genius {

Node::Node(int id, double x, double y) {
	this->Id = id;
	this->X = x;
	this->Y = y;
	this->Priority = 0;
}

Node::Node(int id, double x, double y, int priority) {
	this->Id = id;
	this->X = x;
	this->Y = y;
	this->Priority = priority;
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
	double xi = this->X;
	double yi = this->Y;
	double xj = node->X;
	double yj = node->Y;

	double xx = ( (xi - xj) * (xi - xj) );
	double yy = ( (yi - yj) * (yi - yj) );
	double d = sqrt(xx + yy);

	return d;
}

} /* namespace Genius */
