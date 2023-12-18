# Alexandre Bismuth Reporting File

Part of the Backend Team. Working on the Data Organisation & Storage, the Search bar, the Kernel implementation, and the text editor. Details of each of these features can be found in the Week 1 report. Please note that most of my work is not in this repository, but in the Backend repository.

## Week 1

Discussed the project as a group and started doing personal research to evaluate the feasability and the structure of all the features I would be working on.

1. Data Organisaion - Started doing research about handling of Data in C++ to avoid using pure SQL. Therefore, I think we will have to use SQLiteCpp, a library which allows us to use SQL within a C++ file.
2. Search bar - Started doing reasearch about implementation of search bars in C++. I will divide the work in different steps : Data Indexing, Search Algorithm Implementation, Integration within the UI, Testing.
3. Kernel Implementation - Brainstormed and researched with Octave the feasability and the potential structure of a kernel which would run code inside our app similarly to a Jupyter Notebook. For now, we are still unsure how we could do this without comprimising the UX as opening a local host is inconvenient.
4. Text Editor - Plan to implement a feature which allows the user to have a text box formatted and highlighted as would be a code in VSCode: Command recognition, Box Creation, Syntax highlighting & code formatting databasing, integration and testing within UI.

## Week 2

Naturally, I am starting off the project by designing the first essential feature : the database Manager. With Hung, I have installed (and spent consequent time understanding) the SQLite_orm library, a library which allows us to manage our content files using SQL within a C++ file. To this purpose, I have written functions in a Backend cpp file which allow me to initialize a database of files, create new files, edit them, and delete them. Now, my next step is to organise all of these function in various files and classes for documents and integreated features.

## Week 3

This week, I continued the database implementation. To that end, I have organized every storage in one database file, with many different tables. Given our Frontend feature, I have written a BaseModel class which is a parent class which defines the overall structure of each storage class. For the subclasses (which inherit BaseModel), I have thus designed 5 of them. Note - which stores all of the text files, Folder - which organises the notes, Timer - which sets and stores timers, Focus Time - which stores the time spent working by the user, and Commands - which stores all of the commands that will be usable as shortcuts or to create graphs/images/code boxes...

For next week, my objective is to finalize this database implementation (with the Backend Team), and potentially start working the search bar, as planned in Week 1.

## Week 4

After restrucring the database with Hung to use structs instead of classes, the database should be done. I have constructed 20 tests of our database.hpp file which all build & pass. Then, I investigated the search bar. Thanks to the 'like' function of SQLite_orm which kind of acts as a search bar, all I needed to do what to implement 2 20 lines functions and the trick was done.

For next week, we will make sure that everyone on the front-end can properly integrate and use the database and I will try to work on the text editor, to add a feature where you can have a block which formats text as code.
