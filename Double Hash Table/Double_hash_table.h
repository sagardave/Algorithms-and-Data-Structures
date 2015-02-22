/*****************************************
 * UW User ID:  s3dave
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template <typename Type>
class Double_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		state *occupied;

		int h1( Type const & ) const;
		int h2( Type const & ) const;

	public:
		Double_hash_table( int = 5 );
		~Double_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_hash_table<T> const & );
};

template <typename Type>
Double_hash_table<Type>::Double_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new state[array_size] ) {

	for ( int i = 0; i < array_size; i++ ) {
		occupied[i] = EMPTY;
	}
}

template <typename Type>
Double_hash_table<Type>::~Double_hash_table(){
	//Deallocate memory by the 2 arrays
	delete[] array;
	delete[] occupied;
}

template <typename Type>
int Double_hash_table<Type>::size() const {
	//Returns the total number of occupied indexes
	return count;
}

template <typename Type>
int Double_hash_table<Type>::capacity() const {
	return array_size;
}

template <typename Type>
double Double_hash_table<Type>::load_factor() const {
	//Returns the load factor of the hash table
	return count/array_size;
}

template <typename Type>
bool Double_hash_table<Type>::empty() const {
	return count == 0;
}

template <typename Type>
int Double_hash_table<Type>::h1(Type const &val) const {
	int i = static_cast<int>(val);
	//Gets the integer modulo 
	//Adds the array_size(M) to it if the integer module is negative
	int intMod = i % array_size;
	if(intMod < 0){
		intMod = intMod + array_size;
	}
	return intMod;
}

template <typename Type>
int Double_hash_table<Type>::h2(Type const &val) const {
	int i = static_cast<int>(val);
	//Gets the integer modulo 
	int intMod = (i / array_size) % array_size;
	//Adds one to make it odd
	if(intMod % 2 == 0){
		intMod++;
	}
	//Adds the array_size(M) to it if the integer module is negative
	if(intMod < 0){
		intMod = intMod + array_size;
	}
	return intMod;
}

template <typename Type>
bool Double_hash_table<Type>::member(Type const &val) const {
	int h_fun1 = h1(val);
	int h_fun2 = h2(val);

	int i = 0;
	int hashNum = (h_fun1 + i*h_fun2) % array_size;

	//Keeps jumping over the index based on the hashNum until it finds an occupied index
	//which is holding a value.
	//Returns false if it hits h_fun1 again and finds an empty spot
	while(!(hashNum == h_fun1 && i != 0) && occupied[hashNum] != EMPTY)
	{			
		if(occupied[hashNum] == OCCUPIED && array[hashNum] == val){
			return true;			
		}
		else{
			//Increments i to determine the next jump value 
			i++;
			hashNum = (h_fun1 + i*h_fun2) % array_size;
		}
	}
	return false;
}

template <typename Type>
Type Double_hash_table<Type>::bin(int num) const {
	//returns the entry in bin num
	return (Type)array[num];
}

template <typename Type>
void Double_hash_table<Type>::print() const {

}

template <typename Type>
void Double_hash_table<Type>::insert(Type const &val ) {
	if(!member(val))
	{
		int h_fun1 = h1(val);
		int h_fun2 = h2(val);

		int i = 0;
		int hashNum = (h_fun1 + i*h_fun2) % array_size;
		//Keeps jumping over the index based on the hashNum until it finds an occupied index
		//and hasn't hit h_fun again.
		while(!(hashNum == h_fun1 && i != 0) && occupied[hashNum] == OCCUPIED)
		{
			i++;
			hashNum = (h_fun1 + i*h_fun2) % array_size;
		}	
		//Throws overflow exceptiong if the size of hash reaches the (capacity) array_size
		if(count == array_size){
			throw underflow();
		}
		//Assigns val to predefined index(hashNum) of the array and marks it as occupied
		array[hashNum] = val;
		occupied[hashNum] = OCCUPIED;
		count++;
	}
	
}

template <typename Type>
bool Double_hash_table<Type>::erase(Type const &val ) {
	
	int h_fun1 = h1(val);
	int h_fun2 = h2(val);

	int i = 0;
	int hashNum = (h_fun1 + i*h_fun2) % array_size;
	//Keeps jumping over the index based on the hashNum until it finds an occupied index
	//and hasn't hit h_fun again.
	while(!(hashNum == h_fun1 && i != 0) && occupied[hashNum] != EMPTY)
	{		
		if(occupied[hashNum] == OCCUPIED && array[hashNum] == val){
			//Once the value if found, it is set to 0 and marked as deleted. 
			//Decreases the hash table size (count)
			array[hashNum] = 0;
			occupied[hashNum] = DELETED;
			count--;
			return true;
		}
		else{
			i++;
			hashNum = (h_fun1 + i*h_fun2) % array_size;
		}
	}
	return false;
}

template <typename Type>
void Double_hash_table<Type>::clear() {
	//Deallocate memory created by the array
	//and create a new array with each index marked as empty
	//Also reset count
	delete[] array;
	array = new Type[array_size];

	for(int i = 0; i < array_size; i++)
	{
		occupied[i] = EMPTY;
	}
	count = 0;
}		

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == EMPTY ) {
			out << "- ";
		} else if ( hash.occupied[i] == DELETED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
