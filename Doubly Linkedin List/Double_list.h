/*****************************************
 * UW User ID:  s3dave
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"
#include "Double_list_tester.h"

#define nullptr 0

template <typename Type>
class Double_list {
	private:
		Double_node<Type> *list_head;
		Double_node<Type> *list_tail;
		int list_size; 

	public:
		Double_list();
		Double_list( Double_list const & );
		~Double_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node<Type> *head() const;
		Double_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Double_list & );
		Double_list &operator=( Double_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_list<T> const & );
};

template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	
	//Copies each of the nodes in the existing doubly linked list into a new pointer.
	Double_node<Type> *ptr = list.list_head;
	while(ptr != nullptr){
		push_back(ptr->element);
		ptr = ptr->next_node;
	}

}

template <typename Type>
Double_list<Type>::~Double_list<Type>() {	

	//Removes each node from the doubly linked list
	Double_node<Type> *current = list_head;		
	while(current != nullptr)
	{
		Double_node<Type> *next = current->next_node;
		delete current;
		current = next;	//current node points to the next node in the list	
	}
}

template <typename Type>
int Double_list<Type>::size() const {
	//returns the size of the list
	return list_size;
}

template <typename Type>
bool Double_list<Type>::empty() const {
	//returns true if the size of the list is 0, else false
	return (list_size == 0);
}

template <typename Type>
Type Double_list<Type>::front() const {
	if(empty()){
		throw underflow();
	}
	//returns the front elements in the list
	if(list_head->retrieve() == nullptr){
		return nullptr;	
	}
	else{
		return list_head->retrieve();
	}
}

template <typename Type>
Type Double_list<Type>::back() const {
	if(empty()){
		throw underflow();
	}
	//returns the back elements in the list
	if(list_tail->retrieve() == nullptr){
		return nullptr;	
	}
	else{
		return list_tail->retrieve();
	}
	
}

template <typename Type>
Double_node<Type> *Double_list<Type>::head() const {
	//returns the head node of the list
	if(list_head == nullptr){
		return nullptr;	
	}
	else{
		return list_head;
	}
}

template <typename Type>
Double_node<Type> *Double_list<Type>::tail() const {
	//returns the tail node of the list
	if(list_tail == nullptr){
		return nullptr;	
	}
	else{
		return list_tail;
	}
}

template <typename Type>
int Double_list<Type>::count( Type const &obj ) const {
	int count = 0;
	//Counts and returns the total number of non-null elements in the linked list
	for ( Double_node<Type> *ptr = head(); ptr != nullptr; ptr = ptr->next() ) {
		if(ptr->retrieve() == obj){
			++count;
		}
	}

	return count;
}

template <typename Type>
void Double_list<Type>::swap( Double_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_list<Type> &Double_list<Type>::operator=( Double_list<Type> const &rhs ) {
	Double_list<Type> copy( rhs );

	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_list<Type>::push_front( Type const &obj ) {
	
	if(empty()){
		//Creates a new node and the head and tail point to the new node if list is empty
		list_head = new Double_node<Type>(obj, nullptr, nullptr);;
		list_tail = list_head;		
		list_size++;
	}	
	else{	
		//Creates new head node and the head of the list point to the new head node
		Double_node<Type> *current = list_head;
		list_head = new Double_node<Type>(obj, nullptr, list_head);
		current->previous_node = list_head;
		list_size++;
	}
 
}

template <typename Type>
void Double_list<Type>::push_back( Type const &obj ) {
	if(empty()){
		//Creates a new node and the head and tail point to the new node if list is empty
		list_tail = new Double_node<Type>(obj, nullptr, nullptr);
		list_head = list_tail;
		list_size++;
	}
	else{
		//Creates new head node and the tail of the list point to the new head node
		Double_node<Type> *current = list_tail;
		list_tail = new Double_node<Type>(obj, list_tail, nullptr);	
		current->next_node = list_tail;
		list_size++;
	}
}

template <typename Type>
Type Double_list<Type>::pop_front() {
	if(empty()){
		throw underflow();
	}
	Type e = front();

	if(size() == 1){	
		//deletes the head node of the list if its empty
		delete list_head;
		list_head = nullptr;
		list_tail = nullptr;
		list_size--;
	}
	else {
		//deletes the head of the list and then it points to the next node in the list 
		Double_node<Type> *current = list_head->next_node;
		delete list_head;
		list_head = current;
		list_head->previous_node = nullptr;
		list_size--;
	}
	return e;
	
}

template <typename Type>
Type Double_list<Type>::pop_back() {
	if(empty()){
		throw underflow();
	}
	Type e = back();

	if(size() == 1){		
		//deletes the tail node of the list if its empty
		delete list_tail;
		list_tail = nullptr;
		list_head = nullptr;
		list_size--;
	}
	else {
		//deletes the tail of the list and then it points to the previous node in the list
		Double_node<Type> *current = list_tail->previous_node;
		delete list_tail;
		list_tail = current;
		list_tail->next_node = nullptr;
		list_size--;
	}
	
	return e;
}

template <typename Type>
int Double_list<Type>::erase( Type const &obj ) {

	//Loops through the list for the elements and deletes it
	for (Double_node<Type> *ptr = list_head; ptr != nullptr; ptr = ptr->next_node ) {
		Double_node<Type> *newPrev;
		Double_node<Type> *newNext;
		if(ptr->element == obj){
				//if the element is at the head, implements pop front method
				if(ptr->previous_node == nullptr){
					if(empty()){
						throw underflow();
					}
					if(ptr->next_node == nullptr){
						//If there is only one element in the list, deletes the pointer and asigns both head the tail to null pointer
						delete ptr;	
						ptr = nullptr;
						list_head = nullptr;
						list_tail = nullptr;
					}
					else{
						//if there are more then 1 elements in the list, deletes the head and the pointer points to the new head 
						list_head = list_head->next_node;
						list_head->previous_node = nullptr;
						delete ptr;						
					}
				}
				//if the element is at the tail, deletes the tail of the list and the tail points to the previous node of the list
				else if(ptr->next_node == nullptr){
					if(empty()){
							throw underflow();
						}
						list_tail = list_tail->previous();
						list_tail->next_node = nullptr;
						delete ptr;									
				}
				else{		
					//if the element is somewhere in the middle, previous node points to the next node and next node points to the previous node
					//and then deletes the current node and current node points to the new node
					newPrev = ptr->previous_node;
					newPrev->next_node = ptr-> next_node;
					newNext = ptr->next_node;
					newNext->previous_node = newPrev;
					delete ptr;										
				}
				list_size--;
				return 1;
			}	
	}	
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
