/**************************************************************************** 
 
                                                        Kyle Sit 
                                                        3 November 2015 
                                Hashtable 
 
File Name:      Driver.c
Description:    This program contains the UCSDStudent Class and the 
		executable code to manipulate our HashTable at command
		line.
****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include "Base.h"
#include "SymTab.h"
#include <cstdlib>
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

class UCSDStudent : public Base {
	char * name;
	long studentnum;
public:

/***************************************************************************
% Routine Name : UCSDStudent
% File :         Driver.c
% 
% Description : Constructor for the student object
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% nm             The student name
% sn             the student number
***************************************************************************/
	UCSDStudent (char * nm, long sn) :
		name (strdup (nm)), studentnum (sn) {}

/***************************************************************************
% Routine Name : ~UCSDStudent
% File :         Driver.c
% 
% Description : Destructor for student
%
***************************************************************************/
	~UCSDStudent (void) {
		free(name);
	}

/***************************************************************************
% Routine Name : operator const char
% File :         Driver.c
% 
% Description : Getter for name
***************************************************************************/
	operator const char * (void) const {
		return name;
	}
	
/***************************************************************************
% Routine Name : operator long File 
% Driver.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
	operator long (void) const {
		long sum = 0;
	
		for (long index = 0; name[index]; index++)
			sum += name[index];

		return sum;
	}

/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         Driver.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
	long operator == (const Base & base) const {
		return ! strcmp (name, base);
	}

/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         Driver.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
	long operator < (const Base & base) const {
		return (strcmp (name, base) < 0) ? 1 : 0;
	}

/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         Driver.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
	ostream & Write (ostream & stream) const {
		return stream << "name:  " << name
			<< "  Studentnum:  " << studentnum;
	}
};


int main (int argc, char * const * argv) {
	SymTab ST (5);
	char buffer[128];
	char command;
	long number;
	char option;

	/* initialize debug variable */
	HashTable::Set_Debug(0);

	 /* check command line options for debug display */
	 while ((option = getopt (argc, argv, "x")) != EOF) {

		 switch (option) {
			 case 'x': HashTable::Set_Debug(1);
				 break;
		 	}
	} 

	ST.Write (cout << "Initial Symbol Table:\n");
	while (cin) {
		command = NULL;		// reset command each time in loop
		cout << "Please enter a command:  ((i)nsert, (l)ookup, (w)rite):  ";
		cin >> command;

		switch (command) {
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			if(!ST.Insert (new UCSDStudent (buffer, number))){

				ST.Write (cout << "\nFinal Symbol Table:\n");
				exit (0);
			}
			break;

		case 'l': {
			const Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST.Lookup (& stu);
			
			if (found)
				found->Write (cout << "Student found!!!\n") << "\n";
			else
				cout << "Student " << buffer << " not there!\n";
			}
			break;

		case 'w':
			ST.Write (cout << "The Symbol Table contains:\n");
		}
	}
	ST.Write (cout << "\nFinal Symbol Table:\n");
}

