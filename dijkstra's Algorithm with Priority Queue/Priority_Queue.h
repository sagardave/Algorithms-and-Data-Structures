#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "Pair.h"

class Priority_Queue {
	private:

		Pair *array;
		int left( int );
		int right( int );
		int parent( int );
		void heapify( int ); 
		int size;

	public:
		Priority_Queue( int );
		~Priority_Queue();

		void insert( int, double );
		void decreaseKey( int , double );
		Pair ExtractMin();
		bool empty() const;
		void clear();
};


Priority_Queue::Priority_Queue( int n ){
	array = new Pair[n];
	size = 0;
}


Priority_Queue::~Priority_Queue(){	
	delete[] array;
	
}

bool Priority_Queue::empty() const {
	return size == 0;	
}

int Priority_Queue::left( int i ) {

	//Gets the index of the left child of a node in the array
	return 2 * (i + 1) - 1;
}

int Priority_Queue::right( int i ) {

	//Gets index of the right child of a node in the array
	return 2 * (i + 1);
}

int Priority_Queue::parent( int i ) {
	
	//Gets the index of the parent of a node in the array
	return std::max(((i + 1) / 2) - 1, 0);
}
void Priority_Queue::clear() {
	size = 0;
}

void Priority_Queue::decreaseKey( int i, double key ) {
	//Assign vertex and weight to appropriate index of the heap array
	array[i].adacent_vertex = i;
	array[i].edge_weight = key;
		
	//Go through to array and place the min weight value at the root node by making sure it places the min values root as the parent	
	while(i > 0 && (array[parent(i)].weight() > array[i].weight()))
	{
		//swap parent node with one of it's children if it is smaller then its parent
		Pair tmp = array[parent(i)];
		array[parent(i)] = array[i];
		array[i] = tmp;
		i = parent(i);
	}	
}

void Priority_Queue::insert(int i, double key ) {
	size++;
	decreaseKey(i, key);
}

void Priority_Queue::heapify( int i ) {
	
	//Picks which nodes contains the smaller weight value and assigns the index to min
	//Intially assigned as current i
	int min = i;
	if(left(i) <= size && (array[left(i)].weight() < array[i].weight())){
		min = left(i);
	}	
	if(right(i) <= size && (array[right(i)].weight() < array[min].weight())){
		min = right(i);
	}
	//Swap the parent with the node which has a smaller weight value and recursivelt call heapify on that node 
	//to get the minimum valued node to the root
	if(min != i){
		//Swap
		Pair tmp = array[i];
		array[i] = array[min];
		array[min] = tmp;
		heapify(min);
	}	
	
}

Pair Priority_Queue::ExtractMin() {	
	//Returns the minimum value (Root) node from the heap and assigns the last node of the array as the root and 
	//calls heapify on it to maintain correct heap structure
	Pair min = array[0];	
	size--;
	array[0] = array[size-1];	
	heapify(0);
	return min;
}

#endif