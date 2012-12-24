#ifndef NODE_H_
#define NODE_H_

#include "CommonIncludes.h"

namespace Genius {

class Node {

//	friend bool operator==(const Node &first, const Node &second);
//	friend bool operator!=(const Node &first, const Node &second);

public:
	int Id;
	double X;
	double Y;

	Node(int id, double x, double y);
	virtual ~Node();

    //Node* Clone();

	string ToString();

	//operator int();

	int Compare(Node* node) const;
	double DistanceFrom(Node* node);
};
typedef Node* pNode;

typedef vector<pNode> NodeVector;
typedef NodeVector* pNodeVector;

} /* namespace Genius */
#endif /* NODE_H_ */
