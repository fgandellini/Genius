#ifndef TOUR_H_
#define TOUR_H_

#include "CommonIncludes.h"

namespace Genius {

class Tour {

private:
	int id;

public:

	Tour();
	virtual ~Tour();

	int Length() const;
	Tour* Append(int node);

	//int getId() const;

	//bool add(pArc arc);
	//bool remove(pArc arc);


};
typedef Tour* pTour;

} /* namespace Genius */
#endif /* TOUR_H_ */
