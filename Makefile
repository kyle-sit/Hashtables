#This is the Makefile to use for Homework Assignment #6
# To use, at the prompt, type:
#
#       make Calc               # This will make executable calc
# or
#       make Driver             # This will make executable driver
# or
#       make clean              # This will safely remove old stuff

DIR=$(HOME)/../public/hw6

all:	Calc1 Driver1 Calc2 Driver2

Calc1:	Calc.o Decin.o Hash.o Namein.o Main.o List.o Stack.o
	g++ -o Calc1 -g Calc.o Namein.o Decin.o Hash.o List.o Main.o Stack.o

Calc2:	Main.class
	echo 'java Main $$*' > Calc2
	chmod ug+rx Calc2

Calc.o:	Base.h Calc.c Calc.h Decin.h Hash.h List.h Stack.h SymTab.h
	g++ -g -c Calc.c

Calculator.class:	Calculator.java
	javac -g Calculator.java

Driver:		Driver1 Driver2

Driver1:	Driver.o Hash.o
	g++ -o Driver1 -g Driver.o Hash.o

Driver.o:	Base.h Driver.c Hash.h SymTab.h
	g++ -g -c Driver.c

Driver2:	Driver.class
	echo 'java Driver $$*' > Driver2
	chmod ug+rx Driver2

Driver.class:	Base.java Driver.java HashTable.java MyLib.java SymTab.java
	javac -g Driver.java

Decin.o:	Decin.c Decin.h
	g++ -g -c Decin.c

Hash.o:	Base.h Hash.c Hash.h SymTab.h
	g++ -g -c Hash.c

List.o:	Base.h List.c List.h
	g++ -g -c List.c

Main.o:	Base.h Main.c Calc.h Hash.h List.h Stack.h SymTab.h
	g++ -g -c Main.c

Main.class:	Base.java Calculator.java HashTable.java List.java Main.java \
		MyLib.java Stack.java SymTab.java
	javac -g Main.java

Namein.o:	Namein.h Namein.c
	g++ -g -c Namein.c

Stack.o:	Base.h List.h Stack.c Stack.h
	g++ -g -c Stack.c

valgrind_Driver: Driver1
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Driver1 $(DEBUG)

valgrind_Calc: Calc1
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Calc1 $(DEBUG)

clean:
	rm -f *.o Driver1 Calc1 Driver2 Calc2 core *.class

new:
	make clean
	make

backup:	*.[ch] *.java Makefile
	cp -p *.[ch] *.java Makefile backup

directories:
	mkdir $(HOME)/hw6
	mkdir $(HOME)/hw6/backup

install:
	cp -p $(DIR)/Makefile \
		$(DIR)/Base.h \
		$(DIR)/Calc.c \
		$(DIR)/Calc.h \
		$(DIR)/Decin.h \
		$(DIR)/Decin.c \
		$(DIR)/Driver.c.empty \
		$(DIR)/Hash.c.empty \
		$(DIR)/Hash.h \
		$(DIR)/List.c \
		$(DIR)/List.h \
		$(DIR)/Main.c \
		$(DIR)/Namein.c \
		$(DIR)/Namein.h \
		$(DIR)/Stack.c \
		$(DIR)/Stack.h \
		$(DIR)/SymTab.h \
		$(DIR)/Calculator.java \
		$(DIR)/Base.java \
		$(DIR)/Driver.java.empty \
		$(DIR)/HashTable.java.empty \
		$(DIR)/Main.java \
		$(DIR)/MyLib.java \
		$(DIR)/List.java \
		$(DIR)/Stack.java \
		$(DIR)/SymTab.java \
		$(HOME)/hw6

public:
	make new

	# remove .o files to prepare for java executable creation
	rm -f *.o

	# produce java executables
	gcj -c *.java
	gcj -o Driver2 --main=Driver Base.o Driver.o List.o MyLib.o \
		Stack.o SymTab.o HashTable.o
	gcj -o Calc2 --main=Main Base.o Calculator.o HashTable.o List.o \
		Main.o MyLib.o Stack.o SymTab.o
	
	# done with .o files
	rm -f *.o

	# lock public directory
	chmod 700 $(DIR)

	# copy all files to directory
	cp -p Makefile *.c *.h *.java *.empty Calc1 Driver1 Calc2 Driver2 $(DIR)
	#
	# copy html files into public_html/hw6/
	cp -p *html $(HOME)/public_html/hw6/
	 
	# strip executables of debugging information
	strip $(DIR)/Driver1 $(DIR)/Calc1 $(DIR)/Driver2 $(DIR)/Calc2

	# remove solution files from public directory
	rm -f $(DIR)/Hash.c
	rm -f $(DIR)/Driver.c
	rm -f $(DIR)/HashTable.java
	rm -f $(DIR)/Driver.java

	# give all permissions to other users, take away some permissions later
	chmod o-rwx $(DIR)/*

	# set correct permissions on executables
	chmod go=x $(DIR)/Calc1 $(DIR)/Driver1 $(DIR)/Calc2 $(DIR)/Driver2

	# set correct permissions on source files
	chmod go+r $(DIR)/Makefile \
		$(DIR)/Base.h \
		$(DIR)/Calc.h \
		$(DIR)/Decin.h \
		$(DIR)/Decin.c \
		$(DIR)/Driver.c.empty \
		$(DIR)/Hash.c.empty \
		$(DIR)/Hash.h \
		$(DIR)/List.h \
		$(DIR)/Main.c \
		$(DIR)/Namein.c \
		$(DIR)/Namein.h \
		$(DIR)/Stack.c \
		$(DIR)/Stack.h \
		$(DIR)/SymTab.h \
		$(DIR)/Base.java \
		$(DIR)/Driver.java.empty \
		$(DIR)/HashTable.java.empty \
		$(DIR)/Main.java \
		$(DIR)/Makefile \
		$(DIR)/Stack.java \
		$(DIR)/SymTab.java
	chmod go+r $(DIR)/Calculator.java
	chmod go+r $(DIR)/MyLib.java
	#chmod go+r $(DIR)/List.java
	chmod go+r $(DIR)/Calc.c
	#chmod go+r $(DIR)/List.c

        # move html files to public_html directory
	rm -r $(HOME)/public_html/hw6/
	mkdir $(HOME)/public_html/hw6
	cp -p *html $(HOME)/public_html/hw6
	chmod 644 $(HOME)/public_html/hw6/*html
	chmod 755 $(HOME)/public_html/hw6/

	#Unlock public directory
	chmod 755 $(DIR)
	# copy solution to Tracker's account
	#scp -p Makefile *.c *.h *.java cs12xzz@ieng6-202.ucsd.edu:~/hw6
	rm -f *.o *.class core
