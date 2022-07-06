#include "heap.h"


int parent(int index) {return (index-1)/2 ;}
int leftchild(int index) {return 2*index + 1 ;}
int rightchild(int index) {return 2*index + 2 ;}

bool compare(Timestamp *arg1, Timestamp* arg2) {return arg1->dayInfected < arg2->dayInfected;}

void Heap::addtoHeap(int id, int day, event type){
	Timestamp *info = (Timestamp*)malloc(sizeof(Timestamp));
	info->personid = id;
	info->dayInfected = day;
	info->type = type;

	int index = heapContainer.size();
	heapContainer.push_back(info);
	while(index){
		if(compare(heapContainer.at(index),heapContainer.at(parent(index)))){
			std::swap(heapContainer.at(index),heapContainer.at(parent(index)));
		}
		index = parent(index);
	}
}

void Heap::heapify(int index){
	if(leftchild(index) > heapContainer.size()-1) return;//base case


	if(leftchild(index) == heapContainer.size()-1 && compare(heapContainer.at(index), heapContainer.at(leftchild(index)))) return;
	if(compare(heapContainer.at(index), heapContainer.at(leftchild(index))) &&
			compare(heapContainer.at(index),heapContainer.at(rightchild(index)))){
		//if the parent is smaller than both the children then this process should terminate
		return;
	}
	if(leftchild(index) == heapContainer.size()-1){
		//here the node will have only left chld
		std::swap(heapContainer.at(leftchild(index)),heapContainer.at(index));
		return;
	}
	Timestamp *left, *right;
	left = heapContainer.at(leftchild(index));
	right = heapContainer.at(rightchild(index));
	if(compare(left,right)){
		std::swap(heapContainer.at(leftchild(index)),heapContainer.at(index));
		heapify(leftchild(index));
	}
	else{
		std::swap(heapContainer.at(rightchild(index)),heapContainer.at(index));
		heapify(rightchild(index));
	}
}

Timestamp* Heap::deleteMin(){
	Timestamp* info;
	if(heapContainer.size() == 1){
		info = heapContainer.back();
		heapContainer.pop_back();
		return info;
	}
	std::swap(heapContainer.front(), heapContainer.back());
	info = heapContainer.back();
	heapContainer.pop_back();
	heapify(0);
	return info;
}
