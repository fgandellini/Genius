#include "TourFactory.h"

namespace Genius {

TourFactory::TourFactory() {
	this->instance = NULL;

	// inizializza un set di tour disponibili da usare (?)

	// oppure inizializza una lista vuota di tour
}

TourFactory::TourFactory(pInstance instance) {
	this->instance = NULL;
	this->SetInstance(instance);

	// inizializza un set di tour disponibili da usare (?)

	// oppure inizializza una lista vuota di tour
}


TourFactory::~TourFactory() {

	// distrugge tutti i tour generati con questa factory
}

pTourFactory TourFactory::SetInstance(pInstance instance) {
	this->instance = instance;
	return this;
}

pTour TourFactory::GetTour() {
	return new Tour(this->instance);

	// ritorna il primo tour libero in lista o
	// aggiunge il nuovo tour alla lista
}

} /* namespace Genius */
