Maxime Despréaux Weekly Update


    Week 1: 
        After disscussing in lecture about how we wanted to tackle this project and with what tools, we chose to create a WebApp with Qt's WebAssembly, Emscripten and CMake.
        For now, the structure is very generic as we thought having a basis for everyone to be able to work on at the same time (and not have to wait for certain things to be 
        added until they could implement there part). 




    Week 2: 
        This week, we finished setting up the environment on each local machine so that everyone can get to work. The UI is coming along with a header at the top. For now, it
        isn't functional as we still need to add the functions and classes to link everything. That will be the goal for next week for the already existing UI and main
        functionalities, as well as keep improving the UI. Also just saw a potential issue in builds for windows, linux or macOS, will ask in lecture about version compatibility.

    Week 3:
        This week, we got further into the UI and we're implementing the text editor into the app. I'll focus on UI handling
        in the following days. The UI uses qml and our choice of an Executable App instead of a WebApp let's us not use 
        Qt Design (Screen01.ui.qml was deleted and everything merged into main.qml). We also settled on using a View/Edit
        feature for the Text Editor, the 2nd column will display and clicking the edit button should open a new window to 
        edit with the Text Editor.

    Week 4: 
        The Text editor is pretty well-implemented already and we can see progress in the UI. We have been running into quite a bit of trouble with Windows and are starting to            consider switching to Linux on Ubuntu. For now, the database is finished but requires some polishment, we're using sqliteorm. The timer is now implemented but still               doesn't run. Once we'll get it to run, we considered adding statistics and data tracking for performance in productivity.

    Week 5: 
        The UI was redesigned and retouched quite a lot during the vacation introducing a more eye pleasing dark-theme. There' also a side task bar for space management.
        The database was also changed to qxorm, which created a lot of errors for my computer and could't build. I'm dedicating a lot of my work to getting Qt6 running our               project on Ubuntu.
