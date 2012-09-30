#include "MyObj.h"

namespace Genius {

int MyObj::InternalIdCounter = 0;

MyObj::MyObj() {
	this->id = MyObj::InternalIdCounter;
	this->name = "myObj " + this->id;
	this->prev = NULL;
	this->next = NULL;
	MyObj::InternalIdCounter++;
}

MyObj::~MyObj() {
}

} /* namespace Genius */
