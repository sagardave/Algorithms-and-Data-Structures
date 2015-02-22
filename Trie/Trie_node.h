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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;

	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false )
{
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	char c = str[depth];	
	if(isupper(c)){
		c = tolower(c);	
	}
	c = c - 'a';
	
	if(this == nullptr)
	{		
		return false;//node is null
	}		
	//Not a leaf node. Need to check for its children till reached a leaf node or a terminal node
	else if(this->children != nullptr)
	{							
		if(depth == str.length()){
			//returns the state of terminal if reached at end of string
			return this->is_terminal;
		}
		else
		{
			depth++;			
			return this->children[c]->member( str, depth );//recurse through string until reached end of string
		}		
	}			
	else
	{		
		if(depth == str.length())
		{
			return this->is_terminal;//At a leaf node - children are null. Doesn't need to check for children			
		}
		else
		{
			return false;//reached leaf node but not end of string. String doesnt exist in the trie
		}
	}			

}

bool Trie_node::insert( std::string const &str, int depth ) {
	char c = str[depth];	
	if(isupper(c)){
		c = tolower(c);	
	}
	c = c - 'a';

	bool inserted = false;
	
	if(this->children == nullptr)
	{	
		//Reached a leaf node. Assigns an array of 26 trie nodes to children
		//Initialzes each of the 26 nodes to null
		this->children = new Trie_node* [CHARACTERS];
		for(int i = 0; i < CHARACTERS; i++)
		{
			this->children[i] = nullptr;
		}
		inserted = true;
	}					
	if(depth < str.length())
	{
		//Assigns a new trie node at cth position if its null
		if(this->children[c] == nullptr)
		{
			this->children[c] = new Trie_node;	
			inserted = true;
		}
		depth++;
		if (depth == str.length())
		{
			//the cth node is set as the terminal node when reached at end of string
			this->children[c]->is_terminal = true;
			return true;
		}
		return this->children[c]->insert(str, depth);
		inserted = true;
	}			
	return inserted;
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	char c = str[depth];	
	if(isupper(c)){
		c = tolower(c);	
	}
	c = c - 'a';
	
	bool del = true;
	if(ptr_to_this != nullptr)
	{	
		if(depth != str.length()-1)
		{		
			//keep recursing until reached end of string
			depth++;
			erase(str, depth, ptr_to_this->children[c]);			
		}		
		else
		{
			if(ptr_to_this->children[c]->is_terminal && ptr_to_this->children[c]->children == nullptr)
			{
				//Deletes the cth node of children when it is the terminla and a leaf node
				delete ptr_to_this->children[c];
				ptr_to_this->children[c] = nullptr;
			}
			else
			{
				//Sets the cth node of children to be a non terminal node
				//Since it is note a lead node, it does not get deleted. Part of another word
				ptr_to_this->children[c]->is_terminal = false;
			}
		}			
			//loop through each of the children to see if it is null
			for(int i = 0; i < 26; i++)
			{
				if(ptr_to_this->children[i] != nullptr)
				{
					del = false;//Found a child that isn't null which means the pointer cannot be deleted.
				}
			}
			if(del){
				//Only delete children array every child is null
				delete[] ptr_to_this->children;
				ptr_to_this->children = nullptr;	
				if(!ptr_to_this->is_terminal)	{	
					//Deletes the parent of the children if it is not a terminal node.
					//Which means the parent is not part of any other word
					delete ptr_to_this;
					ptr_to_this = nullptr;					
				}
			}		
	}		
	return true;
}

void Trie_node::clear() {
	if(this->children)
	{		
		for(int i = 0; i < 26; i++)
		{	
			//Go through each child and call clear
			if(this->children[i]){
				this->children[i]->clear();	
			}
		}		
		delete[] this->children;//deletes each of the children array
		this->children = nullptr;
	}
	//Deletes each of the parent node of the children
	delete this;
		
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
