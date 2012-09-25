#ifndef NODE_H_
#define NODE_H_

#include "CommonIncludes.h"

namespace Genius {

class Node {
private:
	int id;

//	Node* previous;
	Node* next;

	void init();

public:
	Node();
	Node(int id);
	virtual ~Node();

	int getId() const;
	void setId(int id);

//	Node* getPrevious();
//	void setPrevious(Node* node);

	Node* getNext();
	void setNext(Node* node);

	static const int ID_UNKNOWN = -1;
};
typedef Node* pNode;
typedef vector<pNode> Nodes;
typedef Nodes* pNodes;

} /* namespace Genius */
#endif /* NODE_H_ */
