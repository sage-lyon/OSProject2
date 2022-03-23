Sage Lyon & Matthew Sylvester 3/23/2022
Group Project 2


### HOW TO COMPILE AND RUN ###
1. Unzip folder into a folder.
2. open a terminal, navigate to the folder where the contents of the zip were placed.
3. run "make" within the terminal.
4. Now compiled, you can run the project by typing "./project2 <buffer size> <number of producers> <number of consumers>"

example: ./project2 10 5 3



This zip contains 4 files.

1. The first file is the makefile
--> This is used to compile the assignment via the "make" command.

2. The second is prod_cons_MT.h
--> This is the header file for the project and contains the structure declaration for the monitor, as well as the declarations of other functions.

3. The third file is prod_cons_MT.c
--> This file contains the definitions for the functions, consumer and producer, that the threads are initialized to from the main.c file. 
    It also contains the function definitions for the monitor_destroy function, and the monitor_init function to initialize the monitor struct.

4. The fourth file is main.c
--> This file contains the main() function call, and is responsible for taking user inputs from the console, and then creating the resulting monitor, and 
    threads required.


