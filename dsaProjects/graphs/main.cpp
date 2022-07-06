#include "graph.h"
#include "heap.h"
#include <iostream>

enum class status{susceptible, infected, recovered};

typedef struct {
	int personId;
	int timestamp;
	status infectionStatus;
}personStatus;

personStatus susceptible[number_people], infected[number_people], recovered[number_people];

void move(event type, int personid, int day){

	//if type is infection then we are going to move him from susceptible to infected
	//else we will move him from infected to recovered vector
	if(type == event::infection){
		susceptible[personid].personId = -1;
		infected[personid].personId = personid;
		infected[personid].timestamp = day;
		infected[personid].infectionStatus = status::infected;
	}
	else if(type == event::recovery){
		infected[personid].personId = -1;
		recovered[personid].personId = personid;
		recovered[personid].timestamp = day;
		recovered[personid].infectionStatus = status::recovered;
	}
}

void dailyReport(int dayno){
	int countSusceptible=0;
	int countInfected=0;
	int countRecovered=0;
	for(int i=0; i<number_people; i++){
		if(susceptible[i].personId != -1) countSusceptible++;
		if(infected[i].personId != -1) countInfected++;
		if(recovered[i].personId != -1) countRecovered++;
	}
	std::cout<<"Day: "<<dayno<<"  ";
	std::cout<<"susceptible: " << countSusceptible << " infected: "<<countInfected<<" recovered: "<<countRecovered<<std::endl;
}


void HeightVsActual(graph *graphptr){
	for(int i=0; i<number_people;i++){
		std::cout<<"For person "<<i<<std::endl;
		std::cout<<"Distance "<<graphptr->persons[i].height<<" Vs Actual Infected "<< infected[i].timestamp <<std::endl;
	}
}

 int main(){
	//The constructor of graph tosses a coin and creates edges
	graph population;
	Heap minHeap;
	//population.printGraph();

	personStatus temp;
	//add all citizens to susceptible
	for(int i=0; i<number_people;i++){
		temp.personId = i;
		temp.infectionStatus = status::susceptible;
		temp.timestamp = 0;
		susceptible[i] = temp;

		temp.personId = -1;
		infected[i] = temp;
		recovered[i] = temp;
	}



	int virusSource = std::rand() % number_people;

	population.persons[virusSource].height = 0;

	population.assignHeight(virusSource);

	minHeap.addtoHeap(virusSource, 0, event::infection);

	//create recovery for the person one

	minHeap.addtoHeap(virusSource, std::rand() % 5 + 1, event::recovery);


	int dayno = 0;
	while(!minHeap.isEmpty()){
		Timestamp* info = minHeap.deleteMin();
		if(dayno != info->dayInfected) {
			//printing daily report
			dailyReport(dayno);
			dayno++;
		}

		if(info->type == event::recovery){
			//we are going to move this person from infected to recovered vector
			move(event::recovery, info->personid, info->dayInfected);
		}
		else if(susceptible[info->personid].personId != -1){
			//we are going to move this person from susceptible to infected vector
			move(event::infection, info->personid, info->dayInfected);
			listnode* head = population.persons[info->personid].head;
			while(head){
				//and will write the destiny of his neighbors
				int nid = head->neighborid;
				if(susceptible[nid].personId != -1){
					//now we will tell him when to get infected
					for(int i=1;i<6;i++){
						if(std::rand() % 2){
							minHeap.addtoHeap(nid, info->dayInfected+i,event::infection);
							minHeap.addtoHeap(nid, info->dayInfected+i+std::rand() % 5 + 1,event::recovery);
						}
					}
				}
				head = head->next;
			}
		}
	}

	population.assignHeight(virusSource);
	HeightVsActual(&population);


}
