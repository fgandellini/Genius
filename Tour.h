#ifndef TOUR_H_
#define TOUR_H_

#include "CommonIncludes.h"
#include "Node.h"

namespace Genius {

class Tour {
private:
	int Id;

public:
	data::clist<pNode> nodes;

	Tour();
	virtual ~Tour();

	int Length() const;

	void Append(pNode node);
	void GoTo(pNode node);

	pNode Current();
	pNode Next();
	pNode Next(pNode node);
	pNode Previous();
	pNode Previous(pNode node);

	void DeleteAt(int position);

	int GetIndex(pNode node);
	bool IsBetween(pNode x, pNode from, pNode to);

	data::clist<pNode> GetSubtour(pNode from, pNode to);
	data::clist<pNode> GetReversedSubtour(pNode from, pNode to);
	void AddSubtour(data::clist<pNode> subtour, data::clist<pNode> &result);

	double EvaluateInsertTypeI(pNode v, pNode vi, pNode vj, pNode vk);
	double EvaluateInsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl);

	void InsertTypeI(pNode v, pNode vi, pNode vj, pNode vk);
	void InsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl);

	double CalcDistance(pNode first, pNode second);
	double TotalDistance();

	list<pNode> GetNodesByDistanceFrom(pNode referenceNode);
	void BuildNeighborhoods(int size);

	string ToString();
	string TourToString(data::clist<pNode> &tourToPrint);
};
typedef Tour* pTour;

} /* namespace Genius */
#endif /* TOUR_H_ */
