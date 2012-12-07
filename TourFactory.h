#ifndef TOURFACTORY_H_
#define TOURFACTORY_H_

#include "CommonIncludes.h"
#include "Tour.h"

namespace Genius {

class TourFactory {
private:
	pInstance instance;

public:
	TourFactory();
	TourFactory(pInstance instance);
	virtual ~TourFactory();

	TourFactory* SetInstance(pInstance instance);
	pTour GetTour();
};
typedef TourFactory* pTourFactory;

} /* namespace Genius */
#endif /* TOURFACTORY_H_ */
