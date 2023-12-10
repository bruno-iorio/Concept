# Alexandre Bismuth Reporting File

Part of the Backend Team. Working on the Data Organisation & Storage, the Search bar, the Kernel implementation, and the text editor. Details of each of these features can be found in the Week 1 report. Please note that most of my work is not in this repository, but in the Backend repository. 

# Week 1:

Discussed the project as a group and started doing personal research to evaluate the feasability and the structure of all the features I would be working on.

1. Data Organisaion - Started doing research about handling of Data in C++ to avoid using pure SQL. Therefore, I think we will have to use SQLiteCpp, a library which allows us to use SQL within a C++ file.
2. Search bar - Started doing reasearch about implementation of search bars in C++. I will divide the work in different steps : Data Indexing, Search Algorithm Implementation, Integration within the UI, Testing.
3. Kernel Implementation - Brainstormed and researched with Octave the feasability and the potential structure of a kernel which would run code inside our app similarly to a Jupyter Notebook. For now, we are still unsure how we could do this without comprimising the UX as opening a local host is inconvenient.
4. Text Editor - Plan to implement a feature which allows the user to have a text box formatted and highlighted as would be a code in VSCode: Command recognition, Box Creation, Syntax highlighting & code formatting databasing, integration and testing within UI.

# Week 2:

Naturally, I am starting off the project by designing the first essential feature : the database Manager. With Hung, I have installed (and spent consequent time understanding) the SQLiteCpp library, a library which allows us to manage our content files using SQL within a C++ file. To this purpose, I have written functions in a Backend cpp file which allow me to initialize a database of files, create new files, edit them, and delete them. Now, my next step is to organise all of these function in various files and classes for documents and integreated features.

# Week 3:

This week, I continued (and almost finished) the database implementation. To that end, I have, as planned, organized every storage in one database file, with many different tables. Given our Frontend feature, I have written a BaseModel class which is a parent class which defines the overall structure of each storage class. For the subclasses (which inherit BaseModel), I have thus designed 5 of them. Note - which is the class to store all of the text files, Folder - which allows us to organise the notes, Timer - which allows the user to set and store timers, Focus Time - which stores the time spent working by the user, and Commands - which stores all of the commands (and their descriptions) that will be usable in the notes as shortcuts or to create graphs/images/code boxes...

For next week, my objective is to finalize this database implementation (as I still need to check everything with the Backend Team), and to start working on two other things. The search bar (as planned in Week 1), and start investating the account setup (new necessity to store accounts credentials and to be able to store & restore data online).