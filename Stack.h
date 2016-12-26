#ifndef STACK_H
#define STACK_H

/* DO NOT CHANGE:  This file is needed in evaluation.  */

#include <iostream>
#include "List.h"
using namespace std;

class Stack : private List {
public:
	using List :: IsEmpty;
	using List :: NumElements;
	using List :: Write;

	Base * Pop (void);
	Base * Push (Base *);
	const Base * Top (void) const;
};

#endif
