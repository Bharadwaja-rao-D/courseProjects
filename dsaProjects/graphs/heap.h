#ifndef _HEAP_
#define _HEAP_

#include <iostream>
#include <vector>

enum class event{infection,recovery};
typedef struct{
	int personid;
	int dayInfected;
	event type;
}Timestamp;

class Heap{
	std::vector<Timestamp*> heapContainer;
	public:
	void addtoHeap(int id, int day, event type);
	void heapify(int index);
	Timestamp* deleteMin();
	bool isEmpty(){ return heapContainer.size() == 0 ;}
};

#endif
