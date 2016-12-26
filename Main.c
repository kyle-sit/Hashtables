#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <stdio.h>
#include "Calc.h"
using namespace std;

int main (int argc, char * const * argv) {

	char option;

	/* Initialize debug variable */
	HashTable::Set_Debug(0);

	/* check command line options for debug display */
	while ((option = getopt (argc, argv, "x")) != EOF) {
		switch (option) {
		    case 'x': 
			    HashTable::Set_Debug(1);
			    break;
	        }

	} 

	Calculator calc (53);		// Calculator to use

	
	while (1) {
		cout << "\nPlease enter an expression to calculate:  ";
		cout.flush ();
		if (calc.InToPost () == EOF)
			break;
		
		calc.Write_Postfix
			(cout << "\nThe expression in postfix order is:  ");

		cout << "\nwhich evaluates to:  " << calc.Eval () << "\n";

		calc.Write (cout << "\nCalculator is:\n");
	}
	cout << "\n";
	cout.flush ();
}
