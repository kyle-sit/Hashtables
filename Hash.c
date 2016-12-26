/**************************************************************************** 
 
                                                        Kyle Sit 
                                                        3 October 2015 
                                Hashtable 
 
File Name:      Hash.c
Description:    This program provides methods for inserting items into
		a Hashtable.
****************************************************************************/

#include <cstdlib>
#include <string.h>
#include "Hash.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

using namespace std;

/* debug messages */
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_INSERT[] = " - Insert]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char FULL[] = " is full...aborting...]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT_BUMP[] = "[bumping to next location...]\n";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";


long HashTable :: debug = 0;
int HashTable :: counter = 0;


void HashTable :: Set_Debug (long option)

/***************************************************************************
% Routine Name : HashTable :: Set_Debug (public)
% File :         Hash.c
% 
% Description :  This function sets debug mode on or off
%
% Parameters descriptions :
% ------------------ ------------------------------------------------------
% option             true should set debug mode on, false should set debug
%                    mode off.
***************************************************************************/

{
        debug = option;
}


HashTable :: HashTable (long sz) : size (sz),
        table_count(++counter), occupancy (0), table (new Base *[sz])
/***************************************************************************
% Routine Name : HashTable :: HashTable (public)
% File :         Hash.c
% 
% Description :  This function allocates an initializes the memory
%                associated with a hash table.
%
% Parameters descriptions :
% ------------------ ------------------------------------------------------
% table		     The actual hashtable
% occupancy	     The number of elements in the table
% counter	     The number of hashtables allocated
% size               The number of elements for the table...MUST BE PRIME!!!
***************************************************************************/

{

	/* Set each space in table to null */
	for( int spot = 0; spot < this->size; spot++ ) {
		this->table[spot] = 0;
	}

	/* Debug Statement */
	if( debug ) {
		cerr << HASH << counter << DEBUG_ALLOCATE ;
	}

}

HashTable :: ~HashTable (void)
/***************************************************************************
% Routine Name : HashTable :: ~HashTable  (public)
% File :         Hash.c
% 
% Description :  deallocates memory associated with the Hash Table.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
        for( int spot = 0; spot < this->size; spot++ ) {
		if( this->table[spot] != 0 ) {
			delete this->table[spot];
		}
	}
	
	delete[] table;
}


long HashTable :: Insert (Base * element, long recursiveCall)
/***************************************************************************
% Routine Name : HashTable :: Insert (public)
% File :         Hash.c
% 
% Description : This function will insert the element in the hash table.
%		If the element cannot be inserted, false will be returned.
                If the element can be inserted, the element is inserted and 
		true is returned. Duplicate insertions will cause the existing
		element to be deleted, and the duplicate element to take its
		place.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert.
% recursiveCall      Whether the call to this function is recursive or not.
% <return>           1 or 0 indicating success or failure of insertion
***************************************************************************/

{
		/* Holder for the pointer in the table to bump */
		Base *test = 0;
		
		/* debug statement */
		if( debug ) {
			cerr << HASH << counter << DEBUG_INSERT;
		}
		
		/* Make call to location */
		Locate(element);

		/* If the table was exhausted we print debug and return false */
		if( this->table[index] == 0 ) {
			this->table[index] = element;
			this->occupancy++;
			return true;
		}

		/* If the returned element was the same then we know we either 
		 * have a null spot to insert or a duplicate. */
		else if( *(this->table[index]) == *element ) {
			this->table[index] = element;
			return true;
		}

		/* Otherwise we have an alphabetic order case and need to move
		 * the current element in the spot to its next probe location*/
		else if( *(this->table[index]) < *element ) {
			
			test = this->table[index];
			/* First insert the element into the table */
			this->table[index] = element;
			/* Make recursive call */
			Insert( test, true );

			/* debug statement */
			if( debug ) {
				cerr << INSERT_BUMP;
			}

			this->occupancy++;
			return true;
		}

}


