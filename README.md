# project_examples

This repository contains a set of projects carried out during my learning of C++ and Python. In addition, the codes of both the solved exercises and other short projects are available in the cplusplus_lessons and python_lessons repositories.

C++:

1. Calculator: this application was programmed to solve a list of mathematical operations. From the application, a text file containing the list of operations is accessed. Each operation is solved and the solutions are saved in another text file. The complexity of operations is increased by combining the elementary operations of the application (e.g., 57.5 * pi + pow(2,3) - 5! + var1 - sqrt(16)). The defined operations are: +, -, *, /, factorial (!), exponentiation, square root, integers -to operate on ints only-, and help. In addition, in this application both variables and constants can be defined. Operations are parsed using recursion and OOP (the application follows the precedence established in C++). The operations can also be solved through the graphical interface of the calculator. Examples of the calculator's operation are presented after the description of the projects.

    - FLTK was installed following the instructions of README.OSX.txt 
    - Command used: g++ -w -Wall -std=c++17 GUI/Graph.cpp GUI/Window.cpp GUI/GUI.cpp GUI/Simple_window.cpp EX169_calculator_to.cpp `fltk-config --ldflags --use-images` -o EX169_calculator_to

2. Vector Template (Buscar proyecto y describirlo): 


Tech stack: C++ 17 and FLTK 1.3.8 (It was used for developing the calculator GUI.)


Python:

1. Data-Access Layer: in this project, a Data-Access Layer (DAL) was implemented using Python. This DAL was used to access a database managed through PostgreSQL. The information in the database was contained in a table. A set of classes was programmed to interact with this table through CRUD statements. In addition, in this set were included the classes to manage both the connection pool and the user's instructions provided from a terminal.


-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

Calculator

The project files are saved in the "/Calculator" directory. To run the calculator, it is necessary to double click on the binary file EX169_calculator_to. The main components of the calculator's GUI are the edit box "Operations" and the buttons "Start" and "Quit". The operation must be entered in the edit box, then the button "Start" must be pressed to solve it. The calculator is finished if the button "Quit" is pressed.

- Enter 'to results; from operations; end; end;' to run a list of commands from the file named "operations" and save the results to the file called "results". The double 'end;' is required to close the files. The files must be attached in the calculator's containing folder.

- Use the 'to' command to save a list of results to the file "results". Example: 'to results; 4+5; 6*8; end; end;'. The first 'end;' finishes the instructions and the other one closes the file.

- Use the 'from' command to load a list of operations from the "operations" file. Example: 'from operations; end;'.

- Use the edit box to enter a list of operations. Example: '4/6; # var1 = 6; const pi = 3.1416; 5! + var1 - (2/pi); end;'.

