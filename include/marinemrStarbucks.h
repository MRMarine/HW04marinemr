#pragma once
#include "Starbucks.h"
#include <vector>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

class VPEntry {
public:
	VPEntry();
	//~VPEntry();
	VPEntry(Entry*, double);
	Entry* entry;
	double radius;
	VPEntry* inside;
	VPEntry* outside;

	VPEntry* search(Entry*);
};

void drawEntry(VPEntry *);

// this should probably be renamed getDistance, but I've already included quite a few calls to getRadius.
double getRadius(Entry*, Entry*);

// allows me to remove an Entry without calling deconstructor (which doesn't exist)
//template <class T>
void remove(vector<Entry>* vect, int x);

class marinemrStarbucks : public Starbucks {
public:
	VPEntry* head;
	vector<Entry> list;
	//Arr list;
	int size;
	
	marinemrStarbucks();
	~marinemrStarbucks();

	VPEntry* insert(Entry*, VPEntry*, double);

	// Starbucks methods
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);

	void assign(VPEntry*);
};

class Census{
public:
	int state, county, track, block, population;
	double x, y;
};