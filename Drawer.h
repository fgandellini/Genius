#ifndef DRAWER_H_
#define DRAWER_H_

#include "CommonIncludes.h"
#include "Node.h"

namespace Genius {

class Drawer {
public:
	Drawer();
	virtual ~Drawer();

	Draw(pInstance instance);
};
typedef Drawer* pDrawer;

} /* namespace Genius */
#endif /* DRAWER_H_ */
