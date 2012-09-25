#ifndef TOUR_H_
#define TOUR_H_

#include "Arc.h"

namespace Genius {

class Tour {

private:
	static int internalToursCounter;
	int id;

	pNodes nodes;
	pArcs arcs;

public:
	Tour();
	virtual ~Tour();

	int getId() const;
	int Length() const;

	bool add(pArc arc);
	bool remove(pArc arc);


};
typedef Tour* pTour;

} /* namespace Genius */
#endif /* TOUR_H_ */
