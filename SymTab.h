#ifndef SYMTAB_H
#define SYMTAB_H

/* DO NOT CHANGE:  This file is needed in evaluation.  */

#include <iostream>
#include "Base.h"
#include "Hash.h"
using namespace std;

class SymTab : private HashTable {
public:
	using HashTable :: Insert;
	using HashTable :: Lookup;
	using HashTable :: Write;
	SymTab (long sz) : HashTable (sz) {}
};

#endif

