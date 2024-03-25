# project_examples

This repository contains a set of projects carried out during my learning of C++ and Python. In addition, the codes of both the solved exercises and other short projects are available in the cplusplus_lessons and python_lessons repositories.

C++:

1. Mathematical parser: this application was programmed to solve a list of mathematical operations. From the application, a text file containing the list of operations is accessed. Each operation is solved and the solutions are saved in another text file. The complexity of operations is increased by combining the elementary operations of the application (e.g., 57.5 * pi + pow(2,3) - 5! + var1 - sqrt(16)). The defined operations are: +, -, *, /, factorial (!), exponentiation, square root, integers -to operate on ints only-, and help. In addition, in this application both variables and constants can be defined. Operations are parsed using recursion and OOP (the application follows the precedence established in C++). The operations can also be solved through the graphical interface of the calculator. Examples of the calculator's operation are presented after the description of the projects.

    - FLTK was installed following the instructions of README.OSX.txt 
    - Build Command: g++ -w -Wall -std=c++17 GUI/Graph.cpp GUI/Window.cpp GUI/GUI.cpp GUI/Simple_window.cpp EX169_calculator_to.cpp `fltk-config --ldflags --use-images` -o EX169_calculator_to

2. Two STL containers: the simplified versions of "vector" and "list" were developed as practice. For these versions, the iterators and the functions size, capacity, reserve, push_back, resize, begin, end, insert and erase were implemented. The main language resources or techniques used for the development were the templates, RAII, and the functions for the dynamic management of memory (allocate, deallocate, construct and destroy).

3. A simple text editor: this program is based on the STL containers "vector" and "list". By means of the linked list, the lines of the document are managed. Containers functionalities -such as iterators, back, size, push_back, begin, end, etc.- were used to develop the editor functions. These functions are: print_document, erase_line, match, find_txt, find_replace, char_number, words_whitespace, among others.

4. This LRU Cache is a key/value pair data store that allows for random access and deletion of data items via the key. The cache has a predetermined capacity and once that is exceeded, stale (least recently used) data items are evicted. The term "used” is defined as new data added or existing data that is accessed. The type of the key and value is arbitrary, but well known at compile time and the LRU Cache is type homogenous once created. The key type is guaranteed to be less-than and equality comparable. Both the key and the value type are guaranteed to be copyable and movable. Upon creating the LRU cache, the desired capacity is specified. It is possible to clear the cache at any time. It is possible to get the cache capacity and item count at any time. Upon process termination, the cache is free to discard its contents.

Tech stack: C++ 17 and FLTK 1.3.8 (It was used for developing the calculator GUI.)


Python:

- Data-Access Layer: in this project, a Data-Access Layer (DAL) was implemented using Python. This DAL was used to access a database managed through PostgreSQL. The information in the database was contained in a table. A set of classes was programmed to interact with this table through CRUD statements.

- Customer management system: this system was implemented by combining HTML templates, a web browser and the tools of Django. An alternative version of this project was programmed using Flask. The information of the customers was contained in a table managed through PostgreSQL and CRUD statements.

Tech stack: Python 3.9.6, PostgreSQL 15, Django 4.2.4 and Flask 2.3.3.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

Mathematical parser

The project files are saved in the "/Calculator" directory. To run the app, it is necessary to double click on the binary file EX169_calculator_to. The main components of the app's GUI are the edit box "Operations" and the buttons "Start" and "Quit". The operation must be entered in the edit box, then the button "Start" must be pressed to solve it. The calculator is finished if the button "Quit" is pressed.

- Enter 'to results; from operations; end; end;' to run a list of commands from the file named "operations" and save the results to the file called "results". The double 'end;' is required to close the files. The files must be attached in the calculator's containing folder.

<img width="1728" alt="Captura de pantalla 2023-05-02 a la(s) 10 34 36 p m" src="https://user-images.githubusercontent.com/116608938/235828304-eed6a115-b789-4066-8cf2-3e8e21eb256d.png">

- Use the 'to' command to save a list of results to the file "results". Example: 'to results; 4+5; 6*8; end; end;'. The first 'end;' finishes the instructions and the other one closes the file.

<img width="1728" alt="Captura de pantalla 2023-05-02 a la(s) 10 56 27 p m" src="https://user-images.githubusercontent.com/116608938/235830268-51f3114e-f688-4b3c-b893-fe22139eb79f.png">

- Use the 'from' command to load a list of operations from the "operations" file. Example: 'from operations; end;'.

<img width="1728" alt="Captura de pantalla 2023-05-02 a la(s) 11 01 53 p m" src="https://user-images.githubusercontent.com/116608938/235830745-80197d86-ce7a-45cf-8c07-d0f14bd25487.png">

- Use the edit box to enter a list of operations. Example: '4/6; # var1 = 6; const pi = 3.1416; 5! + var1 - (2/pi); end;'.

<img width="1728" alt="Captura de pantalla 2023-05-02 a la(s) 11 09 54 p m" src="https://user-images.githubusercontent.com/116608938/235831447-25399482-f4d2-49fe-8125-fe23891f178c.png">

