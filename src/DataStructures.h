#ifndef D_DataStructures_H
#define D_DataStructures_H

///////////////////////////////////////////////////////////////////////////////
//
//  DataStructures contiene le definizioni dei tipi di dato e delle strutture
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <assert.h>

using namespace std;

#define PI 3.14159265

#define VEHICLE 0
#define DEPOT   1
#define SITE    2
#define UNKNOWN 3

// Coordinate
typedef double Coord;
typedef vector<Coord> CoordVector;
typedef CoordVector* pCoordVector;

// Cost
typedef double Cost;
typedef vector<Cost> CostVector;
typedef CostVector* pCostVector;
#define INF_COST numeric_limits<Cost>::max()

// Profit
typedef int Profit;
typedef vector<Profit> ProfitVector;
typedef ProfitVector* pProfitVector;

// Distance
typedef double Distance;
typedef vector<Distance> DistanceVector;
typedef DistanceVector* pDistanceVector;
typedef vector< pDistanceVector > DistanceMatrix;
typedef DistanceMatrix* pDistanceMatrix;
#define INF_DISTANCE numeric_limits<Distance>::max()
#define INF_DURATION INF_DISTANCE

// Angle
typedef double Angle;

// ID
typedef int Id;
typedef Id* pId;
typedef vector<Id> IdVector;
typedef IdVector* pIdVector;
typedef vector< pIdVector > IdMatrix;
typedef IdMatrix* pIdMatrix;

// Arcs
typedef vector<bool> ArcVector;
typedef ArcVector* pArcVector;
typedef vector< pArcVector > ArcMatrix;
typedef ArcMatrix* pArcMatrix;

// Tour
//typedef vector<Id> Tour;
//typedef Tour* pTour;

// Angle
typedef int Capacity;

#endif  // D_DataStructures_H
