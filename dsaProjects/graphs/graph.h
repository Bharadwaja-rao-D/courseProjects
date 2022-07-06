#ifndef _graph_h
#define _graph_h

#include <iostream>
#include <vector>
#define number_people 100


typedef struct listnode{
	int neighborid;
	struct listnode *next;
}listnode;

void addtoList(struct listnode* head, int id);

class graphNode{
	int personid;
public:
	int height=-1;
	listnode* head = nullptr;
	graphNode(){
		static int inc;
		personid = inc++;
	}
	void printInfo(){
		std::cout<<personid<<": "<<height<<std::endl;
	}
};

class graph{
	public:
		graphNode persons[number_people];
		graph();
		void printGraph();
		void assignHeight(int sourcePersonId);
		//destructs deletes all the neighbors of the persons and frees the
		//memory used by malloc function
		//~graph();


};

#endif
