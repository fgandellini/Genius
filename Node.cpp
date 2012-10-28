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

string Node::ToString() {
	ostringstream convert;
	convert << this->Id;
	return convert.str();
}

int Node::Compare(Node* node) const {
	return (this->Id == node->Id) ? 0 : ((this->Id > node->Id) ? 1 : -1);
}

} /* namespace Genius */
