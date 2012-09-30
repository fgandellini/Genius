#include "MyPoolObj.h"

namespace Genius {

int MyPoolObj::InternalIdCounter = 0;

MyPoolObj::MyPoolObj() {
	this->id = MyPoolObj::InternalIdCounter;
	this->name = "myObj " + this->id;
	this->prev = NULL;
	this->next = NULL;
	MyPoolObj::InternalIdCounter++;
}

MyPoolObj::~MyPoolObj() {
}

} /* namespace Genius */
