#include "TourFactory.h"

namespace Genius {

TourFactory::TourFactory() {
	this->instance = NULL;

	// inizializza un set di tour disponibili da usare (?)

	// oppure inizializza una lista vuota di tour
}

TourFactory::TourFactory(pInstance instance) {
	this->SetInstance(instance);

	// inizializza un set di tour disponibili da usare (?)

	// oppure inizializza una lista vuota di tour
}


TourFactory::~TourFactory() {

	// distrugge tutti i tour generati con questa factory
}

pTourFactory TourFactory::SetInstance(pInstance instance) {
	TourFactory::instance = instance;
	return this;
}

pTour TourFactory::GetTour() {
	return new Tour(TourFactory::instance);

	// ritorna il primo tour libero in lista o
	// aggiunge il nuovo tour alla lista
}

} /* namespace Genius */
