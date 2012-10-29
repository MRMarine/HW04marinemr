#include "marinemrStarbucks.h"
#include <vector>


void marinemrStarbucks::build(Entry* c, int n){
	VPEntry* current = NULL;

	for(int i = 0; i < n; i++){
		list.push_back(c[i]);
	}

	head = new VPEntry(&(list[0]), 0.5);
	entries.push_back(head);

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
	VPEntry* insideNodes = new VPEntry[inside.size()];
	for(int i = 0; i < inside.size(); i++){
		current->inside == new VPEntry(&inside[i], current->radius / 2.0);
		assign(current->inside, inside);
	}

	// assign outside nodes
	for(int j = 0; j < list.size() && current->outside == NULL; j++){
		if(getRadius(&(current->entry), &list[j]) > current->radius){
			current->outside == new VPEntry(&list[j], current->radius / 2.0);
			assign(current->outside, outside);
		}
	}
}

Entry* marinemrStarbucks::getNearest(double x, double y){
	Entry* location = new Entry;
	location->x = x;
	location->y = y;
	location->identifier = "given";

	head->search(location);
}

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