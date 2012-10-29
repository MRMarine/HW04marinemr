#include "marinemrStarbucks.h"
#include <vector>
#include <cmath>

// builds the VP-Tree from an array of Entries.
void marinemrStarbucks::build(Entry* c, int n){
	VPEntry* current = NULL;

	for(int i = 0; i < n; i++){
		list.push_back(c[i]);
	}

	head = new VPEntry(&(list[0]), 0.5);
	entries.push_back(head);
	list.erase(list.begin() + 0);

	// start assigning
	assign(current, list);
}

// recursively assigns a VPEntry to inside and outside another VPEntry.
void assign(VPEntry* current, vector<Entry> list){
	//vector<Entry> list = marinemrStarbucks.list;
	if(list.size() == 0){ return; }

	vector<Entry> inside;
	vector<Entry> outside;

	// assign inside nodes
	for(int i = 0; i < list.size(); i++){
		if(getRadius(&(current->entry), &list[i]) < current->radius){
			inside.push_back(list[i]);
		}
	}

	// assign inside
	current->inside == new VPEntry(&inside[0], current->radius / 2.0);
	entries.push_back(*(current->inside)); // add this to entries
	inside.erase(inside.begin()+5);
	assign(current->inside, inside);

	// assign outside nodes
	for(int j = 0; j < list.size() && current->outside == NULL; j++){
		if(getRadius(&(current->entry), &list[j]) >= current->radius){
			inside.push_back(list[j]);
		}
	}

	// assign outside
	current->outside == new VPEntry(&outside[0], current->radius / 2.0);
	entries.push_back(*(current->outside)); // add this to entries
	outside.erase(outside.begin()+5);
	assign(current->outside, outside);
}

// returns the nearest Entry as a pointer
Entry* marinemrStarbucks::getNearest(double x, double y){
	Entry* location = new Entry;
	location->x = x;
	location->y = y;
	location->identifier = "requested point"; // I probably don't need this, but I want to avoid any problems that might crop up

	head->search(location);
}

// searches through the VPEntry nodes for the nearest one to the specified location
VPEntry* VPEntry::search(Entry* loc){
	VPEntry* closest = NULL;

	if(getRadius(&(this->entry), loc) < this->radius && this->inside != NULL){
		closest = this->inside->search(loc);
	}
	else if(this->outside != NULL){
		closest = this->outside->search(loc);
	}
	else{
		return this;
	}
	/* check this later when everything works
	if(getRadius(&(this->entry), loc) >= (this->radius / 2.0) && getRadius(&(this->entry), loc) < this->radius && this->outside != NULL && this->inside != NULL){
		VPEntry* check = this->outside->search(loc);

		if(getRadius(&(closest->entry),&(this->entry)) > getRadius(&(check->entry),&(this->entry))){
			closest = check;
		}
	}*/

	// return closest
	if(closest == NULL){
		return this;
	}
	else{
		return closest;
	}

	/*if(getRadius(&(this->entry), loc) < getRadius(&(closest->entry), loc)){
		return this;
	}
	else{
		return closest;
	}*/
}

// returns the distance between Entries a and b
double getRadius(Entry* a, Entry* b){
	return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

// constructor for VP-Tree
marinemrStarbucks::marinemrStarbucks(){
	head = NULL;
}

// deconstructor for the VP-Tree
marinemrStarbucks::~marinemrStarbucks(){
	for(int i = 0; i < list.size(); i++){
		delete(entries[i]->inside);
		delete(entries[i]->outside);
	}
}

VPEntry::VPEntry(){
	radius = 0.5;
	inside = NULL;
	outside = NULL;

	entry = *(new Entry);
	entry.x = 0.0;
	entry.y = 0.0;
	entry.identifier = "missingNo.";
}

VPEntry::VPEntry(Entry* ent, double r){
	entry = *ent;
	radius = r;
	inside = NULL;
	outside = NULL;
}