#include "Node.h"

namespace Genius {

//bool operator==(const Node &first, const Node &second) {
//	return first.Id == second.Id;
//}
//
//bool operator!=(const Node &first, const Node &second) {
//	return first.Id != second.Id;
//}

Node::Node(int id, double x, double y) {
	this->Id = id;
	this->X = x;
	this->Y = y;
}

Node::~Node() {

}

//pNode Node::Clone() {
//	return new Node(this->Id, this->X, this->Y);
//}

string Node::ToString() {
	ostringstream convert;
	convert << this->Id;
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
