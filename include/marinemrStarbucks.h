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
double getRadius(Entry*, Entry*);

class marinemrStarbucks : public Starbucks {
public:
	VPEntry* head;
	static vector<Entry> list;
	static vector<VPEntry> entries;

	marinemrStarbucks();
	~marinemrStarbucks();

	VPEntry* getNearest(VPEntry*, Entry*);

	// Starbucks methods
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);

};

