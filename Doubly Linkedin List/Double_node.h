/*****************************************
 * UW User ID:  s3dave
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#define nullptr 0

#include "ece250.h"

template <typename Type>
class Double_list;

template <typename Type>
class Cyclic_double_list;

template <typename Type>
class Double_sentinel_list;

template <typename Type>
class Cyclic_double_sentinel_list;

template <typename Type>
class Double_node {
	private:
		Type       element;
		Double_node *previous_node;
		Double_node *next_node;

	public:
		Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

		Type retrieve() const;
		Double_node *previous() const;
		Double_node *next() const;

		friend class Double_list<Type>;
		friend class Cyclic_double_list<Type>;
		friend class Double_sentinel_list<Type>;
		friend class Cyclic_double_sentinel_list<Type>;

		// if ptr is a pointer to a Double_node<Type> object
		// in one of the friendly classes, you should:
		//    use   ptr->next_node   to modify it
		//    use   ptr->next()      to access it
};

template <typename Type>
Double_node<Type>::Double_node( Type const &e, Double_node<Type> *p, Double_node<Type> *n ):
element( e ),
previous_node( p ),
next_node( n ) {
	// empty constructor
}

template <typename Type>
Type Double_node<Type>::retrieve() const {
//returns the elements at the desired node in the list
	if(element == nullptr){
		return nullptr;	
	}
	else{
		return element;
	}	
}

template <typename Type>
Double_node<Type> *Double_node<Type>::previous() const {
//returns the previous node of the desired node in the list
	if(previous_node == nullptr){
		return nullptr;	
	}
	else{
		return previous_node;
	}
}

template <typename Type>
Double_node<Type> *Double_node<Type>::next() const {
//returns the next node of the desired node in the list
	if(next_node == nullptr){
		return nullptr;	
	}
	else{
		return next_node;
	}
}

#endif
