/*
 * Main.cpp
 *
 *  Created on: 24/giu/2011
 *      Author: Federico Gandellini
 */
#include "DataStructures.h"

void PressKey(void)
{
	cout << "\nPress any key to continue...";
	while (!getc(stdin)) { }
}

int main(int argc, char** argv) {
	cout << "Genius" << endl;
}