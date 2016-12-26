#ifndef HASH_H
#define HASH_H

/* DO NOT CHANGE:  This file is needed in evaluation.  */

#include <iostream>
#include "Base.h"
using namespace std;

class HashTable : public Base {
        // counters, flags, and constant
	static int counter;	   // how many tables allocated so far
	static long debug;

	const int table_count;     // the table number
	long occupancy;		   // how many elements are in the Hash Table
	const long size;	   // size of Hash Table
	Base ** table;	   // the Hash Table itself ==> array of Base pointers

        // initialized by Locate function
	mutable int index;         // last location checked in hash table

        // functions
	const Base * Locate (const Base *) const;   // locate an item
	
public:
	static void Set_Debug (long);
	HashTable (long);		       	    // constructor
	~HashTable (void);		     	    // destructor
	long Insert (Base *, long recursiveCall = 0); // insert an item
	const Base * Lookup (const Base *) const;    // lookup an item
	ostream & Write (ostream &) const;	    // display Hash Table
};

#endif
