/**************************************************************************** 
 
                                                        Kyle Sit 
                                                        CSE 12, Fall 
                                                        3 November 2015 
                                                        cs12xgj 
                                Assignment Six 
 
File Name:      Driver.java 
Description:    This program contains the UCSDStudent Class and the 
		executable code to manipulate our HashTable at command
		line.
****************************************************************************/

import java.io.*;

class UCSDStudent extends Base {
        private String name;
        private long studentnum;

	/**
         * UCSDStudent Basic Constructor.
	 * Only passes in the string
         *
         * @param   name        name of the student
         */
	public UCSDStudent( String name ) {
		this.name = new String(name);
		this.studentnum = 0;
	}
	
	/**
         * UCSDStudent Overloaded Constructor (The one we use).
	 * Passes in a name and the student number
         *
         * @param   name	name of the student
	 * @param   stuNum	the student number
	 * 
         */
	public UCSDStudent( String name, long stuNum ) {
		this.name = new String(name);
		this.studentnum = stuNum;
	}  
	
	/**
         * Getter for the student's name.
	 * Returns the string of the name
         *
         * @return  String containing the student's name
         */
	public String getName() {
		return this.name;
	}
	
	/**
         * Getter for a Student number.
	 * Returns the long
         *
         * @return  returns the long containing the student number
         */
	public long getStuNum() {
		return this.studentnum;
	}
	 
	/**
         * Function that compares Students.
	 * Using the equals method of Object class we can compare two student
	 * objects to see if they are the same.
         *
         * @param   object	the object to compare to the one we call on
         * @return  Returns true if the objects are the same, false if not
         */
	public boolean equals (Object object) {   
		Base bbb = (Base) object;
                return name.equals (bbb.getName ());
	}  
	
	/**
         * Checks the alphabetic order of two Bases.
	 * Compares the ASCII characters of the names
         *
         * @param   bbb		is the base to compare to the one we are
	 *			calling on
         * @return  Returns true if the base we call on is alphabetically
	 *	    less than the one we pass in and false if not
         */
	public boolean isLessThan (Base bbb) {  
                return (name.compareTo (bbb.getName ()) < 0) ? true : false;
	}  
	
	/**
         * Displays the contents of a Student in a string
         *
         * @return  Returns a string containing the name and student number
         */
	public String toString () {  
	        return "name: " +this.name+" Studentnum: "+this.studentnum;
	}  
	
	/**
         * Converts a student name to hashcode to be used for other purposes.
	 * We use the hashcode to navigate the Hashtable
	 *
         * @return  the ASCII sum of the name
         */
	public int hashCode () {  
	        int retval = 0;  
	        int index = 0;  
  
	        //Loop adding each ASCII value to a sum
		while (index != this.name.length ()) {  
		      retval += this.name.charAt (index);  
		      index ++;  
		}  
	  
	        return retval;
	}

}

public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
                /* initialize debug states */
                HashTable.setDebugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                HashTable.setDebugOn();
                }

                /* The real start of the code */
                SymTab symtab = new SymTab (5);
                String buffer = null;
                char command;
                long number = 0;

                System.out.print ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = 0;    // reset command each time in loop
                        System.out.print ("Please enter a command:  "
                                + "((i)nsert, (l)ookup, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'i':
                                System.out.print (
                                "Please enter UCSD Student name to insert:  ");
                                buffer = MyLib.getline ();// formatted input

                                System.out.print (
                                        "Please enter UCSD Student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create Student and place in symbol table
                                if(!symtab.insert (
                                        new UCSDStudent (buffer, number))){

                                        System.out.print ("\nFinal Symbol "
                                                        + "Table:\n" + symtab);
                                        System.exit(0);
                                }
                                break;

                        case 'l': {
                                Base found;     // whether found or not

                                System.out.print (
                                "Please enter UCSD Student name to lookup:  ");

                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println ("Student found!!!");
                                        System.out.println (found);
                                }
                                else
                                        System.out.println ("Student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.print (
                                    "The Symbol Table contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }

                System.out.print ("\nFinal Symbol Table:\n" + symtab);
        }
}
