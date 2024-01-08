--------------------------WEEK 1--------------------------

We have split the project into main parts - representing its main features and functionalities. 
Everyone is assigned one or more of these parts - we are aiming to create a functional base by everyone working at the same time and then merge together into working on the same target. 

For the moment, we are developing the following:
- Databases and Handling - how the input is stored into the database: Peter, Alex and Marta 
- Text Editor: Bruno, Sacha 
- Search and Organization - Keeping track of the contents of the database and return it upon user search: Peter
- Timer and Focus Tracking - Implement a timer (start, stop, pause etc) and predict possible outcomes by the already existing data: Klaara
- User Interface: Andreea and Milana
- User Input Handling: Raluca and Max
- Feedback System - From already existing data create daily, weekly or on request feedbacks: Max 
- Sync System: Hung and Nguyen Vu
- Kernel: Alex and Octave
- To Do Lists - basic Notion feature: Hung and Nguyen Vu

We are defining classes - to have a better structural view of our project - and possible templates.
We plan on starting actual coding in week 2.


--------------------------WEEK 2--------------------------

At Hung's suggestion, we have restructured the team a bit, we have mege some parts into just frontend, backend and infrastructure.

Max and I have managed to install, activate and run the project and its required tools on our teammates laptops. This also helped us understand how the components work together and which files build what.

Personally, I have been working on analysing classes (hierarchy) and templates can help me implement the help section, how they'll connect with the other parts of the app. I plan on implementing this into code the next week and also tie it to the already existing ui. 

--------------------------WEEK 3--------------------------

Backend is doing nice progress, databases are being implemented and properly handled. The ui team is solving the bugs across devices.
We had the problem of a Qt version change - some libraries din not build properly, so we switched back to a callable app (no web anymore).
We had to reconfigure some laptops, but with the already gained experience it all went smoothly.

We had to rethink our texteditor and now we have a second header into the main collumn and a button that triggers a new window of texteditor.

Personal work:
 - I have implemented a way for the contents to fit into each screen (adapt by the width and height of each) - contribution to Screen01.ui.qml (Now main.qml)
 - Reordered Help and Search button (in ui) in order to implement the Help Section + rearranged the buttons. (main.qml)

 - Tried implementing the Help Section as a dropdown in qml but could not align the items. 
 Documented options in cpp and understood the scheme for that. 
 Will implement it all in cpp - Week 4 (with few additions in qml).
 

--------------------------WEEK 4--------------------------

Backend has been implemented into the Concept Project (it's been initially developed individually).
We have observed and analysed problems for the Windows users in the team. Solutions to these issues were found and the project follows its normal course. 

The timer is currently being implemented, together with its features. To-do lists are also being put into place and will be soon functional + their qml tools.

Personal work:
- Implemented the dropdown menu, alligned, options and functional
- (+ Break Week 1 ) Implemented the first option in the dropdown menu

