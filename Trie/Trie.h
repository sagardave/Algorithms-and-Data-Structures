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

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const; 
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	if(this){
		this->clear();
	}
}

int Trie::size() const {	
	return trie_size;
}

bool Trie::empty() const {
	return trie_size == 0;
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	//checks if the character is a letter between a and z
	//gives illegal argument exception otherwise
	for(int i = 0; i <str.length(); i++)
	{
		char c = str[i];	
		if(isupper(c)){
			c = tolower(c);	
		}
		c = c - 'a';
	
		if(!(c < 26 && c >= 0))
		{
			throw illegal_argument();
		}
	}	
	return root_node->member(str, 0);	
	
}

bool Trie::insert( std::string const &str ) {
	bool inserted = false;
	//checks if the character is a letter between a and z
	//gives illegal argument exception otherwise
	for(int i = 0; i <str.length(); i++)
	{
		char c = str[i];	
		if(isupper(c)){
			c = tolower(c);	
		}
		c = c - 'a';
	
		if(!(c < 26 && c >= 0))
		{
			throw illegal_argument();
		}
	}
	//return false if the string is already a member of the trie	
	if(root_node)
	{
		if(root_node->member(str,0))
		{
			return false;
		}
	}
	else
	{
		root_node = new Trie_node();  
    } 	
				
	inserted = root_node->insert(str, 0);
	trie_size++;
	return inserted;		
	
}

bool Trie::erase( std::string const &str ) {	
	bool erased = false;
	//checks if the character is a letter between a and z
	//gives illegal argument exception otherwise
	for(int i = 0; i <str.length(); i++)
	{
		char c = str[i];	
		if(isupper(c)){
			c = tolower(c);	
		}
		c = c - 'a';
		if(!(c < 26 && c >= 0))
		{
			throw illegal_argument();
		}
	}

	//return false if the string is not a member of the trie	
	if(!root_node->member(str,0) || trie_size == 0)
	{
		return false;
	}	
	else
	{
		erased = root_node->erase(str, 0, root_node);
	}
	if(erased)
	{
		trie_size--;
		return true;
	}
	else
	{
		return false;
	}
	
}

void Trie::clear() {
	if(root_node){
		root_node->clear();
		trie_size = 0;
	}
	
	root_node = nullptr;
	
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
/*	for ( Trie_node *ptr = trie.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->value();
	}*/

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
