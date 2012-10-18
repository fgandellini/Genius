#ifndef TOUR_H_
#define TOUR_H_

#include "CommonIncludes.h"
#include <boost/circular_buffer.hpp>

namespace Genius {

class Tour {

private:
	int id;
	boost::circular_buffer<int> nodes;

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
