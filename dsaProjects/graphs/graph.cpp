#include "graph.h"
#include <iostream>


void addtoList(struct listnode **headref, int neighborid){
	listnode* head = *headref;
	listnode* newnode = (listnode*)malloc(sizeof(listnode));
	newnode->neighborid = neighborid;
	newnode->next = head;
	*headref = newnode;
}

graph::graph(){
	for(int i=0; i<number_people; i++){
		for(int j=i+1;j<number_people;j++){
			if(std::rand() % 2){
				addtoList(&persons[i].head, j);
				addtoList(&persons[j].head, i);
			}
		}
	}
}

void graph::printGraph(){
	for(int i=0; i<number_people;i++){
		listnode* head = persons[i].head;
		persons[i].printInfo();
		while(head){
			std::cout<<head->neighborid<<":";
			head = head->next;
		}
		std::cout<<std::endl;
	}
}

void graph::assignHeight(int sourcePersonId){
	listnode* head = persons[sourcePersonId].head;
	std::vector<int> nowAssigned;
	while(head){
		if(persons[head->neighborid].height == -1 || persons[head->neighborid].height
				> persons[sourcePersonId].height+1){
			persons[head->neighborid].height = persons[sourcePersonId].height + 1;
			nowAssigned.push_back(head->neighborid);
		}
		head = head->next;
	}
	for(int neighbors: nowAssigned){
		assignHeight(neighbors);
	}
}

/*
 * graph::~graph(){
	for(int i=0; i<number_people;i++){
		listnode *head = persons[i].head;
	}
}
*/
