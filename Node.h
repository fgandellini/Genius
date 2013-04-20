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
	Node(int id, double x, double y, int priority);
	virtual ~Node();

	string ToString();

	int Compare(Node* node) const;
	double DistanceFrom(Node* node);
};
typedef Node* pNode;

typedef vector<pNode> NodeVector;
typedef NodeVector* pNodeVector;
typedef struct _Arc {
	pNode From;
	pNode To;
} Arc;
typedef Arc* pArc;

} /* namespace Genius */
#endif /* NODE_H_ */
