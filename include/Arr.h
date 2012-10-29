#include <vector>
#include "marinemrStarbucks.h"


class Arr{
public:
	Arr();
	Entry get(int);
	void push_back(Entry);
	int length();
	void remove(int);

private:
	Entry* arr;
	int size, maxSize;
};