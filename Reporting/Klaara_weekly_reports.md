Week 1:
We met with the team to discuss our roles. I planned out what kind of features I could be responsible for implementing and started searching for pre-existing simple implementations of these features.
- timer: set focus time, collect data for total duration of focus time, implement pause/quit/continue
- to-do list: add and complete tasks
- focus tracking: set goals for day/week/month, follow progress, collect stats (time, words typed, tasks completed)
- feedback system: gather and display statistics about progression of goals/comparison to previous days/weeks
- trend prediction: draw predicitions for productivity in the future based on exisiting data

Created framework for a class of Timer objects to start the implementation of the timer.

Week 2:
Medically excused absence from classes and coursework.

Week 3:
Defined more functions for the timer. Researched and used the std::chrono library to simplify how time is tracked and stored by class timer items.

Week 4:
Discussed and redesigned the storing of timer-related data with Alex. Realized in the TD (after discussing with a TA and my team members) that my implementation of the timer was not compatible with our app, and started rewriting it. My functions involved while loops that would prohibit the rest of the app fron responding to user interaction.

Vacatiom:

Week 5:

Returned to work with my timer, tried to connect my Timer class (in which I had defined a exhaustive set of functionalities) directly to qml. After working on it for some time realized it wasn't plausible. (Later realized it was best to create a new class inheriting from QObject that then calls said Timer class).

In the mean time, created a strictly visual timer in qml (does not track/store time spent). (branch qml_timer)

Also pushed a c++ version of the timer that was improved but not connected to the ui (experimented with Q_objects). This version was debugged by Marta and Andreea. (branch cpp_timer)

Week 6:

Spent a whole day trying to pull the lastest version of our project to my laptop, integrate my cpp class files to it, and run it without crashing.
Finally connected a simple implementation of the timer to the UI (branch Klaara_Timer2.0)
- start, stop, break, continue button functionalities as expected
- set focus period: define how long u want to work -> starts a count down timer
- no focus period set -> starts a count up timer from zero
- time tracking in theory but I later found bugs

Week 7:
Added features to timer: (branch Klaara_Timer2.0)
- tracks how long the timer has been running and how long youve been on break
- User can choose break length from dropdown menu (or choose 'until continued') and the timer display will be replaced by a break timer
- the focus timer automatically continues when break timer ends / is ended by the user.

