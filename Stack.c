#include <iostream>
#include "Base.h"
#include "Stack.h"
using namespace std;

Base * Stack :: Pop (void) {
	return Remove (END);
}

Base * Stack :: Push (Base * element) {
	return Insert (element, END);
}

const Base * Stack :: Top (void) const {
	return View (END);
}
