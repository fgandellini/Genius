#include "Drawer.h"

using namespace svg;

namespace Genius {

Drawer::Drawer() {
	this->ImagesDirPath = "/home/fede/workspace/Genius/Images";
	this->border = 10.0;
}

Drawer::~Drawer() {
}

void Drawer::Draw(pInstance instance, string name) {
	Document doc = this->CreateDocument(instance, "instance");
	this->DrawNodes(instance, &doc);
	this->SaveDocument(doc);
}

void Drawer::Draw(pTour tour, string name) {
	this->Draw(tour, name, NULL);
}

void Drawer::Draw(pTour tour, string name, pNode nodeToHighlight) {
	pInstance instance = tour->GetInstance();
	Document doc = this->CreateDocument(instance, name);

	Font f(2, "Verdana");
	svg::Color c = svg::Color::Black;
	Point p = this->GetOrigin(instance);
	p.x += 2.0;

	p.y += this->GetImageHeight(instance) + border;
	doc << Text(p, instance->Name, c, f);
	p.y += 3.0; doc << Text(p, name, c, f);
	p.y += 3.0; doc << Text(p, tour->ToString(), c, f);
	p.y += 3.0; doc << Text(p, Utils::ToString(tour->TotalDistance()), c, f);

	doc << this->DrawTour(tour);
	this->DrawNodes(instance, &doc);

	for (int n=0; n<tour->Length(); n++) {
		pNode node = tour->Get(n);
		doc << this->DrawNode(node, Color::DarkGray);
		doc << this->DrawNodeId(node, Color::White);
	}

	if (nodeToHighlight != NULL) {
		doc << this->DrawNode(nodeToHighlight, Color::Red);
		doc << this->DrawNodeId(nodeToHighlight, Color::White);
	}

	this->SaveDocument(doc);
}

Point Drawer::GetOrigin(pInstance instance) {
	return Point(
		this->GetMinX(instance) - (border/2.0),
		this->GetMinY(instance) - (border/2.0));
}

Document Drawer::CreateDocument(pInstance instance, string name) {

	Dimensions dimensions(
		this->GetImageWidth(instance) + border,
		this->GetImageHeight(instance) + border + 20.0);

	Point originOffset(
		- this->GetMinX(instance) + (border/2.0),
		- this->GetMinY(instance) + (border/2.0));

	string instanceDir = this->ImagesDirPath + "/" + instance->Name;
	mkdir(instanceDir.c_str(), 0775);

	Document document(
		instanceDir + "/" + name + ".svg",
		Layout(dimensions, Layout::TopLeft, 1.0, originOffset));
	document << Rectangle(this->GetOrigin(instance),
		dimensions.width,dimensions.height,svg::Color::White);

	return document;
}

void Drawer::SaveDocument(Document document) {
	document.save();
}

Polyline Drawer::DrawTour(pTour tour) {
	Polyline t(Stroke(0.5, svg::Color::Black));
//	Polyline t(Stroke(5, svg::Color::Black));

	for (int n=0; n<tour->Length(); n++) {
		t << Point(tour->Get(n)->drawableX, tour->Get(n)->drawableY);
	}
	t << Point(tour->Get(0)->drawableX, tour->Get(0)->drawableY);

	return t;
}

double Drawer::GetImageWidth(pInstance instance) {
	return this->GetMaxX(instance) - this->GetMinX(instance);
}

double Drawer::GetImageHeight(pInstance instance) {
	return this->GetMaxY(instance) - this->GetMinY(instance);
}

Rectangle Drawer::DrawNode(pNode node, Color color) {
	double size = 2.0;
//	double size = 20.0;
	return Rectangle(
		Point(node->drawableX - (size/2.0), node->drawableY - (size/2.0)),
		size, size,
		color);
}

Text Drawer::DrawNodeId(pNode node, Color color) {
	double size = 2.0;
//	double size = 20.0;
	return Text(Point(node->drawableX - (size/2.0), node->drawableY),
			Utils::ToString(node->Id), color, Font((size/2.0), "Verdana"));
}

void Drawer::DrawNodes(pInstance instance, Document* doc) {
	for (int n=0; n<instance->Size(); n++) {
		pNode node = instance->GetNode(n);
		*doc << this->DrawNode(node, Color::LightGray);
		*doc << this->DrawNodeId(instance->GetNode(n), Color::Black);
	}
}

double Drawer::GetMaxX(pInstance instance) {
	double maxX = numeric_limits<double>::min();
	int size = instance->Size();
	for (int n=0; n<size; n++) {
		maxX = max(instance->GetNode(n)->drawableX, maxX);
	}
	return maxX;
}

double Drawer::GetMaxY(pInstance instance) {
	double maxY = numeric_limits<double>::min();
	int size = instance->Size();
	for (int n=0; n<size; n++) {
		maxY = max(instance->GetNode(n)->drawableY, maxY);
	}
	return maxY;
}

double Drawer::GetMinX(pInstance instance) {
	double minX = numeric_limits<double>::max();
	int size = instance->Size();
	for (int n=0; n<size; n++) {
		minX = min(instance->GetNode(n)->drawableX, minX);
	}
	return minX;
}

double Drawer::GetMinY(pInstance instance) {
	double minY = numeric_limits<double>::max();
	int size = instance->Size();
	for (int n=0; n<size; n++) {
		minY = min(instance->GetNode(n)->drawableY, minY);
	}
	return minY;
}

} /* namespace Genius */
