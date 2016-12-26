import java.io.*;

public class Main {
        public static void main (String [] args) {
                /* initialize debug states */
                HashTable.setDebugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                HashTable.setDebugOn();
                }
                
                Calculator calc = new Calculator (53);  // Calculator to use

                while (true) {
                        System.out.print
                          ("\nPlease enter an expression to calculate:  ");

                        try {
                                calc.convertInToPost ();
                        }

                        catch (EOFException eof) {
                                break;
                        }

                        System.out.print ("\nThe expression in postfix " +
                                "order is:  " + calc.writePostfix());

                        System.out.println ("\nwhich evaluates to:  "
                                + calc.evaluate ());

                        System.out.print ("\nCalculator is:\n" + calc);
                }
                System.out.print ("\n");
        }
}
