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

	string ToString();

	operator int();

	int Compare(Node* node) const;
};
typedef Node* pNode;

} /* namespace Genius */
#endif /* NODE_H_ */
