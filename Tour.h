#ifndef TOUR_H_
#define TOUR_H_

#include "CommonIncludes.h"
#include "Instance.h"
#include "Node.h"

namespace Genius {

typedef struct {
	pNode vi;
	pNode vj;
	pNode vk;
	bool tourMustBeReversed;
	double distance;
} InsertTypeIParams;

typedef struct {
	pNode vi;
	pNode vj;
	pNode vk;
	pNode vl;
	bool tourMustBeReversed;
	double distance;
} InsertTypeIIParams;

typedef struct {
	pNode vj;
	pNode vk;
	bool tourMustBeReversed;
	double distance;
} RemoveTypeIParams;

typedef struct {
	pNode vj;
	pNode vk;
	pNode vl;
	bool tourMustBeReversed;
	double distance;
} RemoveTypeIIParams;

typedef vector<pNodeVector> Neighborhoods;
typedef Neighborhoods* pNeighborhoods;

class Tour {
private:
	int Id;
	pInstance instance;

	pNeighborhoods neighborhoods;
	void InitNeighborhoods();
	void ClearNeighborhoods();
	void UpdateNeighborhoods();
	void DeleteNeighborhoods();

public:
	data::clist<pNode> nodes;

	Tour(pInstance instance);
	virtual ~Tour();
	Tour* Clone();

	pInstance GetInstance();

	int Length() const;

	void Append(pNode node);
	void GoTo(pNode node);
	bool Contains(pNode node);

	void ResetIterator();
	pNode Current();
	pNode Next();
	pNode Next(pNode node);
	pNode Previous();
	pNode Previous(pNode node);

	pNode Get(int position);
	void DeleteAt(int position);

	int GetIndex(pNode node);
	bool IsBetween(pNode x, pNode from, pNode to);

	void Reverse();

	bool CheckInsertTypeIConditions(pNode v, pNode vi, pNode vj, pNode vk, bool useAssert);
	bool CheckInsertTypeIIConditions(pNode v, pNode vi, pNode vj, pNode vk, pNode vl, bool useAssert);
	bool CheckRemoveTypeIConditions(pNode vi, pNode vj, pNode vk, bool useAssert);
	bool CheckRemoveTypeIIConditions(pNode vi, pNode vj, pNode vk, pNode vl, bool useAssert);

	double EvaluateInsertTypeI(pNode v, pNode vi, pNode vj, pNode vk);
	double EvaluateInsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl);
	double EvaluateRemoveTypeI(pNode vi, pNode vj, pNode vk);
	double EvaluateRemoveTypeII(pNode vi, pNode vj, pNode vk, pNode vl);

	data::clist<pNode> GetSubtour(pNode from, pNode to);
	data::clist<pNode> GetReversedSubtour(pNode from, pNode to);
	void AddSubtour(data::clist<pNode> subtour, data::clist<pNode> &result);

	void InsertTypeI(pNode v, pNode vi, pNode vj, pNode vk);
	void InsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl);
	void RemoveTypeI(pNode vi, pNode vj, pNode vk);
	void RemoveTypeII(pNode vi, pNode vj, pNode vk, pNode vl);

	double TotalDistance();

	pNodeVector GetNeighborhood(pNode node);
	bool IsNodeInNeighborhood(pNode node, pNodeVector neighborhood);
	void PrintNeighborhoods();

	string ToString();
	string TourToString(data::clist<pNode> &tourToPrint);

	bool IsEqualTo(Tour* tourToCompare);

	bool ContainsArc(pNode from, pNode to);
};
typedef Tour* pTour;
typedef vector<pTour> TourVector;
typedef TourVector* pTourVector;

} /* namespace Genius */
#endif /* TOUR_H_ */
