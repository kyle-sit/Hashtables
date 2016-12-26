#ifndef LIST_H
#define LIST_H

/* DO NOT CHANGE:  This file is needed in evaluation.  */

#include <iostream>
#include "Base.h"
using namespace std;

#ifndef NULL
#define NULL 0
#endif

struct Node;

class List : public Base {
	Node * joint;
	long occupancy;
public:
	List (void) : joint (NULL), occupancy (0) {}
	~List (void);
	Base * Insert (Base *, long);
	Base * Remove (long);
	const Base * View (long) const;
	long IsEmpty (void) const {
		return ! NumElements ();
	}
	long NumElements (void) const {
		return occupancy;
	}
	ostream & Write (ostream &) const;
};

/* where to insert, view, remove */
#define FRONT 0
#define END 1

#endif
