#include "marinemrStarbucks.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace std;

//vector<VPEntry> entries;

// builds the VP-Tree from an array of Entries.
void marinemrStarbucks::build(Entry* c, int n){

	head = new VPEntry(&c[0], 0.5);
	size = n;

	for(int i = 1; i < n; i++){
		insert(&c[i], head, 0.25);
		//list.push_back(c[i]);
	}

	
	//entries.push_back(*head);
	//list.erase(list.begin() + 0);


	// start assigning
	//assign(head);
}

VPEntry* marinemrStarbucks::insert(Entry* add, VPEntry* r, double d){
	if(r == NULL){
		return new VPEntry(add, d/2.0);
	}
	if((r->entry) == add){
		return r;
	}
	if(getRadius(add, r->entry) < d){
		r->inside = insert(add,r->inside, d/2.0);
	}
	else{
		r->outside = insert(add,r->outside, d/2.0);
	}

	return r;
}

/*
// recursively assigns a VPEntry to inside and outside another VPEntry.
void marinemrStarbucks::assign(VPEntry* current){
	//vector<Entry> list = marinemrStarbucks.list;
	if(list.size() == 0){ return; }
	try{

	for(int i=0; i<(int)list.size(); i++) {
		//if(list[i] == current->entry) continue;
		if(current->inside != NULL && current->outside != NULL) continue;
		if(current->inside == NULL && getRadius((current->entry), &list[i])) {
			current->inside = new VPEntry(&list[i], getRadius((current->entry), &list[i]));
			list.erase(list.begin() + i);
			//list.swap(newArr);
			//remove(&list,i);
			//assign(current->inside);
			
			i--;
		}
		if(list.size() == 0){
			return;
		}
		int j = i;
		if(i < 0){
			j = 0;
		}
		if(current->outside == NULL && getRadius((current->entry), &list[j])) {
			current->outside = new VPEntry(&list[j], getRadius((current->entry), &list[j]));
			list.erase(list.begin()+ i);
			//list.swap(newArr);
			//remove(&list,j);
			//assign(current->outside);
			
			if(i != 0){
				i--;
			}
		}
	}
	}
	catch(int e){}

	return;
}
*/

// returns the nearest Entry as a pointer
Entry* marinemrStarbucks::getNearest(double x, double y){
	Entry* location = new Entry;
	location->x = x;
	location->y = y;
	location->identifier = "requested point"; // I probably don't need this, but I want to avoid any problems that might crop up

	return ((head->search(location))->entry);
}

// searches through the VPEntry nodes for the nearest one to the specified location
VPEntry* VPEntry::search(Entry* loc){
	VPEntry* closest = NULL;

	if(getRadius((this->entry), loc) == 0){return this;}

	if(this->inside != NULL && getRadius((this->entry), loc) < this->radius){
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
	else if(getRadius((this->entry), loc) <= getRadius((closest->entry), loc)){
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

	ifstream in("Starbucks_2006.csv");
	vector<Entry> list2;
	string str;
	double x, y;
	char filler;

	// take in file input and save Entries
	while(in.good()){
		Entry* e = new Entry;
		getline(in, str, ',');
		in >> x;
		in >> filler;
		in >> y;

		e->identifier = str;
		e->x = x;
		e->y = y;

		list2.push_back(*e);
	}

	// make array for Entries
	Entry* entrie = new Entry[(int)list2.size()];

	for(int i = 0; i < (int)list2.size(); i++){
		entrie[i] = list2[i];
	}

	// build VP-Tree
	build(entrie, list2.size());

}

// deconstructor for the VP-Tree
marinemrStarbucks::~marinemrStarbucks(){
}

VPEntry::VPEntry(){
	radius = 0.5;
	inside = NULL;
	outside = NULL;

	entry = (new Entry);
	entry->x = 0.0;
	entry->y = 0.0;
	entry->identifier = "missingNo.";
}

VPEntry::VPEntry(Entry* ent, double r){
	entry = ent;
	radius = r;
	inside = NULL;
	outside = NULL;
}


template <class T>
void remove(vector<Entry>* vect, int x){
	vector<Entry> newArr;

	for(int i = 0; i < (int)vect->size() - 1; i++){
		if(i != x){
			newArr.push_back(vect[i]);
		}
	}

	vect->swap(newArr);
}