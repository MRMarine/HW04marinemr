#include "Starbucks.h"

class VPEntry {
public:
	VPEntry();
	VPEntry(Entry*, double);
	Entry entry;
	double radius;
	VPEntry* inside;
	VPEntry* outside;

	VPEntry* search(Entry*);
};

void assign(VPEntry*, vector<Entry>);
// this should probably be renamed getDistance, but I've already included quite a few calls to getRadius.
double getRadius(Entry*, Entry*);

class marinemrStarbucks : public Starbucks {
public:
	VPEntry* head;
	static vector<Entry> list;
	
	marinemrStarbucks();
	~marinemrStarbucks();

	// Starbucks methods
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);

};

vector<VPEntry> entries;