const Base * HashTable :: Locate (const Base * element) const
/***************************************************************************
% Routine Name : HashTable :: Locate (private)
% File :         Hash.c
% 
% Description : This function will locate the location in the
                table for the insert or lookup.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element needing a location
% <return>           item found, or null if not found

***************************************************************************/

{
        
		/* Initialize necessary variables for checks */
		int hashVal = (long) *element;
		int init_loc = hashVal % this->size;
		int increment = (hashVal % (this->size-1)) + 1;
		int current_loc = (init_loc + increment) % this->size;
		int place = 0;
		
		/* Debug statement block */
		if( debug ) {
			cerr << HASH << counter << DEBUG_LOCATE;
			cerr << PROCESSING << (const char *)*element << "]" 
			<< endl;
			cerr << HASH_VAL << hashVal << "]" << endl;
			cerr << TRYING << init_loc << "]" << endl;
		}

		/* First check for initial location
		 * If the initial location in the table is null we return the
		 * element we are trying to insert and reset index */
		if( this->table[init_loc] == 0 
			|| *(this->table[init_loc]) == *element ){
			index = init_loc;
			return element;
		}
		
		/* If the initial location contains an element that has a lower
		 * alphabetic order than the element we want to insert, we
		 * return our element and reset the index */
		else if( *(this->table[init_loc]) < *(element) ) {
			index = init_loc;
			return this->table[init_loc];
		}
	
		/* If we cannot insert at the initial location we check the
		 * probe sequence using a loop. */
		else {
			while( current_loc != init_loc ) {
		
				if( debug ) {
				       cerr << TRYING << current_loc << "]" 
				       << endl;
				}
				
				/* If the current location in the table is null 
				 * we return the element we are trying to 
				 * insertand reset index */
				if( this->table[current_loc] == 0
				   || *(this->table[current_loc]) == *element){
					index = current_loc;
					return element;
				}

				/* If the current location contains an element 
				 * that has a lower alphabetic order than the 
				 * element we want to insert, we return our
				 * element and reset the index */
				else if( *(this->table[current_loc]) < *element){
					return this->table[current_loc];
				}			
				else {
					current_loc = (current_loc + increment) 
							% this->size;
				}
			}
		}

		/* If no locations were open we exhausted the table */
		return 0;

}


const Base * HashTable :: Lookup (const Base * element) const
/***************************************************************************
% Routine Name : HashTable :: Lookup (public)
% File :         Hash.c
% 
% Description : This function will lookup the element in the hash table.  If
%               found a pointer to the element is returned.  If the element
%               is not found, NULL will be returned to the user.
%
% Parameters descriptions :
% ------------------ ------------------------------------------------------
% element            The element to insert or to lookup.
% <return>           A pointer to the element if found, else NULL
***************************************************************************/

{
        
		/* Debug Statement */
		if( debug ) {
			cerr << HASH << counter << DEBUG_LOOKUP;
		}
		
		/* Initialize Base variable to hold locates return */
		const Base *find = Locate(element);

		/* If we return the same element that means we found a null spot
		 * or the element we want */
		if( find == element ) {
			/* This null check means we found the element and return
			 * it because there exists something at index */
			if( this->table[index] != 0 ) {
				find = this->table[index];
				return find;
			}
			/* If we get null that means the object was not inserted
			 * where it should have been so it is not in the table 
			 */
			else {
				return 0;
			}
		}

		/* If we get a different base returned that means the base we 
		 * are looing for did not bump out the one currently in the 
		 * table so the base is not in the table */
		else {
			return 0;
		}



}


ostream & HashTable :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         hash.c
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

{
	stream << "Hash Table " << table_count << ":\n"
		<< "size is " << size << " elements, "
		<< "occupancy is " << occupancy << " elements.\n";

	/* go through all table elements */
	for (long index = 0; index < size; index++)
		if (table[index])
			table[index]->Write(stream << "at index "
			<< index << ":  ") << "\n";
	return stream;
}	/* end: Write */

