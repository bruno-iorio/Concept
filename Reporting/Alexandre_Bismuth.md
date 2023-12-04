# Alexandre Bismuth Reporting File

Lead for the development of the Kernel implementation, the Data Organisation, as well as the Search Bar. Part of the development of the Text editor.

# Week 1:

Discussed the project as a group and started doing personal research to evaluate the feasability and the structure of all the features I would be working on.

1. Data Organisaion - Started doing research about handling of Data in C++ to avoid using pure SQL. Therefore, I think we will have to use SQLiteCpp, a library which allows us to use SQL within a C++ file.
2. Search bar - Started doing reasearch about implementation of search bars in C++. I will divide the work in different steps : Data Indexing, Search Algorithm Implementation, Integration within the UI, Testing.
3. Kernel Implementation - Brainstormed and researched with Octave the feasability and the potential structure of a kernel which would run code inside our app similarly to a Jupyter Notebook. For now, we are still unsure how we could do this without comprimising the UX as opening a local host is inconvenient.
4. Text Editor - Plan to implement a feature which allows the user to have a text box formatted and highlighted as would be a code in VSCode: Command recognition, Box Creation, Syntax highlighting & code formatting databasing, integration and testing within UI.

# Week 2:

Naturally, I am starting off the project by designing the first essential feature : the database Manager. With Hung, I have installed (and spent consequent time understanding) the SQLiteCpp library, a library which allows us to manage our content files using SQL within a C++ file. To this purpose, I have written functions in a Backend cpp file which allow me to initialize a database of files, create new files, edit them, and delete them. Now, my next step is to organise all of these function in various files and classes for documents and integreated features.
