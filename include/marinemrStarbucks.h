#pragma once
#include "Starbucks.h"
#include <vector>

class VPEntry {
public:
	VPEntry();
	//~VPEntry();
	VPEntry(Entry*, double);
	Entry entry;
	double radius;
	VPEntry* inside;
	VPEntry* outside;

	VPEntry* search(Entry*);
};


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
	
	marinemrStarbucks();
	~marinemrStarbucks();

	// Starbucks methods
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	void assign(VPEntry*);

};