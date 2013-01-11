#ifndef DRAWER_H_
#define DRAWER_H_

#include "CommonIncludes.h"
#include "Instance.h"
#include "Tour.h"

namespace Genius {

class Drawer {
private:
	string ImagesDirPath;
	double border;

	Point GetOrigin(pInstance instance);

	double GetMaxX(pInstance instance);
	double GetMaxY(pInstance instance);
	double GetMinX(pInstance instance);
	double GetMinY(pInstance instance);
	double GetImageWidth(pInstance instance);
	double GetImageHeight(pInstance instance);
	Rectangle DrawNode(pNode node, Color color);
	Text DrawNodeId(pNode node, Color color);
	void DrawNodes(pInstance instance, Document* doc);

	Polyline DrawTour(pTour tour);

	Document CreateDocument(pInstance instance, string name);
	void SaveDocument(Document document);


public:
	Drawer();
	virtual ~Drawer();

	void Draw(pInstance instance, string name);
	void Draw(pTour tour, string name);
	void Draw(pTour tour, string name, pNode nodeToHighlight);
};
typedef Drawer* pDrawer;

} /* namespace Genius */
#endif /* DRAWER_H_ */
