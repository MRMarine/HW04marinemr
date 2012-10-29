#include "Arr.h"

void Arr::remove(int x){
	Entry* arr2 = new Entry[size - 1];
	int j = 0;

	for(int i = 0; i < size - 1; i++){
		if(i != x){
			arr2[j] = arr[i];
			j++;
		}
	}

	arr = arr2;
	size--;
}

int Arr::length(){
	return size;
}

void Arr::push_back(Entry ent){
	if(size > maxSize){
		arr[size] = ent;
		size++;
	}
	else{
		Entry* arr2 = new Entry[maxSize*2];
		for(int i = 0; i < size; i++){
			arr2[i] = arr[i];
		}
		arr2[size] = ent;

		maxSize = maxSize * 2;
		size++;
	}
}

Arr::Arr(){
	maxSize = 1;
	size = 0;
	arr = new Entry[maxSize];
}

Entry Arr::get(int i){
	return arr[i];
}