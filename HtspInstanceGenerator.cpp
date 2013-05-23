#include "HtspInstanceGenerator.h"

namespace Genius {

HtspInstanceGenerator::HtspInstanceGenerator() {
}

HtspInstanceGenerator::~HtspInstanceGenerator() {
}

void HtspInstanceGenerator::CreateInstance(string filePath, int dimension, int P, int k) {
	FILE* htspFile = fopen(filePath.c_str(), "w");
	assert(htspFile != NULL);

	assert(dimension >= P * 4);

	fprintf(htspFile, "P: %d\n", P);
	fprintf(htspFile, "K: %d\n", k);

	fprintf(htspFile, "D: %d\n", dimension);

	int nodesPerLevel = (int)floor((double)dimension / (double)P);

	int currentCounter = nodesPerLevel;
	fprintf(htspFile, "NODE_COORD_SECTION\n");
	for (int n=0; n<dimension; n++) {

		fprintf(htspFile,
				"%d %d %.2f %.2f\n",
				n+1, HtspInstanceGenerator::GetLevel(n, nodesPerLevel, P),
				RandomNumberGenerator::GetNumber() * 10.0,
				RandomNumberGenerator::GetNumber() * 10.0);
	}

	fclose(htspFile);
}

int HtspInstanceGenerator::GetLevel(int index, int nodesPerLevel, int P) {
	int calculatedLevel = floor( (double)index / (double)nodesPerLevel ) + 1;
	return (calculatedLevel <= P) ? calculatedLevel : P;
}

} /* namespace Genius */
