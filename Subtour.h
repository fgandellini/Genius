#ifndef SUBTOUR_H_
#define SUBTOUR_H_

#include "CommonIncludes.h"
#include "InstanceLoader.h"

namespace Genius {

class Subtour {
public:
	int priorityRangeBegin;
	int priorityRangeEnd;
	pTour tour;
	pArcVector candidateArcs;

	Subtour();
	~Subtour();

	void Print();
	void PrintTour();
};
typedef Subtour* pSubtour;
typedef vector<pSubtour> SubtourVector;
typedef SubtourVector* pSubtourVector;

} /* namespace Genius */
#endif /* SUBTOUR_H_ */
