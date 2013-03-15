#ifndef NODE_H_
#define NODE_H_

#include "CommonIncludes.h"

namespace Genius {

class Node {

public:
	int Id;
	double X;
	double Y;

	int Priority;

	Node(int id, double x, double y);
	virtual ~Node();

	string ToString();

	int Compare(Node* node) const;
	double DistanceFrom(Node* node);
};
typedef Node* pNode;

typedef vector<pNode> NodeVector;
typedef NodeVector* pNodeVector;

} /* namespace Genius */
#endif /* NODE_H_ */
